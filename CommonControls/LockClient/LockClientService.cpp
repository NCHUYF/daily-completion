#include "stdafx.h"
#include "LockClientService.h"
#include "InbreakProtect.h"
#include "LicenceAccess.h"
#include "LockClientDialog.h"

IMPL_SINGLE_CLASS(CLockClientService)
UINT_PTR CLockClientService::s_nCheckTm = 0; ///< �������ʱ��
int CLockClientService::s_nLockInitStatus = 0; ///< ����ʼ��״̬
bool CLockClientService::_bNetLogin = false;

CLockClientService::CLockClientService()
{
	InitLockDetect();
}

CLockClientService::~CLockClientService()
{
	UninitLockDetect();
}

bool CLockClientService::CheckLicence(int nMode)
{
	VMProtectBegin("Lic5");

#ifndef USE_LOCK//δʹ�����ж�
	return true;	// �����������ʱ��ֱ�ӷ���
#endif

	CLicenceAccess* pLicAccess = CLicenceAccess::GetInstance();
	if (pLicAccess == NULL)
		return false;

	SupportLicMap licMap = pLicAccess->GetAppSupperLicenceMap();
	SupportLicMap::iterator iter = licMap.find(nMode);
	if (iter == licMap.end())
		return false;

	return pLicAccess->CheckFunctionLicence(nMode);

	VMProtectEnd();
}

void CLockClientService::InitLockDetect()
{
	VMProtectBegin("CommonTools");

#ifdef USE_LOCK//δʹ�����ж�
	// ����ʼ��
	void* pVoid = NULL;
	LockInitial(pVoid);

	// ��������ⶨʱ��
	LockFirst();
	//s_nCheckTm = SetTimer(NULL, 0, 500, LockDetectProc);

#endif

	VMProtectEnd();
}

UINT CLockClientService::LockInitial(LPVOID lpParam)
{
	VMProtectBegin("LockInit");

	CLicenceAccess* pLicAccess = CLicenceAccess::GetInstance();
	bool bResult = pLicAccess->CreateLock();

	// ������ʧ��
	if (!bResult)
	{
		s_nLockInitStatus = -1;
		pLicAccess->ReleaseLock();
		toolkit::commkit::CLog::WriteLog(L"���ؼ�����ʧ��-" + pLicAccess->GetLastError());
	}
	else
	{
		s_nLockInitStatus = 1;
	}

	VMProtectEnd();

	return 0;
}

void CLockClientService::LockFirst()
{
	VMProtectBegin("LockDetect");

	if (1 != s_nLockInitStatus)
	{
		return;
	}

	CLicenceAccess* pLicAccess = CLicenceAccess::GetInstance();
	try
	{
		do
		{
			bool bResult = false;

			// ��鵥������������
			if (!_bNetLogin)
			{
				bResult = pLicAccess->CheckNatLock();
			}
			else
			{
				bResult = pLicAccess->CheckNetLock();

				// ������������½
				_bNetLogin = bResult;
			}

			// �ҵ����֤
			if (bResult)
			{
				s_nCheckTm = SetTimer(NULL, 0, 20 * 1000, LockDetectProc);
				return;
			}

#ifdef USE_LOCK//δʹ�����ж�
			// ������Լ��(��ע�͵�����Realease���²ſ�ʹ��)
			//CInbreakProtect apiProtect;
			//if (apiProtect.DebugDetection(1) == 0)
			//{
			//	CLog::LogError(L"��⵽�������쳣��");
			//	exit(0);
			//}
#endif

			// û�п������֤��ʾ��ʾ��Ϣ
			INIT_RESHANDLE();
			CWnd* pMainWnd = CWnd::GetActiveWindow();
			CNoFoundLienceDlg dlg(pMainWnd);
			dlg.DoModal();

			// ������ʾ�������н�һ������
			ENotFoundMode noFoundMode = dlg.GetNoFoundMode();
			if (noFoundMode == eShowLic)
			{
				// ��ʾ���֤����(ע����)
				CServerLicenceMgrDlg dlgServerLicenceMgrDlg(pMainWnd);
				dlgServerLicenceMgrDlg.DoModal();
			}
			else if (noFoundMode == eNetLogin)
			{
				if (dlg.IsManualLoginIn())
				{
					CNetLoginDlg LoginDlg(pLicAccess);
					LoginDlg.DoModal();
					if (LoginDlg.LoginSucceed() != TRUE)
					{
						continue;
					}
					_bNetLogin = true;
					s_nCheckTm = SetTimer(NULL, 0, 5 * 1000, LockDetectProc);
					return;
				}
				else
				{
					// �����¼�����м��
					if (pLicAccess->AppNetLogin())
					{
						_bNetLogin = true;
						s_nCheckTm = SetTimer(NULL, 0, 20 * 1000, LockDetectProc);
						return;
					}
					else
					{
						toolkit::commkit::CLog::WriteLog(L"�����½ʧ��-" + pLicAccess->GetLastError());
						::MessageBox(GetActiveWindow(), pLicAccess->GetLastError(), L"����", MB_OK | MB_ICONINFORMATION);
					}
				}

			}
			else if (noFoundMode == eQuitLock)
			{
				exit(1);
				return;
			}
		} while (true);
	}
	catch (_com_error& er)
	{
		CString strMsg;
		strMsg.Format(L"����������쳣��������:%d", er.Error());
		::MessageBox(GetActiveWindow(), strMsg, L"����", MB_OK | MB_ICONINFORMATION);
	}
	catch (...)
	{
		CString strMsg = L"����������쳣��δ֪����!";
		::MessageBox(GetActiveWindow(), strMsg, L"����", MB_OK | MB_ICONINFORMATION);
	}
	VMProtectEnd();
}

void CALLBACK CLockClientService::LockDetectProc(HWND, UINT, UINT_PTR, DWORD)
{
	VMProtectBegin("LockDetect");

	// �����ڳ�ʼ��
	if (0 == s_nLockInitStatus)
	{
		// 30��δ��ʼ���������Ϊ��ȷ����
		static int nInitCount = 0;
		if (++nInitCount > 20 * 30)
		{
			KillTimer(NULL, s_nCheckTm);
		}
		return;
	}
	// ����ʼ������
	else if (-1 == s_nLockInitStatus)
	{
		KillTimer(NULL, s_nCheckTm);
		return;
	}

	// ��ͣ��ʱ��
	KillTimer(NULL, s_nCheckTm);

	CLicenceAccess* pLicAccess = CLicenceAccess::GetInstance();
	try
	{
		do
		{
			bool bResult = false;

			// ��鵥������������
			if (!_bNetLogin)
			{
				bResult = pLicAccess->CheckNatLock();
			}
			else
			{
				bResult = pLicAccess->CheckNetLock();

				// ������������½
				_bNetLogin = bResult;
			}

			// �ҵ����֤
			if (bResult)
			{
				s_nCheckTm = SetTimer(NULL, 0, 20 * 1000, LockDetectProc);
				return;
			}

#ifdef USE_LOCK//δʹ�����ж�
			// ������Լ��(��ע�͵�����Realease���²ſ�ʹ��)
			//CInbreakProtect apiProtect;
			//if (apiProtect.DebugDetection(1) == 0)
			//{
			//	CLog::LogError(L"��⵽�������쳣��");
			//	exit(0);
			//}
#endif

			// û�п������֤��ʾ��ʾ��Ϣ
			INIT_RESHANDLE();
			CWnd* pMainWnd = CWnd::GetActiveWindow();
			CNoFoundLienceDlg dlg(pMainWnd);
			dlg.DoModal();

			// ������ʾ�������н�һ������
			ENotFoundMode noFoundMode = dlg.GetNoFoundMode();
			if (noFoundMode == eShowLic)
			{
				// ��ʾ���֤����(ע����)
				CServerLicenceMgrDlg dlgServerLicenceMgrDlg(pMainWnd);
				dlgServerLicenceMgrDlg.DoModal();
			}
			else if (noFoundMode == eNetLogin)
			{
				if (dlg.IsManualLoginIn())
				{
					CNetLoginDlg LoginDlg(pLicAccess);
					LoginDlg.DoModal();
					if (LoginDlg.LoginSucceed() != TRUE)
					{
						continue;
					}
					_bNetLogin = true;
					s_nCheckTm = SetTimer(NULL, 0, 5 * 1000, LockDetectProc);
					return;
				}
				else
				{
					// �����¼�����м��
					if (pLicAccess->AppNetLogin())
					{
						_bNetLogin = true;
						s_nCheckTm = SetTimer(NULL, 0, 20 * 1000, LockDetectProc);
						return;
					}
					else
					{
						toolkit::commkit::CLog::WriteLog(L"�����½ʧ��-" + pLicAccess->GetLastError());
						::MessageBox(GetActiveWindow(), pLicAccess->GetLastError(), L"����", MB_OK | MB_ICONINFORMATION);
					}
				}

			}
			else if (noFoundMode == eQuitLock)
			{
				KillTimer(NULL, s_nCheckTm);

				// ֪ͨ����ر�
				// ::PostMessage(d3s::platform::frame::CFrameManager::GetMainFrame()->GetMainWindow()->m_hWnd, WM_CLOSE, (WPARAM)0, (LPARAM)0);
				exit(1);
				return;
			}

		} while (true);
	}
	catch (_com_error& er)
	{
		KillTimer(NULL, s_nCheckTm);
		CString strMsg;
		strMsg.Format(L"����������쳣��������:%d", er.Error());
		::MessageBox(GetActiveWindow(), strMsg, L"����", MB_OK | MB_ICONINFORMATION);
	}
	catch (...)
	{
		KillTimer(NULL, s_nCheckTm);
		CString strMsg = L"����������쳣��δ֪����!";
		::MessageBox(GetActiveWindow(), strMsg, L"����", MB_OK | MB_ICONINFORMATION);
	}

	VMProtectEnd();
}

void CLockClientService::UninitLockDetect()
{
	VMProtectBegin("UninitLock");

	// �Ƴ��������
	//s_instanceMapping.Unmap();

#ifdef USE_LOCK//δʹ�����ж�

	// �ر�����ⶨʱ��
	::KillTimer(NULL, s_nCheckTm);

	// �ͷ����ؼ�
	CLicenceAccess::GetInstance()->ReleaseLock();

	CLicenceAccess::ReleaseInstance();
#endif

	VMProtectEnd();
}

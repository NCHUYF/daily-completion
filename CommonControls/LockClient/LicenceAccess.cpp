#include "stdAfx.h"
#include <comdef.h>
#include "LicenceCtx.h"
#include "LicenceAccess.h"

CString GetModulePath()
{
	TCHAR AppPath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, AppPath, MAX_PATH);

	// ȥ��������
	TCHAR *pSlash = _tcsrchr(AppPath, _T('\\'));
	pSlash++;
	*pSlash = _T('\0');

	return AppPath;
}

// ������
CLicenceAccess* CLicenceAccess::s_pLicAccess = NULL;

// ���庯��com�����ӿ�
typedef BOOL(WINAPI* BOOWAYPCO)(LPVOID pOuterHandle, LPVOID pRiidHandle, void** ppvObject);

IUnknown* CreateLockObject(UUID uuidof)
{
#ifdef _WIN64
	CString strLockFile = CPathConfig::GetModulePath() + L"\\LockClientServiced64.dll";
#else
	CString strLockFile = CPathConfig::GetModulePath() + L"\\LockClientServiced64.dll";
#endif

	// �����������dll
	if (!CFileToolkit::FileExist(strLockFile))
	{
		exit(1);
		return NULL;
	}

	HMODULE hLockModule = LoadLibrary(strLockFile);
	if (NULL == hLockModule)
		return NULL;

	BOOWAYPCO boowayPco = (BOOWAYPCO)GetProcAddress(hLockModule, "BOOWAY_PCO");
	if (NULL == boowayPco)
		return NULL;

	IUnknown *pUnknow = NULL;
	if (boowayPco(NULL, (LPVOID)&uuidof, (void**)&pUnknow) != S_OK || pUnknow == NULL)
	{
		return NULL;
	}

	pUnknow->AddRef();
	return pUnknow;
}

CLicenceAccess* CLicenceAccess::GetInstance()
{
	if (NULL == s_pLicAccess)
	{
		s_pLicAccess = new CLicenceAccess();
	}

	return s_pLicAccess;
}

void CLicenceAccess::ReleaseInstance()
{
	if (NULL != s_pLicAccess)
	{
		delete s_pLicAccess;
		s_pLicAccess = NULL;
	}
}

bool CLicenceAccess::CreateLock()
{
	_pNetLock = CreateLockObject(__uuidof(BooLockClientManager));
	_pNatLock = CreateLockObject(__uuidof(BooLockClientManager));

	if (!_pNatLock)
	{
		_strLastError = L"������ʵ��ʧ�ܣ�";
		return false;
	}

#if 1
	// �°������
	try
	{
		if (S_OK != _pNatLock->NewS5NativeService(10000))
		{
			_strLastError = L"����������ʧ�ܣ�";
			return false;
		}
	}
	catch (_com_error& e)
	{
		_strLastError = (LPCTSTR)e.Description();
		return false;
	}
	catch (...)
	{
		return false;
	}
#else
	try
	{
		if (S_OK != _pNatLock->NewNativeService(10000))
		{
			_strLastError = L"����������ʧ�ܣ�";
			return false;
		}
	}
	catch (_com_error& e)
	{
		_strLastError = (LPCTSTR)e.Description();
		return false;
	}
	
#endif

	return true;
}

void CLicenceAccess::ReleaseLock()
{
	if (NULL != _pNetLock)
	{
		_pNetLock->FreeService();
		_pNetLock.Release();
		_pNetLock = NULL;
	}

	if (NULL != _pNatLock)
	{
		_pNatLock->FreeService();
		_pNatLock.Release();
		_pNatLock = NULL;
	}
}

CLicenceAccess::CLicenceAccess()
{
	_bNetLogin = false;
	_nLockLicMode = LOCK_LIC_MASTER;
}

void CLicenceAccess::SetLockLicMode(int nMode)
{
	_nLockLicMode = nMode;
}

int CLicenceAccess::GetLockLicMode()
{
	return _nLockLicMode;
}

bool CLicenceAccess::CheckFunctionLicence(int nLockLicMode)
{
	CString strLic = GetSupportLicenceByMode(nLockLicMode);
	if (strLic.IsEmpty())
		return false;

	// �����������ü���
	if (_bNetLogin)
		return CheckLicence(_pNetLock, strLic, false, false);
	else
		return CheckLicence(_pNatLock, strLic, false, true);
}

CString CLicenceAccess::GetSupportLicenceByMode(int nMode)
{
	VMProtectBegin("Lic2");
	SupportLicMap licMap = GetAppSupperLicenceMap();

	if (!(nMode & _nLockLicMode))
		return L"";

	SupportLicMap::iterator iter = licMap.find(nMode);
	if (iter == licMap.end())
		return L"";

	return iter->second;
	VMProtectEnd();
}

SupportLicMap CLicenceAccess::GetAppSupperLicenceMap()
{
	VMProtectBegin("Lic6");
	SupportLicMap licMap;
	licMap[LOCK_LIC_MASTER] = L"�����άʩ��ģ��2021";

	return licMap;
	VMProtectEnd();
}

bool CLicenceAccess::CheckNatLock()
{
	_strLastError = L"";
	return CheckLicence(_pNatLock, L"", false, true);
}

bool CLicenceAccess::CheckNetLock()
{
	_strLastError = L"";
	return CheckLicence(_pNetLock, L"", false, false);
}

void GetNetLockInfo(CString& strServer, CString& strAccount, CString& strPassword)
{
	CString strCfg = CLockTool::GetLockCfgFile();

	LPTSTR lpServer = strServer.GetBuffer(MAX_PATH);
	LPTSTR lpAccount = strAccount.GetBuffer(MAX_PATH);
	LPTSTR lpPassword = strPassword.GetBuffer(MAX_PATH);

	GetPrivateProfileString(L"NetLock", L"Server", L"", lpServer, MAX_PATH, strCfg);
	GetPrivateProfileString(L"NetLock", L"Account", L"", lpAccount, MAX_PATH, strCfg);
	GetPrivateProfileString(L"NetLock", L"Password", L"", lpPassword, MAX_PATH, strCfg);

	strServer.ReleaseBuffer();
	strAccount.ReleaseBuffer();
	strPassword.ReleaseBuffer();
}

CString GetUserAuthority(CString strServerUrl, CString strAccount)
{
	strServerUrl.Replace(L"pcdm", L"");
	strServerUrl.Replace(L"PCDM", L"");
	strServerUrl += L"authority=" + strAccount;

	CString strAuthority;
	//HINTERNET hSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	//if (NULL == hSession)
	//	return strAuthority;

	//HINTERNET hHttp = InternetOpenUrl(hSession, strServerUrl, NULL, 0,
	//	INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);

	//if (NULL != hHttp)
	//{
	//	DWORD readNum = 0;
	//	char buffer[128] = { 0 };
	//	do
	//	{
	//		readNum = 0;
	//		if (InternetReadFile(hHttp, buffer, 128, &readNum))
	//		{
	//			buffer[readNum] = '\0';
	//			strAuthority += buffer;
	//		}
	//	} while (readNum > 0);

	//	InternetCloseHandle(hHttp);
	//}

	//InternetCloseHandle(hSession);

	return strAuthority;
}

bool CLicenceAccess::AppNetLogin()
{
	_strLastError = L"";
	_pNetLock->FreeService();

	CString strServer, strAccount, strPassword;
	GetNetLockInfo(strServer, strAccount, strPassword);

	try
	{
		CString strSignId = (LPCTSTR)_pNetLock->NewRemoteService(strServer.GetString(),
			strAccount.GetString(), strPassword.GetString());

		if (strSignId.IsEmpty())
		{
			_pNetLock->FreeService();
			_strLastError = L"����������ʧ�ܣ������°�װ�������";
			return false;
		}
	}
	catch (_com_error& e)
	{
		_pNetLock->FreeService();
#ifdef  _WIN64
		CString strDes = (LPCTSTR)e.Description();
		_strLastError = CString(L"��½������ʧ�ܡ�");
#else
		_strLastError = CString(L"��½ʧ��\n") + (LPCTSTR)e.Description();
#endif
		return false;
	}
	catch (...)
	{
		_pNetLock->FreeService();
		_strLastError = CString(L"����δ֪����");
		return false;
	}

	bool bResult = CheckLicence(_pNetLock, L"", true, false);
	_bNetLogin = bResult;
	if (!bResult)
		_pNetLock->FreeService();

	//// ��������½�ɹ����ȡ�û�Ȩ��
	//CLicenceAccessImpl::s_strAuthority = GetUserAuthority(strServer, strAccount);

	return bResult;
}

CString CLicenceAccess::GetLastError()
{
	return _strLastError;
}

bool CLicenceAccess::CheckLicence(IBooLockClientManagerPtr pLockPtr,
	CString strLic, bool bAddLicence, bool bNativeLock)
{
	VMProtectBegin("Lic3");

	// ���֤Ϊ����ȡ�����֤
	bool bLicExist = false;
	if (strLic.IsEmpty())
	{
		SupportLicMap licMap = GetAppSupperLicenceMap();
		std::map<int, CString>::iterator iter = licMap.begin();
		for (; iter != licMap.end(); ++iter)
		{
			strLic = GetSupportLicenceByMode(iter->first);
			bLicExist = IsLicenceExist(strLic, pLockPtr, bNativeLock);
			if (bLicExist)
				break;
		}
	}
	else
	{
		bLicExist = IsLicenceExist(strLic, pLockPtr, bNativeLock);
	}
		

	// ֻҪ��������֤���ɵ�½
	if (bLicExist)
	{
		if (!bAddLicence)
		{
			return true;
		}

		// �������֤���ü���
		try
		{
			IBooLockClientServicePtr service = pLockPtr->GetService();
			service->AddLicenceRef(strLic.GetString());
		}
		catch (_com_error& e)
		{
			_strLastError = (LPCTSTR)e.Description();

			return false;
		}
		catch (...)
		{
			_strLastError = _T("����δ֪����");
			return false;
		}

		return true;
	}

	return false;
	VMProtectEnd();
}

bool CLicenceAccess::IsLicenceExist(LPCTSTR licence, IBooLockClientManagerPtr pLockPtr, bool bNativeLock)
{
	VMProtectBegin("Lic4");
	if (!pLockPtr)
		return false;

	IBooLockClientServicePtr service = pLockPtr->GetService();
	int lockCount = service->GetDeviceCount();
	for (int i = 0; i < lockCount; i++)
	{
		IBooReadLockInfoPtr lockInfo = service->ReadDeviceInfo(i);

		// �ų�����������������
		if (bNativeLock && lockInfo->GetLockType() != StandardLock)
			continue;

		int licCount = service->GetLicenceCount(lockInfo->GetDeviceId());
		for (int j = 0; j < licCount; j++)
		{
			IBooReadLicInfoPtr licInfo = service->ReadLicenceInfo(
				lockInfo->GetDeviceId(), j);

			if (!_tcscmp((LPCTSTR)licInfo->GetName(), licence))
			{
				return true;
			}
		}
	}

	return false;
	VMProtectEnd();
}

IBooLockClientServicePtr CLicenceAccess::GetNatServer()
{
	CLicenceAccess* pLicAccess = CLicenceAccess::GetInstance();

	if (!pLicAccess->_pNatLock)
		return NULL;

	return pLicAccess->_pNatLock->GetService();
}

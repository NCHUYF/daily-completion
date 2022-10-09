#include "pch.h"
#include "AutoStartUtility.h"

void AutoStartUtility::SetAutoStart(bool bAuto)
{
	try
	{
		HKEY hKey;

		//�ҵ�ϵͳ��������
		CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

		//��������
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)
			MessageBox(::GetActiveWindow(), _T("��������ʧ��"), _T(""), MB_OK);

		//�ҵ���������·��
		TCHAR pFileName[MAX_PATH] = {};
		GetModuleFileName(NULL, pFileName, MAX_PATH);

		//�ж��Ƿ��Ѿ����ÿ�������
		TCHAR PowerBoot[MAX_PATH] = {};
		DWORD nLongth = MAX_PATH;
		long result = RegGetValue(hKey, NULL, _T("PowerBoot"), RRF_RT_REG_SZ, 0, PowerBoot, &nLongth);
		if (result == ERROR_SUCCESS)        //����״̬
		{
			if (!bAuto)
			{
				//ȡ���Զ�����
				lRet = RegDeleteValue(hKey, _T("PowerBoot"));
				if (lRet == ERROR_SUCCESS)
					MessageBox(::GetActiveWindow(), _T("�ر������ɹ�"), _T(""), MB_OK);
				else
					MessageBox(::GetActiveWindow(), _T("�ر�����ʧ��"), _T(""), MB_OK);
			}
		}
		else        //δ����״̬
		{
			if (bAuto)
			{
				//��������
				lRet = RegSetValueEx(hKey, _T("PowerBoot"), 0, REG_SZ, (LPBYTE)pFileName, (lstrlen(pFileName) + 1) * sizeof(TCHAR));
				if (lRet == ERROR_SUCCESS)
					MessageBox(::GetActiveWindow(), _T("���������ɹ�"), _T(""), MB_OK);
				else
					MessageBox(::GetActiveWindow(), _T("��������ʧ��"), _T(""), MB_OK);
			}
		}

		//�ر�ע���
		RegCloseKey(hKey);
	}
	catch (...) {
	}
}

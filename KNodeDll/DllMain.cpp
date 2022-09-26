// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "PathConfig/PathConfig.h"
#include "Tool\LogOutput.h"

#ifdef _X86_
extern "C" { int _afxForceUSRDLL; }
#else
extern "C" { int __afxForceUSRDLL; }
#endif

HINSTANCE gInstance = NULL;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		gInstance = hModule;
		// ��ʼ����־�ļ�
		CString strSysConfig = CommBase::CPathConfig::GetSystemPath() + L"System.ini";
		UINT nLogType = GetPrivateProfileInt(L"SYSTEM", L"LogType", CommBase::eLogError | CommBase::eLogWarning, strSysConfig);
		CString strAppStartPath = CommBase::CPathConfig::GetAppStartPath();
		strAppStartPath += "AppLog\\";
		CommBase::CLog::InitLog(strAppStartPath, nLogType);

		CommBase::CLog::LogInfo(L"�������");

		CommBase::InitKObjectFactory();
	}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		CommBase::UninitKObjectFactory();

		CommBase::CLog::LogInfo(L"����˳�");

		// �ͷ���־�ļ�
		CommBase::CLog::UninitLog();
		break;
	}

	return TRUE;
}
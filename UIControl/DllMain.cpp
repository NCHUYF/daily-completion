// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"

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
		if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
		{
			CommBase::CLog::LogInfo(L"MFCģ���ʼ��ʧ��");
		}
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
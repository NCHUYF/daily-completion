#pragma once

#include <Tlhelp32.h>

/************************************************************************/
/* ���ڼ�����ؼ�API��dll�Ƿ�����                                   */
/************************************************************************/

template<class T, DWORD ErrVal>
class CInbreakProtectT
{
public:
	/*
	*	���ؼ�API�Ƿ����أ����û�������򷵻ش����ֵ�����򷵻�0
	*/
	T ApiDetection (T value)
	{
		ATLASSERT (value != (T) ErrVal);

		HMODULE hModule = NULL;
		T result = ErrVal;

		// ��� Kernel32.dll
		CAtlArray<CString> api_list;
		api_list.Add (_T("DeviceIoControl"));
		api_list.Add (_T("CreateFileA"));
		api_list.Add (_T("GetSystemTime"));
		api_list.Add (_T("GetSystemTimeAsFileTime"));
		api_list.Add (_T("CreateToolhelp32Snapshot"));
		api_list.Add (_T("GetModuleFileNameW"));
		api_list.Add (_T("GetProcAddress"));
		api_list.Add (_T("LoadLibraryA"));
		api_list.Add (_T("LoadLibraryExW"));
		api_list.Add (_T("LoadLibraryW"));
		api_list.Add (_T("Module32FirstW"));
		api_list.Add (_T("Module32NextW"));

		hModule = LoadLibrary(_T("Kernel32.dll"));
		if (hModule == NULL)
			return result;

		if (_check_jmp_api_detection(hModule, api_list))
		{
			FreeLibrary(hModule);
			return result;
		}

		if (_check_twolib_api_detection(hModule, api_list))
		{
			FreeLibrary(hModule);
			return result;
		}

		FreeLibrary(hModule);

		// ��� setupapi.dll
		api_list.RemoveAll ();
		api_list.Add (_T("SetupDiEnumDeviceInterfaces"));
		api_list.Add (_T("SetupDiEnumDeviceInfo"));
		api_list.Add (_T("SetupDiGetDeviceInterfaceDetailA"));
		api_list.Add (_T("SetupDiGetDeviceRegistryPropertyA"));

		hModule = LoadLibrary(_T("setupapi.dll"));
		if (hModule == NULL)
			return result;

		if (_check_jmp_api_detection(hModule, api_list))
		{
			FreeLibrary(hModule);
			return result;
		}

		if (_check_twolib_api_detection(hModule, api_list))
		{
			FreeLibrary(hModule);
			return result;
		}

		FreeLibrary(hModule);

		// ��� USER32.DLL
		api_list.RemoveAll ();
		api_list.Add (_T("EnableWindow"));
		api_list.Add (_T("EnumChildWindows"));
		api_list.Add (_T("EnumWindows"));
		api_list.Add (_T("GetClassNameW"));

		hModule = LoadLibrary(_T("USER32.DLL"));
		if (hModule == NULL)
			return result;

		if (_check_jmp_api_detection(hModule, api_list))
		{
			FreeLibrary(hModule);
			return result;
		}

		if (_check_twolib_api_detection(hModule, api_list))
		{
			FreeLibrary(hModule);
			return result;
		}

		FreeLibrary(hModule);

		result = value;

		return result;
	}

	/*
	*	���ؼ�DLL�Ƿ�����,û�����ط��ش�������ݣ�ʧ�ܷ���0
	*/
	T DllDetection (T value)
	{
		ATLASSERT (value != (T) ErrVal);

		//1.1 ���ҵ�ǰĿ¼�µ��ļ�
		TCHAR		szPath[MAX_PATH] = {0};
		TCHAR		szSearch[MAX_PATH] = {0};
		CString		strPath;

		DWORD	dwRet = 0;
		int		nPos = 0;

		T	result = ErrVal;

		// ��ȡ�������ڵ�·��
		dwRet = GetModuleFileName(NULL, szPath, MAX_PATH);
		if (!dwRet)
		{
			return result;
		}

		strPath = szPath; strPath.MakeLower();
		nPos = strPath.ReverseFind('\\');
		_tcsncpy_s(szPath, MAX_PATH, strPath, nPos);
		_tcsncpy_s(szSearch, MAX_PATH, szPath, _tcslen (szPath));
		_tcscat_s(szSearch, MAX_PATH, _T("\\*.*"));

		// ������ǰĿ¼�µ������ļ�
		WIN32_FIND_DATA fd;
		HANDLE  hFile = NULL;

		hFile = FindFirstFile(szSearch, &fd);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return result;
		}

		while(FindNextFile(hFile, &fd))
		{
			CString strTemp = fd.cFileName;
			strTemp.MakeLower ();
			if (strTemp == _T("usp10.dll") || strTemp == _T("lpk.dll") || strTemp == _T("hid.dll"))
			{
				FindClose(hFile);
				return result;
			}
		}
		FindClose(hFile);

		//1.3�������ģ��ļ��
		//�������·���µļ���ģ���ϵͳ·���µļ���ģ��������ͬ������Ϊ������DLL�ٳ�
		TCHAR szSysPath[MAX_PATH] = {0};
		BOOL bOk = FALSE;
		BOOL bSameModule = FALSE;
		DWORD sysFileCnt = 0;
		DWORD curDirFileCnt = 0;
		CString SysPath;

		CString *pCurDirFile[MAX_PATH];
		CString *pSysDirFile[MAX_PATH];	 

		GetSystemDirectory(szSysPath, MAX_PATH);
		SysPath = szSysPath; SysPath.MakeLower();
		DWORD dwCurid = GetCurrentProcessId();

		//ö�ٳ����е�����ģ��
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwCurid);
		if (hSnapShot == INVALID_HANDLE_VALUE)
			return result;

		MODULEENTRY32 moduleEntry = { 0 };
		moduleEntry.dwSize = sizeof (MODULEENTRY32);

		if (!Module32First(hSnapShot, &moduleEntry))
		{
			CloseHandle (hSnapShot);
			return result;
		}

		do
		{
			CString ExePath = moduleEntry.szExePath;
			ExePath.MakeLower();

			if (!_tcsncmp(ExePath, szPath, _tcslen(szPath)))
			{
				//��ǰĿ¼�µ��ļ�
				pCurDirFile[curDirFileCnt] = new CString();
				*pCurDirFile[curDirFileCnt] = CString(moduleEntry.szModule).MakeLower();
				curDirFileCnt += 1;
			}
			else if (!_tcsncmp(ExePath, SysPath, SysPath.GetLength()))
			{
				//ϵͳĿ¼�µ��ļ�
				pSysDirFile[sysFileCnt] = new CString();
				*pSysDirFile[sysFileCnt] = CString(moduleEntry.szModule).MakeLower();
				sysFileCnt += 1;
			}
		}while (Module32Next (hSnapShot, &moduleEntry));

		// ���Ƿ�����ͬ���ļ�
		for (size_t i = 0; i< curDirFileCnt; i++)
		{
			for (size_t j = 0; j< sysFileCnt; j++)
			{
				if (*pCurDirFile[i] == *pSysDirFile[j])
				{
					bSameModule = TRUE;
					break;
				}
			}
			if (bSameModule)
			{
				break;
			}
		}

		//�����ڴ�
		for (size_t i = 0; i< curDirFileCnt; i++)
		{
			delete pCurDirFile[i];
		}
		for (size_t i = 0; i< sysFileCnt; i++)
		{
			delete pSysDirFile[i];		 
		}

		// ���û�з�����ͬģ�飬�򷵻���ȷ���
		if (!bSameModule)
			result = value;

		return result;
	}

	/** ���Գ����Ƿ񱻵��ԣ�û�е��Է�������ֵ���е��Է���0 */
	T DebugDetection (T value)
	{
		ATLASSERT (value != (T) ErrVal);

		T result = ErrVal;

#ifdef _DEBUG

		result = value;

#else
		// ͨ���жϺ������ж��Ƿ���û�е�����
		typedef void (FAR WINAPI *DEBUG_BREAK_FUNC)();
		HMODULE hModule = LoadLibrary(_T("Kernel32.dll"));
		__try 
		{
			DEBUG_BREAK_FUNC break_func = (DEBUG_BREAK_FUNC) GetProcAddress(hModule, "DebugBreak");
			break_func();
		}
		__except(GetExceptionCode() == EXCEPTION_BREAKPOINT ?
					EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) 
		{
			// ���û�й��������������ٲ����Ƿ��е������
			if (!_find_ollydbg_ida ())
			{
				result = value;
			}
		}

		FreeLibrary(hModule);
#endif

		return result;
	}

private:
	// �������ж��㴰��
	static BOOL CALLBACK EnumTopWindowProc(HWND hwndChild, LPARAM lParam)
	{
		HWND* findDebugWindow = (HWND*) lParam;
		EnumChildWindows(hwndChild, EnumChildProc, lParam);
		return *findDebugWindow == NULL;
	}

	// �����Ӵ���
	static BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam)
	{
		HWND* findDebugWindow = (HWND*) lParam;
		TCHAR* find_names[] =
		{
			_T("lCPUASM"),	_T("lCPUREG"),	_T("lCPUINFO"),	_T("lCPUSTACK"),
			_T("IDAView"),	_T("hexview_t"),	_T("structview_t")
		};

		// ȡ�ô��������Ʋ��ж������Ƿ��ǵ�����
		TCHAR className[MAX_PATH] = { 0 };
		if (GetClassName (hwndChild, className, MAX_PATH))
		{
			for (int i = 0; i < 7; i ++)
			{
				// �ҵ�������ͬ�������˳�
				if (!_tcscmp (className, find_names[i]))
				{
					*findDebugWindow = hwndChild;
					return FALSE;
				}
			}
		}

		return TRUE;
	}

	// �������д���
	static BOOL CALLBACK EnableTopWindowProc(HWND hwndChild, LPARAM lParam)
	{
		EnumChildWindows(hwndChild, EnableChildProc, lParam);
		EnableWindow(hwndChild, !!lParam);
		return TRUE;
	}
	// �������д���
	static BOOL CALLBACK EnableChildProc(HWND hwndChild, LPARAM lParam)
	{
		EnableWindow(hwndChild, !!lParam);
		return TRUE;
	}

	/**���� OllyDbg ���򣬳ɹ�����1��ʧ�ܷ���0 */
	BOOL _find_ollydbg_ida (void)
	{
		// ������OllyDbg��IDA����Ĵ��ڼ���
		//OllyDbg
		//	MDIClient
		//	  lCPU
		//	    lCPUASM
		//	    lCPUREG
		//	    lCPUINFO
		//	    lCPUSTACK
		//IDA
		//  TaqDockingSite
		//    TaqDockingControl
		//	    TMDIForm \ IDAView
		//	    THexForm \ hexview_t
		//	    TStrucForm \ structview_t

		// ԭ�����Ҷ��㴰�ڼ����ڣ��ҵ���ΪlCPUASM��lCPUREG��lCPUINFO��lCPUSTACK��
		//			IDAView��hexview_t��structview_t��ʾ�е�����

		HWND findDebugWindow = NULL;
		EnumWindows(EnumTopWindowProc, (LPARAM) &findDebugWindow);

		// ��������е��Գ����������������д���
		if (findDebugWindow)
		{
			EnumWindows (EnableTopWindowProc, FALSE);
		}

		return findDebugWindow != NULL;
	}

	/** ���ñȽ���ת����ķ������ж��Ƿ��� API �ٳ� */
	BOOL _check_jmp_api_detection (HMODULE hModule, CAtlArray<CString>& api_list)
	{
		FARPROC lpProc = NULL;
		BYTE    jmpOpCode1 = 0xE9;
		BYTE    jmpOpCode2 = 0xEB;
		BYTE	firstProcCode = 0;

		for (size_t i = 0; i < api_list.GetCount (); i ++)
		{
			// ���������ǰΪjmp���ʾ�������ҹ�
			CW2A apiname = api_list[i];
			lpProc = GetProcAddress(hModule, apiname);
			firstProcCode = *((BYTE*)lpProc);
			if (lpProc != NULL && (firstProcCode == jmpOpCode1 || firstProcCode == jmpOpCode2))
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	/** ���ü��صڶ���dll�ļ��ķ������ж��Ƿ���api�ٳ� */
	BOOL _check_twolib_api_detection (HMODULE hModule, CAtlArray<CString>& api_list)
	{
		// ��ȡģ��·���������ȡ��������Ϊ���ٳ�
		TCHAR src_path[MAX_PATH] = { 0 };
		::GetModuleFileName (hModule, src_path, MAX_PATH);

		// ������ʱ�ļ�
		TCHAR lpPathBuffer[MAX_PATH] = { 0 };
		if (GetTempPath (MAX_PATH, lpPathBuffer) == 0)
			return TRUE;

		TCHAR temp_sign[MAX_PATH] = { 0 };
		_stprintf_s(temp_sign, MAX_PATH, _T("%d_"), ::GetTickCount());
		_tcscat_s (lpPathBuffer, MAX_PATH, temp_sign);
		TCHAR *nameptr = _tcsrchr (src_path, _T('\\'));
		_tcscat_s (lpPathBuffer, MAX_PATH, ++ nameptr);
		if (!CopyFile (src_path, lpPathBuffer, TRUE))
			return TRUE;

		// ������ʱ�ļ������ʧ�����ʾ�ٳ�
		HMODULE tempModule = LoadLibraryEx (lpPathBuffer, NULL, DONT_RESOLVE_DLL_REFERENCES);
		if (tempModule == NULL)
		{
			DeleteFile (lpPathBuffer);
			return TRUE;
		}

		// �Ƚ�����ģ���к�����ͷ5���ֽڣ����Ƿ��в���ͬ�ģ��в���ͬ���ʾ������
		FARPROC lpProc1 = NULL;
		FARPROC lpProc2 = NULL;
		long errcnt = 0;
		for (size_t i = 0; i < api_list.GetCount (); i ++)
		{
			// ���������ǰΪjmp���ʾ�������ҹ�
			CW2A apiname = api_list[i];
			lpProc1 = GetProcAddress (hModule, apiname);
			lpProc2 = GetProcAddress (tempModule, apiname);

			BYTE* codebuff1 = (BYTE *) lpProc1;
			BYTE* codebuff2 = (BYTE *) lpProc2;

			if (memcmp (codebuff1, codebuff2, 5))
				errcnt ++;
		}

		// ��� errcnt > 0 ��ʾ������
		FreeLibrary (tempModule);
		DeleteFile (lpPathBuffer);

		return errcnt > 0;
	}
};

typedef CInbreakProtectT<DWORD,0> CInbreakProtect;
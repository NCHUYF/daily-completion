#include "stdafx.h"
#include "..\include\libtoolkit.h"
#include "..\include\EnumProc.h"
#include "shellapi.h"
#include "psapi.h"

using namespace BwProj::toolkit;

/** ���� GUID��*/
CString CLibToolkit::CreateGuid (void)
{
	GUID id;
	WCHAR idstr[MAXBYTE];
	CoCreateGuid (&id);
	StringFromGUID2 (id, idstr, MAXBYTE);

	return CString (idstr);
}

/** ȡ��ģ��·����c:\a.exe��*/
CString CLibToolkit::GetAppModuleFilename (HINSTANCE hInst)
{
	TCHAR m_pstr[MAX_PATH];

	// 2012-01-30 LY ������DLL�е��øú�������NULL����ʱ��ȡ�Ĳ���Ӧ�ó���·������
	// Get entire module filepath
	//#if (_ATL_VER >= 0x0700)
	//	if( hInst == NULL ) hInst = ATL::_AtlBaseModule.GetResource2Instance();
	//#else
	//	if( hInst == NULL ) hInst = _Module.GetModuleInstance();
	//#endif // _ATL_VER
	//

	if (hInst == NULL) {
		// ���ڻ�ȡ������·��
		::GetModuleFileName(hInst, m_pstr, MAX_PATH);
	} else {
		// ���ڻ�ȡ�����·��
		::GetModuleFileNameEx(hInst, 0, m_pstr, MAX_PATH);
	}
		

	return m_pstr;
}

/** ȡ��ģ��·����c:\����*/
CString CLibToolkit::GetAppModulePath (HINSTANCE hInst)
{
	CString path = GetAppModuleFilename(hInst);

	if (path.GetLength() > 0) {
		path = path.Mid(0, path.ReverseFind('\\')+1);
	}

	return path;
}

/** ȡ����ʱ·����c:\����*/
CString CLibToolkit::GetTempPath (void)
{
	TCHAR m_pstr[MAX_PATH];

	DWORD dwLength = ::GetTempPath(MAX_PATH, m_pstr);
	m_pstr[dwLength] = _T('\0');
	return m_pstr;
}

/** ȡ��API������Ϣ��*/
CString CLibToolkit::GetWin32LastError ()
{
	CString str;
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf, 0, NULL 
	);
	str = (LPCTSTR)lpMsgBuf;
	LocalFree( lpMsgBuf );

	return str;
}

/** ȡ��ϵͳͼ�� */
HICON CLibToolkit::GetSystemIcon(SYSTEM_ICON_INDEX index)
{
	TCHAR path[MAX_PATH] = {0};
	GetSystemDirectory(path, MAX_PATH);
	CString systemPath = CString(path);
	CString shell32Path = systemPath + CString("\\shell32.dll");
	HICON icon = ExtractIcon((HINSTANCE)::GetCurrentProcess(), shell32Path.GetBuffer(),index);
	return icon;
}

// ��ȡ����·���б�
// ��ȡ����·���б�
int CLibToolkit::LoadProcessList(CAtlArray<CString>& list)
{
	CProcessIterator piFind;

	list.RemoveAll();
	DWORD pid = piFind.First();
	while (pid) {
		CProcessModuleIterator miFind(pid);
		if (miFind.GetProcessHandle() == NULL) {
			pid = piFind.Next();
			continue;
		}

		CString path = GetAppModuleFilename((HINSTANCE)miFind.GetProcessHandle());
		if (path.GetLength() == 0) {
			pid = piFind.Next();
			continue;
		}

		list.Add(path);
		pid = piFind.Next();
	}

	return list.GetCount();
}
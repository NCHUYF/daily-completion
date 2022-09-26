
#pragma once

//=========================================================
// Ӧ�ó�����������
//=========================================================
// begin namespace
namespace BwProj{ namespace toolkit{

/** @addtogroup CadreLibToolkit
* @{
*/


#ifdef _DEBUG
#define TIME_TEST_INIT			 \
	DWORD dwStart = 0; \
	DWORD dwEnd = 0;

#define TIME_TEST_START			 \
	dwStart = ::GetTickCount ();

#define TIME_TEST_END			 \
	dwEnd = ::GetTickCount ();

#define TIME_TEST_PRINT(msg)	 \
	ATLTRACE ("%s: %i ms.\n", msg, dwEnd - dwStart);
#else
#define TIME_TEST_INIT
#define TIME_TEST_START
#define TIME_TEST_END
#define TIME_TEST_PRINT(msg)
#endif

/** ϵͳͼ������ö������ */
typedef enum
{
	SYSTEM_ICON_DOCUMENT = 1,
	SYSTEM_ICON_NETWORK_AREA = 17,
	SYSTEM_ICON_FOLDER_CLOSE = 3,
	SYSTEM_ICON_FOLDER_OPNE = 4,
	SYSTEM_ICON_FLOPPY = 6,
	SYSTEM_ICON_HARDWARE_DISK = 7,
	SYSTEM_ICON_NETLINK_DISK = 9,
	SYSTEM_ICON_NETLINK_DISK_DISCONNECT = 10,
	SYSTEM_ICON_CDROOM = 11,
	SYSTEM_ICON_INTERNET = 13,
	SYSTEM_ICON_MYCOMPUTER = 15,
	SYSTEM_ICON_PRINTER = 16,
	SYSTEM_ICON_FINDER = 22,
	SYSTEM_ICON_HELPER = 23,
	SYSTEM_ICON_RUN = 24,
	SYSTEM_ICON_SHUTDOWN = 27,
	SYSTEM_ICON_RECYCLE_EMPTY = 31,
	SYSTEM_ICON_RECYCLE_FULL = 32,
	SYSTEM_ICON_DESKTOP = 34,
	SYSTEM_ICON_FONT_FOLDER = 38,
	SYSTEM_ICON_MUSIC = 40,
	SYSTEM_ICON_IEFAV_FOLDER = 43,
	SYSTEM_ICON_LOCK = 44,
}SYSTEM_ICON_INDEX;

//! Ӧ�ó�����������
class COMMONTOOLS_API CLibToolkit
{
public:
	/** 
	* ���� GUID
	* @return	�������ɵ�GUID�ַ���
	*/
	static CString CreateGuid (void);

	/** 
	* ȡ��ģ��·��
	* @param [in] hInst		ģ��ľ��
	* @return	����ģ��·�����磨c:\\a.exe��
	*/
	static CString GetAppModuleFilename (HINSTANCE hInst);

	/** 
	* ȡ��ģ��·��
	* @param [in] hInst		ģ��ľ��
	* @return	����ģ��·�����磨c:\\��
	*/
	static CString GetAppModulePath (HINSTANCE hInst);

	/** 
	* ȡ����ʱ·��
	* @return	������ʱ·���ַ������磨c:\\��
	*/
	static CString GetTempPath (void);

	/** 
	* ȡ��API������Ϣ
	* @return	����API������Ϣ
	*/
	static CString GetWin32LastError (void);

	/** 
	* ȡ��ϵͳͼ�� 
	* @param [in] index		ϵͳͼ������
	* @return	ϵͳͼ�����
	*/
	static HICON GetSystemIcon(SYSTEM_ICON_INDEX index);

	// ��ȡ����·���б�
	static int LoadProcessList(CAtlArray<CString>& list);
};

/** * @} */
}}	// end namespace
/** @} */
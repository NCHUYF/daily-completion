//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           FileTool.H
//    @author         fanHong
//    @date           2017/11/2 18:10
//    @brief          �ļ����߼�
//
//*****************************************************

#pragma once

#include "Type/TypeDefine.h"

namespace CommBase
{
	//! �ļ�ϵͳ
	class COMMBASE_API CFileTool
	{
	public:
		/**
		* �½�Ŀ¼ ��֧�ֶ༶��
		* @param [in] Directory		Ŀ¼����
		* @return	�����½�Ŀ¼�Ƿ�ɹ�
		* - true �½��ɹ��� false �½�ʧ��
		*/
		static bool CreateDirectory(CString Directory);

		/**
		* �����ļ��Ƿ����
		* @param [in] Filename		�ļ�����
		* @return	�����ļ��Ƿ����
		* - true �ļ����ڣ� false �ļ�������
		*/
		static bool FileExist(CString Filename);

		/**
		* ����Ŀ¼�Ƿ����
		*
		* ��֧������·��
		* @param [in] Directory		Ŀ¼����
		* @return	����Ŀ¼�Ƿ����
		* - true Ŀ¼���ڣ� false Ŀ¼������
		*/
		static bool DirectoryExist(CString Directory);

		/**
		* ��ȡ�ض�Ŀ¼���ļ��Լ�Ŀ¼��Ϣ�б�
		* @param [in] Directory		Ŀ¼����
		* @param [out] arr			Ŀ¼�Լ�Ŀ¼��Ϣ�б�
		* @param [in] Recursion		�Ƿ�ݹ飨Ĭ��Ϊ��
		* @param [fileExt		    ��ȡ����չ��
		* @return	�����Ƿ�ɹ���ȡ�ض�Ŀ¼���ļ��Լ�Ŀ¼��Ϣ�б�
		* - true ��ȡ�ɹ��� false ��ȡʧ��
		*/
		static bool ReadDirectory(CString Directory , StringArray& arr,
			bool Recursion = false, CString fileExt = L"*.*");

		/**
		* ��ȡ�ض�Ŀ¼�µ��ļ���
		* @param [in] Directory		Ŀ¼����
		* @param [out] arr			Ŀ¼�Լ�Ŀ¼��Ϣ�б�
		* @param [in] Recursion		�Ƿ�ݹ飨Ĭ��Ϊ��
		* @param [fileExt		    ��ȡ����չ��
		* @return	�����Ƿ�ɹ���ȡ�ض�Ŀ¼���ļ��Լ�Ŀ¼��Ϣ�б�
		* - true ��ȡ�ɹ��� false ��ȡʧ��
		*/
		static bool ReadDirectoryDir(CString Directory, StringArray& arr,
								  bool Recursion = false);

		/**
		* ȡ�õ�ǰĿ¼
		* @return	���ص�ǰĿ¼�ַ���
		*/
		static CString GetCurrentDirectory();

		/**
		* ��ʽ��Ŀ¼
		*
		* �����޷�׼ȷ�����ļ���Ŀ¼����˴�����ļ�Ҳ������ΪĿ¼����
		* �紫��"C:\\Windows\\explorer.exe"�᷵��"C:\\Windows\\explorer.exe\\"
		* ���·��ֻ֧��һ�������ơ�..\..\��ֻ�ᴦ���һ����..\��
		* @param [in] Directory		Ŀ¼����
		* @return	���ظ�ʽ�����Ŀ¼�ַ���,��β����'\'
		* - ��ʽ�����Ŀ¼�磺C:\\hello\\
		*/
		static CString FormatDirectory(CString Directory);

		/**
		* ��ʽ���ļ���(���Filename������չ����ExtendName��Ϊ����ֵ����չ�������򷵻�ֵ����Filename)
		* @param [in] Filename		�ļ�����
		* @param [in] ExtendName	��չ���ƣ�Ĭ��Ϊ�գ���Filename������չ��ʱ�ò�����������.��
		* @return	���ظ�ʽ������ļ�����
		* - ����FilenameΪC:\\hello, ExtendNameΪtxt���򷵻�C:\\hello.txt
		*/
		static CString FormatFilename(CString Filename , CString ExtendName = _T(""));

		/**
		* ȡ���ļ��߼���
		* @param [in] Filename		�ļ�����
		* @return	�����ļ��߼���
		* - ����FilenameΪC:\\hello.txt, �򷵻�hello.txt
		*/
		static CString GetFileLogicName(CString Filename);

		/**
		* ȡ���ļ���չ����������.����
		* @param [in] Filename		�ļ�����
		* @return	�����ļ���չ��
		* - ����FilenameΪC:\\hello.txt, �򷵻�.txt
		*/
		static CString GetFileExtendName(CString Filename);

		/**
		* ȡ���ļ�������
		* @param [in] Filename		�ļ�����
		* @return	�����ļ�������
		* - ����FilenameΪC:\\hello.txt, �򷵻�hello
		*/
		static CString GetFileBaseName(CString Filename);

		/**
		* ȡ���ļ�����Ŀ¼
		* @param [in] Filename		�ļ�����
		* @return	�����ļ�����Ŀ¼
		* - ����FilenameΪC:\\hello\\hello.txt, �򷵻�C:\\hello
		*/
		static CString GetFileDirectory(CString Filename);

		/**
		* ȡ���ļ���������
		*
		* ���������ϸ���·���Ϸ���
		* ǰ��λ��"\\"����Ϊ������·��������\\+��һ��\֮ǰ����
		* �ڶ�λ�ǡ�:������Ϊ�Ǵ���·��������ǰ�����ַ�
		* ��һλ�ǡ�\��,��Ϊ�Ǵӵ�ǰ��Ŀ¼��ʼ��·�������ص�ǰĿ¼��ǰ�����ַ�
		* ���򣬷��ؿ��ַ���
		* @param [in] Path		�ļ�·��
		* @return	�����ļ���������
		*/
		static CString GetDrive(CString Path);

		/**
		* �����ļ���չ��
		* Filename��BaseName������Ϊ��
		* @param [in] Filename		�ļ�����
		* @param [in] ExtendName	��չ���ƣ�Ĭ��Ϊ�գ�
		* @return	�������ú���ļ���
		*/
		static CString SetFileExtendName(CString Filename , CString ExtendName = _T(""));

		/**
		* �����ļ��߼���
		* @param [in] Filename		�ļ�����
		* @param [in] LogicName		�߼�����
		* @return	�������ú���ļ���
		*/
		static CString SetFileLogicName(CString Filename , CString LogicName);

		/**
		* �����ļ�������
		* @param [in] Filename		�ļ�����
		* @param [in] BaseName		�ļ�������(������Ϊ��)
		* @return	�������ú���ļ���
		*/
		static CString SetFileBaseName(CString Filename , CString BaseName);

		/**
		* �����ļ�����Ŀ¼
		*
		* ��������Դ���Ŀ¼�ĺϷ�����У�飬ʹ������Ҫ�Լ�ȷ��������Ч
		* @param [in] Filename		�ļ�����
		* @param [in] Directory		Ŀ��Ŀ¼,
		* @return	�������ú���ļ���
		*/
		static CString SetFileDirectory(CString Filename , CString Directory);

		/**
		* ɾ���ļ����ļ���
		* @param [in] strFile		�ļ�·��
		* @param [in] fFlag			״ֵ̬��Ĭ��Ϊ�봰�ڣ�
		* @return	�����Ƿ�ɹ�ɾ���ļ����ļ��е�����վ
		*/
		static bool DeleteDirectory(CString strDir);

		/**
		* �����ļ���չ��ȡ�ö�Ӧ��ϵͳͼ��
		* - ���ص�hIcon��������Լ�ɾ�������������Դй¶
		* @param [in] strExt		�ļ�·��
		* @param [out] hIcon		ͼ�����
		* @param [out] nIndex		ͼ������
		* @param [in] attrib		�ļ����ԣ�Ĭ��ΪFILE_ATTRIBUTE_NORMAL��
		* @return	�����Ƿ�ɹ�ȡ�ö�Ӧ��ϵͳͼ��
		* - true ��ȡ�ɹ��� false ��ȡʧ��
		*/
		static bool GetIconByExtName(CString strExt , HICON& hIcon , int& nIndex , DWORD attrib = FILE_ATTRIBUTE_NORMAL);

		/**
		* ����ļ����Ƿ�Ϊ��׼�ļ���
		* Windows�ļ��������򣺣�ժ��MSDN��ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.chs/fileio/fs/naming_a_file.htm��
		*   - ʹ�õ�(.)�ָ�����ļ�������չ��
		*   - ʹ�÷�б��(\)�ָ�·��Ԫ�أ���Ŀ¼��Ŀ¼֮�䡢Ŀ¼���ļ���֮��
		*   - ��б��(\)��Ҫ��Ϊ��������һ���֣��� "C:\<path>\<file>" �е�"C:\"����б��(\)��������ʵ�ʵ�Ŀ¼���ļ�����
		*   - ����ʹ�õ�ǰ����ҳ(����Unicode)�������ַ�������ֵΪ0-31�����±����ַ���
		*			< > : " / \ | ? *
		*   - ��·����ʹ��һ�����(.)��Ϊ·��Ԫ��ʱ����ǰĿ¼
		*   - ��·����ʹ�������������(..)��Ϊ·��Ԫ��ʱ����Ŀ¼
		*   - ��Ҫʹ�ñ����豸����Ϊ�ļ�����
		*		CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8, COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9
		*		ͬʱҲ����ʹ����Щ���ƴ�����չ������ NUL.tx7
		*   - ��Ҫ�ٶ���Сд���С����� OSCAR, Oscar, �� oscar��Ϊ����ͬ��
		*   - ��Ҫʹ�ÿհ��ַ��͵����Ϊ�ļ���Ŀ¼�Ľ�β���������Ե�ſ�ͷ
		*
		* -��������Ч�ַ����ļ��������ܰ���·��
		* @param [in] strFile		�ļ�����
		* @param [out] pChar		���ؼ�鲻���ϵ��ַ���ʲô
		* @return	�����ļ����Ƿ�Ϊ��׼�ļ���
		* - true ��׼��false ����׼
		*/
		static bool CheckFileNameValidate(CString strFile , TCHAR* pChar);

		/**
		*  @brief    ��ȡ��Ч�ļ�����(��֧�ֵķ���ת��Ϊȫ��)
		*
		*  @param    const CString strFile �ļ�����
		*  @return   CString ת������ļ�����
		*/
		static CString GetValidateFileName(const CString strFile);

		/**�����ļ����ȡ���ļ�·�� */
		static BOOL GetFilePathFromHandle(HANDLE hFile , LPWSTR lpszPath , UINT cchMax);

		/**
		* Ŀ¼����
		* @param [in] srcDir		ԴĿ¼
		* @param [in] dstDir		Ŀ��Ŀ¼
		* @return	�Ƿ񿽱��ɹ�
		* - true �����ɹ��� false ����ʧ��
		*/
		static BOOL CopyDirectory(const CString& srcDir , const CString& dstDir);

		/**
		*  @brief    �������·��
		*
		*  @param    const CString & strSrcPath
		*  @param    const CString & strRelateDir
		*  @return   CString
		*/
		static CString GetRelatePath(const CString& strSrcPath , const CString& strRelateDir);

		/**
		* ȡ����ʱ·��
		* @return	������ʱ·���ַ������磨c:\\��
		*/
		static CString GetTempPath(void);

		/**
		*  @brief    ��windows ������Ի������û�ѡ��һ��Ŀ¼;
		*
		*  @param    const CString& strTitle	�Ի���ı���;
		*  @param    CString& strPathChoosed	�û�����ѡ���·��;
		*  @param    HWND hwndOwner				�Ի���ĸ����ھ��;
		*  @param    const CString& strDirBegin	�Ի����ʱ��λ�ĳ�ʼĿ¼;
		*  @return   �û��Ƿ������ѡ��;
		*/
		static bool OpenBrowseDirDlg(const CString& strTitle, CString& strPathChoosed, HWND hwndOwner = NULL, const CString& strDirBegin = _T(""));

		/**
		* ���ļ�����������
		*
		* @param [in] srcFile		Դ�ļ�
		* @param [in] dstFile		Ŀ���ļ�
		* @param [in] nHeadLen		�ļ�ͷ��С�����ⷽʽ����)
		* @param [in] nKey			������Կ
		*/
		static bool EncryptFile(const CString& srcFile, const CString& dstFile, int nHeadLen = 128, int nKey = 0xC5236911);

		/**
		* ���ļ�����������
		*
		* @param [in] srcFile		Դ�ļ�
		* @param [in] dstFile		Ŀ���ļ�
		* @param [in] nHeadLen		�ļ�ͷ��С�����ⷽʽ����)
		* @param [in] nKey			������Կ
		*/
		static bool DeEncryptFile(const CString& srcFile, const CString& dstFile, int nHeadLen = 128, int nKey = 0xC5236911);

		/**
		* �ж��ļ��Ƿ����
		*
		* @param [in] srcFile		Դ�ļ�
		*/
		static bool IsFileEncrypt(const CString& strFile);

		/**
		* ��������Ի���
		*
		* @param [in] szFilters		�ļ���׺��
		* @param [in] strDefExt		�ļ�����
		*/
		static StringArray ImportFileWnd(const LPCTSTR& szFilters, const LPCTSTR& strDefExt);

		/**
		* ���������Ի���
		*
		* @param [in] strName		�ļ���
		* @param [in] szFilters		�ļ���׺��
		* @param [in] strDefExt		�ļ�����
		*/
		static CString ExportFileWnd(const CString& strName, const CString& szFilters, const LPCTSTR& strDefExt);

		
	};
}
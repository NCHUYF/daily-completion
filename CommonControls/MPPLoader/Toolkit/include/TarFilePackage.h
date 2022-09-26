#pragma once

#include "IFilePackage.h"

namespace BwProj { namespace toolkit {

/** @addtogroup FilePackage
* @{
*/

/************************************************************************/
/*  CTarFilePackage                                                     */
/************************************************************************/
#define TARFILE_FLAGS_ENCRYPTTABLE	0x0001	/**< �����ļ����ݱ� */
#define TARFILE_FLAGS_ENCRYPTDATA	0x0002	/**< ���������ļ� */
#define TARFILE_FLAGS_ENCRYPT		(TARFILE_FLAGS_ENCRYPTTABLE|TARFILE_FLAGS_ENCRYPTDATA)

//! ��Դ�ļ�����
class COMMONTOOLS_API CTarFilePackage : public IFilePackage
{
public:
	CTarFilePackage(DWORD submitFlags = TARFILE_FLAGS_ENCRYPTTABLE);
	virtual ~CTarFilePackage (void);

	/** 
	* �ر��ļ������������submit������в���
	*/
	virtual void close (void);

	/**
	* ȡ���ļ�ö�ٶ���
	* @return	�����ļ�ö��
	*/
	virtual EntryEnumeration_ptr getEntries (void);

	/**
	* ȡ�ð����ļ���Ϣ�������ִ�Сд��
	* @param [in] name	�ļ�����
	*/
	virtual LPCFILEENTRY getEntry (LPCTSTR name);

	/**
	* ȡ���ļ����� 
	* @param [in] entry		�ļ�����
	* @return �����ļ������������Ҫ�Լ�ɾ��
	*/
	virtual RandomReadStream_ptr getReadStream (LPCFILEENTRY entry);

	/**
	* ����ļ������� 
	* @param [in] name		�ļ�����
	* @param [in] stream	��������ȡ����
	*/
	virtual void putNextEntry (LPCTSTR name, RandomReadStream_ptr stream);

	/**
	* ɾ�����е��ļ� 
	* @param [in] entry		�ļ�����
	*/
	virtual void removeEntry (LPCFILEENTRY entry);
	

	/** �����ļ��ܳ��� */
	ULONGLONG calcPackageLength (void);

protected:
	/** �ļ�ͷ */
	typedef struct
	{
		TCHAR		HeaderTag[30];			/**< �ļ�ͷ��ʶ */
		TCHAR		FilePassword[30];		/**< �ļ����룬��ʱ���ղ�ʹ�ã�Ϊ�Ժ���չ���� */
		DWORD		FileVersion;			/**< �ļ��汾��0,1,2�� */
		DWORD		FileOptions;			/**< �ļ���ʽѡ�� */
		DWORD		DataTablesPos;			/**< ���ݱ���ʼλ�� */
		DWORD		DataTablesSize;			/**< ���ݱ��С */
	}TARFILEHEADER;

	typedef struct 
	{
		DWORD	dataLength;	/**< �ļ�����(�ֽ���) */
		DWORD	dataOffset;	/**< ���ļ��е�ƫ���� */
		DWORD	nameLength;	/**< �ļ����Ƴ��� */
	}ENTRYINFO;

	/** entryͷ */
	typedef struct
	{
		ENTRYINFO	fileInfo;			/**< �ļ���Ϣ */
		TCHAR		fileName[MAX_PATH];	/**< �ļ����� */
	}ENTRYHEADER, *LPENTRYHEADER;

	/** �ѵ�ǰ�ļ�д�����ļ� */
	void _submitToFile (HANDLE handle);

	/**
	* ���µ�ǰ�ļ������ģ����ļ��򿪺�����
	* @param [in] context	�Ѵ��������úõ�������
	*/
	virtual void _updateContext (OPENCONTEXT* context);

	/** ��ʹ���ļ�ͷ�ṹ */
	void _initFileHeaderStruct (TARFILEHEADER* header);

	/** �������ݣ�����Ҳ���ô˺��������������ĳ�����ͬ */
	DWORD _encryptDataBuffer(LPBYTE pDataBuffer, DWORD dwLength, LPCTSTR lpPasswrod, DWORD dwPwdLength);

	/** ��ȡ�����ļ��б� */
	void _loadFileEntryList (void* lpDatabaseBuffer, DWORD size);

	/** ����һ���ļ����� */
	LPFILEENTRY _newFileEntry (LPENTRYHEADER zipentry);
	LPFILEENTRY _newFileEntry (IRandomReadStream* stream);

	/** ɾ��һ���ļ����� */
	void _deleteFileEntry (LPFILEENTRY fileentry);

	/** �������б��в����Ѵ��ڵĽ�� */
	BOOL _findEntryInArray (LPFILEENTRY find_entry, CAtlArray<LPFILEENTRY>** save_ptr, size_t* save_idx);

	/** �������ݱ��� */
	DWORD _calcDataTableLength (DWORD* totalCount);

	void _submit(CString filePath);
protected:
	typedef CAtlFileMapping<char> CTarFileMapping;
	std::auto_ptr<CTarFileMapping>	_fileMapping;	/**< ���ڰ��ļ�ӳ�䵽�ڴ� */
	TARFILEHEADER					_fileHeader;	/**< �ļ�ͷ */
	DWORD							_submitFlags;	/**< ���ܱ�� */

	CAtlArray<LPFILEENTRY>	_entryList;		/**< zip���Ѵ��ڵ��ļ��б� */
	CAtlArray<LPFILEENTRY>	_addEntry;		/**< ����ӵ��ļ��б� */
	BOOL					_srcChanged;	/**< ���ԭʼ�ļ��Ƿ����޸ģ���ɾ�������ļ� */
};

/** * @} */
}}	// end namespace
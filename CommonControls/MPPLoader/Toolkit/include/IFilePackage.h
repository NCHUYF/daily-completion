
#pragma once

#include "IDataStream.h"
#include "CriticalSection.h"
#include "Exception.h"

namespace BwProj { namespace toolkit {

/** @addtogroup FilePackage
* @{
*/

/** �ļ���Ϣ */
typedef struct
{
	TCHAR	name[MAX_PATH];		/**< �ļ����� */
	DWORD	originalSize;		/**< δѹ���ļ����� */
	DWORD	compressedSize;		/**< ѹ�����ļ����� */
	DWORD	extendType;			/**< ��չֵ���ͣ����ڴ洢ʵ���� */
	void*	extendData;			/**< ��չֵ���ݣ����ڴ洢ʵ��������� */
}FILEENTRY, *LPFILEENTRY;
typedef const LPFILEENTRY LPCFILEENTRY;

/** ���¶�������FILEENTRY.extendType  */
#define ENTRY_EXTEND_EXISTENTRY	0x01	/**< �ļ����Ѵ����ڵ� */
#define ENTRY_EXTEND_NEWSTREAM	0x02	/**< �ļ�������ӵĵ� */

//! EntryEnumeration �ļ������ļ��ı�����
class IEntryEnumeration
{
public:
	virtual ~IEntryEnumeration () {}
	virtual BOOL hasMoreElements (void) = 0;
	virtual LPCFILEENTRY nextElement (void) = 0;
};
typedef std::auto_ptr<IEntryEnumeration> EntryEnumeration_ptr;

//! IFilePackage �ļ�������ӿڣ����ڰѶ���ļ�����һ���ļ��й���
class IFilePackage
{
public:
	virtual ~IFilePackage ();

	/**
	* ���á���ȡ�����õ�����
	*/
	virtual void setPassword (LPCTSTR password);
	virtual LPCTSTR getPassword (void);

	/** 
	* �Կɶ�ȡģʽ���ļ�
	* @param [in] filePath	�ļ�·��
	*/
	virtual void open (LPCTSTR filePath);
	virtual void open (HANDLE fileHandle);

	/** 
	* ��ֻ��ȡģʽ���ļ�
	* @param [in] fileStream	�ļ���
	*/
	virtual void open (IRandomReadStream* fileStream);

	/** 
	* �ر��ļ������������submit������в���
	*/
	virtual void close (void);

	/**
	* ȡ���ļ�ö�ٶ���
	* @return	�����ļ�ö��
	*/
	virtual EntryEnumeration_ptr getEntries (void) = 0;

	/**
	* ȡ�ð����ļ���Ϣ�������ִ�Сд��
	* @param [in] name	�ļ�����
	*/
	virtual LPCFILEENTRY getEntry (LPCTSTR name) = 0;

	/**
	* ȡ���ļ�����(ע���ⲿ���ɵ�ZIP���ڿ��ܴ���Ŀ¼����entryΪĿ¼ʱ�˷�������RandomReadStream_ptr�ڲ�Ϊ�գ�
	* ��ʹ��.get�����жϷ��صĶ�ȡ�������Ƿ���Ч)
	* @param [in] entry		�ļ�����
	* @return �����ļ������������Ҫ�Լ�ɾ��
	*/
	virtual RandomReadStream_ptr getReadStream (LPCFILEENTRY entry) = 0;

	/**
	* ����ļ������� 
	* @param [in] name		�ļ�����
	* @param [in] stream	��������ȡ����
	*/
	virtual void putNextEntry (LPCTSTR name, RandomReadStream_ptr stream) = 0;

	/**
	* ɾ�����е��ļ� 
	* @param [in] entry		�ļ�����
	*/
	virtual void removeEntry (LPCFILEENTRY entry) = 0;

	/**
	* ���������ļ�
	* -�ļ�����ӻ�ɾ��������� Flush ���µ������ļ���Closeʱ���Զ����ô˺���
	* -���ļ��Ƚ϶���ʱ��Flush��ʱ����ܻ�Ƚϳ�
	* @param [in] entry		�ļ�����Ϊ��ʱʹ���ڲ�������ļ���������ͨ���ļ����򿪵İ���
	* @result �ȴ������߳��˳���ʧ���׳� BwProj::Exception �쳣
	*/
	virtual void submit (CString filename);

protected:
	/** �ļ���Ϣ */
	typedef struct
	{
		HANDLE				fileHandle; /**< �򿪵��ļ����������Ϊ�� */
		CString				filename;	/**< �򿪵��ļ���������Ϊ�� */
		IRandomReadStream*	readStream;	/**< �ļ����ݶ�ȡ�� */
		IRandomWriteStream*	writeStream;/**< �ļ�����д���� */
		BOOL	closeDeleteReadStream;	/**< �˳�ʱ�Ƿ�ɾ��readStream */
		BOOL	closeDeleteWriteStream;	/**< �˳�ʱ�Ƿ�ɾ��writeStream */
	}OPENCONTEXT;

	/**
	* ���µ�ǰ�ļ������ģ����ļ��򿪺�����
	* @param [in] context	�Ѵ��������úõ�������
	*/
	virtual void _updateContext (OPENCONTEXT* context);

	/** ���Ե���_updateContext��������쳣����ͷ�context���� */
	BOOL _tryUpdateContext (OPENCONTEXT* context, CString& errmsg);

	virtual void _submit(CString filePath) = 0;

protected:
	std::auto_ptr<OPENCONTEXT>	_openContext;	/**< �ļ�����Ϣ */
	CString						_filePassword;	/**< �ļ������� */
	BwProj::toolkit::CCriticalSectionHandle	_CSC;
};

//! CEntryEnumeration �ļ������ļ��ı�����
class CEntryEnumeration : public IEntryEnumeration
{
public:
	CEntryEnumeration ();
	virtual ~CEntryEnumeration ();
	virtual BOOL hasMoreElements (void);
	virtual LPCFILEENTRY nextElement (void);

	CAtlArray<LPFILEENTRY>& getEntryList (void);

protected:
	size_t					_position;	/**< ��ǰ����λ�� */
	CAtlArray<LPFILEENTRY>	_entryList;	/**< ����б� */
};

/** * @} */
}}	// end namespace
/** @} */
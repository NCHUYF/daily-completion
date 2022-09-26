#include "StdAfx.h"
#include "..\include\IFilePackage.h"
#include "..\include\MemoryDataStream.h"
#include "..\include\FileDataStream.h"
#include "..\include\LibToolkit.h"
#include "..\include\FileToolkit.h"


using namespace BwProj::toolkit;
using namespace BwProj::toolkit;

/************************************************************************/
/* IFilePackage                                                         */
/************************************************************************/
IFilePackage::~IFilePackage(void)
{
	// Ҫ�����������йر��ļ�
	ATLASSERT (_openContext.get() == NULL);
}

/**
* ���á���ȡ�����õ�����
*/
void IFilePackage::setPassword (LPCTSTR password)
{
	_filePassword = password;
}

LPCTSTR IFilePackage::getPassword (void)
{
	return _filePassword;
}


/** 
* �Կɶ�ȡģʽ���ļ�
* @param [in] filePath	�ļ�·��
*/
void IFilePackage::open (LPCTSTR filePath)
{
	if (_openContext.get())
		throw new BwProj::Exception (_T("�ļ��Ѵ򿪣����ȹرա�"));

	// ���ļ�
	HANDLE handle = ::CreateFile (filePath, GENERIC_READ | GENERIC_WRITE,
						FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	if (handle == INVALID_HANDLE_VALUE)
		throw BwProj::Exception(CLibToolkit::GetWin32LastError());

	std::auto_ptr<OPENCONTEXT> context (new OPENCONTEXT ());
	context->fileHandle = handle;
	context->closeDeleteReadStream = TRUE;
	context->closeDeleteWriteStream = TRUE;
	context->readStream = NULL;
	context->writeStream = NULL;
	context->filename = filePath;

	CString errmsg;
	if (!_tryUpdateContext (context.get(), errmsg))
		throw BwProj::Exception (errmsg);

	context.release();
}

void IFilePackage::open (HANDLE fileHandle)
{
	if (_openContext.get())
		throw BwProj::Exception (_T("�ļ��Ѵ򿪣����ȹرա�"));

	std::auto_ptr<OPENCONTEXT> context (new OPENCONTEXT ());
	context->fileHandle = fileHandle;
	context->closeDeleteReadStream = TRUE;
	context->closeDeleteWriteStream = TRUE;
	context->readStream = NULL;
	context->writeStream = NULL;

	CString errmsg;
	if (!_tryUpdateContext (context.get(), errmsg))
		throw BwProj::Exception (errmsg);

	context.release();
}

/** 
* ��ֻ��ȡģʽ���ļ�
* @param [in] fileStream	�ļ���
*/
void IFilePackage::open (IRandomReadStream* fileStream)
{
	if (_openContext.get())
		throw BwProj::Exception (_T("�ļ��Ѵ򿪣����ȹرա�"));

	std::auto_ptr<OPENCONTEXT> context (new OPENCONTEXT ());
	context->fileHandle = NULL;
	context->closeDeleteReadStream = FALSE;
	context->closeDeleteWriteStream = TRUE;
	context->readStream = fileStream;
	context->writeStream = NULL;

	CString errmsg;
	if (_tryUpdateContext (context.get(), errmsg))
		throw BwProj::Exception (errmsg);

	context.release();
}

/** 
* �ر��ļ������������submit������в���
*/
void IFilePackage::close (void)
{
	if (_openContext.get())
	{
		if (_openContext->fileHandle)
			::CloseHandle(_openContext->fileHandle);

		if (_openContext->closeDeleteReadStream && _openContext->readStream)
			delete _openContext->readStream;

		if (_openContext->closeDeleteWriteStream && _openContext->writeStream)
			delete _openContext->writeStream;

		_openContext.reset();
	}
}

/**
* ���µ�ǰ�ļ������ģ����ļ��򿪺�����
* @param [in] context	�Ѵ��������úõ�������
*/
void IFilePackage::_updateContext (OPENCONTEXT* context)
{
	_openContext.reset(context);
}

/** ���Ե���_updateContext��������쳣����ͷ�context���� */
BOOL IFilePackage::_tryUpdateContext (OPENCONTEXT* context, CString& errmsg)
{
	try
	{
		_updateContext (context);
		return TRUE;
	}
	catch (BwProj::Exception& e)
	{
		if (context->fileHandle)
			::CloseHandle(context->fileHandle);

		if (context->closeDeleteReadStream && context->readStream)
			delete context->readStream;

		if (context->closeDeleteWriteStream && context->writeStream)
			delete context->writeStream;
		errmsg = e.what();
		return FALSE;
	}
}

void IFilePackage::submit(CString filename)
{
	CString filePath;
	if (filename.IsEmpty())	// δָ���ļ�
	{
		// ʹ��ԭ�ļ���
		if (_openContext->filename.IsEmpty())
		{
			throw BwProj::Exception (_T("δָ���ļ�·����"));
		}
		else
		{
			filePath = _openContext->filename;
		}
	}
	else // ָ�����ļ���
	{
		filePath = filename;
	}

	// ֻ�ܱ��浽�ļ���
	if (!_openContext->fileHandle)
		throw BwProj::Exception (_T("ȱ���ļ������"));

	CString tempPath = filePath;
	tempPath += _T(".") + CLibToolkit::CreateGuid ();
	_submit(tempPath);

	if (!CFileToolkit::FileExist(tempPath))
	{
		return;
	}

	close ();

	// Ŀ���ļ�����ʱ�����ȱ���Ŀ���ļ�
	CString fileBuckup = CString (filePath) + _T(".") + CLibToolkit::CreateGuid();
	if (CFileToolkit::FileExist(filePath))
	{
		CopyFile (filePath, fileBuckup, FALSE);
		DeleteFile(filePath);
	}


	CString errmsg;
	if (!MoveFile (tempPath, filePath))
	{
		errmsg = filePath + _T("����ʧ�ܣ�") + CLibToolkit::GetWin32LastError();

		// ��ԭ�ļ������´��ļ�
		MoveFile (fileBuckup, filePath);
	}
	::DeleteFile (tempPath);
	::DeleteFile (fileBuckup);

	// ȥ����������
	DWORD dwAttrs = GetFileAttributes(filePath); 
	SetFileAttributes(filePath, dwAttrs & ~FILE_ATTRIBUTE_HIDDEN);

	// ���´��ļ�
	open (filePath);

	if (!errmsg.IsEmpty())
	{
		throw BwProj::Exception(errmsg);
	}
}

/************************************************************************/
/* CEntryEnumeration                                                 */
/************************************************************************/
CEntryEnumeration::CEntryEnumeration ()
{
	_position = 0;
}

CEntryEnumeration::~CEntryEnumeration ()
{
	_entryList.RemoveAll();
}

BOOL CEntryEnumeration::hasMoreElements (void)
{
	return _position < _entryList.GetCount();
}

LPCFILEENTRY CEntryEnumeration::nextElement (void)
{
	if (_position >= _entryList.GetCount())
		return NULL;

	LPCFILEENTRY entry = _entryList[_position];
	_position ++;
	return entry;
}

CAtlArray<LPFILEENTRY>& CEntryEnumeration::getEntryList (void)
{
	return _entryList;
}
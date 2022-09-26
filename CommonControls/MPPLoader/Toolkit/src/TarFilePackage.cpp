#include "StdAfx.h"
#include "..\include\TarFilePackage.h"
#include "..\include\FileDataStream.h"
#include "..\include\MemoryDataStream.h"
#include "..\include\LibToolkit.h"
#include "..\include\FileToolkit.h"

using namespace BwProj::toolkit;

/** ��Դ���ʽ��ʶ */
#define TARFILE_HEADER_TEXTTAG		_T("BwProj Resource2 Database File")

/** ��Դ������������ */
#define TARFILE_PASSWORD_DEFAULT	_T("0x420\x6F0\x6F0\x770\x610\x790\x52")


/** ��ǰ�汾�� */
#define TARFILE_CURRENT_VERSION	0

CTarFilePackage::CTarFilePackage(DWORD submitFlags)
{
	_srcChanged = FALSE;
	_submitFlags = submitFlags;
	setPassword  (TARFILE_PASSWORD_DEFAULT);
	_initFileHeaderStruct (&_fileHeader);
}

CTarFilePackage::~CTarFilePackage (void)
{
	close ();
}

/** 
* �ر��ļ������������submit������в���
*/
void CTarFilePackage::close (void)
{
	// ɾ���ļ��б�
	for (size_t i = 0; i < _entryList.GetCount(); i ++)
		_deleteFileEntry(_entryList[i]);
	_entryList.RemoveAll();

	// ɾ�������ύ���ļ�
	for (size_t i = 0; i < _addEntry.GetCount(); i ++)
		_deleteFileEntry(_addEntry[i]);
	_addEntry.RemoveAll();

	if (_fileMapping.get())
	{
		_fileMapping.reset();
	}

	_srcChanged = FALSE;

	__super::close();
}

/**
* ȡ���ļ�ö�ٶ���
* @return	�����ļ�ö��
*/
EntryEnumeration_ptr CTarFilePackage::getEntries (void)
{
	CEntryEnumeration* enumeration = new CEntryEnumeration ();
	CAtlArray<LPFILEENTRY>&	saveList = enumeration->getEntryList();

	// �����Ѵ����ļ�
	saveList.RemoveAll();
	for (size_t i = 0; i < _entryList.GetCount(); i ++)
		saveList.Add(_entryList[i]);

	// ��������ӵ��ļ�
	for (size_t i = 0; i < _addEntry.GetCount(); i ++)
		saveList.Add(_addEntry[i]);

	return EntryEnumeration_ptr(enumeration);
}

/**
* ȡ�ð����ļ���Ϣ�������ִ�Сд��
* @param [in] name	�ļ�����
*/
LPCFILEENTRY CTarFilePackage::getEntry (LPCTSTR name)
{
	CString name2 (name);
	name2 = name2.MakeLower();

	EntryEnumeration_ptr list = getEntries();
	while (list->hasMoreElements ())
	{
		LPCFILEENTRY entry = list->nextElement();
		CString entry2 = entry->name;
		entry2 = entry2.MakeLower();

		if (name2 == entry2)
			return entry;
	}

	return NULL;
}

/**
* ����ļ������� 
* @param [in] name		�ļ�����
* @param [in] stream	��������ȡ����
*/
void CTarFilePackage::putNextEntry (LPCTSTR name, RandomReadStream_ptr stream)
{	
	// 2013.6.20 jxh �̳߳��Ż�
	CCriticalSectionSync sc(_CSC);
	
	ULONGLONG packageLength = calcPackageLength(); 
	if ((packageLength >= MAXDWORD) || (stream->GetLength() > (MAXDWORD - packageLength)))
		throw BwProj::Exception(_T("�ļ��Ѵﵽ��󳤶ȡ�"));

	if (_tcslen (name) >= MAX_PATH)
		throw BwProj::Exception(_T("�ļ����Ƴ�������ĳ��ȡ�"));

	// ��ɾ���Ѵ��ڵ��ļ�
	while (LPCFILEENTRY existEntry = getEntry (name))
	{
		removeEntry(existEntry);
	}

	// ��ӵ�����б�
	LPFILEENTRY entry = _newFileEntry (stream.release());
	_tcscpy_s(entry->name, MAX_PATH, name);
	_addEntry.Add(entry);
}

/**
* ɾ�����е��ļ� 
* @param [in] entry		�ļ�����
*/
void CTarFilePackage::removeEntry (LPCFILEENTRY entry)
{
	CAtlArray<LPFILEENTRY>* list = NULL;
	size_t index = 0;

	if (_findEntryInArray (entry, &list, &index))
	{
		_deleteFileEntry(list->GetAt(index));
		list->RemoveAt(index);

		// ���ԭ�ļ��ı�
		if (list == &_entryList)
			_srcChanged = TRUE;
	}
	else
	{
		throw BwProj::Exception (CString (entry->name) + _T(" �����ڡ�"));
	}
}

/**
* ȡ���ļ����� 
* @param [in] entry		�ļ�����
* @return �����ļ������������Ҫ�Լ�ɾ��
*/
RandomReadStream_ptr CTarFilePackage::getReadStream (LPCFILEENTRY entry)
{
	if (!_findEntryInArray (entry, NULL, NULL))
		throw BwProj::Exception (CString (entry->name) + _T(" �����ڡ�"));

	switch (entry->extendType)
	{
	case ENTRY_EXTEND_EXISTENTRY:
		{
			// ���ļ��ж�ȡ���ݵ��ڴ棬Ȼ���������ķ�ʽ����
			ENTRYHEADER* ze = (ENTRYHEADER*)entry->extendData;
			CMemoryDataReadStream* stream = NULL;

			// �����ת�����ڴ�������ȡָ��
			CMemoryDataReadStream* testStream =
				dynamic_cast<CMemoryDataReadStream*> (_openContext->readStream);

			if (testStream == NULL)
			{
				// ���ļ��ж�ȡ
				DWORD nBytesRead = 0;
				c_buffer_ptr buffer = c_buffer_ptr::alloc(ze->fileInfo.dataLength);
				_openContext->readStream->SetPosition(ze->fileInfo.dataOffset);
				_openContext->readStream->Read(buffer.get(), ze->fileInfo.dataLength, nBytesRead);

				if (_fileHeader.FileOptions & TARFILE_FLAGS_ENCRYPTDATA)
				{
					_encryptDataBuffer((LPBYTE) buffer.get(), buffer.length(),
						_filePassword, _filePassword.GetLength());
				}

				stream = new CMemoryDataReadStream (buffer);
			}
			else
			{
				// ���ڴ��ж�ȡ
				char* buffer = (char*)testStream->getOriginalBuffer();
				buffer += ze->fileInfo.dataOffset;

				if (_fileHeader.FileOptions & TARFILE_FLAGS_ENCRYPTDATA)
				{
					// Ϊ�����������·��仺����
					c_buffer_ptr bufptr = c_buffer_ptr::alloc(ze->fileInfo.dataLength);
					memcpy (bufptr.get(), buffer, ze->fileInfo.dataLength);

					_encryptDataBuffer((LPBYTE) bufptr.get(), bufptr.length(),
										_filePassword, _filePassword.GetLength());

					stream = new CMemoryDataReadStream (bufptr);
				}
				else
				{
					// ʹ��ԭʼ�ڴ���
					stream = new CMemoryDataReadStream (buffer, ze->fileInfo.dataLength);
				}
			}

			return RandomReadStream_ptr (stream);
		}
		break;
	case ENTRY_EXTEND_NEWSTREAM:
		{
			// ���������ж�ȡ���ݣ�ֻ֧���ڴ���
			CMemoryDataReadStream* stream = dynamic_cast<CMemoryDataReadStream*>
				((IDataReadStream*)entry->extendData);
			if (!stream)
			{
				throw BwProj::Exception (CString (entry->name) +
					_T("�����ڴ��У���ҪΪCMemoryDataReadStream���͵�ԭʼ���������ܶ�ȡ��"));
			}

			return RandomReadStream_ptr (new CMemoryDataReadStream(
									stream->getOriginalBuffer(), stream->GetLength()));
		}
		break;
	}

	return RandomReadStream_ptr();
}


void BwProj::toolkit::CTarFilePackage::_submit(CString tempPath)
{
	HANDLE tempHandle = ::CreateFile (tempPath, GENERIC_WRITE,
		FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN, NULL);
	if (tempHandle == INVALID_HANDLE_VALUE)
		throw BwProj::Exception(CLibToolkit::GetWin32LastError());

	// д���ļ�
	try
	{
		_submitToFile (tempHandle);
		CloseHandle(tempHandle);
	}
	catch (BwProj::Exception& e)
	{
		CloseHandle(tempHandle);
		DeleteFile (tempPath);
		throw BwProj::Exception (e);
	}	
}


/** �ѵ�ǰ�ļ�д�����ļ� */
void CTarFilePackage::_submitToFile (HANDLE handle)
{
	// ����Ҫд�����ݱ��С
	DWORD entryCount = 0;
	DWORD tableSizes = _calcDataTableLength (&entryCount);
	
	CFileDataWriteStream stream (handle);

	// д���ļ�ͷ��entry��Ϣ
	TARFILEHEADER tempHeader = { 0 };
	_initFileHeaderStruct(&tempHeader);
	tempHeader.DataTablesSize = tableSizes;
	tempHeader.DataTablesPos = sizeof(TARFILEHEADER);

	if (tempHeader.FileOptions & TARFILE_FLAGS_ENCRYPTTABLE)
	{
		_encryptDataBuffer((LPBYTE)&tempHeader, sizeof(TARFILEHEADER),
							_filePassword, _filePassword.GetLength());
	}

	stream.Write (&tempHeader, sizeof(TARFILEHEADER));

	CMemoryDataWriteStream listStream;
	EntryEnumeration_ptr list = getEntries();
	DWORD dataOffset = sizeof (TARFILEHEADER) + tableSizes;
	listStream.Write(&entryCount, sizeof (DWORD));	/**< д���ļ����� */
	while (list->hasMoreElements())
	{
		ENTRYHEADER entryHeader = { 0 };
		LPCFILEENTRY entry = list->nextElement();

		switch (entry->extendType)
		{
		case ENTRY_EXTEND_EXISTENTRY:
			{
				entryHeader = *(LPENTRYHEADER) entry->extendData;
			}
			break;
		case ENTRY_EXTEND_NEWSTREAM:
			{
				IRandomReadStream* newstream = (IRandomReadStream*) entry->extendData;
				entryHeader.fileInfo.dataLength = newstream->GetLength();
				entryHeader.fileInfo.nameLength = _tcslen (entry->name) + 1;
				_tcscpy_s(entryHeader.fileName, MAX_PATH, entry->name);
			}
			break;
		}

		entryHeader.fileInfo.dataOffset = dataOffset;
		listStream.Write(&entryHeader.fileInfo, sizeof (ENTRYINFO));
		listStream.Write(entryHeader.fileName, entryHeader.fileInfo.nameLength * sizeof(TCHAR));
		dataOffset += entryHeader.fileInfo.dataLength;
	}

	c_buffer_ptr listBuffer = c_buffer_ptr::alloc(listStream.GetLength());
	listStream.CopyBuffer(listBuffer.get());
	if (tempHeader.FileOptions & TARFILE_FLAGS_ENCRYPTTABLE)
	{
		_encryptDataBuffer((LPBYTE)listBuffer.get(), listBuffer.length(),
							_filePassword, _filePassword.GetLength());
	}
	stream.Write(listBuffer.get(), listBuffer.length());

	// д���ļ�����
	list = getEntries();
	c_buffer_ptr readBuffer = c_buffer_ptr::alloc(10240);
	while (list->hasMoreElements())
	{
		LPCFILEENTRY entry = list->nextElement();
		RandomReadStream_ptr readStream = getReadStream(entry);

		// LY 2014-04-29 �����������ߴ�������Ӧ���仺�������Խ��TARFILE_FLAGS_ENCRYPTDATAģʽ�����ڱ��������ʱ
		// ����_encryptDataBuffer�����������ݲ�������µ������ļ�����ʶ��BUG
		if (readBuffer.length() < entry->originalSize)
		{
			readBuffer = c_buffer_ptr::alloc(entry->originalSize);
		}

		DWORD nBytesRead = 0;
		while (readStream->Read(readBuffer.get(), entry->originalSize, nBytesRead))
		{
			if (!nBytesRead) break;
			if (tempHeader.FileOptions & TARFILE_FLAGS_ENCRYPTDATA)
			{
				_encryptDataBuffer((LPBYTE)readBuffer.get(), entry->originalSize,
									_filePassword, _filePassword.GetLength());
			}
			stream.Write(readBuffer.get(), nBytesRead);
		}
	}
}

/**
* ���µ�ǰ�ļ������ģ����ļ��򿪺�����
* @param [in] context	�Ѵ��������úõ�������
*/
void CTarFilePackage::_updateContext (OPENCONTEXT* context)
{
	// ������ļ����������
	std::auto_ptr<CTarFileMapping> fileMap;
	if (context->fileHandle && !context->readStream)
	{
		fileMap.reset(new CTarFileMapping ());
		if (fileMap->MapFile(context->fileHandle) == S_OK)
		{
			ULARGE_INTEGER liFileSize;
			liFileSize.LowPart = ::GetFileSize(context->fileHandle, &liFileSize.HighPart);

			context->readStream = new CMemoryDataReadStream ((char*)(*fileMap), liFileSize.LowPart);
			context->closeDeleteReadStream = TRUE;
		}
		else
		{
			context->readStream = new CFileDataReadStream (context->fileHandle);
			context->closeDeleteReadStream = TRUE;
		}
	}

	// Ҫ��������
	IRandomReadStream* stream = context->readStream;
	if (!stream)
		throw BwProj::Exception(_T("ȱ����������"));

	// ��ȡ�ļ�ͷ���ļ��б�
	TARFILEHEADER tempHeader = { 0 };
	if (stream->GetLength() >= sizeof (TARFILEHEADER))
	{
		DWORD nBytesRead = 0;
		stream->Read (&tempHeader, sizeof (TARFILEHEADER), nBytesRead);

		// ����ļ�ͷ��ʽ�Ƿ���ȷ(δ���ܸ�ʽ��ֱ�Ӷ�ȡ)
		if (_tcsicmp(tempHeader.HeaderTag, TARFILE_HEADER_TEXTTAG) != 0)
		{
			_encryptDataBuffer((LPBYTE)&tempHeader, sizeof(TARFILEHEADER),
								_filePassword, _filePassword.GetLength());
			if (_tcsicmp(tempHeader.HeaderTag, TARFILE_HEADER_TEXTTAG))
				throw BwProj::Exception (_T("�ļ�ͷУ�����"));
		}

		if (tempHeader.FileVersion > TARFILE_CURRENT_VERSION)
		{
			CString msg;
			msg.Format (_T("��֧�ָ߰汾��%d�����ļ���"), tempHeader.FileVersion);
			throw BwProj::Exception (msg);
		}

		memcpy (&_fileHeader, &tempHeader, sizeof (TARFILEHEADER));

		// ��ȡ�ļ���ͷ���ڴ�
		c_buffer_ptr buffer = c_buffer_ptr::alloc(tempHeader.DataTablesSize);
		stream->Read (buffer.get(), tempHeader.DataTablesSize, nBytesRead);

		if (tempHeader.FileOptions & TARFILE_FLAGS_ENCRYPTTABLE)
		{
			_encryptDataBuffer((LPBYTE)buffer.get(), buffer.length(),
								_filePassword, _filePassword.GetLength());
		}

		// ��ȡ�����ļ��б�
		_loadFileEntryList (buffer.get(), buffer.length());
	}

	if (fileMap.get())
	{
		_fileMapping.reset(fileMap.release());
	}

	__super::_updateContext (context);
}

/** ��ʹ���ļ�ͷ�ṹ */
void CTarFilePackage::_initFileHeaderStruct (TARFILEHEADER* header)
{
	memset (header, 0, sizeof (TARFILEHEADER));
	header->FileVersion = TARFILE_CURRENT_VERSION;
	header->FileOptions = _submitFlags;
	header->DataTablesSize = 0;
	header->DataTablesPos = sizeof(TARFILEHEADER);
	_tcscpy_s(header->HeaderTag, 30, TARFILE_HEADER_TEXTTAG);
}

/** �������ݣ�����Ҳ���ô˺��������������ĳ�����ͬ */
DWORD CTarFilePackage::_encryptDataBuffer(LPBYTE pDataBuffer,
						DWORD dwLength, LPCTSTR lpPasswrod, DWORD dwPwdLength)
{
	ATLASSERT(pDataBuffer != NULL && lpPasswrod != NULL);
	if (pDataBuffer == NULL || lpPasswrod == NULL || dwLength == 0 || dwPwdLength == 0)
	{
		ATLASSERT(FALSE);
		return 0;
	}

	for (DWORD i = 0, j = 0; i < dwLength; ++i,++j)
	{
		if (j > dwPwdLength)
			j = 0;

		pDataBuffer[i] ^= lpPasswrod[j];
	}

	return 0;
}

/** ��ȡ�����ļ��б� */
void CTarFilePackage::_loadFileEntryList(void* lpDatabaseBuffer, DWORD size)
{
	// ɾ��������
	for (size_t i = 0; i < _entryList.GetCount(); i ++)
		_deleteFileEntry(_entryList[i]);
	_entryList.RemoveAll();

	// ͷ4���ֽ�Ϊentry����
	CMemoryDataReadStream stream (lpDatabaseBuffer, size);
	DWORD nBytesRead = 0;

	DWORD entryCount = 0;
	stream.Read(&entryCount, sizeof (DWORD), nBytesRead);

	for (size_t i = 0; i < entryCount; ++i)
	{
		ENTRYHEADER entryHeader = { 0 };
		stream.Read(&entryHeader.fileInfo, sizeof (ENTRYINFO), nBytesRead);
		stream.Read(entryHeader.fileName, entryHeader.fileInfo.nameLength * sizeof(TCHAR), nBytesRead);

		_entryList.Add(_newFileEntry (&entryHeader));
	}
}

/** ����һ���ļ����� */
LPFILEENTRY CTarFilePackage::_newFileEntry (CTarFilePackage::LPENTRYHEADER zipentry)
{
	LPFILEENTRY fileentry = new FILEENTRY ();
	memset (fileentry, 0, sizeof (FILEENTRY));

	if (zipentry)
	{
		fileentry->extendType = ENTRY_EXTEND_EXISTENTRY;
		fileentry->extendData = ::malloc(sizeof (ENTRYHEADER));
		memcpy (fileentry->extendData, zipentry, sizeof (ENTRYHEADER));

		_tcscpy_s(fileentry->name, MAX_PATH, zipentry->fileName);
		fileentry->originalSize = zipentry->fileInfo.dataLength;
		fileentry->compressedSize = zipentry->fileInfo.dataLength;
	}

	return fileentry;
}

LPFILEENTRY CTarFilePackage::_newFileEntry (IRandomReadStream* stream)
{
	LPFILEENTRY fileentry = new FILEENTRY ();
	memset (fileentry, 0, sizeof (FILEENTRY));

	if (stream)
	{
		fileentry->extendType = ENTRY_EXTEND_NEWSTREAM;
		fileentry->extendData = stream;

		fileentry->originalSize = stream->GetLength();
	}

	return fileentry;
}

/** ɾ��һ���ļ����� */
void CTarFilePackage::_deleteFileEntry (LPFILEENTRY fileentry)
{
	if (fileentry->extendData)
	{
		switch (fileentry->extendType)
		{
		case ENTRY_EXTEND_EXISTENTRY:
			::free(fileentry->extendData);
			break;
		case ENTRY_EXTEND_NEWSTREAM:
			RandomReadStream_ptr stream ((IRandomReadStream*)fileentry->extendData);
			break;
		}
	}
	delete fileentry;
}

/** �������б��в����Ѵ��ڵĽ�� */
BOOL CTarFilePackage::_findEntryInArray (LPFILEENTRY find_entry,
										 CAtlArray<LPFILEENTRY>** save_ptr, size_t* save_idx)
{
	// �����Ѵ����ļ�
	for (size_t i = 0; i < _entryList.GetCount(); i ++)
	{
		if (_entryList[i] == find_entry)
		{
			if (save_ptr)
				*save_ptr = &_entryList;
			if (save_idx)
				*save_idx = i;
			return TRUE;
		}
	}

	// ��������ӵ��ļ�
	for (size_t i = 0; i < _addEntry.GetCount(); i ++)
	{
		if (_addEntry[i] == find_entry)
		{
			if (save_ptr)
				*save_ptr = &_addEntry;
			if (save_idx)
				*save_idx = i;
			return TRUE;
		}
	}

	return FALSE;
}

/** �����ļ��ܳ��� */
ULONGLONG CTarFilePackage::calcPackageLength (void)
{
	 ULONGLONG totalLength = sizeof (TARFILEHEADER) + _calcDataTableLength(NULL);
	 EntryEnumeration_ptr list = getEntries();
	 while (list->hasMoreElements())
	 {
		 LPCFILEENTRY entry = list->nextElement();

		 switch(entry->extendType)
		 {
		 case ENTRY_EXTEND_EXISTENTRY:
			 {
				LPENTRYHEADER entryHeader = (LPENTRYHEADER) entry->extendData;
				totalLength += entryHeader->fileInfo.dataLength;
			 }
			 break;
		 case ENTRY_EXTEND_NEWSTREAM:
			 {
				IRandomReadStream* newstream = (IRandomReadStream*) entry->extendData;
				totalLength += newstream->GetLength();
			 }
			 break;
		 }
	 }

	 return totalLength;
}

/** �������ݱ��� */
DWORD CTarFilePackage::_calcDataTableLength (DWORD* totalCount)
{
	DWORD tableSizes = sizeof (DWORD);
	DWORD entryCount = 0;
	EntryEnumeration_ptr list = getEntries();
	while (list->hasMoreElements())
	{
		LPCFILEENTRY entry = list->nextElement();
		tableSizes += sizeof (ENTRYINFO);
		tableSizes += (_tcslen (entry->name) + 1) * sizeof (TCHAR);	/**< ����\0������ */
		entryCount ++;
	}

	if (totalCount)
		*totalCount = entryCount;

	return tableSizes;
}


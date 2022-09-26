//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           XmdxDefines.H
//    @author         fanHong
//    @date           2017/11/3 11:21
//    @brief          Xmdx��д
//
//*****************************************************

#pragma once

#include "IDataStream.h"
#include "AllocMemoryPoolDef.h"

namespace CommBase
{
	//! ����xmdx�ļ��Ķ�д�����֧��MAXWORD����㣨65535��
	#pragma pack(push, 1)

	// xmdx �ļ�ͷ
	typedef struct
	{
		char	tag[5];			// �ļ���� XMDXHEADER_TAG
		BYTE	version;		// �汾��, 1,2,3����
		BYTE	encrypt;		// ���ܰ汾�ţ�0��ʾ������
		WORD	NodeCount;		// �������
		DWORD	ElementBytes;	// ��������ֽ���
		DWORD	NodeBytes;		// ����ֽ���
		DWORD	ElementAddress;	// ������ݿ�ʼ��ַ
		DWORD	NodeAddress;	// ��㿪ʼ��ַ
	}XMDXHEADER;

	#define XMDXHEADER_TAG "xmdx"
	#define	XMDXFILE_VERSION	1	// xmdx�ļ��汾��

	#define XMDXATTR_FLOAT		1	// ������
	#define XMDXATTR_DWORD		2	// ������
	#define XMDXATTR_WORD		3	// ������
	#define XMDXATTR_BYTE		4	// �ֽ���
	#define XMDXATTR_TEXT		5	// �ı���
	#define XMDXATTR_TEXTW		6	// Unicode�ı���
	#define XMDXATTR_BUFFER		7	// �ֽ���

	// �������
	typedef struct
	{
		char name[MAX_PATH];
		BYTE type;
		union
		{
			double	floatVal;
			DWORD	longVal;
			WORD	intVal;
			BYTE	byteVal;
			char*	textVal;
			WCHAR*	wTextVal;
			BYTE*	bufferVal;
		};
	}XMDXATTR, *LPXMDXATTR;

	// д���ļ��Ľ������ֵ
	typedef struct
	{
		BYTE	type;		// �������
		WORD	nameLen;	// ���Ƴ���
		WORD	valueLen;	// ֵ����
		WORD	datOffset;	// ����ƫ����
	}XMDXATTRHEADER, *LPXMDXATTRHEADER;

	// ����ڴ���Ϣ
	typedef struct
	{
		DWORD	elementBytes;	// ������ֽ���
		BYTE	attrCount;		// �ܹ���������
	}XMDXELMTINFO, *LPXMDXELMTINFO;

	// xmdx���
	typedef struct
	{
		WORD			index;			// ���������Ϊ0��ʾ�����
		WORD			parent;			// �����������indexΪ0ʱparent������
		WORD			nextSibling;	// ��һ�ֵܽ�㣬Ϊ0��ʾû��
		WORD			firstChildren;	// �洢��һ���ӽ���������Ϊ0��ʾ���ӽ��
		WORD			lastChildren;	// �洢�����ӽ���������Ϊ0��ʾ���ӽ��

		XMDXELMTINFO	entryInfo;		// ���ֵ��Ϣ
		DWORD			entryAddress;	// ��������ļ��е����ݵ�ַ > 0
	}XMDXNODE, *LPXMDXNODE;

	// ���ڲ��ҵĽ��
	typedef struct
	{
		LPXMDXNODE	parent;		// ���ҽ��ĸ����
		WORD		index;		// ��ǰ������Ĭ��Ϊ0
	}XMDXFIND, *LPXMDXFIND;

	#pragma pack(pop)

	typedef LPXMDXNODE XMDXHANDLE;
	typedef LPXMDXFIND FINDHANDLE;

	class COMMBASE_API IXmdxDocumentWriter;
	class COMMBASE_API IXmdxDocumentReader;

	/*
	*	��������Ҫ�������Բ�������
	*
	*	�ڵ������ڵ�ֵ��������ֻ֧��ʹ��ANSI�ַ���
	*	�ַ������͵�����ֵͬʱ֧��ANSI��Unicode��������������ֵʱ����Ĳ��������Զ��ж�
	*/
	class COMMBASE_API IXmdxElementWriter
	{
	public:
		virtual ~IXmdxElementWriter()
		{
		}

		// ȡ�ù������
		virtual XMDXHANDLE getNode() = 0;

		// ȡ�ù������ļ�д����
		virtual IXmdxDocumentWriter* getWriter() = 0;

		// ��д����
		virtual LPCSTR getName() = 0;
		virtual void setName(LPCSTR name) = 0;

		// ��д���ֵ
		virtual LPVOID getValue(size_t* readBytes = 0) = 0;
		virtual void setValue(LPCSTR value, size_t length) = 0;

		// ��������ֵ
		virtual BOOL addAttrText(LPCSTR name, LPCSTR value) = 0;	// XMDXATTR_TEXT
		virtual BOOL addAttrText(LPCSTR name, LPCWSTR value) = 0;	// XMDXATTR_TEXTW
		virtual BOOL addAttrDouble(LPCSTR name, double value) = 0;	// XMDXATTR_FLOAT
		virtual BOOL addAttrLong(LPCSTR name, DWORD value) = 0;	// XMDXATTR_DWORD
		virtual BOOL addAttrShort(LPCSTR name, WORD value) = 0;	// XMDXATTR_WORD
		virtual BOOL addAttrByte(LPCSTR name, BYTE value) = 0;		// XMDXATTR_BYTE
		virtual BOOL addAttrBuffer(LPCSTR name, byte* value, int length) = 0;	// XMDXATTR_BUFFER

		// ��д�������												   
		virtual BOOL write(IRandomWriteStream* stream) = 0;
	};

	/*
	*	��������Ҫ�������Բ�������
	*/
	class COMMBASE_API IXmdxElementReader
	{
	public:
		virtual ~IXmdxElementReader()
		{
		}

		// ȡ�ù������
		virtual XMDXHANDLE getNode() = 0;

		// ȡ�ù������ļ�������
		virtual IXmdxDocumentReader* getReader() = 0;

		// ��д����
		virtual LPCSTR getName() = 0;

		// ��д���ֵ
		virtual size_t getValueLength() = 0;
		virtual LPCSTR getValue() = 0;

		virtual size_t getAttrCount() = 0;
		virtual LPCSTR getAttrName(int index) = 0;
		virtual BYTE getAttrType(int index) = 0;

		// ȡ����ֵ
		virtual BOOL getAttrValue(int index, LPXMDXATTR attr) = 0;

		// �÷�������������ת����ָ��name������ֵ����XMDXATTR_TEXTʱ����defVal
		virtual LPCSTR getAttrTextA(LPCSTR name, LPCSTR defVal = "") = 0;

		// �÷�������������ת����ָ��name������ֵ����XMDXATTR_TEXTWʱ����defVal
		virtual LPCWSTR getAttrTextW(LPCSTR name, LPCWSTR defVal = L"") = 0;

		// �÷������������ת�����������;�����double����
		virtual double getAttrDouble(LPCSTR name, double defVal = 0.0) = 0;

		// �÷������������ת�����������;�����DWORD����
		virtual DWORD getAttrLong(LPCSTR name, DWORD defVal = 0) = 0;

		// �÷������������ת�����������;�����WORD����
		virtual WORD getAttrShort(LPCSTR name, WORD defVal = 0) = 0;

		// �÷������������ת�����������;�����BYTE����
		virtual BYTE getAttrByte(LPCSTR name, BYTE defVal = 0) = 0;

		// �÷�������������ת����ָ��name������ֵ����XMDXATTR_BUFFERʱ����defVal
		virtual byte* getAttrBuffer(LPCSTR name, int &length, byte* defVal = 0) = 0;

		// ��д�������
		virtual BOOL read(IRandomReadStream* stream) = 0;
	};

	/*
	*	����xmdx�ĵ�
	*/
	class COMMBASE_API IXmdxDocumentWriter
	{
	public:
		virtual ~IXmdxDocumentWriter()
		{
		}

		// ȡ��root���
		virtual IXmdxElementWriter* rootElement() = 0;

		// ������һ���½��
		virtual IXmdxElementWriter* newElement(IXmdxElementWriter* parent, LPCSTR name) = 0;

		virtual void freeElement(IXmdxElementWriter* element) = 0;

		// д��һ�����������Դ
		virtual size_t writeElement(IXmdxElementWriter* element) = 0;

		// �ر��ļ�
		virtual void close() = 0;

		virtual LPCTSTR getLastError() = 0;

		// ȡ���ڴ��
		virtual IAllocMemoryPool* getMemoryPool() = 0;

		// ȡ�ýڵ�����
		virtual size_t GetNodeCount() = 0;
	};

	/*
	*	��ȡxmdx�ĵ�
	*/
	class COMMBASE_API IXmdxDocumentReader
	{
	public:
		virtual ~IXmdxDocumentReader()
		{
		}

		// ȡ��root���
		virtual XMDXHANDLE rootNode() = 0;

		// �����ж�ȡһ������
		virtual IXmdxElementReader* readElement(XMDXHANDLE handle) = 0;

		virtual void freeElement(IXmdxElementReader* element) = 0;

		// ���ҽ��ĵ�һ���ӽ��
		virtual FINDHANDLE findFirstChild(XMDXHANDLE parent, XMDXHANDLE* findNode) = 0;

		// ���ҽ�����һ���ӽ��
		virtual BOOL findNextChild(FINDHANDLE handle, XMDXHANDLE* findNode) = 0;

		// �رղ��Ҿ��
		virtual void closeFindHandle(FINDHANDLE handle) = 0;

		// �رն�ȡ�ļ�
		virtual void close() = 0;

		virtual LPCTSTR getLastError() = 0;

		// ȡ���ڴ��
		virtual IAllocMemoryPool* getMemoryPool() = 0;
	};

	/*
	*	xmdx����洢�ӿ�
	*/
	class COMMBASE_API IXmdxStorage
	{
	public:
		virtual ~IXmdxStorage()
		{
		}

		virtual void loadXmdxStorage(IXmdxElementReader* element) = 0;
		virtual void saveXmdxStorage(IXmdxElementWriter* element) = 0;
	};
}
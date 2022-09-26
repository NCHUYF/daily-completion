//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           XmdxElement.H
//    @author         fanHong
//    @date           2017/11/3 11:29
//    @brief          XmdxԪ��
//
//*****************************************************

#pragma once

#include "XmdxDefines.h"
#include <atlcoll.h>

namespace CommBase
{
	/*
	*	��������Ҫ�������Բ�������
	*/
	class COMMBASE_API CXmdxElementWriter : public IXmdxElementWriter
	{
	public:
		CXmdxElementWriter();
		virtual ~CXmdxElementWriter();

		// ȡ�ù������
		void setNode(XMDXHANDLE node);
		virtual XMDXHANDLE getNode();

		// ȡ�ù������ļ�д����
		void setWriter(IXmdxDocumentWriter* writer);
		virtual IXmdxDocumentWriter* getWriter();

		// ��д����
		virtual LPCSTR getName();
		virtual void setName(LPCSTR name);

		// ��д���ֵ
		virtual LPVOID getValue(size_t* readBytes);
		virtual void setValue(LPCSTR value, size_t length);

		// ��������ֵ
		virtual BOOL addAttrText(LPCSTR name, LPCSTR value);
		virtual BOOL addAttrText(LPCSTR name, LPCWSTR value);
		virtual BOOL addAttrDouble(LPCSTR name, double value);
		virtual BOOL addAttrLong(LPCSTR name, DWORD value);
		virtual BOOL addAttrShort(LPCSTR name, WORD value);
		virtual BOOL addAttrByte(LPCSTR name, BYTE value);
		virtual BOOL addAttrBuffer(LPCSTR name, byte* value, int length);

		// ��д�������
		virtual BOOL write(IRandomWriteStream* stream);

		void clear();

	protected:
		// д���ַ���
		BOOL _writeText(IDataWriteStream* stream, LPCSTR text);

		// ��������Ѵ�����ֱ�ӷ��أ��������һ���µ�
		LPXMDXATTR _resetOrAddAttr(LPCSTR name);

		// �����ڴ�
		__inline LPVOID _malloc(size_t size, size_t nGrowBy);
		__inline void _free(LPVOID buffer);

	protected:
		IXmdxDocumentWriter*	_writer;
		XMDXHANDLE				_attachNode;

		LPVOID					_value;
		WORD					_valLength;

		char					_name[MAX_PATH];
		CAtlArray<LPXMDXATTR>	_attrArray;
	};

	/*
	*	��������Ҫ�������Բ�������
	*/
	class COMMBASE_API CXmdxElementReader : public IXmdxElementReader
	{
	public:
		CXmdxElementReader();
		virtual ~CXmdxElementReader();

		// ȡ�ù������
		void setNode(XMDXHANDLE node);
		virtual XMDXHANDLE getNode();

		// ȡ�ù������ļ�������
		void setReader(IXmdxDocumentReader* reader);
		virtual IXmdxDocumentReader* getReader();

		// ��д����
		virtual LPCSTR getName();

		// ��д���ֵ
		virtual size_t getValueLength();
		virtual LPCSTR getValue();

		virtual size_t getAttrCount();
		virtual LPCSTR getAttrName(int index);
		virtual BYTE getAttrType(int index);

		// ȡ����ֵ
		virtual BOOL getAttrValue(int index, LPXMDXATTR attr);
		virtual LPCSTR getAttrTextA(LPCSTR name, LPCSTR defVal = "");
		virtual LPCWSTR getAttrTextW(LPCSTR name, LPCWSTR defVal = L"");
		virtual double getAttrDouble(LPCSTR name, double defVal = 0.0);
		virtual DWORD getAttrLong(LPCSTR name, DWORD defVal);
		virtual WORD getAttrShort(LPCSTR name, WORD defVal);
		virtual BYTE getAttrByte(LPCSTR name, BYTE defVal);
		virtual byte* getAttrBuffer(LPCSTR name, int &length, byte* defVal = 0);

		// ��д�������
		virtual BOOL read(IRandomReadStream* stream);

		void clear();

	protected:
		// ȡ��ָ�����������Ե����Ƽ�ֵ
		__inline void _lookupAttr(int index, LPCSTR* namePtr, LPCSTR* valuePtr);
		void _lookupAttr(int index, LPXMDXATTR findAttr);
		BOOL _lookupAttr(LPCSTR name, LPXMDXATTR findAttr);

	protected:
		IXmdxDocumentReader*	_reader;
		XMDXHANDLE				_attachNode;

		LPCSTR					_buffer;

		LPCSTR					_name;			// ���Ƽ�����
		WORD					_nameLength;
		LPCSTR					_value;			// ֵ������
		WORD					_valLength;

		LPXMDXATTRHEADER		_attrHeadEntry;	// ����ͷ��ʼ��ַ
		LPCSTR					_attrValueEntry;// ����ֵ��ʼ��ַ
	};
}
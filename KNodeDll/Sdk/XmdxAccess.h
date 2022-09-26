//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           XmdxDefines.H
//    @author         fanHong
//    @date           2017/11/3 11:21
//    @brief          XMDX������
//					  �ڵ������ڵ�ֵ��������ֻ֧��ʹ��ANSI�ַ���
//					  �ַ������͵�����ֵͬʱ֧��ANSI��Unicode��������������ֵʱ����Ĳ��������Զ��ж�
//
//*****************************************************

#pragma once

#include "XmdxDefines.h"
#include "Type/Any.h"
#include "XmdxDocument.h"
#include "FileDataStream.h"
#include "Type/KNode.h"

namespace CommBase
{
	/**
	*  @class    XMD�ڵ�д�������Զ������ͷ�
	*
	*  @brief
	*/
	class COMMBASE_API CXmdxElmWriter
	{
	public:
		CXmdxElmWriter();

		CXmdxElmWriter(IXmdxElementWriter* pWriter);

		CXmdxElmWriter(CXmdxElmWriter& pElmWriter);

		~CXmdxElmWriter();

		CXmdxElmWriter& operator =(CXmdxElmWriter& pElmWriter);

		IXmdxElementWriter* Get();

		// ���ڴ����ӽڵ�ʱ����
		IXmdxElementWriter* Detach();

		// �½��ӽڵ�
		CXmdxElmWriter NewElement(LPCSTR name = NULL);

		// ��дԪ������
		LPCSTR GetName();
		void SetName(LPCSTR name);

		// ��дԪ��ֵ
		LPCSTR GetValue();
		void SetValue(LPCSTR value);

		// ��������ֵ
		bool AddTextAttr(LPCSTR name, LPCSTR value);	// XMDXATTR_TEXT
		bool AddTextAttr(LPCSTR name, LPCWSTR value);	// XMDXATTR_TEXTW
		bool AddDoubleAttr(LPCSTR name, double value);	// XMDXATTR_FLOAT
		bool AddIntAttr(LPCSTR name, int value);		// XMDXATTR_DWORD
		bool AddShortAttr(LPCSTR name, short value);	// XMDXATTR_WORD
		bool AddByteAttr(LPCSTR name, BYTE value);		// XMDXATTR_BYTE
		bool AddAttrBuffer(LPCSTR name, BYTE* value, int length);	// XMDXATTR_BUFFER
		bool AddVariantAttr(LPCSTR name, const CAny& varData);
		bool AddGuidAttr(LPCSTR name, const CGuid& guid);

	public:
		void Submit();

	protected:
		IXmdxElementWriter*	_element;
	};

	//XMD�ڵ��ȡ�����Զ������ͷ�
	class COMMBASE_API CXmdxElmReader
	{
	public:
		CXmdxElmReader();
		CXmdxElmReader(IXmdxElementReader* pReader);
		CXmdxElmReader(CXmdxElmReader& elmReader);
		CXmdxElmReader(CXmdxDocumentReader& docReader);

		~CXmdxElmReader();

		CXmdxElmReader& operator =(CXmdxElmReader& pElmReader);
		IXmdxElementReader* Get();

		// ���ڴ����ӽڵ�ʱ����
		IXmdxElementReader* Detach();
		bool IsNone();

		// ������Ԫ��, û�в��ҵ�ʹ��IsNone�ж�
		CXmdxElmReader FindChildElement(LPCSTR name);

		// ��Ԫ������
		LPCSTR GetName();

		// ��Ԫ��ֵ
		LPCSTR GetValue();

		// ��Ԫ������ֵ
		int GetAttrCount();
		LPCSTR GetAttrName(int index);
		BYTE GetAttrType(int index);

		// ��ȡ����������������ʱ����-1
		int GetAttrIndex(LPCSTR name);

		// ͨ��������ȡ����ֵ������������ת��
		LPCSTR GetTextAttrA(int index, LPCSTR defVal = "");		// XMDXATTR_TEXT
		LPCWSTR GetTextAttrW(int index, LPCWSTR defVal = L"");		// XMDXATTR_TEXTW
		double GetDoubleAttr(int index, double defVal = 0.0);		// XMDXATTR_FLOAT
		int GetIntAttr(int index, DWORD defVal = 0);				// XMDXATTR_DWORD
		short GetShortAttr(int index, short defVal = 0);			// XMDXATTR_WORD
		BYTE GetByteAttr(int index, BYTE defVal = 0);				// XMDXATTR_BYTE
		BYTE* GetAttrBuffer(int index, int &length, BYTE* defVal = 0);
		CGuid GetAttrGuid(int index, const CGuid& defVal = CGuid());
		CAny GetAttrVariant(int index, const CAny& defVal = CAny());

		// ͨ����������ȡ����ֵ�����Զ���������ת��
		CString GetTextAttr(LPCSTR name, const CString& defVal = _T(""));
		double GetDoubleAttr(LPCSTR name, double defVal = 0.0);
		int GetIntAttr(LPCSTR name, DWORD defVal = 0);
		short GetShortAttr(LPCSTR name, short defVal = 0);
		BYTE GetByteAttr(LPCSTR name, BYTE defVal = 0);
		BYTE* GetAttrBuffer(LPCSTR name, int &length, BYTE* defVal = 0);
		CGuid GetAttrGuid(LPCSTR name, const CGuid& defVal = CGuid());

	public:
		void Submit();

	protected:
		IXmdxElementReader* _element;
	};

	class COMMBASE_API CXmdxElmFind
	{
	public:
		CXmdxElmFind(CXmdxElmReader& parentReader);
		~CXmdxElmFind();

		bool FindNext();

		// ������1��ʼ
		WORD NextIndex();
		CXmdxElmReader* operator->();

		// �����ָ�룬��Ҫ�ֶ��ͷ�,���ô˷������ٵ���->����Ч
		IXmdxElementReader* DetachReader();

	protected:
		WORD _index;
		FINDHANDLE _handle;
		XMDXHANDLE _pParentElm;
		IXmdxDocumentReader* _pDocReader;
		CXmdxElmReader _xmdReader;
	};

	class COMMBASE_API ILargXmdxSave
	{
	public:
		virtual ~ILargXmdxSave()
		{
		}

		/**
		*  @brief    ȡ�ýڵ�
		*
		*  @return   IXmdxElementWriter* xmdx�ڵ�
		*			 �ڵ��ô˷���ʱ��Ҫ��֤��һ�εĽڵ������submit
		*/
		virtual IXmdxElementWriter* GetWriter() = 0;

		/**
		*  @brief    �ر��ĵ�����
		*
		*/
		virtual void CloseXmdxDocument() = 0;

		/**
		*  @brief    ��ȡ��ǰ��¼����
		*
		*/
		virtual UINT CurRecordIndex() = 0;
	};

	/**
	*	@class	CLargXmdxFileSave
	*
	*	@brief �����ļ��洢��С�Զ��ָ�ɶ��С�ļ�
	*		   �������������δ洢��ÿ��С�ļ��еĸ��ڵ�����
	*/
	class COMMBASE_API CLargXmdxFileSave : public ILargXmdxSave
	{
	public:
		/**
		*  @brief    ���캯��
		*
		*/
		CLargXmdxFileSave(const CString& strFile);

		/**
		*  @brief    ��������
		*
		*/
		~CLargXmdxFileSave();

	public:
		/**
		*  @brief    ȡ�ýڵ�
		*
		*  @return   IXmdxElementWriter* xmdx�ڵ�
		*			 �ڵ��ô˷���ʱ��Ҫ��֤��һ�εĽڵ������submit
		*/
		IXmdxElementWriter* GetWriter();

		/**
		*  @brief    �ر��ĵ�����
		*
		*/
		void CloseXmdxDocument();

		/**
		*  @brief    ��ȡ��ǰ��¼����
		*
		*/
		UINT CurRecordIndex();

	protected:
		/**
		*  @brief    �����ĵ�����
		*
		*/
		bool CreateXmdxDocument();

		/**
		*  @brief    ����־��ļ�
		*
		*/
		void ClearVolumeFiles();

	protected:
		UINT					_nVulume;
		CString					_strDir;
		CString					_strBaseName;
		CString					_strExtName;
		CAtlFile				*_pFile;
		CFileDataWriteStream	*_pStream;
		CXmdxDocumentWriter		*_pXmdxDoc;
		UINT					_nRecordIdx;
	};

	/**
	*	@class	CLargXmdxMemSave
	*
	*/
	class COMMBASE_API CLargXmdxMemSave : public ILargXmdxSave
	{
	public:
		/**
		*  @brief    ���캯��
		*
		*/
		CLargXmdxMemSave(const CString& strFile);

		/**
		*  @brief    ��������
		*
		*/
		~CLargXmdxMemSave();

	public:
		/**
		*  @brief    ȡ�ýڵ�
		*
		*  @return   IXmdxElementWriter* xmdx�ڵ�
		*			 �ڵ��ô˷���ʱ��Ҫ��֤��һ�εĽڵ������submit
		*/
		IXmdxElementWriter* GetWriter();

		/**
		*  @brief    �ر��ĵ�����
		*
		*/
		void CloseXmdxDocument();

		/**
		*  @brief    ��ȡ��ǰ��¼����
		*
		*/
		UINT CurRecordIndex();

	protected:
		/**
		*  @brief    ����־��ļ�
		*
		*/
		void ClearVolumeFiles();

		/**
		*  @brief    �����ĵ�����
		*
		*/
		bool CreateXmdxDocument();

	protected:
		UINT					_nVulume;
		CString					_strDir;
		CString					_strBaseName;
		CString					_strExtName;
		FileMWriteDataArray		_memDataAray;
		CXmdxDocumentWriter		*_pXmdxDoc;
		UINT					_nRecordIdx;
	};

	class COMMBASE_API ILargXmdxLoad
	{
	public:
		virtual ~ILargXmdxLoad()
		{
		}

		/**
		*  @brief    ȡ�ø��ڵ�
		*
		*  @return   IXmdxElementReader* xmdx�ڵ�
		*			 �ڵ��ô˷���ʱ��Ҫ��֤��һ�εĽڵ������submit
		*/
		virtual IXmdxElementReader* GetReader() = 0;

		/**
		*  @brief    �ر��ĵ�����
		*
		*/
		virtual void CloseXmdxDocument() = 0;
	};

	/**
	*	@class	CLargXmdxFileLoad
	*
	*	@brief �����ļ��洢��С�Զ��ָ�ɶ��С�ļ�
	*		   �������������δӵ�ÿ��С�ļ��еĸ��ڵ������ȡ
	*/
	class COMMBASE_API CLargXmdxFileLoad : public ILargXmdxLoad
	{
	public:
		/**
		*  @brief    ���캯��
		*
		*/
		CLargXmdxFileLoad(const CString& strFile);

		/**
		*  @brief    ��������
		*
		*/
		~CLargXmdxFileLoad();

	public:
		/**
		*  @brief    ȡ�ø��ڵ�
		*
		*  @return   IXmdxElementReader* xmdx�ڵ�
		*			 �ڵ��ô˷���ʱ��Ҫ��֤��һ�εĽڵ������submit
		*/
		IXmdxElementReader* GetReader();

		/**
		*  @brief    �ر��ĵ�����
		*
		*/
		void CloseXmdxDocument();

	protected:
		/**
		*  @brief    ���ĵ�����
		*
		*/
		bool OpenXmdxDocument();

	protected:
		UINT					_nVulume;
		CString					_strDir;
		CString					_strBaseName;
		CString					_strExtName;
		CAtlFile				*_pFile;
		CFileDataReadStream		*_pStream;
		CXmdxDocumentReader		*_pXmdxDoc;
		FINDHANDLE				_pXmdxFind;
	};

	/**
	*	@class	CLargXmdxMemLoad
	*
	*/
	class COMMBASE_API CLargXmdxMemLoad : public ILargXmdxLoad
	{
	public:
		/**
		*  @brief    ���캯��
		*
		*/
		CLargXmdxMemLoad(const CString& strFile);

		/**
		*  @brief    ��������
		*
		*/
		~CLargXmdxMemLoad();

	public:
		/**
		*  @brief    ȡ�ø��ڵ�
		*
		*  @return   IXmdxElementReader* xmdx�ڵ�
		*			 �ڵ��ô˷���ʱ��Ҫ��֤��һ�εĽڵ������submit
		*/
		IXmdxElementReader* GetReader();

		/**
		*  @brief    �ر��ĵ�����
		*
		*/
		void CloseXmdxDocument();

	protected:
		/**
		*  @brief    ���ĵ�����
		*
		*/
		bool OpenXmdxDocument();

	protected:
		UINT					_nVulume;
		CString					_strDir;
		CString					_strBaseName;
		CString					_strExtName;
		FileMReadDataArray		_memDataAray;
		CXmdxDocumentReader		*_pXmdxDoc;
		FINDHANDLE				_pXmdxFind;
	};
}
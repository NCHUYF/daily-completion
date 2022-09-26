//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           XmdxDocument.H
//    @author         fanHong
//    @date           2017/11/3 11:22
//    @brief          Xmdx�ĵ�
//
//*****************************************************

#pragma once

#include "XmdxElement.h"
#include "ObjectFastNew.h"
#include "AllocMemoryPool.h"

namespace CommBase
{
	/*
	*	����б����ڱ������н����Ϣ
	*/
	class CXmdxNodeList
	{
	public:
		CXmdxNodeList();
		~CXmdxNodeList();
		BOOL getNewNode(LPXMDXNODE* nodePtr);
		size_t getCount();
		LPXMDXNODE getAt(size_t nIndex);
		XMDXNODE& operator[] (size_t nIndex);
		void clear();

	protected:
		CAtlArray<LPXMDXNODE>	_nodeListArray;
		size_t					_length;
		size_t					_blockSize;
		size_t					_maxnodes;
	};

	/*
	 *	����xmdx�ĵ�
	 */
	class COMMBASE_API CXmdxDocumentWriter : public IXmdxDocumentWriter
	{
	public:
		CXmdxDocumentWriter(IRandomWriteStream* file);
		~CXmdxDocumentWriter();

		// ȡ��root���
		virtual IXmdxElementWriter* rootElement();

		// ������һ���½��
		virtual IXmdxElementWriter* newElement(IXmdxElementWriter* parent, LPCSTR name);

		// д��һ�����������Դ
		virtual size_t writeElement(IXmdxElementWriter* element);

		virtual void freeElement(IXmdxElementWriter* element);

		// �ر��ļ�
		virtual void close();

		virtual LPCTSTR getLastError();

		// ȡ���ڴ��
		virtual IAllocMemoryPool* getMemoryPool();

		/**
		*  @brief    ȡ�ýڵ�����
		*
		*  @return   size_t �ڵ�������
		*/
		virtual size_t GetNodeCount();

	protected:
		IRandomWriteStream*	_file;
		CXmdxNodeList		_nodes;
		IXmdxElementWriter*	_root;
		CString				_lastError;

		XMDXHEADER			_header;
		DWORD				_headerAddress;

		CAllocMemoryPool	_memoryPool;

		CObjectFastNew<CXmdxElementWriter>	_ElementFactory;

	};

	/*
	 *	��ȡxmdx�ĵ�
	 */
	class COMMBASE_API CXmdxDocumentReader : public IXmdxDocumentReader
	{
	public:
		CXmdxDocumentReader(IRandomReadStream* file);
		~CXmdxDocumentReader();

		// ȡ��root���
		virtual XMDXHANDLE rootNode();

		// �����ж�ȡһ������
		virtual IXmdxElementReader* readElement(XMDXHANDLE handle);

		virtual void freeElement(IXmdxElementReader* element);

		// ���ҽ��ĵ�һ���ӽ��
		virtual FINDHANDLE findFirstChild(XMDXHANDLE parent, XMDXHANDLE* findNode);

		// ���ҽ�����һ���ӽ��
		virtual BOOL findNextChild(FINDHANDLE handle, XMDXHANDLE* findNode);

		// �رղ��Ҿ��
		virtual void closeFindHandle(FINDHANDLE handle);

		// �رն�ȡ�ļ�
		virtual void close();

		virtual LPCTSTR getLastError();

		// ȡ���ڴ��
		virtual IAllocMemoryPool* getMemoryPool();

		// ȡ��ָ������������
		LPVOID getElementBuffer(XMDXHANDLE handle);

		// ȡ�ø��ڵ��ȡ��
		IXmdxElementReader* rootElement();

	protected:
		IRandomReadStream*	_file;

		XMDXHEADER			_header;		/**< �ļ�ͷ */

		LPXMDXNODE			_nodes;			/**< ���ͷ */
		LPBYTE				_elements;		/**< ������� */
		BOOL				_closeFreeNodes;/**< �ر�ʱ�Ƿ��ͷ� _nodes��_elements */

		CString				_lastError;
		CAllocMemoryPool	_memoryPool;

		CObjectFastNew<CXmdxElementReader>	_ElementFactory;
		CObjectFastNew<XMDXFIND>			_FindHanleFactory;
	};
}
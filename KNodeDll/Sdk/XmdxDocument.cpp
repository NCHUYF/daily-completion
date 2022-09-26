#include "StdAfx.h"
#include "XmdxDocument.h"
#include "../Sdk/MemoryDataStream.h"

namespace CommBase
{
	/************************************************************************/
	/* CXmdxNodeList                                                        */
	/************************************************************************/
	/*
	*	����б����ڱ������н����Ϣ
	*/
	CXmdxNodeList::CXmdxNodeList()
	{
		_blockSize = 512;	// sizeof(XMDXNODE)*512 = 5K
		_length = 0;
		_maxnodes = 0;
		_nodeListArray.SetCount(0, int(_blockSize));
	}

	CXmdxNodeList::~CXmdxNodeList()
	{
		clear();
	}

	BOOL CXmdxNodeList::getNewNode(LPXMDXNODE* nodePtr)
	{
		// �����µ�����
		if (_length >= _maxnodes)
		{
			size_t newBytes = sizeof(XMDXNODE) *_blockSize;
			LPXMDXNODE nodeArray = (LPXMDXNODE) ::malloc(newBytes);
			memset(nodeArray, NULL, newBytes);

			_nodeListArray.Add(nodeArray);
			_maxnodes += _blockSize;
		}
		else
		{
			//TODO: ���Բ�����������������getAt�ӿ��ٶ�
		}

		// ����ֵ
		LPXMDXNODE node = getAt(_length);
		node->index = WORD(_length);
		*nodePtr = node;

		_length++;
		return TRUE;
	}

	size_t CXmdxNodeList::getCount()
	{
		return _length;
	}

	LPXMDXNODE CXmdxNodeList::getAt(size_t nIndex)
	{
		size_t arrIndex = nIndex / _blockSize;
		size_t posIndex = nIndex - arrIndex * _blockSize;

		LPXMDXNODE nodeArray = _nodeListArray[arrIndex];
		return &nodeArray[posIndex];
	}

	XMDXNODE& CXmdxNodeList::operator[] (size_t nIndex)
	{
		return *getAt(nIndex);
	}

	void CXmdxNodeList::clear()
	{
		for (size_t i = 0; i < _nodeListArray.GetCount(); i++)
		{
			::free(_nodeListArray[i]);
		}
		_nodeListArray.RemoveAll();

		_length = 0;
		_maxnodes = 0;
	}
	/************************************************************************/
	/* CXmdxDocumentWriter                                                          */
	/************************************************************************/
	CXmdxDocumentWriter::CXmdxDocumentWriter(IRandomWriteStream* file)
	{
		ATLASSERT(file != NULL);
		if (file == NULL)
		{
			_file = NULL;
			_root = NULL;
			return;
		}
		_file = file;

		// ���ɲ�Ԥд��ͷ
		memset(&_header, NULL, sizeof(XMDXHEADER));
		strcpy_s(_header.tag, 5, XMDXHEADER_TAG);
		_header.version = XMDXFILE_VERSION;

		_headerAddress = file->GetPosition();
		file->Write(&_header, sizeof(XMDXHEADER));

		_header.ElementAddress = file->GetPosition();

		// ����root
		_root = newElement(NULL, "xmdx");
	}

	CXmdxDocumentWriter::~CXmdxDocumentWriter()
	{
		close();
	}

	// ȡ��root���
	IXmdxElementWriter* CXmdxDocumentWriter::rootElement()
	{
		return _root;
	}

	// ������һ���½��
	IXmdxElementWriter* CXmdxDocumentWriter::newElement(IXmdxElementWriter* parent, LPCSTR name)
	{
		if (_file == NULL)
		{
			_lastError.Format(_T("û��ָ�����������"));
			return NULL;
		}

		if (name == NULL)
		{
			_lastError.Format(_T("�ڵ����ƿ�ָ�롣"));
			return NULL;
		}

		// ����ռ�
		if (_nodes.getCount() >= MAXWORD)
		{
			_lastError.Format(_T("�Ѵﵽ֧�ֵ����������%d��"), MAXWORD);
			return NULL;
		}

		LPXMDXNODE node = NULL;
		if (!_nodes.getNewNode(&node))
		{
			_lastError.Format(_T("�ڴ�ռ䲻�㡣"));
			return NULL;
		}

		// ���ýڵ��ϵ
		if (parent)
		{
			// ���õ�ǰ���ĸ����
			node->parent = parent->getNode()->index;

			// ���ø����ĵ�һ���ӽ������
			if (!parent->getNode()->firstChildren)
			{
				parent->getNode()->firstChildren = node->index;
			}
			else
			{
				// �����ϼ�����ֵܽ��Ϊ��
				DWORD prevSibling = parent->getNode()->lastChildren;
				_nodes.getAt(prevSibling)->nextSibling = node->index;
			}

			// ���¸��������һ���ӽ������Ϊ�����
			parent->getNode()->lastChildren = node->index;
		}

		// �����Ͻ�����
		CXmdxElementWriter* elmt = _ElementFactory.getnew();
		elmt->setNode(node);
		elmt->setName(name);
		elmt->setWriter(this);
		return elmt;
	}

	// д��һ�����������Դ
	size_t CXmdxDocumentWriter::writeElement(IXmdxElementWriter* element)
	{
		if (element == NULL)
			return 0;

		// �����ظ�д�루�ж��Ƿ��е�ַ���ݣ�
		if (element->getNode()->entryAddress)
			return 0;

		return element->write(_file);
	}

	void CXmdxDocumentWriter::freeElement(IXmdxElementWriter* element)
	{
		if (element == NULL)
			return;

		CXmdxElementWriter* celmt = dynamic_cast<CXmdxElementWriter*> (element);
		if (celmt)
		{
			celmt->clear();
			_ElementFactory.recycle(celmt);
		}
		else
		{
			//delete celmt;  // SHL celmtһ��Ϊ��ָ��
			delete element;
		}
	}

	// �ر��ļ�
	void CXmdxDocumentWriter::close()
	{
		if (!_root || !_file)
			return;

		// д�벢ɾ��root���
		_root->getWriter()->writeElement(_root);
		_root->getWriter()->freeElement(_root);

		// ����ͷ��Ϣ
		_header.NodeAddress = _file->GetPosition();
		_header.ElementBytes = _header.NodeAddress - _header.ElementAddress;
		_header.NodeCount = WORD(_nodes.getCount());

		// д����
		for (size_t i = 0; i < _nodes.getCount(); i++)
		{
			LPXMDXNODE node = _nodes.getAt(i);
			_file->Write(node, sizeof(XMDXNODE));
		}

		DWORD curPosition = _file->GetPosition();
		_header.NodeBytes = curPosition - _header.NodeAddress;

		// �ٴ�д��ͷ
		_file->SetPosition(_headerAddress);
		_file->Write(&_header, sizeof(XMDXHEADER));
		_file->SetPosition(curPosition);

		// ����
		_file = NULL;
		_root = NULL;
		_nodes.clear();
		_ElementFactory.clear();
		_memoryPool.ClearUp();
	}

	LPCTSTR CXmdxDocumentWriter::getLastError()
	{
		return _lastError;
	}

	// ȡ���ڴ��
	IAllocMemoryPool* CXmdxDocumentWriter::getMemoryPool()
	{
		return &_memoryPool;
	}

	size_t CXmdxDocumentWriter::GetNodeCount()
	{
		return _nodes.getCount();
	}

	/************************************************************************/
	/* CXmdxDocumentReader                                                  */
	/************************************************************************/
	CXmdxDocumentReader::CXmdxDocumentReader(IRandomReadStream* file)
	{
		_file = file;
		_nodes = NULL;
		_elements = NULL;

		// ��ȡ�ļ�ͷ
		DWORD bytesRead = 0;

		// �������ת�����ڴ���������Բ���������
		CMemoryDataReadStream* memoryStream = dynamic_cast<CMemoryDataReadStream*>(file);
		_closeFreeNodes = memoryStream ? FALSE : TRUE;
		_file->Read(&_header, sizeof(XMDXHEADER), bytesRead);
		if (bytesRead != sizeof(XMDXHEADER) || strcmp(_header.tag, XMDXHEADER_TAG))
		{
			_file = NULL;
		}
		else if (_header.version > XMDXFILE_VERSION)
		{
			_file = NULL;
		}

		// ��ȡ�������
		if (_file && _header.NodeCount > 0)
		{
			DWORD allNodeBytes = _header.NodeCount * sizeof(XMDXNODE);
			if (_closeFreeNodes)
			{
				// ��������
				_nodes = (LPXMDXNODE) ::malloc(allNodeBytes);
				if (_nodes && _file->SetPosition(_header.NodeAddress))
				{
					_file->Read(_nodes, allNodeBytes, bytesRead);
				}
			}
			else
			{
				// ��ָ��
				LPBYTE buffer = (LPBYTE)memoryStream->getOriginalBuffer();
				_nodes = (LPXMDXNODE)(buffer + _header.NodeAddress);
				_file->SetPosition(_header.NodeAddress + allNodeBytes);
			}
		}

		// ��ȡ��������
		if (_file && _header.NodeCount > 0)
		{
			if (_closeFreeNodes)
			{
				// ��������
				_elements = (LPBYTE) ::malloc(_header.ElementBytes);
				if (_elements && _file->SetPosition(_header.ElementAddress))
				{
					_file->Read(_elements, _header.ElementBytes, bytesRead);
				}
			}
			else
			{
				// ��ָ��
				LPBYTE buffer = (LPBYTE)memoryStream->getOriginalBuffer();
				_elements = buffer + _header.ElementAddress;
				_file->SetPosition(_header.ElementAddress + _header.ElementBytes);
			}
		}
	}

	CXmdxDocumentReader::~CXmdxDocumentReader()
	{
		close();
	}

	// �رն�ȡ�ļ�
	void CXmdxDocumentReader::close()
	{
		// ��ָ���ƶ�β��
		if (_file)
		{
			_file = NULL;
		}

		if (_nodes)
		{
			if (_closeFreeNodes)
				::free(_nodes);
			_nodes = NULL;
		}
		if (_elements)
		{
			if (_closeFreeNodes)
				::free(_elements);
			_elements = NULL;
		}

		_memoryPool.ClearUp();
	}

	// ȡ��root���
	XMDXHANDLE CXmdxDocumentReader::rootNode()
	{
		if (_nodes)
			return &_nodes[0];
		return NULL;
	}

	IXmdxElementReader* CXmdxDocumentReader::rootElement()
	{
		return readElement(rootNode());
	}

	// �����ж�ȡһ������
	IXmdxElementReader* CXmdxDocumentReader::readElement(XMDXHANDLE handle)
	{
		if (_file && handle)
		{
			CXmdxElementReader* elmt = _ElementFactory.getnew();
			elmt->setNode(handle);
			elmt->setReader(this);
			elmt->read(_file);
			return elmt;
		}

		return NULL;
	}

	void CXmdxDocumentReader::freeElement(IXmdxElementReader* element)
	{
		if (element == NULL)
			return;

		CXmdxElementReader* celmt = dynamic_cast<CXmdxElementReader*> (element);
		if (celmt)
		{
			celmt->clear();
			_ElementFactory.recycle(celmt);
		}
		else
		{
			//delete celmt;
			delete element;
		}
	}

	// ���ҽ��ĵ�һ���ӽ��
	FINDHANDLE CXmdxDocumentReader::findFirstChild(XMDXHANDLE parent, XMDXHANDLE* findNode)
	{
		// ���û���ӽ���򷵻�NULL����ʾ����ʧ��
		if (!parent || !parent->firstChildren)
			return NULL;

		// �������ҽṹ
		LPXMDXFIND handle = _FindHanleFactory.getnew();

		handle->parent = parent;
		handle->index = parent->firstChildren;

		// ���ص�һ���ӽ��
		if (findNode)
		{
			*findNode = &_nodes[parent->firstChildren];
		}

		// ���ز��ҽṹ
		return (FINDHANDLE)handle;
	}

	// ���ҽ�����һ���ӽ��
	BOOL CXmdxDocumentReader::findNextChild(FINDHANDLE handle, XMDXHANDLE* findNode)
	{
		if (!handle) return FALSE;

		// ���ŵ�ǰ���ҽ��Ϊ��nextSibling���в���
		LPXMDXFIND findHandle = (LPXMDXFIND)handle;
		LPXMDXNODE curNode = &_nodes[findHandle->index];

		if (curNode->nextSibling)
		{
			findHandle->index = curNode->nextSibling;
			*findNode = &_nodes[curNode->nextSibling];
			return TRUE;
		}

		return FALSE;
	}

	// �رղ��Ҿ��
	void CXmdxDocumentReader::closeFindHandle(FINDHANDLE handle)
	{
		_FindHanleFactory.recycle((LPXMDXFIND)handle);
	}

	LPCTSTR CXmdxDocumentReader::getLastError()
	{
		return _lastError;
	}

	// ȡ���ڴ��
	IAllocMemoryPool* CXmdxDocumentReader::getMemoryPool()
	{
		return &_memoryPool;
	}

	// ȡ��ָ������������
	LPVOID CXmdxDocumentReader::getElementBuffer(XMDXHANDLE handle)
	{
		if (handle == NULL)
			return NULL;

		DWORD index = handle->entryAddress - _header.ElementAddress;
		return &_elements[index];
	}
}
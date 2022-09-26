#include "StdAfx.h"
#include <algorithm>
#include "KNode.h"
#include <utility>
#include "TypeDefine.h"
#include "../Sdk/XmlDocument.h"
#include <list>
#include "../Sdk/XmdxAccess.h"
#include "..\Tool\StringTool.h"

namespace CommBase
{
	KNode::KNode()
	{
		_nTag = 0;
		_pParent = NULL;
		_pNodes = NULL;
		_pDataMap = NULL;
		_pUndo = NULL;
	}

	KNode::KNode(const CGuid& guid) : _id(guid)
	{
		_nTag = 0;
		_pParent = NULL;
		_pNodes = NULL;
		_pDataMap = NULL;
		_pUndo = NULL;
	}

	KNode::KNode(const KNode& value)
	{
		if (this == &value)
			return;

		CopyFrom(&value);
	}

	KNode& KNode::operator = (const KNode& value)
	{
		if (this == &value)
			return *this;

		CopyFrom(&value);
		return *this;
	}

	KNode::~KNode()
	{
		// ɾ���ӽڵ�(������������¼)
		if (NULL != _pNodes)
		{
			for (KNode* pNode : (*_pNodes))
			{
				delete pNode;
			}
			_pNodes->clear();
		}
		
		SAFE_DELETE(_pNodes);
		SAFE_DELETE(_pDataMap);
		
		_nTag = -1;
		_pParent = NULL;
		_pUndo = NULL;
	}

	int KNode::GetTag() const
	{
		return _nTag;
	}

	void KNode::SetTag(int nTag)
	{
		// ��¼�����޸�
		if (NULL != _pUndo)
		{
			_pUndo->OnTagModify(this, _nTag, nTag);
		}

		_nTag = nTag;
	}

	const CGuid& KNode::GetId() const
	{
		return _id;
	}

	void KNode::SetId(const CGuid& id)
	{
		_id = id;
	}

	bool KNode::RemoveData(LPCWSTR lpKey)
	{
		if (NULL == lpKey || NULL == _pDataMap)
			return false;

		KNodeDataMapIter findIter = _pDataMap->find(lpKey);
		if (findIter != _pDataMap->end())
		{
			// ��¼����ɾ��
			if (NULL != _pUndo)
				_pUndo->OnDataDelete(this, findIter->first, findIter->second);

			_pDataMap->erase(findIter);

			return true;
		}

		return false;
	}

	void KNode::RemoveAllData()
	{
		if (NULL != _pDataMap)
		{
			if (NULL != _pUndo)
			{
				KNodeDataMapCIter endIter = _pDataMap->end();
				for (KNodeDataMapCIter it = _pDataMap->begin(); it != endIter; ++it)
				{
					// ��¼����ɾ��
					_pUndo->OnDataDelete(this, it->first, it->second);
				}
			}

			_pDataMap->clear();
			SAFE_DELETE(_pDataMap);
		}
	}

	const CAny& KNode::GetData(LPCWSTR lpKey, const CAny& defData)
	{
		static CAny stAny; // ���ڷ�����ʱ����
		if (NULL == lpKey && defData.IsEmpty())
			return stAny;

		if (NULL == _pDataMap)
			_pDataMap = new KNodeDataMap();

		KNodeDataMapCIter findIter = _pDataMap->find(lpKey);
		if (findIter != _pDataMap->end())
		{
			return findIter->second;
		}

		// û���ҵ�������Ĭ��ֵΪ�շ���
		if (defData.IsEmpty())
		{
			return stAny;
		}

		// ��¼Ĭ��ֵ�������
		if (NULL != _pUndo)
		{
			_pUndo->OnDataInsert(this, lpKey, defData);
		}

		// ���Ĭ��ֵ
		std::pair<KNodeDataMapIter, bool> ret = _pDataMap->insert(
			KNodeDataMap::value_type(lpKey, defData));

		// ��������ӵ�Ĭ��ֵ
		return ret.first->second;
	}

	void KNode::SetData(LPCWSTR lpKey, const CAny& data, bool bAttach)
	{
		if (NULL == lpKey)
			return;

		if (NULL == _pDataMap)
			_pDataMap = new KNodeDataMap();

		CAny& oldData = (*_pDataMap)[lpKey];
		if (oldData == data)
			return;

		if (oldData.IsEmpty())
		{
			// ��¼�������
			if (NULL != _pUndo)
			{
				_pUndo->OnDataInsert(this, lpKey, data);
			}
		}
		else
		{
			// ��¼�����޸�
			if (NULL != _pUndo)
			{
				_pUndo->OnDataModify(this, lpKey, oldData, data);
			}
		}

		// �޸�
		if (bAttach)
			oldData.Attach(data);
		else
			oldData = data;
	}

	bool KNode::HasData(LPCWSTR lpKey) const
	{
		return (NULL != lpKey) && (NULL != _pDataMap) && (_pDataMap->find(lpKey) != _pDataMap->end());
	}

	const KNodeDataMap& KNode::GetDataMap() const
	{
		static KNodeDataMap tmpDataMap;
		if (NULL == _pDataMap)
			return tmpDataMap;

		return (*_pDataMap);
	}

	size_t KNode::RemoveFromParent(bool bDelete)
	{
		if (NULL == _pParent)
			return KNODE_ERROR;

		return _pParent->RemoveNode(this, bDelete);
	}

	KNode* KNode::GetParent() const
	{
		return _pParent;
	}

	CommBase::KNode* KNode::GetParent(int nTag) const
	{
		if (_pParent == NULL)
			return NULL;

		if (_pParent->GetTag() == nTag)
			return _pParent;

		return _pParent->GetParent(nTag);
	}

	const KNodeList& KNode::GetNodeList() const
	{
		static KNodeList tmpNodeList;
		if (NULL == _pNodes)
			return tmpNodeList;

		return (*_pNodes);
	}

	void KNode::GetAllNode(KNodeList& childNodes, int nTag) const
	{
		// ���÷ǵݹ�����ڵ�
		std::list<const KNode*> stackNodes;
		stackNodes.push_back(this);
		while (!stackNodes.empty())
		{
			const KNode* pTopNode = stackNodes.front();
			stackNodes.pop_front();
			if (NULL == pTopNode)
				continue;

			const KNodeList& childNodeList = pTopNode->GetNodeList();

			for (KNodeListCIter iter = childNodeList.begin(); 
				iter != childNodeList.end(); ++iter)
			{
				if (nTag == KNODE_NONE_TAG || nTag == (*iter)->GetTag())
					childNodes.push_back(*iter);
				stackNodes.push_back(*iter);
			}
		}
	}

	void KNode::GetAllNode(KNodeMap& childNodes, int nTag) const
	{
		// ���÷ǵݹ�����ڵ�
		std::list<const KNode*> stackNodes;
		stackNodes.push_back(this);
		while (!stackNodes.empty())
		{
			const KNode* pTopNode = stackNodes.front();
			stackNodes.pop_front();
			if (NULL == pTopNode)
				continue;

			const KNodeList& childNodeList = pTopNode->GetNodeList();
			for (KNode* pNode : childNodeList)
			{
				if (nTag == KNODE_NONE_TAG || nTag == pNode->GetTag())
					childNodes[pNode->GetId()] = pNode;
				stackNodes.push_back(pNode);
			}
		}
	}


	bool KNode::HasChildNode() const
	{
		return (_pNodes && !_pNodes->empty());
	}

	std::vector<KNode*> KNode::GetChildNode(const CString& strChildNodeName)
	{
		std::vector<KNode*> vecResult;
		if (nullptr == this)
		{
			return vecResult;
		}

		const KNodeList& vecNodeList = GetNodeList();
		for (KNode* pNode : vecNodeList)
		{
			CString str = pNode->GetData(L"����");
			if (str == strChildNodeName)
			{
				vecResult.emplace_back(pNode);
			}
		}
		return vecResult;
	}

	void KNode::RemoveAllNode(bool bDelete)
	{
		if (NULL == _pNodes)
			return;

		// ���뷴��ɾ������������¼���������
		size_t nIndex = _pNodes->size();
		KNodeList::reverse_iterator rendIter = _pNodes->rend();
		for (KNodeList::reverse_iterator rit = _pNodes->rbegin(); rit != rendIter; ++rit, --nIndex)
		{
			// ��¼�ڵ�ɾ��
			if (NULL != _pUndo)
			{
				_pUndo->OnNodeDelete(this, *rit, nIndex-1);
			}

			(*rit)->_pParent = NULL;
			if (bDelete)
			{
				delete (*rit);
			}
		}

		_pNodes->clear();
		SAFE_DELETE(_pNodes);
	}

	KNode* KNode::RemoveNode(size_t nRemIndex, bool bDelete)
	{
		size_t nCount = _pNodes->size();
		if (NULL == _pNodes || 0 == nCount)
			return NULL;

		// �Ƴ����һ��
		if (KPOS_TAIL == nRemIndex)
		{
			KNode* pNode = _pNodes->back();

			// ��¼�ڵ�ɾ��
			if (NULL != _pUndo)
				_pUndo->OnNodeDelete(this, pNode, nCount - 1);

			_pNodes->pop_back();
			pNode->_pParent = NULL;
			if (bDelete)
			{
				delete pNode;
				pNode = NULL;
			}
			return pNode;
		}
		// �Ƴ���ǰһ��
		else if (KPOS_HEAD == nRemIndex)
		{
			KNode* pNode = _pNodes->front();

			// ��¼�ڵ�ɾ��
			if (NULL != _pUndo)
				_pUndo->OnNodeDelete(this, pNode, 0);

			_pNodes->erase(_pNodes->begin());
			pNode->_pParent = NULL;
			if (bDelete)
			{
				delete pNode;
				pNode = NULL;
			}
			return pNode;
		}

		// ���Ҳ�ɾ��
		if (nRemIndex >= 0 && nRemIndex < nCount)
		{
			KNodeListIter it = _pNodes->begin();
			std::advance(it, nRemIndex);
			KNode* pNode = (*it);

			// ��¼�ڵ�ɾ��
			if (NULL != _pUndo)
				_pUndo->OnNodeDelete(this, pNode, nRemIndex);

			pNode->_pParent = NULL;
			_pNodes->erase(it);
			if (bDelete)
			{
				delete pNode;
				pNode = NULL;
			}

			return pNode;
		}

		return NULL;
	}

	bool KNode::SwapNode(KNode* pNode)
	{
		if (pNode == NULL || pNode == this || pNode->GetParent() == NULL
			|| _pParent == NULL || pNode->_pUndo != _pUndo)
			return false;

		size_t nIndex = 0;
		size_t nSrcIndex = 0;
		size_t nDstIndex = 0;
		KNode* pSrcParent = _pParent;
		KNode* pDstParent = pNode->_pParent;

		// ��ͬ���׽ڵ�֮�佻��
		if (pSrcParent != pDstParent)
		{
			// �ӵ�ǰ�ڵ㸸�׽ڵ���ɾ����ǰ�ڵ�
			nIndex = 0;
			KNodeListIter iterSrcEnd = _pParent->_pNodes->end();
			for (KNodeListIter it = _pParent->_pNodes->begin(); it != iterSrcEnd; ++nIndex, ++it)
			{
				if (*it == this)
				{
					*it = pNode;
					pNode->_pParent = pSrcParent;
					nSrcIndex = nIndex;
					break;
				}
			}
			// ��Ŀ��ڵ㸸�ڵ���ɾ��Ŀ��ڵ�
			nIndex = 0;
			KNodeListIter iterDstEnd = pNode->_pParent->_pNodes->end();
			for (KNodeListIter it = pNode->_pParent->_pNodes->begin(); it != iterDstEnd; ++nIndex, ++it)
			{
				if (*it == pNode)
				{
					*it = this;
					this->_pParent = pDstParent;
					nDstIndex = nIndex;
					break;
				}
			}
		}
		else
		{
			nIndex = 0;
			KNodeListIter iterSrcEnd = _pParent->_pNodes->end();
			KNodeListIter srcIter = iterSrcEnd;
			KNodeListIter dstIter = iterSrcEnd;
			for (KNodeListIter it = _pParent->_pNodes->begin(); it != iterSrcEnd; ++nIndex, ++it)
			{
				if (*it == this)
				{
					srcIter = it;
					nSrcIndex = nIndex;
				}
				else if (*it == pNode)
				{
					dstIter = it;
					nDstIndex = nIndex;
				}
				if (srcIter != iterSrcEnd && dstIter != iterSrcEnd)
				{
					KNode* pSwapNode = *srcIter;
					*srcIter = *dstIter;
					*dstIter = pSwapNode;
					break;
				}
			}
		}

		// ��¼�ڵ㽻��
		if (NULL != _pUndo)
			_pUndo->OnNodeSwap(pSrcParent, nSrcIndex, pDstParent, nDstIndex);

		return true;
	}

	size_t KNode::RemoveNode(KNode* pRemNode, bool bDelete)
	{
		size_t nCount = _pNodes->size();
		if (NULL == _pNodes || 0 == nCount || NULL == pRemNode)
			return KNODE_ERROR;

		size_t nIndex = 0;
		KNodeListIter iterEnd = _pNodes->end();
		for (KNodeListIter it = _pNodes->begin(); it != iterEnd; ++nIndex, ++it)
		{
			if (*it == pRemNode)
			{
				// ��¼�ڵ�ɾ��
				if (NULL != _pUndo)
					_pUndo->OnNodeDelete(this, *it, nIndex);

				_pNodes->erase(it);
				pRemNode->_pParent = NULL;
				if (bDelete)
				{
					delete pRemNode;
					pRemNode = NULL;
				}

				return nIndex;
			}
		}

		return KNODE_ERROR;
	}

	size_t KNode::InsertNode(KNode* pInsNode, size_t nInsIndex)
	{
		if (pInsNode == this || NULL == pInsNode || NULL != pInsNode->_pParent)
			return KNODE_ERROR;

		if (NULL == _pNodes)
			_pNodes = new KNodeList();

		size_t nCount = _pNodes->size();
		if (KPOS_TAIL == nInsIndex)
		{
			// ��¼�ڵ����
			if (NULL != _pUndo)
				_pUndo->OnNodeInsert(this, pInsNode, nCount);

			_pNodes->push_back(pInsNode);
			pInsNode->_pParent = this;
			return nCount;
		}
		else if (KPOS_HEAD == nInsIndex)
		{
			// ��¼�ڵ����
			if (NULL != _pUndo)
				_pUndo->OnNodeInsert(this, pInsNode, 0);

			_pNodes->insert(_pNodes->begin(), pInsNode);
			pInsNode->_pParent = this;
			return 0;
		}
		
		if (nInsIndex >= 0 && nInsIndex <= nCount)
		{
			// ��¼�ڵ����
			if (NULL != _pUndo)
				_pUndo->OnNodeInsert(this, pInsNode, nInsIndex);

			KNodeListIter it = _pNodes->begin();
			std::advance(it, nInsIndex);

			_pNodes->insert(it, pInsNode);
			pInsNode->_pParent = this;

			return nInsIndex;
		}

		return KNODE_ERROR;
	}

	size_t KNode::InsertNode(KNode* pInsNode, KNode* pRefNode, bool bAfterIns)
	{
		if (pInsNode == this || NULL == pInsNode || NULL == pRefNode || NULL != pInsNode->_pParent)
			return KNODE_ERROR;

		if (NULL == _pNodes)
			_pNodes = new KNodeList();

		auto iter = std::find(_pNodes->begin(), _pNodes->end(), pRefNode);
		if(iter != _pNodes->end())
		{
			if (bAfterIns) ++iter; //���
			size_t nIndex = std::distance(_pNodes->begin(), iter);

			// ��¼�ڵ����
			if (NULL != _pUndo)
				_pUndo->OnNodeInsert(this, pInsNode, nIndex);

			_pNodes->insert(iter, pInsNode);
			pInsNode->_pParent = this;

			return nIndex;
		}

		return KNODE_ERROR;
	}

	void KNode::CopyFrom(const KNode* pSrcNode, bool bRecursion)
	{
		if (NULL == pSrcNode || pSrcNode == this)
			return;

		// ���Դ��������
		RemoveAllData();
		SetTag(pSrcNode->_nTag);

		// ��������,����������¼
		const KNodeDataMap& dataMap = pSrcNode->GetDataMap();
		for (auto it : dataMap)
		{
			SetData(it.first, it.second);
		}

		if (!bRecursion)
			return;

		// ɾ����ǰ�����ӽڵ�
		RemoveAllNode(true);

		// ��ʼ�����ӽڵ�
		const KNodeList& childNodeList = pSrcNode->GetNodeList();
		for (const KNode* pNode : childNodeList)
		{
			KNode* pChildNode = new KNode();
			InsertNode(pChildNode);
			pChildNode->CopyFrom(pNode, bRecursion);
		}
	}

	bool KNode::LoadFromXmlElm(void* pVXmlElm, bool bRecursion)
	{
		CXmlElement* pXmlElm = (CXmlElement*)pVXmlElm;
		if (NULL == pXmlElm)
			return false;

		// ���Դ���������뵱ǰ�����ӽڵ�
		RemoveAllData();
		RemoveAllNode(true);

		_strElementName = pXmlElm->GetElementName();

		// ��ȡXML����
		CXmlAttributes* pAttrs = pXmlElm->GetAttributes();
		size_t nAttCount = pAttrs->GetCount();
		for (size_t i = 0; i < nAttCount; ++i)
		{
			CXmlAttribute* pAttr = pAttrs->GetAt(i);
			CString strAttName = pAttr->GetAttrName();
			if (strAttName == L"ITag")
			{
				_nTag = pAttr->GetIntValue();
				continue;
			}else if (strAttName == L"GGuid")
			{
				_id = CGuid(pAttr->GetStrValue());
				continue;
			}

			TCHAR cType = strAttName.GetAt(0);
			strAttName.Delete(0); // �Ƴ���������
			switch (cType)
			{
			case L'B':	//BOOL
				SetData(strAttName,!!pAttr->GetIntValue());
				break;
			case L'I':  //INT
				SetData(strAttName, pAttr->GetIntValue());
				break;
			case L'D':  //DOUBLE
				SetData(strAttName, pAttr->GetDblValue());
				break;
			case L'S':  //STRING
				SetData(strAttName, pAttr->GetStrValue());
				break;
			case L'G':	//GUID
				SetData(strAttName, CGuid(pAttr->GetStrValue()));
				break;
			default:
				break;
			}
		}

		if (!bRecursion)
			return true;

		// ��ʼ��ȡXML�ӽڵ�
		CXmlElements* pElmChilds = pXmlElm->GetChildElements();
		size_t nChildCount = pElmChilds->GetCount();
		for (size_t i = 0; i < nChildCount; ++i)
		{
			CXmlElement* pElmChild = pElmChilds->GetAt(i);
			KNode* pNode = new KNode();
			InsertNode(pNode);
			pNode->LoadFromXmlElm(pElmChild, bRecursion);
		}

		return true;
	}

	bool KNode::SaveToXmlElm(void* pVXmlElm, bool bRecursion) const
	{
		CXmlElement* pXmlElm = (CXmlElement*)pVXmlElm;
		if (NULL == pXmlElm)
			return false;

		pXmlElm->SetElementName((_strElementName.IsEmpty() ? L"KNode" : _strElementName));

		CXmlAttributes* pAttrs = pXmlElm->GetAttributes();
		CXmlAttribute* pAttr = pAttrs->Add();
		pAttr->SetAttrName(L"ITag");
		pAttr->SetAttrValue(_nTag);
		pAttr = pAttrs->Add();
		pAttr->SetAttrName(L"GGuid");
		pAttr->SetAttrValue(_id.ToString().GetString());

		// ����XML����
		const KNodeDataMap& dataMap = GetDataMap();
		for (auto iter : dataMap)
		{
			CString strKey = iter.first;
			const CAny& data = iter.second;
			switch (data.GetType())
			{
			case ANY_BOOL:	//BOOL
				pAttr = pAttrs->Add();
				pAttr->SetAttrName(L"B" + strKey);
				pAttr->SetAttrValue(bool(data));
				break;
			case ANY_INT:  //INT
				pAttr = pAttrs->Add();
				pAttr->SetAttrName(L"I" + strKey);
				pAttr->SetAttrValue(int(data));
				break;
			case ANY_DOUBLE:  //DOUBLE
				pAttr = pAttrs->Add();
				pAttr->SetAttrName(L"D" + strKey);
				pAttr->SetAttrValue(double(data));
				break;
			case ANY_STRING:  //STRING
				pAttr = pAttrs->Add();
				pAttr->SetAttrName(L"S" + strKey);
				pAttr->SetAttrValue(CString(data));
				break;
			case ANY_POINT:  //POINT
				pAttr = pAttrs->Add();
				pAttr->SetAttrName(L"P" + strKey);
				pAttr->SetAttrValue(CString(data));
				break;
			case ANY_GUID:	//GUID
				pAttr = pAttrs->Add();
				pAttr->SetAttrName(L"G" + strKey);
				pAttr->SetAttrValue(CString(data));
				break;
			default:
				break;
			}
		}

		if (!bRecursion)
			return true;

		// ��ʼ�����ӽڵ㵽XML��
		const KNodeList& childNodeList = GetNodeList();
		CXmlElements* pChildElms = pXmlElm->GetChildElements();
		for (const KNode* pChildNode : childNodeList)
		{
			CXmlElement* pChildElm = pChildElms->Add();
			pChildElm->SetElementName(L"KNode");
			pChildNode->SaveToXmlElm(pChildElm, bRecursion);
		}

		return true;
	}

	bool KNode::LoadFromLargeXmdx(const CString& strFile, bool bRecursion)
	{
		// ���Դ���������뵱ǰ�����ӽڵ�
		RemoveAllData();
		RemoveAllNode(true);

		// �����Ѽ��صĽڵ㣬���ڿ����ҵ����ڵ�
		// ��Ϊ��¼�������Ǵ�1��ʼ
		std::vector<KNode*> loadNodes;
		loadNodes.push_back(NULL);

		KNode* pNode = this;
		// ��Ҫ�Ĵ�ѭ�ṹ����������xmdxReader����˳����ȷ����
		CLargXmdxMemLoad largXmdxLoad(strFile);
		do
		{
			IXmdxElementReader* pXmdxReader = largXmdxLoad.GetReader();
			if (NULL == pXmdxReader)  break;// ��ȡ���

			if ((IXmdxElementReader*)-1 == pXmdxReader) // ����
				return false;

			CXmdxElmReader xmdxReader(pXmdxReader);

			int nAttrCount = xmdxReader.GetAttrCount();
			if (nAttrCount < 3) return false; // ������Ŀ����

			if (NULL == pNode) pNode = new KNode();
			for (int i = 0; i < (nAttrCount - 3); ++i)
			{
				CString strKey(xmdxReader.GetAttrName(i));
				pNode->SetData(strKey, xmdxReader.GetAttrVariant(i));
			}
			pNode->SetId(xmdxReader.GetAttrGuid(nAttrCount-3)); // GUID
			pNode->SetTag(xmdxReader.GetIntAttr(nAttrCount-2)); // TAG
			loadNodes.push_back(pNode);

			// ��ȡ���ڵ�ָ��
			int nParentIndex = xmdxReader.GetIntAttr(nAttrCount - 1, 0);
			KNode* pParentNode = loadNodes[nParentIndex];
			if (NULL != pParentNode)
			{
				pParentNode->InsertNode(pNode);
			}

			pNode = NULL;
			// �����еݹ����
			if (!bRecursion)
				break;

		} while (true);

		return true;
	}

	bool KNode::SaveToLargeXmdx(const CString& strFile, bool bRecursion) const
	{
		typedef struct tag_NodePir {
			tag_NodePir(const KNode* node = NULL, int nIndex = 0) : pNode(node), nParentIndex(nIndex) {}
			const KNode* pNode;
			int nParentIndex;
		}NodePir;

		// XMDX���ļ����浽�ڴ�
		CLargXmdxMemSave xmdxSaver(strFile);

		// ���÷ǵݹ�����ڵ�
		std::list<NodePir> stackNodes;
		stackNodes.push_back(NodePir(this, 0));
		while (!stackNodes.empty())
		{
			NodePir topNode = stackNodes.front();
			stackNodes.pop_front();
			IXmdxElementWriter* pXmdxWirter = xmdxSaver.GetWriter();
			if (NULL == pXmdxWirter)
				return false;

			CXmdxElmWriter xmdxWriter(pXmdxWirter);

			// ��������
			const KNodeDataMap& dataMap = topNode.pNode->GetDataMap();
			for (auto iter : dataMap)
			{
				CStringA strKey = CStringTool::WCharToMChar(iter.first);
				xmdxWriter.AddVariantAttr(strKey, iter.second);
			}

			xmdxWriter.AddGuidAttr("UID", topNode.pNode->_id);
			xmdxWriter.AddIntAttr("TAG", topNode.pNode->_nTag);
			xmdxWriter.AddIntAttr("PID", topNode.nParentIndex);
			

			// ����Ҫ�ݹ�
			if (!bRecursion) continue;

			// �����ӽڵ�
			int nCurIndex = xmdxSaver.CurRecordIndex();
			const KNodeList& childNodeList = topNode.pNode->GetNodeList();
			for (const KNode* pNode : childNodeList)
			{
				stackNodes.push_back(NodePir(pNode, nCurIndex));
			}
		}

		return true;
	}

	bool KNode::LoadFromXmdxElm(void* pVElmReader, bool bRecursion)
	{
		IXmdxElementReader* pElmReader = (IXmdxElementReader*)pVElmReader;
		if (NULL == pElmReader)
			return false;

		// ���Դ���������뵱ǰ�����ӽڵ�
		RemoveAllData();
		RemoveAllNode(true);

		CXmdxElmReader xmdxReader(pElmReader);

		// ���ؽڵ���Ϣ
		int nAttrCount = xmdxReader.GetAttrCount();
		if (nAttrCount < 2)
			return false;

		for (int i = 0; i < (nAttrCount-2); ++i)
		{
			CString strAttrName(xmdxReader.GetAttrName(i));
			SetData(strAttrName, xmdxReader.GetAttrVariant(i));
		}
		SetId(xmdxReader.GetAttrGuid(nAttrCount - 2)); // GUID
		SetTag(xmdxReader.GetIntAttr(nAttrCount - 1)); // TAG

		// �����ӽڵ�����
		CXmdxElmFind find(xmdxReader);
		while (find.FindNext())
		{
			KNode* pSubNode = new KNode();
			InsertNode(pSubNode);
			pSubNode->LoadFromXmdxElm(find->Detach(), bRecursion);
		}

		return true;
	}

	bool KNode::SaveToXmdxElm(void* pVElmWriter, bool bRecursion) const
	{
		IXmdxElementWriter* pElmWriter = (IXmdxElementWriter*)pVElmWriter;
		if (NULL == pElmWriter)
			return false;

		CXmdxElmWriter xmdxWriter(pElmWriter);

		// ����ڵ���Ϣ
		const KNodeDataMap& dataMap = GetDataMap();
		for (auto iter : dataMap)
		{
			const CString& strName = iter.first;
			CStringA name = CStringTool::WCharToMChar(strName);
			xmdxWriter.AddVariantAttr(name, iter.second);
		}
		xmdxWriter.AddGuidAttr("UID", _id);
		xmdxWriter.AddIntAttr("TAG", _nTag);

		// �ǵݹ��ӽڵ�
		if (!bRecursion)
			return true;

		// �����ӽڵ�����
		const KNodeList& nodeList = GetNodeList();
		for (const KNode* pNode : nodeList)
		{
			// �˴���Ҫָ���ڵ����ƣ���Ȼ���������
			CXmdxElmWriter childWriter = xmdxWriter.NewElement("N");
			pNode->SaveToXmdxElm(childWriter.Detach(), bRecursion);
		}

		return true;
	}

	void KNode::AttachUndo(KNodeUndo* pUndo)
	{
		_pUndo = pUndo;
	}
}
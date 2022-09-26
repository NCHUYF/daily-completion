//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           KNode.H
//    @author         JZL
//    @date           2017/12/7 16:01
//    @brief          ���ṹ�ڵ���
//
//*****************************************************

#pragma once
#include "Any.h"
#include "Guid.h"
#include <map>
#include <vector>

namespace CommBase
{
	class KNode;

	// �ڵ㷵�ش�����
	#define KPOS_TAIL (size_t(-1))	 // ���������λ��
	#define KPOS_HEAD (size_t(-2))	 // ������ǰ��λ��
	#define KNODE_ERROR (size_t(-3)) // KNODE��������
	#define KNODE_NONE_TAG (-1)		 // KNODE�ޱ�ǩ

	// �ӽڵ��б�
	typedef std::vector<KNode*> KNodeList;
	typedef KNodeList::iterator KNodeListIter;
	typedef KNodeList::const_iterator KNodeListCIter;


	// �ڵ�����MAP
	typedef std::map<CString, CAny> KNodeDataMap;
	typedef KNodeDataMap::iterator KNodeDataMapIter;
	typedef KNodeDataMap::const_iterator KNodeDataMapCIter;

	typedef KNodeDataMap::reverse_iterator	KNodeDataMapRIter;

	// �ڵ�MAP
	typedef std::map<CGuid, KNode*> KNodeMap;
	typedef KNodeMap::iterator KNodeMapIter;
	typedef KNodeMap::const_iterator KNodeMapCIter;

	/**
	*  @class    ���ͽڵ㳷���ӿ���
	*
	*  @brief
	*/
	class COMMBASE_API KNodeUndo
	{
	public:
		virtual ~KNodeUndo() {}

	public:
		/**
		*  @class    ����ɾ��
		*
		*  @param    KNode* pNode ɾ�����ݵĽڵ�
		*  @param    LPCWSTR lpKey ��������
		*  @param    const CAny& oldValue ԭ����ֵ
		*/
		virtual void OnDataDelete(KNode* pNode, LPCWSTR lpKey, const CAny& oldValue) = 0;

		/**
		*  @class    �����޸�
		*
		*  @param    KNode* pNode �޸����ݵĽڵ�
		*  @param    LPCWSTR lpKey ��������
		*  @param    const CAny& oldValue ԭ����ֵ
		*  @param    const CAny& newValue ������ֵ
		*/
		virtual void OnDataModify(KNode* pNode, LPCWSTR lpKey, const CAny& oldValue, const CAny& newValue) = 0;

		/**
		*  @class    ��ʶ�޸�
		*
		*  @param    KNode* pNode �޸����ݵĽڵ�
		*  @param    int oldTag ԭ����ֵ
		*  @param    int newTag ������ֵ
		*/
		virtual void OnTagModify(KNode* pNode, int oldTag, int newTag) = 0;

		/**
		*  @class    �������
		*
		*  @param    KNode* pNode ������ݵĽڵ�
		*  @param    LPCWSTR lpKey ��������
		*  @param    const CAny& newValue ������ֵ
		*/
		virtual void OnDataInsert(KNode* pNode, LPCWSTR lpKey, const CAny& newValue) = 0;

		/**
		*  @class    �ڵ����
		*
		*  @param    KNode* pParent ���׽ڵ�
		*  @param    KNode* pNode �²���ڵ�
		*  @param    size_t nIndex �²���ڵ�����
		*/
		virtual void OnNodeInsert(KNode* pParent, KNode* pNode, size_t nIndex) = 0;

		/**
		*  @class    �ڵ㽻��
		*
		*  @param    KNode* pSrcParent �ƶ��ڵ㸸��
		*  @param    size_t nSrcIndex �ƶ��ڵ�����
		*  @param    KNode* pDstParent Ŀ�Ľڵ㸸��
		*  @param    size_t nDstIndex Ŀ�Ľڵ�����
		*/
		virtual void OnNodeSwap(KNode* pSrcParent, size_t nSrcIndex, KNode* pDstParent, size_t nDstIndex) = 0;

		/**
		*  @class    �ڵ�ɾ��
		*
		*  @param    KNode* pParent ���׽ڵ�
		*  @param    KNode* pNode ɾ���ڵ�
		*  @param    size_t nIndex ɾ���ڵ�����
		*/
		virtual void OnNodeDelete(KNode* pParent, KNode* pNode, size_t nIndex) = 0;
	};

	/**
	*  @class    ���ͽڵ���
	*
	*  @brief
	*/
	class COMMBASE_API KNode
	{
	public:
		KNode();
		KNode(const CGuid& guid);
		KNode(const KNode& value);
		KNode& operator = (const KNode& value);

	public:
		virtual ~KNode();

	public:
		/**
		*  @brief    ��ȡ��ǩ
		*
		*  @return   ���ر�ǩ
		*/
		virtual int GetTag() const;

		/**
		*  @brief    ���ñ�ǩ
		*
		*  @param    int nTag ��ǩ
		*/
		virtual void SetTag(int nTag);

		/**
		*  @brief    ��ȡID
		*
		*  @return   CGuid ����Guid
		*/
		virtual const CGuid& GetId() const;

		/**
		*  @brief	����ID
		*
		*  @param	const CGuid & id
		*  @return	void
		*/
		virtual void SetId(const CGuid& id);

	public:
		/**
		*  @brief    ɾ������
		*
		*  @param    LPCWSTR lpKey �ؼ���
		*  @return   bool ���ڷ���true
		*/
		virtual bool RemoveData(LPCWSTR lpKey);

		/**
		*  @brief    ɾ����������
		*
		*/
		virtual void RemoveAllData();

		/**
		*  @brief    ��ȡ����
		*
		*  @param    LPCWSTR lpKey �ؼ���
		*  @param    const CAny& defData û���ҵ���Ĭ��ֵ
		*								 (���ô˲�����Ĭ����ӵ�������)
		*  @return   const CAny& �������Զ���,���û����Ϊ�ն���
		*/
		virtual const CAny& GetData(LPCWSTR lpKey, const CAny& defData = CAny());

		/**
		*  @brief    ��������
		*
		*  @param    LPCWSTR lpKey �ؼ���
		*  @param    cosnt CAny& data ����
		*  @param    bool bAttach �Ƿ��data��ֱֵ��ת��(��߸�ֵ����)
		*  @remark	 �������ؼ����򴴽���Ӧ����
		*/
		virtual void SetData(LPCWSTR lpKey, const CAny& data, bool bAttach = false);

		/**
		*  @brief    �Ƿ��ָ������
		*
		*  @param    LPCWSTR lpKey �ؼ���
		*  @return   bool ���ڷ���true
		*/
		virtual bool HasData(LPCWSTR lpKey) const;

	public:
		/**
		*  @brief    �Ӹ��ڵ����Ƴ�
		*
		*  @param    bool bDelete �Ƿ�ɾ������
		*  @return   ����ɾ���ڵ�����
		*  @remark	 ��ǰ�ڵ��ڴ���Ҫ�����ͷ�
		*/
		virtual size_t RemoveFromParent(bool bDelete = true);

		/**
		*  @brief    ��ȡ���ڵ�
		*
		*  @return   KNode* ���ظ��ڵ�
		*/
		virtual KNode* GetParent() const;

		/**
		*  @brief    ��ȡָ�����͵ĸ��ڵ�
		*
		*  @param    int nTag
		*  @return   PlatformKernel::KNode*
		*/
		virtual KNode* GetParent(int nTag) const;

		/**
		*  @brief    �Ƿ����ӽ�
		*
		*  @return   bool
		*/
		virtual bool HasChildNode() const;

		std::vector<KNode*> GetChildNode(const CString& strChildNodeName);

	public:
		/**
		*  @brief    ɾ�������ӽڵ�
		*
		*  @param    bool bDelete �Ƿ�ɾ�������ӽڵ��ڴ�
		*/
		virtual void RemoveAllNode(bool bDelete = true);

		/**
		*  @brief    ɾ��ָ������λ�õĽڵ�
		*
		*  @param    size_t nRemIndex ɾ���ڵ������(KPOS_TAIL��ʶ�Ƴ����һ���ڵ�)
		*											(KPOS_HEAD��ʶ�Ƴ���ǰһ���ڵ�)
		*  @param    bool bDelete �Ƿ�ɾ���ڵ��ڴ�
		*  @return   KNode* ����ɾ���Ľڵ㣬û�ҵ��򷵻�NULL��ɾ���ڴ淵��NULL
		*/
		virtual KNode* RemoveNode(size_t nRemIndex = KPOS_TAIL, bool bDelete = true);

		/**
		*  @brief    ɾ��ָ���Ľڵ�(ɾ���Ľڵ��ڴ������ͷ�)
		*
		*  @param   KNode* pRemNode ɾ���Ľڵ�
		*  @param    bool bDelete �Ƿ�ɾ���ڵ��ڴ�
		*  @return  size_t ����ɾ���Ľڵ��������û�ҵ�����KNODE_ERROR
		*/
		virtual size_t RemoveNode(KNode* pRemNode, bool bDelete = true);

		/**
		*  @brief    ������ǰ�ڵ�������ڵ�λ��
		*
		*  @param   KNode* pNode �ƶ��Ľڵ�
		*  @return  bool true �ɹ����������ڵ�λ��
		*/
		virtual bool SwapNode(KNode* pNode);

		/**
		*  @brief    �����ӽڵ���ָ������֮��(����Ľڵ��ڴ������ͷ�)
		*
		*  @param    KNode* pInsNode �²���Ľڵ�
		*  @param    size_t nInsIndex �²���ڵ�����λ�ã�KPOS_TAIL��ֱ�Ӳ��뵽���
		*												  KPOS_HEAD��ֱ�Ӳ��뵽��ǰ
		*  @return   size_t ����ɹ������²���ڵ����0��ʼ����λ��
		*				    ����ڵ��Ѳ��뵽�����ڵ����򷵻�KNODE_ERROR
		*				    ���������������򷵻�KNODE_ERROR
		*/
		virtual size_t InsertNode(KNode* pInsNode, size_t nInsIndex = KPOS_TAIL);

		/**
		*  @brief    �����ӽڵ���ָ���ڵ�֮��(����Ľڵ��ڴ������ͷ�)
		*
		*  @param    KNode* pInsNode �²���Ľڵ�
		*  @param    KNode* pRefNode ��Խڵ�
		*  @param    KNode* pRefNode ��Խڵ�
		*  @param    bool bAfterIns true���뵽��Խڵ����,false���뵽��Խڵ�ǰ��
		*  @return   size_t ����ɹ������²���ڵ����0��ʼ����λ��
		*				    ����ڵ��Ѳ��뵽�����ڵ����򷵻�KNODE_ERROR
		*				    ���pAfterNode�ڵ�û�ҵ��򷵻�KNODE_ERROR
		*/
		virtual size_t InsertNode(KNode* pInsNode, KNode* pRefNode, bool bAfterIns = true);

	public:
		/**
		*  @brief    ���ƽڵ������Լ��ӽڵ�
		*			 (��������ӽڵ���ǰ�ڵ��µ��ӽڵ��ڴ��ȫ���ͷ�)
		*
		*  @param    KNode* pSrcNode ԭʼ���ݵĽڵ�
		*  @param    bool bRecursion �Ƿ����ӽڵ�������
		*/
		virtual void CopyFrom(const KNode* pSrcNode, bool bRecursion = true);

	public:
		/**
		*  @brief    ��ȡ�ӽ��б�(����������)
		*
		*  @return   const KNodeList& �����ӽڵ��б�(û���ӽڵ㷵��NULL)
		*/
		virtual const KNodeList& GetNodeList() const;

		/**
		*  @brief    ����Tag��ȡ�����ӽڵ�(����������)
		*
		*  @param    KNodeList& childNodes* ���������ƶ�TAG�ӽڵ��б�
		*  @param    int nTag KNODE_NONE_TAG
		*/
		virtual void GetAllNode(KNodeList& childNodes, int nTag = KNODE_NONE_TAG) const;

		/**
		*  @brief    ��ȡ��������
		*
		*  @return   const KNodeDataMap& ������������(û�����Է���NULL)
		*/
		virtual const KNodeDataMap& GetDataMap() const;

		/**
		*  @brief    ����Tag��ȡ�����ӽڵ�(����������)
		*
		*  @param    KNodeList& childNodes* ���������ƶ�TAG�ӽڵ��б�
		*  @param    int nTag KNODE_NONE_TAG
		*/
		virtual void GetAllNode(KNodeMap& childNodes, int nTag = KNODE_NONE_TAG) const;

	public:
		/**
		*  @brief    ��XML�ڵ��м�������
		*
		*  @param    CXmlElement* pXmlElm XML�ڵ�ָ��
		*  @param    bool bRecursion �Ƿ�ݹ�
		*  @return   bool �ɹ�����true
		*/
		bool LoadFromXmlElm(void* pXmlElm, bool bRecursion = true);

		/**
		*  @brief    �������ݵ�XML�ڵ�
		*
		*  @param    CXmlElement* pXmlElm XML�ڵ�ָ��
		*  @param    bool bRecursion �Ƿ�ݹ�
		*  @return   bool �ɹ�����true
		*/
		bool SaveToXmlElm(void* pXmlElm, bool bRecursion = true) const;

		/**
		*  @brief    ���ط־�XMDX���ļ�����
		*
		*  @param    const CString& strFile ���ص��ļ���
		*  @param    bool bRecursion �Ƿ�ݹ�
		*  @return   bool �ɹ�����true
		*/
		bool LoadFromLargeXmdx(const CString& strFile, bool bRecursion = true);

		/*
		* @brief     �������ݵ�XMDX�ļ�
		*
		*  @param    const CString& strFile ������ļ���
		*  @param    bool bRecursion �Ƿ�ݹ�
		*  @return   bool �ɹ�����true
		*/
		bool SaveToLargeXmdx(const CString& strFile, bool bRecursion = true) const;

		/**
		*  @brief    ��IXmdxElementReader��������
		*
		*  @param    IXmdxElementReader* pElmReader ��ELM�м�������
		*  @param    bool bRecursion �Ƿ�ݹ�
		*  @return   bool �ɹ�����true
		*/
		bool LoadFromXmdxElm(void* pElmReader, bool bRecursion = true);

		/*
		* @brief     �������ݵ�IXmdxElementWriter��
		*
		*  @param    IXmdxElementWriter* pElmWriter ��������ELM��
		*  @param    bool bRecursion �Ƿ�ݹ�
		*  @return   bool �ɹ�����true
		*/
		bool SaveToXmdxElm(void* pElmWriter, bool bRecursion = true) const;

		/**
		*  @brief    ���������ӿ�
		*
		*  @param    KNodeUndo* pUndo �����ӿ�ָ��(�ⲿ�ͷ�)
		*/
		void AttachUndo(KNodeUndo* pUndo);

	protected:
		CGuid			_id;					///< Ψһ��ʶ
		int				_nTag;					///< ���ͱ�ʶ
		CString			_strElementName;		///< xml���ؼ�¼�ڵ�����
		KNode*			_pParent;				///< ���ڵ�ָ��
		KNodeList*		_pNodes;				///< �ӽڵ��б� 
		KNodeDataMap*	_pDataMap;				///< ���Լ���
		KNodeUndo*		_pUndo;					///< �ڵ㳷��
	};
}
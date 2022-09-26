//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           StandardTreeListCtrl.H
//    @author         zy
//    @data           2015/6/29 15:30
//    @brief          ��׼����Դ�������б�ؼ�
//*****************************************************

#pragma once

#include "TreeListCtrl.h"

// ����Դ�ӽڵ��б�����
class CStandardDataSource;
typedef std::vector<CStandardDataSource*> SubNodeList;
typedef SubNodeList::iterator SubNodeListIter;

// ����Դ������ݵ���������
typedef std::map<int, CString> DataSourceStrVec;
typedef DataSourceStrVec::iterator DataSourceStrVecIter;

// ����Դ��Ԫ��������������
typedef std::map<int, EDITCONFIG> ConfigArr;
typedef ConfigArr::iterator ConfigArrIter;

/**
*  @class	��׼����Դ
*
*  @brief	֧�ֿؼ���
*/
class CStandardDataSource : public IListDataSource
{
public:
	/**
	*  @brief    ���캯��
	*
	*  @param    CStandardDataSource * pParentNode	���ø��ڵ� 
	*/
	CStandardDataSource(CStandardDataSource* pParentNode, bool bCellOwnCfg);
	~CStandardDataSource();

public:
	/**
	*  @brief    ������������
	*
	*  @param    bool bCellOwnCfg	��Ԫ������
	*  @return   void
	*/
	void SetCfgType(bool bCellOwnCfg);

	/**
	*  @brief    ��ȡ������Ŀ
	*
	*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
	*  @return   size_t ����������Ŀ
	*/
	virtual size_t GetCount(CTreeListConfig* pConfig);

	/**
	*  @brief    ��ȡָ����������
	*
	*  @param    size_t nIndex ��������
	*  @param    bool bShowItem ����true��������ݽ���ʾ�ڿؼ��ϣ����ڹ��˲���Ҫ��ʾ���м�ڵ㣩
	*  @param    HITEMDATA hItemData �б�������(ֻ�е�һ�����ò�����)
	*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
	*  @return   IListDataSource*& pListDataSource ��ǰ��ȡ��������Դ
	*/
	virtual IListDataSource* GetItem(size_t nIndex, bool& bShowItem,
		HITEMDATA hItemData, CTreeListConfig* pConfig);

	/**
	*  @brief    ��ȡ��Ԫ��������Ϣ
	*
	*  @param    size_t nCol ��Ԫ��������
	*  @param    size_t nRow ��Ԫ��������
	*  @param    const HCOLUMNDATA hColumnData ��ͷ��Ϣ
	*  @param    HCELLDATA hCellData ���ص�Ԫ��������
	*  @param    HEDITCONFIG hEditConfig ���ر༭��������
	*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
	*/
	virtual void GetCellData(size_t nCol, size_t nRow,
		const HCOLUMNDATA hColumnData, HCELLINFO hCellData, HEDITCONFIG hEditConfig, CTreeListConfig* pConfig);

	/**
	*  @brief    ��ȡ��Ԫ���ı�����
	*
	*  @param    size_t nCol ��Ԫ��������
	*  @param    size_t nRow ��Ԫ��������
	*  @param    const HEDITCONFIG hEditConfig �༭��������
	*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
	*  @return   CString ���ص�Ԫ���ı�����
	*/
	virtual CString GetCellText(size_t nCol, size_t nRow,
		const HEDITCONFIG hEditConfig, CTreeListConfig* pConfig);

	/**
	*  @brief    ���õ�Ԫ���ı�����
	*
	*  @param    size_t nCol	��Ԫ��������
	*  @param    const CString& strNewValue	���õ�ֵ
	*  @return   bool	����true���޸ĳɹ�
	*/
	virtual CString GetCellText(size_t nCol);

	/**
	*  @brief    ���õ�Ԫ���ı�����
	*
	*  @param    size_t nCol ��Ԫ��������
	*  @param    size_t nRow ��Ԫ��������
	*  @param    const HEDITCONFIG hEditConfig �༭��������
	*  @param    const CString& strNewValueg ��ǰ���õ�ֵ
	*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
	*  @return   bool ����true���޸ĳɹ�
	*/
	virtual bool SetCellText(size_t nCol, size_t nRow,
		const HEDITCONFIG hEditConfig, const CString& strNewValue, CTreeListConfig* pConfig);

	/**
	*  @brief    ���õ�Ԫ���ı�����
	*
	*  @param    size_t nCol	��Ԫ��������
	*  @param    const CString& strNewValue	���õ�ֵ
	*  @return   bool	����true���޸ĳɹ�
	*/
	virtual bool SetCellText(size_t nCol, const CString& strNewValue);

	/**
	*  @brief    ����������Դ
	*
	*  @param    size_t nIndex	�ӽڵ��ڸ��ڵ���λ�ã�0���뵽��ǰ��-1���뵽���
	*  @return   CStandardDataSource *	�����ӽڵ�
	*/
	CStandardDataSource *InsertChild(size_t nIndex);

	/**
	*  @brief    ��ȡ�ӽڵ��б�
	*
	*  @return   SubNodeList &	�ӽڵ��б�
	*/
	SubNodeList &GetSubNodeList();

	/**
	*  @brief    ���õ�ǰ����Դĳ�е�Ԫ����ʽ
	*
	*  @param    size_t nColumn	����
	*  @param    const EDITCONFIG & eCellConfig	��ʽ�ṹ��
	*/
	void SetCellConfig(size_t nColumn, const EDITCONFIG& eCellConfig);

	/**
	*  @brief    ��ȡ��ǰ����Դ�ĸ��ڵ�
	*
	*  @return   CStandardDataSource *	���ڵ�ָ��
	*/
	CStandardDataSource *GetParentNode();

	/**
	*  @brief    ��ȡ��Ԫ������
	*
	*  @param    size_t nColumn	�к�
	*  @return   EDITCONFIG	����
	*/
	EDITCONFIG GetCellCfg(size_t nColumn);

private:
	/**
	*  @brief    ��ȡ����ԴΨһ��ʶ(ֻ�ܿؼ�����)
	*
	*  @return   size_t ��������ԴΨһ��ʶ
	*/
	virtual size_t GetKey();

private:
	DataSourceStrVec _strDataArr;		///< ����Դ��������
	SubNodeList _subNodeList;			///< �ӽڵ�����
	CStandardDataSource *_pParentNode;	///< ���ڵ�
	ConfigArr _cellConfig;				///< ��Ԫ����������
	bool _bCellOwnCfg;					///< ��Ԫ�������־λ
};


/**
*  @class	��������Դ�������б�ؼ�
*
*  @brief	�ں���׼����Դ
*/
class COMMONCONTROLS_API CStandardTreeListCtrl : public CTreeListCtrl
{
public:
	CStandardTreeListCtrl(bool bCellOwnCfg = false);
	~CStandardTreeListCtrl();

public:
	/**
	*  @brief    ���ÿؼ���������
	*
	*  @param    bool bCellOwnCfg	��Ԫ������
	*  @return   void
	*/
	void SetTreeListCfgType(bool bCellOwnCfg);

	/**
	*  @brief    ����β��������
	*
	*  @return   HCOLUMNDATA	����������
	*/
	HCOLUMNDATA InsertColumn();

	/**
	*  @brief    ��ȡ����Ϣ
	*
	*  @param    size_t nColumn	�к�
	*  @return   HCOLUMNDATA	��Ϣ�ṹ
	*/
	HCOLUMNDATA GetColInfo(size_t nColumn);

	/**
	*  @brief    ������
	*
	*  @param    size_t nIndex	����
	*  @param    const CString & strText	��һ������
	*  @param    CStandardDataSource * pParentNode	���ڵ�
	*  @return   CStandardDataSource*	�����ӽڵ㣬�������ʧ��ΪNULL
	*/
	CStandardDataSource* InsertRow(size_t nIndex, const CString& strText, CStandardDataSource* pParentNode = NULL);

	/**
	*  @brief    ɾ����
	*
	*  @param    size_t nIndex	���
	*  @param    IModelNode * pParentNode	ɾ���еĸ��ڵ�
	*/
	void DeleteRow(size_t nIndex, CStandardDataSource* pParentNode = NULL);

	/**
	*  @brief    ɾ��������
	*/
	void DeleteAllRow();

	/**
	*  @brief    ���õ�Ԫ������
	*
	*  @param    size_t nRow	����
	*  @param    size_t nColumn	����
	*  @param    const CString & strCellText	����
	*/
	void SetCellText(size_t nRow, size_t nColumn, const CString& strCellText);

	/**
	*  @brief    ����������Ԫ������
	*
	*  @param    size_t nRow	����
	*  @param    size_t nColumn	����
	*  @param    const CString & strCellText	����������������
	*  @param    int nComboIndex	������ţ�Ĭ�ϲ�����
	*  @return   bool	���ý��
	*/
	bool SelectCellText(size_t nRow, size_t nColumn, const CString& strCellText, int nComboIndex = -1);

	/**
	*  @brief    ���õ�Ԫ����ʽ
	*
	*  @param    size_t nRow	����
	*  @param    size_t nColumn	����
	*  @param    const EDITCONFIG & eCellConfig	��ʽ�ṹ��
	*/
	void SetCellConfig(size_t nRow, size_t nColumn, const EDITCONFIG& eCellConfig);

	/**
	*  @brief    ��ȡ����
	*
	*  @return   size_t	��������
	*/
	size_t GetRowsNum() const;

	/**
	*  @brief    ��ȡ��Ԫ������
	*
	*  @param    size_t nRow	����
	*  @param    size_t nColumn	����
	*  @return   CString	��������
	*/
	CString GetCellText(size_t nRow, size_t nColumn);

	/**
	*  @brief    ��������
	*
	*/
	void UpdateList();

protected:
	/**
	*  @brief    �ݹ�����ҵ��ӽڵ�
	*
	*  @param    CStandardDataSource * pParentNode	���ڵ�
	*  @param    CStandardDataSource * pChildNode	���ҵ��ӽڵ�
	*  @return   bool	���ҽ��
	*/
	bool FindChildNode(CStandardDataSource* pParentNode, CStandardDataSource* pChildNode);

	/**
	*  @brief    ��ȡ����Դ�ڵ�
	*
	*  @param    size_t nRow	����
	*  @param    size_t nColumn	����
	*  @return   CStandardDataSource*	��������Դ
	*/
	CStandardDataSource* GetDataSource(size_t nRow, size_t nColumn);

protected:
	CStandardDataSource *_pRootDataSource;	///< ������Դ
	bool	_bCellOwnCfg;					///< ��Ԫ����������
};

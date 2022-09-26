//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           StandardTreeListCtrl.CPP
//    @author         zy
//    @data           2015/6/29 15:29
//    @brief          ��׼����Դ�������б�ؼ�ʵ��
//*****************************************************

#include "StdAfx.h"
#include "StandardTreeListCtrl.h"


CStandardDataSource::CStandardDataSource(CStandardDataSource* pParentNode, bool bCellOwnCfg)
{
	_pParentNode = pParentNode;
	_bCellOwnCfg = bCellOwnCfg;
}

CStandardDataSource::~CStandardDataSource()
{
}

size_t CStandardDataSource::GetCount(CTreeListConfig* pConfig)
{
	// �����ӽڵ���Ŀ
	return _subNodeList.size();
}

IListDataSource* CStandardDataSource::GetItem(size_t nIndex, bool& bShowItem, 
	HITEMDATA hItemData, CTreeListConfig* pConfig)
{
	// �õ��ӽڵ�
	if (nIndex >= _subNodeList.size())
	{
		return NULL;
	}

	return _subNodeList.at(nIndex);
}

void CStandardDataSource::GetCellData(size_t nCol, size_t nRow, 
	const HCOLUMNDATA hColumnData, HCELLINFO hCellData, HEDITCONFIG hEditConfig, CTreeListConfig* pConfig)
{
	if (_bCellOwnCfg)
	{
		// ��Ԫ���������
		*hEditConfig = _cellConfig[(int)nCol];
	}
	else
	{
		// ��Ԫ�����и�ʽ
		hEditConfig->CopyFrom(hColumnData->editConfig);
	}
}

CString CStandardDataSource::GetCellText(size_t nCol, size_t nRow, 
	const HEDITCONFIG hEditConfig, CTreeListConfig* pConfig)
{
	if (!_strDataArr.count((int)nCol))
	{
		return _T("");
	}

	// ��ȡ��ǰ�ڵ�����
	return _strDataArr[(int)nCol];
}

CString CStandardDataSource::GetCellText(size_t nCol)
{
	// ��ȡ��ǰ����
	return _strDataArr[(int)nCol];
}

bool CStandardDataSource::SetCellText(size_t nCol, size_t nRow, 
	const HEDITCONFIG hEditConfig, const CString& strNewValue, CTreeListConfig* pConfig)
{
	return SetCellText(nCol, strNewValue);
}

bool CStandardDataSource::SetCellText(size_t nCol, const CString& strNewValue)
{
	// ���õ�ǰ�ڵ�����
	_strDataArr[(int)nCol] = strNewValue;

	return true;
}

size_t CStandardDataSource::GetKey()
{
	// ��ȡΨһ��ʶ
	return size_t(this);
}

CStandardDataSource * CStandardDataSource::InsertChild(size_t nIndex)
{
	// ������Ų������б�ǰ����
	if (nIndex > _subNodeList.size())
	{
		return NULL;
	}

	CStandardDataSource *pChildNode = new CStandardDataSource(this, _bCellOwnCfg);

	// ���뵽�м��β��
	if (nIndex < _subNodeList.size())
	{
		_subNodeList.insert(_subNodeList.begin() + nIndex, pChildNode);
	}
	else
	{
		_subNodeList.push_back(pChildNode);
	}	

	return pChildNode;
}

SubNodeList &CStandardDataSource::GetSubNodeList()
{
	return _subNodeList;
}

void CStandardDataSource::SetCellConfig(size_t nColumn, const EDITCONFIG& eCellConfig)
{
	int nCol = (int)nColumn;

	// ���õ�Ԫ������
	_cellConfig[nCol].comboDataFile = eCellConfig.comboDataFile;
	_cellConfig[nCol].image = eCellConfig.image;
	_cellConfig[nCol].dotNum = eCellConfig.dotNum;
	_cellConfig[nCol].option = eCellConfig.option;
	_cellConfig[nCol].field = eCellConfig.field;
	_cellConfig[nCol].enumerate = eCellConfig.enumerate;
	_cellConfig[nCol].comboList = eCellConfig.comboList;
}

CStandardDataSource * CStandardDataSource::GetParentNode()
{
	// ���ظ��ڵ�
	return _pParentNode;
}

void CStandardDataSource::SetCfgType(bool bCellOwnCfg)
{
	_bCellOwnCfg = bCellOwnCfg;
}

EDITCONFIG CStandardDataSource::GetCellCfg(size_t nColumn)
{
	return _cellConfig[(int)nColumn];
}





CStandardTreeListCtrl::CStandardTreeListCtrl(bool bCellOwnCfg)
{
	// ������׼����Դ������
	_bCellOwnCfg = bCellOwnCfg;
	_pRootDataSource = new CStandardDataSource(NULL, bCellOwnCfg);
	SetDataSource(_pRootDataSource, false);
}

CStandardTreeListCtrl::~CStandardTreeListCtrl()
{
	if (_pRootDataSource != NULL)
	{
		delete _pRootDataSource;
	}	
}

HCOLUMNDATA CStandardTreeListCtrl::InsertColumn()
{
	// ��ֹ������ʱ�ͷ�����Դָ��
	_listDataSource.clear();
	
	// ���뵽��β
	HCOLUMNDATA colInfo = CTreeListCtrl::InsertColumn(_columnVector.size());

	return colInfo;
}

CStandardDataSource* CStandardTreeListCtrl::InsertRow(size_t nIndex, const CString& strText,
	CStandardDataSource* pParentNode /*= NULL*/)
{
	CStandardDataSource* pTmpNode = NULL;

	if (pParentNode == NULL)
	{
		// ȱʡ���ڵ��Ǹ��ڵ�
		pTmpNode = _pRootDataSource;
	}
	else
	{
		// ָ���ĸ��ڵ��Ƿ��ڸ��ڵ���
		pTmpNode = pParentNode;
		if (!FindChildNode(_pRootDataSource, pParentNode))
		{
			return NULL;
		}
	}

	// ��ָ�����в����ӽڵ�
	CStandardDataSource* pChildNode = pTmpNode->InsertChild(nIndex);
	_ASSERTE(pChildNode != NULL);

	// ������������
	pChildNode->SetCellText(0, strText);

	return pChildNode;
}

void CStandardTreeListCtrl::DeleteRow(size_t nIndex, CStandardDataSource* pParentNode /*= NULL*/)
{
	CStandardDataSource* pTmpNode = NULL;

	if (pParentNode == NULL)
	{
		// ȱʡ���ڵ��Ǹ��ڵ�
		pTmpNode = _pRootDataSource;
	}
	else
	{
		// ָ���ĸ��ڵ��Ƿ��ڸ��ڵ���
		pTmpNode = pParentNode;
		if (!FindChildNode(_pRootDataSource, pParentNode))
		{
			return;
		}
	}

	// ��ų����ӽڵ���
	SubNodeList &nodeList = pTmpNode->GetSubNodeList();
	if (nodeList.size() <= nIndex)
	{
		return;
	}

	// �����ӽڵ��²�ɾ��
	CStandardDataSource* pChildNode = nodeList.at(nIndex);
	SubNodeList &childNodeList = pChildNode->GetSubNodeList();
	while (childNodeList.size() > 0)
	{
		DeleteRow(childNodeList.size() - 1, pChildNode);
	}

	// ���ӽڵ��б����Ƴ���Ӧ�ڵ�
	nodeList.erase(nodeList.begin() + nIndex);
	delete pChildNode;
}

void CStandardTreeListCtrl::DeleteAllRow()
{
	// �Ѹ��ڵ���������Դɾ��
	SubNodeList &nodeList = _pRootDataSource->GetSubNodeList();

	while (nodeList.size() > 0)
	{
		DeleteRow(nodeList.size() - 1);
	}
}

void CStandardTreeListCtrl::SetCellText(size_t nRow, size_t nColumn, const CString& strCellText)
{
	// ��ȡ����Դ�����õ�Ԫ������
	CStandardDataSource* pDataSource = GetDataSource(nRow, nColumn);

	pDataSource->SetCellText(nColumn, strCellText);
}

void CStandardTreeListCtrl::UpdateList()
{
	// ��տؼ�����Դ����
	// ��ֹ���ݽڵ�ˢ�º�ɾ��
	_listDataSource.clear();
	CTreeListCtrl::UpdateList(true);
}

void CStandardTreeListCtrl::SetCellConfig(size_t nRow, size_t nColumn, const EDITCONFIG& eCellConfig)
{
	// ��ȡ����Դ�����õ�Ԫ����ʽ
	CStandardDataSource* pDataSource = GetDataSource(nRow, nColumn);

	pDataSource->SetCellConfig(nColumn, eCellConfig);
}

bool CStandardTreeListCtrl::FindChildNode(CStandardDataSource* pParentNode, CStandardDataSource* pChildNode)
{
	// �ݹ�������еĽڵ�
	SubNodeList nodeList = pParentNode->GetSubNodeList();
	SubNodeListIter nodeIter = nodeList.begin();
	SubNodeListIter endter = nodeList.end();

	for (; nodeIter != endter; ++nodeIter)
	{
		// �ҵ���ͬ�Ľڵ�
		if (pChildNode == (*nodeIter))
		{
			return true;
		}

		// �����ӽڵ����
		if (FindChildNode((*nodeIter), pChildNode))
		{
			return true;
		}
	}

	return false;
}

CStandardDataSource* CStandardTreeListCtrl::GetDataSource(size_t nRow, size_t nColumn)
{
	// ��ȡԽ�����
 	_ASSERTE(nColumn < _columnVector.size() && nRow < _listDataSource.size());

	// �ҵ�������Ӧ������
	ListDataSourceIter dataIter = _listDataSource.begin();	
	size_t nIndex = nRow;
	while (nIndex--)
	{
		++dataIter;
	}

	// ͨ���ؼ�����Դ�����õ�ʵ������Դ
	CStandardDataSource* pDataSource =
		dynamic_cast<CStandardDataSource*>(dataIter->second->GetDataSource());
	_ASSERTE(pDataSource != NULL);

	return pDataSource;
}

size_t CStandardTreeListCtrl::GetRowsNum() const
{
	return _listDataSource.size();
}

CString CStandardTreeListCtrl::GetCellText(size_t nRow, size_t nColumn)
{
	// ��ȡ����Դ
	CStandardDataSource* pDataSource = GetDataSource(nRow, nColumn);

	return pDataSource->GetCellText(nColumn);
}

HCOLUMNDATA CStandardTreeListCtrl::GetColInfo(size_t nColumn)
{
	return _columnVector.at(nColumn);
}

bool CStandardTreeListCtrl::SelectCellText(size_t nRow, size_t nColumn, 
	const CString& strCellText, int nComboIndex)
{	
	CStringVector comboList;

	if (_bCellOwnCfg)
	{
		CStandardDataSource* pDataSource = GetDataSource(nRow, nColumn);
		comboList = pDataSource->GetCellCfg(nColumn).comboList;
	}
	else
	{
		HCOLUMNDATA colInfo = _columnVector.at(nColumn);
		comboList = colInfo->editConfig.comboList;
	}
	
	CStringVectorIter textIter = std::find(comboList.begin(), comboList.end(), (LPCTSTR)strCellText);
	if (textIter == comboList.end())
	{
		if (nComboIndex >= 0 && nComboIndex < (int)comboList.size())
		{
			SetCellText(nRow, nColumn, comboList.at(nComboIndex));
			return true;
		}
		else
			return false;
	}
	else
	{
		SetCellText(nRow, nColumn, strCellText);
	}
	
	return true;
}

void CStandardTreeListCtrl::SetTreeListCfgType(bool bCellOwnCfg)
{
	_bCellOwnCfg = bCellOwnCfg;
	_pRootDataSource->SetCfgType(bCellOwnCfg);
}

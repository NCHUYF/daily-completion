#include "StdAfx.h"
#include "TreeListCfg.h"
#include <algorithm>
#include "TreeListCtrl.h"

BEGIN_ENUMTYPENAME_CONVERSION(EFormatType)
{
	{ FORMAT_LEFT, _T("�����") },
	{ FORMAT_MIDDLE, _T("���ж���") },
	{ FORMAT_RIGHT, _T("�Ҷ���") },
	{ NULL, NULL}
}
END_ENUMTYPENAME_CONVERSION(EFormatType);

BEGIN_ENUMTYPENAME_CONVERSION(ETreeListEditFlag)
{
	{ eNoneEdit, _T("�ޱ༭") },
	{ eNormalEdit, _T("��ͨ�༭") },
	{ eValidEdit, _T("����༭") },
	{ eFileNameEdit, _T("�ļ����༭") },
	{ eDateTimeEdit, _T("���ڱ༭��") },
	{ eDropListCobEdit, _T("����ѡ���") },
	{ eDropDownCobEdit, _T("�ɱ༭������ѡ���") },
	{ eCheckBoxEdit, _T("��ѡ��") },
	{ eCheckBox3StateEdit, _T("��̬��ѡ��") },
	{ eHyperLinkEdit, _T("������") },
	{ eAngleEdit, _T("�Ƕ�") },
	{ eTreeComboEdit, _T("��������") },
	{ eProgressEdit, _T("������") },
	{ eTreeCheckComboEdit, _T("��������ѡ��") },
	{ eRangelEdit, _T("��Χ�༭�ؼ�") },
	{ eAutoSearchCombo, _T("�Զ�������Ͽ�") },
	{ eTreeComboManualEdit, _T("�ɱ༭����������") },
	{ eTreeCheckComboManualEdit, _T("�ɱ༭����������ѡ��") },
	{ NULL, NULL }
}
END_ENUMTYPENAME_CONVERSION(ETreeListEditFlag);

BEGIN_ENUMTYPENAME_CONVERSION(EValidEditControlFlag)
{
	{ eVeDecimal, _T("��������С��") },
	{ eVeNegative, _T("�������븺��") },
	{ eVeDotNum, _T("��������С��λ��") },
	{ eVeNoZero, _T("��ֹ����0") },
	{ eVeNoEmpty, _T("������Ϊ��") },
	{ eVePreZero, _T("����ǰ����") },
	{ NULL, NULL }
}
END_ENUMTYPENAME_CONVERSION(EValidEditControlFlag);

BEGIN_ENUMTYPENAME_CONVERSION(ETreeComboEditControlFlag)
{
	{ eTreeHasSelAll, _T("�Զ����ȫѡ") },
	{ eTreeHasNoLimit, _T("�Զ���Ӳ���") },
	{ eTreeAutoWidth, _T("�Զ������������") },
	{ eTreeSelNotByText, _T("��ͨ������ֵ����ѡ��") },
	{ NULL, NULL }
}
END_ENUMTYPENAME_CONVERSION(ETreeComboEditControlFlag);


BEGIN_ENUMTYPENAME_CONVERSION(EDateTimeEditFlag)
{
	{ eDateSlashYMD, _T("б��������") },
	{ eDateChineseYMD, _T("����������") },
	{ eDateDashYMD, _T("����������") },
	{ NULL, NULL }
}
END_ENUMTYPENAME_CONVERSION(EDateTimeEditFlag);

BEGIN_ENUMTYPENAME_CONVERSION(EProgressControlFlag)
{
	{ ePrgShowText, _T("��ʾ��������") },
	{ NULL, NULL }
}
END_ENUMTYPENAME_CONVERSION(EProgressControlFlag);

CTreeListConfig::CTreeListConfig(CTreeListCtrl* pTreeListCtrl)
{
	_colWdithScale = 1;
	_pTreeListCtrl = pTreeListCtrl;
}

CTreeListConfig::~CTreeListConfig()
{
	ClearCellConfigVectors();
}

void CTreeListConfig::ClearCellConfigVectors()
{
	size_t nRowCount = _cellCfgVectors.size();
	for (size_t nRow = 0; nRow < nRowCount; ++nRow)
	{
		size_t nColCount = _cellCfgVectors[nRow].size();
		for (size_t nCol = 0; nCol < nColCount; ++nCol)
		{
			delete _cellCfgVectors[nRow][nCol];
		}
		_cellCfgVectors[nRow].clear();
	}

	_cellCfgVectors.clear();
}

CTreeListCtrl* CTreeListConfig::GetTreeListCtrl()
{
	return _pTreeListCtrl;
}

bool CTreeListConfig::LoadConfig(const CString& strCfgFile, const CString& strCfgName)
{
	CXmlDocument xmlDoc;

	// ���������ļ�
	if (!xmlDoc.LoadFile(strCfgFile, fmtXML))
		return false;

	CXmlElement* pRoot = xmlDoc.GetElementRoot();
	if (NULL == pRoot || 0 == pRoot->GetChildElementCount())
		return false;

	// ���û��ָ������������ص�һ������
	CXmlElement* pTreeConfig = strCfgName.IsEmpty() ?
		pRoot->GetChildElements()->GetAt(0) : pRoot->GetChildElementAt(strCfgName);
	if (NULL == pTreeConfig)
		return false;

	// ��ȡ�������ű���
	_colWdithScale = _pTreeListCtrl->GetFontScale();

	// ��ȡ��ͷ�ڵ㲢����
	CXmlElement* pListHeader = pTreeConfig->GetChildElementAt(L"ListHeader", FALSE);
	if (!LoadColumn(pListHeader, NULL))
		return false;

	// �����й�����
	CXmlElement* pRowFilter = pTreeConfig->GetChildElementAt(L"RowFilter", FALSE);
	if (NULL != pRowFilter)
	{
		// �������͹�����
		LoadTypeFilter(pRowFilter->GetChildElementAt(L"TypeFilter"));
	}

	// ��������������
	CXmlElement* pListData = pTreeConfig->GetChildElementAt(L"ListData", FALSE);
	if (NULL != pListData)
	{
		LoadListData(pListData);
	}

	return true;
}

bool CTreeListConfig::IsTypeInFilter(int nType)
{
	if (_typeFilter.empty())
		return true;

	return (_typeFilter.end() != std::find(_typeFilter.begin(), _typeFilter.end(), nType));
}

const CellConfigVectors& CTreeListConfig::GetCellConfigVectors()
{
	return _cellCfgVectors;
}

bool CTreeListConfig::GetCellConfigByRowCol(size_t nRow, size_t nCol, HCELLCONFIG& pCellCfg)
{
	pCellCfg = NULL;

	if (nRow >= _cellCfgVectors.size())
		return false;

	// ��ȡ��Ԫ���������Ϣ;
	const CellConfigVector& cellRow = *(_cellCfgVectors.begin() + nRow);
	if (nCol >= cellRow.size())
		return false;

	pCellCfg = *(cellRow.begin() + nCol);

	return true;
}

bool CTreeListConfig::LoadColumn(CXmlElement* pColumnCfg, HCOLUMNDATA hParentColumn)
{
	if (NULL == pColumnCfg)
		return false;

	CXmlElements* pHeaderList = pColumnCfg->GetChildElements(FALSE);
	if (NULL == pHeaderList)
		return false;

	if (NULL == hParentColumn)
	{
		// ���������
		_pTreeListCtrl->DeleteAllColumn();

		// �����и߶�
		CString strHeight = pColumnCfg->GetAttrValue(L"Height", L"0");
		_pTreeListCtrl->SetHeadItemHeight(_ttoi(strHeight));

		CString strWordWarp = pColumnCfg->GetAttrValue(L"WordWarp", L"0");
		_pTreeListCtrl->SetColumnWordWarp(!!_ttoi(strWordWarp));
	}

	// ������ͷ
	size_t nColIndex = 0;
	size_t nCount = pHeaderList->GetCount();
	for (size_t i = 0; i < nCount; ++i)
	{
		CString strText;
		CXmlElement* pHeader = pHeaderList->GetAt(i);

		CString strElmName = pHeader->GetElementName();
		if (strElmName == L"CellCfg" && hParentColumn)
		{
			// ���ر�ͷ��Ԫ��������Ϣ
			LoadEditConfig(pHeader, &hParentColumn->editConfig);
			continue;
		}

		// ��ͷ����ʾ(Ĭ����ʾ)
		strText = pHeader->GetAttrValue(L"Show", L"1");
		if (strText.IsEmpty() || strText == L"0")
			continue;

		// ���һ���±�ͷ
		HCOLUMNDATA hColumn = _pTreeListCtrl->InsertColumn(nColIndex, hParentColumn);

		strText = pHeader->GetAttrValue(L"Fixed");
		if (!strText.IsEmpty())
			hColumn->fixed = !!_ttoi(strText);

		strText = pHeader->GetAttrValue(L"Image");
		if (!strText.IsEmpty())
			hColumn->image = _ttoi(strText);

		strText = pHeader->GetAttrValue(L"Width");
		if (!strText.IsEmpty())
		{
			// ����125%��������
			int nWidth = int(_ttoi(strText) * _colWdithScale);
			hColumn->SetWidth(nWidth);
		}

		strText = pHeader->GetAttrValue(L"HeaderFormat");
		if (!strText.IsEmpty())
			hColumn->headerformat = GetFormatEnum(strText);

		strText = pHeader->GetAttrValue(L"Format");
		if (!strText.IsEmpty())
			hColumn->format = GetFormatEnum(strText);

		strText = pHeader->GetAttrValue(L"TextColor");
		if (!strText.IsEmpty())
			hColumn->textColor = GetStringColor(strText);

		strText = pHeader->GetAttrValue(L"Title");
		if (!strText.IsEmpty())
			hColumn->title = strText;

		strText = pHeader->GetAttrValue(L"SortType");
		if (!strText.IsEmpty())
			hColumn->sortType = _ttoi(strText);

		// ��������չ����;
		strText = pHeader->GetAttrValue(L"IsTreeCol");
		if (!strText.IsEmpty() && !!_ttoi(strText))
			_pTreeListCtrl->SetTreeColumn((int)nColIndex);

		// ��������ͷ��������������
		LoadColumn(pHeader, hColumn);

		// ������
		nColIndex++;
	}

	return true;
}

void CTreeListConfig::LoadListData(CXmlElement* pListData)
{
	CXmlElements* pRowList = pListData->GetChildElements(FALSE);
	if (NULL == pRowList)
		return;

	ClearCellConfigVectors();

	// ������ͷ
	size_t nRowCount = pRowList->GetCount();
	for (size_t nRow = 0; nRow < nRowCount; ++nRow)
	{
		CXmlElement* pRow = pRowList->GetAt(nRow);
		CXmlElements* pCellList = pRow->GetChildElements();

		_cellCfgVectors.push_back(CellConfigVector());
		CellConfigVector& rowList = _cellCfgVectors.back();

		size_t nCellCount = pCellList->GetCount();
		for (size_t nCell = 0; nCell < nCellCount; ++nCell)
		{
			CXmlElement* pClell = pCellList->GetAt(nCell);

			CString strText;
			HCELLCONFIG hCellCfg = new CELLCONFIG();

			// ���ص�Ԫ����������
			strText = pClell->GetAttrValue(L"Text");
			if (!strText.IsEmpty())
				hCellCfg->cellText = strText;

			strText = pClell->GetAttrValue(L"Readonly");
			if (!strText.IsEmpty())
				hCellCfg->cellInfo.readonly = (_ttoi(strText) != 0);

			strText = pClell->GetAttrValue(L"TextColor");
			if (!strText.IsEmpty())
				hCellCfg->cellInfo.textColor = GetStringColor(strText);

			strText = pClell->GetAttrValue(L"BackColor");
			if (!strText.IsEmpty())
				hCellCfg->cellInfo.backColor = GetStringColor(strText);

			HCOLUMNDATA hColumnData = _pTreeListCtrl->GetColumn(nCell);

			// ���ر༭����
			CXmlElement* pCellCfg = pClell->GetChildElementAt(L"CellCfg", FALSE);
			if (NULL != pCellCfg)
			{
				LoadEditConfig(pCellCfg, &(hCellCfg->editConfig), &(hColumnData->editConfig));
			}
			else
			{
				hCellCfg->editConfig = hColumnData->editConfig;
			}

			rowList.push_back(hCellCfg);
		}
	}
}

void CTreeListConfig::LoadTypeFilter(CXmlElement* pTypeFilter)
{
	if (NULL == pTypeFilter)
		return;

	CString strTypeList = pTypeFilter->GetAttrValue(L"TypeList");
	if (strTypeList.IsEmpty())
		return;

	// ��ȡ���˽ڵ�����
	int nWord = CStringToolkit::CountWord((LPCTSTR)strTypeList, L',');
	for (int i = 1; i <= nWord; ++i)
	{
		int nType = _wtoi(CStringToolkit::ReadWord((LPCTSTR)strTypeList, i, L','));
		_typeFilter.push_back(nType);
	}
}

void CTreeListConfig::LoadEditConfig(CXmlElement* pCellCfg, HEDITCONFIG hEditConfig,
	HEDITCONFIG hColEditConfig)
{
	CString strText;

	strText = pCellCfg->GetAttrValue(L"Image");
	if (!strText.IsEmpty())
		hEditConfig->image = _ttoi(strText);
	else if (NULL != hColEditConfig)
		hEditConfig->image = hColEditConfig->image;

	strText = pCellCfg->GetAttrValue(L"DotNum");
	if (!strText.IsEmpty())
		hEditConfig->dotNum = _ttoi(strText);
	else if (NULL != hColEditConfig)
		hEditConfig->dotNum = hColEditConfig->dotNum;

	strText = pCellCfg->GetAttrValue(L"Option");
	if (!strText.IsEmpty())
		hEditConfig->option = GetOptionEnum(strText);
	else if (NULL != hColEditConfig)
		hEditConfig->option = hColEditConfig->option;

	strText = pCellCfg->GetAttrValue(L"Field");
	if (!strText.IsEmpty())
		hEditConfig->field = strText;
	else if (NULL != hColEditConfig)
		hEditConfig->field = hColEditConfig->field;

	strText = pCellCfg->GetAttrValue(L"SplitChar");
	if (!strText.IsEmpty())
		hEditConfig->splitChar = strText;
	else if (NULL != hColEditConfig)
		hEditConfig->splitChar = hColEditConfig->splitChar;

	strText = pCellCfg->GetAttrValue(L"Enumerate");
	if (!strText.IsEmpty())
		hEditConfig->enumerate = strText;
	else if (NULL != hColEditConfig)
		hEditConfig->enumerate = hColEditConfig->enumerate;

	strText = pCellCfg->GetAttrValue(L"EventHandle");
	if (!strText.IsEmpty())
		hEditConfig->eventHandle = strText;
	else if (NULL != hColEditConfig)
		hEditConfig->eventHandle = hColEditConfig->eventHandle;

	// ����������
	CXmlElement* pComboxList = pCellCfg->GetChildElementAt(L"ComboBoxList", FALSE);
	if (NULL != pComboxList)
	{
		hEditConfig->comboDataFile = pComboxList->GetAttrValue(L"DataFile");

		CXmlElements* pChilds = pComboxList->GetChildElements();
		size_t nCount = pChilds->GetCount();
		for (size_t i = 0; i < nCount; ++i)
		{
			hEditConfig->comboList.push_back(pChilds->GetAt(i)->GetElementText());
		}
	}
	else if (NULL != hColEditConfig)
	{
		hEditConfig->comboList = hColEditConfig->comboList;
	}
}

COLORREF CTreeListConfig::GetStringColor(const CString& strColor)
{
	COLORREF color = RGB(0, 0, 0);

	int nFirst = strColor.Find(L",");
	if (-1 == nFirst)
		return color;

	int nSecond = strColor.Find(L",", nFirst + 1);
	if (-1 == nSecond)
		return color;

	return RGB(_ttoi(strColor.Mid(0, nFirst)),
		_ttoi(strColor.Mid(nFirst + 1, nSecond - nFirst - 1)),
		_ttoi(strColor.Mid(nSecond + 1, strColor.GetLength() - nSecond - 1)));
}

int CTreeListConfig::GetFormatEnum(const CString& str)
{
	return TextToEFormatType(str);
}

int CTreeListConfig::GetOptionEnum(const CString& str)
{
	//��Option�ؼ��ֶ�ӦֵΪ0��Ϊ��ʱ
	if (str == L"0" || str == L"")
	{
		return 0;
	}

	std::vector<CString> ArrStr;
	CStringToolkitEx::SplitString((LPCTSTR)str, ArrStr, L"|");

	//��ȡ��һ���ؼ���
	int nEditFlag = TextToETreeListEditFlag(ArrStr.at(0));
	int nSubFlag = 0;
	for (int i = 1; i < (int)ArrStr.size(); ++i)
	{
		switch (nEditFlag)
		{
		//������Ϊ�༭��
		case eNoneEdit:
		case eValidEdit:
		case eRangelEdit:
		{
			//���������༭��ר�ñ�־λ
			nSubFlag += TextToEValidEditControlFlag(ArrStr.at(i));
			break;
		}
		//������Ϊ��������
		case eTreeComboEdit:
		case eTreeComboManualEdit:
		{
			//��������������ר�ñ�־λ
			nSubFlag += TextToETreeComboEditControlFlag(ArrStr.at(i));
			break;
		}
		//������Ϊ���ڱ༭��
		case eDateTimeEdit:
		{
			//��������������ר�ñ�־λ
			nSubFlag += TextToEDateTimeEditFlag(ArrStr.at(i));
			break;
		}
		//������Ϊ������
		case eProgressEdit:
		{
			//��������������ר�ñ�־λ
			nSubFlag += TextToEProgressControlFlag(ArrStr.at(i));
			break;
		}
		case eTreeCheckComboEdit:
		{
			//����������������ѡ���־λ
			nSubFlag += TextToETreeComboEditControlFlag(ArrStr.at(i));
			break;
		}
		default:
			break;
		}
	}
	return nEditFlag + nSubFlag;
}

void CTreeListConfig::SetTempData(const CString& strTmpData)
{
	_strTmpData = strTmpData;
}

const CString& CTreeListConfig::GetTempData()
{
	return _strTmpData;
}

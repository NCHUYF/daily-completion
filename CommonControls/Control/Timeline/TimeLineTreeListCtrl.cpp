#include "stdafx.h"
#include "TimeLineTreeListCtrl.h"

BEGIN_MESSAGE_MAP(CTimeLineTreeListCtrl, CTreeListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

CTimeLineTreeListCtrl::CTimeLineTreeListCtrl(void)
{
	_showHeader = true;
	_hasGrid = true;
	_hasLine = true;
	_hDragingCol = NULL;
	_bBtnDown = false;
	_bMouseOver = false;
	_bSingleSelect = true;
	_nHeaderHeight = LIST_HEAD_HEIGHT;
	_iconSize = CSize(12, 12);
	_bkColor = GetSysColor(COLOR_WINDOW);
	_pListDataSource = NULL;
	_hHoverCol = NULL;
	_hPressCol = NULL;
	_hHoverRow = NULL;
	_nHoverRowIndex = -1;
	_lockTipUpdate = false;
	_nEditRowIndex = -1;
	_nEditColIndex = -1;
	_treeColumn = 0;
	_selTopColor = RGB(220, 235, 252);
	_selBottomColor = RGB(193, 219, 252);
	_selBorderColor = RGB(170, 200, 245);
	_hotTopColor = RGB(250, 251, 252);
	_hotBottomColor = RGB(233, 243, 253);
	_hotBorderColor = RGB(184, 214, 251);
	_gridColor = RGB(173, 193, 218);
	_bNoChild = true;
	_bDelDataSource = false;
	_pConfig = new CTreeListConfig(this);
	_pControl = NULL;
	_rcLastRect = CRect(0, 0, 0, 0);
	_bAutoColumnWidth = false;
	_nLastSelectItem = -1;
	_bUpDownFlag = false;
	_bLinkOn = false;
	_bColumnWordWarp = false;
	_bRowWordWarp = false;
	_nRowHeight = LIST_ROW_HEIGHT;

	_hIconCollapse = NULL;
	_hIconExpand = NULL;
	_hNofigyWnd = NULL;
	_bColumnSort = false;
	_bIsTrim = true;

	_pTimeLineCtrl = nullptr;
}

ListDataSource CTimeLineTreeListCtrl::GetListDataSource(void)
{
	return _listDataSource;
}

void CTimeLineTreeListCtrl::UpdateScrollBar(int scrollMode)
{
	CRect rcHeader = CalcHeaderRect();

	int nSumColumnWidth = 0;

	// ͳ����ͷ���
	size_t nCount = _columnVector.size();
	for (size_t i = 0; i < nCount; ++i)
	{
		nSumColumnWidth += _columnVector[i]->GetWidth();
	}

	SCROLLINFO scrInfo;
	scrInfo.cbSize = sizeof(scrInfo);

	scrInfo.fMask = SIF_PAGE | SIF_RANGE;
	scrInfo.nPage = rcHeader.Width();
	scrInfo.nMin = 0;
	scrInfo.nMax = nSumColumnWidth - 1;

	SetScrollInfo(SB_HORZ, &scrInfo);
}

void CTimeLineTreeListCtrl::DrawRow(CMemoryDC& dcMemory, const CRect& rcHeader, const CRect& rcList)
{
	// û����ͷ
	if (0 == _columnVector.size())
		return;

	// ��ȡ��ͷҶ�ӽڵ�
	ColumnDataVector leafColumnVector;
	GetColumnAllLeafStruct(leafColumnVector);

	// �е����߶�
	int nIncreaseHeight = 0;
	int nVertPos = GetOwner()->GetScrollPos(SB_VERT);

	HGDIOBJ hOldFont = dcMemory.SelectObject(_treeListFont);

	// ��¼��
	size_t nRow = 0;

	// ����������
	ListDataSourceIter endIter = _listDataSource.end();
	for (ListDataSourceIter iter = _listDataSource.begin();
		iter != endIter; ++iter, ++nRow)
	{
		HITEMDATA hItemData = iter->second;
		HITEMDATA hParentData = hItemData->hParentData;

		// ��ȡ��Ԫ������
		IListDataSource* pDataSource = hItemData->pDataSource;
		if (pDataSource == NULL)
			return;

		// ���ڽڵ��ϲ�������,��չ��
		if (NULL != hParentData && hParentData->IsCollapse())
		{
			hItemData->rowRect.SetRectEmpty();
			continue;
		}

		// ����������
		CRect rcRow;
		rcRow.left = _columnVector[0]->colRect.left;
		rcRow.top = nIncreaseHeight - nVertPos + rcHeader.bottom;
		rcRow.bottom = rcRow.top + _nRowHeight;
		rcRow.right = _columnVector[_columnVector.size() - 1]->colRect.right;

		// ��ȡÿ����Ԫʵ����Ϣ
		CellConfigArray cellCfgArray;

		int nMaxRowHeight = _nRowHeight;
		size_t nCount = leafColumnVector.size();
		cellCfgArray.resize(nCount);

		// ������ͷ��ǰ��ȡ��Ԫ���ı�(˳��ͳ�Ƽ����иߣ�
		for (size_t i = 0; i < nCount; ++i)
		{
			HCOLUMNDATA hColumnData = leafColumnVector[i];

			// ��ȡ��Ԫ���ı�
			CELLCONFIG& cellCfg = cellCfgArray[i];
			hItemData->pDataSource->GetCellData(i, nRow, hColumnData,
				&cellCfg.cellInfo, &cellCfg.editConfig, _pConfig);

			cellCfg.cellText = hItemData->pDataSource->GetCellText(i, nRow, &cellCfg.editConfig, _pConfig);

			// �������и����
			if (!_bRowWordWarp || cellCfg.cellText.IsEmpty())
				continue;

			CRect rcNeedRect = hColumnData->colRect;
			CRect rcCell(rcNeedRect.left, rcRow.top, rcNeedRect.right, rcRow.bottom);
			CalcCellTextOutRect(&dcMemory, cellCfg.cellText, rcCell, (i == _treeColumn) && (!_bNoChild || hItemData->hParentData != NULL),
				hItemData, &cellCfg.editConfig, hColumnData, rcNeedRect);

			cellCfg.cellInfo.wpHeight = rcNeedRect.Height();
			if (rcNeedRect.Height() <= rcCell.Height())
				continue;

			int nNeedHeight = cellCfg.cellInfo.wpHeight + 8;
			if (nNeedHeight > nMaxRowHeight)
			{
				nMaxRowHeight = nNeedHeight;
			}
		}

		// ��ֵ����и�
		if (_bRowWordWarp)
		{
			rcRow.bottom = rcRow.top + nMaxRowHeight;
		}

		// ����������
		hItemData->rowRect = rcRow;
		hItemData->expandRect.SetRectEmpty(); // Fix:b w-136479

											  // �����и�
		nIncreaseHeight += rcRow.Height();

		// ������ʾ����Χ���򲻻���(�ӿ�����)
		if ((rcRow.top < rcList.top && rcRow.bottom < rcList.top)
			|| (rcRow.top > rcList.bottom && rcRow.bottom > rcList.bottom))
		{
			continue;
		}

		// �����б���
		DrawRowBackground(dcMemory, hItemData, rcRow, leafColumnVector, !nRow);

		// ��ʼ����Ԫ������
		for (size_t i = 0; i < nCount; ++i)
		{
			HCOLUMNDATA hColumnData = leafColumnVector[i];

			// ���㵥Ԫ������
			CRect rcCell = rcRow;
			rcCell.left = hColumnData->colRect.left;
			rcCell.right = hColumnData->colRect.right;

			// ��ͷ������ʾ����Χ���򲻻���(�ӿ�����)
			if ((hColumnData->colRect.left < rcHeader.left && hColumnData->colRect.right < rcHeader.left)
				|| (hColumnData->colRect.left > rcHeader.right && hColumnData->colRect.right > rcHeader.right))
			{
				continue;
			}

			int nSave = dcMemory.SaveDC();

			// ���ü������򣬷�ֹ���Ƶ���ĵ�Ԫ����
			CRgn rgnClip;
			rgnClip.CreateRectRgn(rcCell.left, rcCell.top, rcCell.right, rcCell.bottom);
			dcMemory.SelectClipRgn(&rgnClip, RGN_AND);

			// ���Ƶ�Ԫ��
			CELLCONFIG& cellCfg = cellCfgArray[i];
			DrawCell(dcMemory, rcCell, (i == _treeColumn && (!_bNoChild || hItemData->hParentData != NULL)),
				(i == 0), hItemData, &cellCfg.cellInfo, &cellCfg.editConfig, hColumnData, cellCfg.cellText);

			dcMemory.RestoreDC(nSave);
		}
	}

	dcMemory.SelectObject(hOldFont);
}

void CTimeLineTreeListCtrl::SetCorrespondingTimeFrameCtrl(CTimeFrameListCtrl *pTimeFrameCtrl)
{
	_pTimeLineCtrl = pTimeFrameCtrl;
}

void CTimeLineTreeListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// ������ʾ
	_cellToolTip.ShowWindow(SW_HIDE);

	SetFocus();

	// ��¼���϶���ʼλ��
	_dragStartPt = point;

	// �������
	SetCapture();
	_bBtnDown = true;

	// ����������
	UpdateHitTest(true);

	// ����ѡ����
	if (_hHoverRow != NULL)
	{
		// �ͷ���겶��(������ʱ�����Ի�����꿨��)
		ReleaseCapture();

		// ���õ�ѡ����
		if (SetItemSelectFlag(_hHoverRow))
		{
			NotifyParent(LCN_SELECTED);
		}

		// �������ؼ��¼�;
		EditItemByPoint(point, false);
	}

	InvalidateRect(NULL);
	CTimeLineSplitCtrl* pTimeLineSplitCtrl = (CTimeLineSplitCtrl*)GetOwner();
	if (nullptr != pTimeLineSplitCtrl)
	{
		pTimeLineSplitCtrl->UpdateScrollBar();
	}
	if (nullptr != _pTimeLineCtrl)
	{
		_pTimeLineCtrl->UpdateCtrl();
	}

	CWnd::OnLButtonDown(nFlags, point);
}

LRESULT CTimeLineTreeListCtrl::NotifyParent(UINT nMessage, int nCol, int nRow, HEDITCONFIG hEditCfg,
	const CString& strCellText, CString* pStrNewText, int nClickType)
{
	CWnd* pTimeLineWnd = nullptr;
	if (_pTimeLineCtrl != nullptr)
	{
		pTimeLineWnd = _pTimeLineCtrl->GetTimeLineCtrl();
		if (pTimeLineWnd == nullptr || pTimeLineWnd->GetSafeHwnd() == nullptr)
			pTimeLineWnd = nullptr;
	}

	CTreeListNotify notify;
	notify.hdrNotify.hwndFrom = pTimeLineWnd == nullptr ? m_hWnd : pTimeLineWnd->GetSafeHwnd();
	notify.hdrNotify.idFrom = pTimeLineWnd == nullptr ? GetDlgCtrlID() : pTimeLineWnd->GetDlgCtrlID() ;
	notify.hdrNotify.code = nMessage;
	notify.row = nRow;
	notify.col = nCol;
	notify.strOldText = strCellText;
	notify.pStrNewText = pStrNewText;
	notify.hEditConfig = hEditCfg;
	notify.nClickType = nClickType;

	// ����NOTIFY��Ϣ;
	return ::SendMessage(_hNofigyWnd, WM_NOTIFY, 0, (LPARAM)&notify);
}
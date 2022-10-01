#include "stdafx.h"
#include "TreeListCtrl.h"

namespace ControlUI
{
	// �ؼ����ñ���ɫ
#define DISABLE_BK_COLOR RGB(238,238,238)

	CTreeListCtrl::CTreeListCtrl()
	{
		_showHeader = true;
		_hasGrid = true;
		_hasLine = true;
		_hDragingCol = NULL;
		_bBtnDown = false;
		_bMouseOver = false;
		_bSingleSelect = true;
		_nHeaderHeight = LIST_HEAD_HEIGHT;
		_iconSize = CSize(16, 16);
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
		_pImageList = NULL;
		_bColumnSort = false;
		_bIsTrim = true;
		_bCheckSelChange = true;

		_bDelImageList = true;

		_bCollapseStyle = true;
	}

	CTreeListCtrl::~CTreeListCtrl()
	{
		_treeListFont.DeleteObject();
		_underlineFont.DeleteObject();

		DeleteAllColumn();

		if (_bDelImageList && _pImageList)
		{
			delete _pImageList;
		}

		if (NULL != _pConfig)
		{
			delete _pConfig;
			_pConfig = NULL;
		}

		if ((NULL != _pListDataSource) && _bDelDataSource)
		{
			delete _pListDataSource;
			_pListDataSource = NULL;
		}

		if (NULL != _hIconCollapse)
		{
			DestroyIcon(_hIconCollapse);
			_hIconCollapse = NULL;
		}
		if (NULL != _hIconExpand)
		{
			DestroyIcon(_hIconExpand);
			_hIconExpand = NULL;
		}
	}

	BEGIN_MESSAGE_MAP(CTreeListCtrl, CWnd)
		ON_WM_PAINT()
		ON_WM_ERASEBKGND()
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_LBUTTONDBLCLK()
		ON_WM_RBUTTONDOWN()
		ON_WM_SETCURSOR()
		ON_WM_VSCROLL()
		ON_WM_HSCROLL()
		ON_WM_SIZE()
		ON_WM_KILLFOCUS()
		ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
		ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
		ON_MESSAGE(LIST_CTRL_END, OnEndEdit)
		ON_MESSAGE(LCN_HYPERLINK, OnHyperLink)
		ON_WM_MOUSEWHEEL()
		ON_WM_KEYDOWN()
		ON_WM_THEMECHANGED()
	END_MESSAGE_MAP()

	void CTreeListCtrl::InitControlData()
	{
		if (NULL == m_hWnd)
			return;

		_hNofigyWnd = GetParent()->GetSafeHwnd();

		// ����Ƥ������
		if (_headerTheme.IsThemeNull())
		{
			_headerTheme.OpenThemeData(m_hWnd, L"HEADER");
		}
		
		RESOURCE_OVERRIDE;

		HINSTANCE curModule = AfxGetResourceHandle();

		if (_bCollapseStyle)
		{
			_hIconExpand = LoadIcon(curModule, MAKEINTRESOURCE(IDI_EXPAND));
			_hIconCollapse = LoadIcon(curModule, MAKEINTRESOURCE(IDI_COLLAPSE));
		}
		else
		{
			_hIconExpand = LoadIcon(curModule, MAKEINTRESOURCE(IDI_EXPAND_ADD));
			_hIconCollapse = LoadIcon(curModule, MAKEINTRESOURCE(IDI_COLLAPSE_MINUS));
		}

		if (_progressTheme.IsThemeNull())
		{
			_progressTheme.OpenThemeData(m_hWnd, L"PROGRESS");
		}

		// ��ʼ������
		LOGFONT tempFont;
		HFONT hDefFont = HFONT(GetStockObject(DEFAULT_GUI_FONT));
		CFont* pFont = CFont::FromHandle(hDefFont);
		pFont->GetLogFont(&tempFont);

		_treeListFont.CreateFontIndirect(&tempFont);

		tempFont.lfUnderline = TRUE;
		_underlineFont.CreateFontIndirect(&tempFont);

		// ������ʾ��Ϣ�ؼ�
		_cellToolTip.Create(this, &_treeListFont);
		_cellToolTip.SetColor(_hotTopColor, _hotBorderColor);
	}

	void CTreeListCtrl::DeleteAllItem()
	{
		// ���������
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin();
			iter != endIter; ++iter)
		{
			delete iter->second;
		}
		_listDataSource.clear();
	}

	bool CTreeListCtrl::RegisterTreeList()
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);

		WNDCLASS wndCls = { 0 };
		if (GetClassInfo(hInstance, L"TreeListCtrl", &wndCls))
			return true;

		wndCls.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wndCls.lpfnWndProc = ::DefWindowProc;
		wndCls.cbClsExtra = 0;
		wndCls.cbWndExtra = 0;
		wndCls.hInstance = GetModuleHandle(NULL);
		wndCls.hIcon = NULL;
		wndCls.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndCls.lpszMenuName = NULL;
		wndCls.lpszClassName = L"TreeListCtrl";

		return !!AfxRegisterClass(&wndCls);
	}

	void CTreeListCtrl::UpdateScrollBar(int scrollMode)
	{
		if (scrollMode == SB_HORZ || scrollMode == SB_BOTH)
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

		if (scrollMode == SB_VERT || scrollMode == SB_BOTH)
		{
			CRect rcListRow = CalcListRect();

			int nSumRowHeight = 0;

			// ͳ�����ܸ߶�
			ListDataSourceIter endIter = _listDataSource.end();
			for (ListDataSourceIter iter = _listDataSource.begin();
				iter != endIter; ++iter)
			{
				HITEMDATA hParentData = iter->second->hParentData;
				if (NULL != hParentData && hParentData->IsCollapse())
					continue;

				nSumRowHeight += iter->second->rowRect.Height();
			}

			SCROLLINFO scrInfo;
			scrInfo.cbSize = sizeof(scrInfo);

			scrInfo.fMask = SIF_PAGE | SIF_RANGE;
			scrInfo.nPage = rcListRow.Height();
			scrInfo.nMin = 0;
			scrInfo.nMax = nSumRowHeight;

			SetScrollInfo(SB_VERT, &scrInfo);
		}
	}

	bool CTreeListCtrl::CollectItemListData(IListDataSource* pDataSource,
		ListDataSource& dataSouceList, MapDataSource& dataSourceMap,
		HITEMDATA hParentData, int nTreeLevel, HITEMDATA& hLastChildItem)
	{
		if (NULL == pDataSource)
			return false;

		bool bHasChild = false;
		HITEMDATA hItemData = NULL; // ��ʱ������Ҳ�����һ������
		MapDataSourceIter dataSourceEndIter = dataSourceMap.end();

		// �ݹ��ȡ������
		size_t nRow = pDataSource->GetCount(_pConfig);
		for (size_t i = 0; i < nRow; ++i)
		{
			bool bShowItem = true;
			ITEMDATA itemData;	// ��ʱ����,���������Ƿ�չ������Ϣ

			IListDataSource* pChildDataSource = pDataSource->GetItem(i, bShowItem, &itemData, _pConfig);

			if (NULL == pChildDataSource)
				continue;

			// �������ʾ��ֻ�ݹ��ѯ�����ӽڵ�
			if (!bShowItem)
			{
				// �����ӽڵ�
				bool bTempHasChild = CollectItemListData(pChildDataSource,
					dataSouceList, dataSourceMap, hParentData, nTreeLevel, hLastChildItem);

				if (!bHasChild)
					bHasChild = bTempHasChild;

				// Fix bw-135813
				if (bTempHasChild)
					hItemData = hLastChildItem;

				// �������ʾ������Դ
				delete pChildDataSource;
				continue;
			}

			// �Ѵ����ӽڵ�
			bHasChild = true;
			size_t nKey = pChildDataSource->GetKey();

			// �����Ƿ��Ѵ�˽ڵ�����
			MapDataSourceIter itemDataSourceIter = dataSourceMap.find(nKey);

			// �Ƿ���ڻ�����
			if (itemDataSourceIter != dataSourceEndIter)
			{
				dataSouceList.push_back(*itemDataSourceIter);

				hItemData = itemDataSourceIter->second;
				hItemData->hParentData = hParentData;
				hItemData->lastChild = false;

				// ���ԭ����Դָ��
				hItemData->DelDataSource();
				hItemData->pDataSource = pChildDataSource;

				// �Ѳ��ҵ������Ƴ�
				dataSourceMap.erase(itemDataSourceIter);
			}
			else // ����Դ��һ��ͬ�����������ڵ�
			{
				hItemData = new ITEMDATA();
				*hItemData = itemData;	 // ��ʼ����ֵ(���ڷ����Ƿ�չ������Ϣ)

				hItemData->hParentData = hParentData;
				hItemData->pDataSource = pChildDataSource;

				dataSouceList.push_back(ListDataSource::value_type(nKey, hItemData));
			}

			// ��ֵ�ڵ���
			hItemData->treeLevel = nTreeLevel;

			// �����ӽڵ�
			HITEMDATA hChildItem = NULL;
			hItemData->hasChild = CollectItemListData(pChildDataSource,
				dataSouceList, dataSourceMap, hItemData, nTreeLevel + 1, hChildItem);

			// ������ڵ�
			if (NULL != hChildItem)
				hChildItem->lastChild = true;
		}

		// �����˽ڵ�ʱ�������Ϊ�����
		if (NULL != hItemData)
			hLastChildItem = hItemData;

		// �޸�bw-134327
		if (bHasChild && nTreeLevel != 0)
			_bNoChild = false;

		return bHasChild;
	}

	void CTreeListCtrl::CollectItemListData()
	{
		// ����ԭ�����е�״̬
		MapDataSource itemDataSourceMap;

		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin();
			iter != endIter; ++iter)
		{
			itemDataSourceMap.insert(*iter);
		}
		_listDataSource.clear();

		// �޸�bw-134327
		_bNoChild = true;

		// �ݹ��ȡ����
		HITEMDATA hLastChildItem = NULL;
		CollectItemListData(_pListDataSource, _listDataSource, itemDataSourceMap, NULL, 0, hLastChildItem);

		// ������ڵ�
		if (hLastChildItem != NULL)
		{
			hLastChildItem->lastChild = true;
		}

		// ��ʣ��ɾ��������Դ�ڵ��Ӧ�ı������ɾ��(����Դ��ɾ���ڵ�)
		MapDataSourceIter dataSourceEndIter = itemDataSourceMap.end();
		for (MapDataSourceIter iter = itemDataSourceMap.begin();
			iter != dataSourceEndIter; ++iter)
		{
			delete iter->second;
		}
		itemDataSourceMap.clear();
	}

	void CTreeListCtrl::CancelEdit()
	{
		if (_pControl && ::IsWindow((_pControl->GetSafeHwnd())))
		{
			IEditBase* pEditBase = dynamic_cast<IEditBase*>(_pControl);
			if (NULL != pEditBase)
				pEditBase->CancelEdit();
		}

		// ������ڱ༭��ȡ��
		DeleteControl();
	}

	void CTreeListCtrl::UpdateList(bool bDataChange, bool bCancelSel)
	{
		// ������ڱ༭��ȡ��
		CancelEdit();

		// ǿ�Ƹ�������
		if (bDataChange)
		{
			// �ռ�������
			CollectItemListData();

			if (bCancelSel)
			{
				for (ListDataSourceIter iter = _listDataSource.begin(); iter != _listDataSource.end(); ++iter)
				{
					iter->second->seleced = false;
				}
			}

			// �����ѡ��һ�м�¼
			_nLastSelectItem = -1;
		}

		UpdateHitTest(false);

		// ������ʾ�ı�ʱ�������������
		SendMessage(WM_PAINT);

		UpdateScrollBar(SB_BOTH);
		InvalidateRect(NULL);

		// �����ʾ��
		_cellToolTip.Reset();
	}

	bool CTreeListCtrl::UpdateHitTest(bool bUpdateSel)
	{
		// ��ȡ���λ��
		CPoint mPt;
		GetCursorPos(&mPt);
		ScreenToClient(&mPt);

		// �ͻ�����
		CRect rcClient;
		GetClientRect(&rcClient);

		// �Ƿ���Ҫ���½���(�ӿ�����)
		bool bNeedUpdate = false;

		// ������ͷλ����״̬(��ͷ���ƶ���ʱ����Ҫ������ͷ״̬)
		if (!(_bBtnDown && _hDragingCol != NULL) && _showHeader)
		{
			HCOLUMNDATA hOldHoverCol = _hHoverCol;
			HCOLUMNDATA hOldPressCol = _hPressCol;

			// �����϶�������ͣ��
			_hHoverCol = _hDragingCol = _hPressCol = NULL;

			// ����������ͷ(��ת�������Խṹ)
			ColumnDataVector columnVector;
			GetColumnLinearityStruct(columnVector);

			size_t nCount = columnVector.size();
			for (size_t i = 0; i < nCount; ++i)
			{
				HCOLUMNDATA hColumnData = columnVector[i];

				// �����Ƿ�����ק����
				CRect rcDragArea = hColumnData->colRect;
				rcDragArea.left = rcDragArea.right - 4;
				rcDragArea.right = rcDragArea.right + 4;

				// �Ƿ����ж�������(��갴��ʱ�����)
				if (!_bBtnDown && rcDragArea.PtInRect(mPt))
				{
					_hDragingCol = hColumnData;
				}

				// ����ƶ��������ϵĲ�������
				CRect rcTest = hColumnData->colRect;
				rcTest.left = rcTest.left < rcClient.left ? rcClient.left : rcTest.left;
				rcTest.right = rcTest.right > rcClient.right ? rcClient.right : rcTest.right;

				// �����Ƿ�����ͷ��
				if (rcTest.PtInRect(mPt))
				{
					// �ж���ʱ����갴����Ч��
					if (_bBtnDown && (_hDragingCol == NULL))
						_hPressCol = hColumnData;

					// �����µ���ͣ��
					_hHoverCol = hColumnData;
				}
			}

			// ״̬�仯��Ҫˢ��
			if (!bNeedUpdate)
			{
				bNeedUpdate = (_hHoverCol != hOldHoverCol) || (_hPressCol != hOldPressCol);
			}
		}
		else if (_showHeader)
		{
			// ��ͷ���ƶ�
			bNeedUpdate = true;
		}

		HITEMDATA hOldHoverRow = _hHoverRow;

		// ������ͣ��
		_hHoverRow = NULL;
		_nHoverRowIndex = -1;

		int nRow = 0;
		// �������ͣ״̬
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin();
			iter != endIter; ++iter, ++nRow)
		{
			HITEMDATA hItemData = iter->second;

			// ���������ʱ��������λ���Ƿ�������ͼ�������ڣ�����ڴ�������ˢ�����б�չ��������״̬��
			if (_bBtnDown && bUpdateSel)
			{
				// ����ƶ����������ϵĲ�������
				CRect rcTest = hItemData->expandRect;

				// ��������Ƿ�������
				if (rcTest.PtInRect(mPt))
				{
					hItemData->expand = !hItemData->expand;
					// �˴���Ҫbreak���������ѡ���н���ᶪʧ��;
					//break;
				}
			}

			// ����ƶ����������ϵĲ�������
			CRect rcTest = hItemData->rowRect;
			rcTest.left = rcTest.left < rcClient.left ? rcClient.left : rcTest.left;
			rcTest.right = rcTest.right > rcClient.right ? rcClient.right : rcTest.right;

			// �������ͷ��,��ѡ����
			CRect rcHeader = CalcHeaderRect();

			// ��������Ƿ�������
			if (!(_showHeader && rcHeader.PtInRect(mPt)) && rcTest.PtInRect(mPt))
			{
				_nHoverRowIndex = nRow;
				_hHoverRow = hItemData;
				break;
			}
		}

		if (!bNeedUpdate)
		{
			bNeedUpdate = (hOldHoverRow != _hHoverRow);
		}

		return bNeedUpdate;
	}

	void CTreeListCtrl::UpdateColumnSortState()
	{
		// ��ʹ����ͷ�����¼�������ͣ��Ϊ��
		if (!_bColumnSort || NULL == _hHoverCol)
			return;

		// ��ȡ���λ��
		CPoint mPt;
		GetCursorPos(&mPt);
		ScreenToClient(&mPt);

		// ����������ͷ
		ColumnDataVector leafColumnVector;
		GetColumnLinearityStruct(leafColumnVector);

		HCOLUMNDATA hSelColumn, hUnsetColumn;
		hSelColumn = hUnsetColumn = NULL;

		size_t nSortColIndex = 0;
		size_t nCount = leafColumnVector.size();
		for (size_t i = 0; i < nCount; ++i)
		{
			HCOLUMNDATA hColumnData = leafColumnVector[i];

			if (hColumnData->sortType != TLC_NO_SORT)
				hUnsetColumn = hColumnData;

			CRect rcDragArea = hColumnData->colRect;
			rcDragArea.left += 4;  // �ų���ק����
			rcDragArea.right -= 4; // �ų���ק����

			// �����Ƿ�����ͷ�е��
			if (rcDragArea.PtInRect(mPt))
			{
				nSortColIndex = i;
				hSelColumn = hColumnData;
			}
		}

		if (hSelColumn != NULL)
		{
			CColumnSortNotify sortNotify;
			sortNotify.hdrNotify.hwndFrom = m_hWnd;
			sortNotify.hdrNotify.idFrom = GetDlgCtrlID();
			sortNotify.hdrNotify.code = LCH_COLUMN_BEGINSORT;
			sortNotify.hColData = hSelColumn;
			sortNotify.nColIndex = nSortColIndex;

			// ���Ϳ�ʼ������Ϣ
			if (LCNR_OK != ::SendMessage(_hNofigyWnd, WM_NOTIFY, 0, (LPARAM)&sortNotify))
				return;

			if (hUnsetColumn != NULL && hUnsetColumn != hSelColumn)
				hUnsetColumn->sortType = TLC_NO_SORT;

			if (hSelColumn->sortType == TLC_ASC_SORT)
			{
				hSelColumn->sortType = TLC_DSC_SORT;
			}
			else
			{
				hSelColumn->sortType = TLC_ASC_SORT;
			}

			sortNotify.hdrNotify.code = LCH_COLUMN_ENDSORT;

			// ���ͽ���������Ϣ
			::SendMessage(_hNofigyWnd, WM_NOTIFY, 0, (LPARAM)&sortNotify);
		}
	}

	void CTreeListCtrl::DoDragColumn()
	{
		// ��ȡ���λ��
		CPoint mPt;
		GetCursorPos(&mPt);
		ScreenToClient(&mPt);

		// �����ƶ���ͷ
		if (_bBtnDown && _hDragingCol != NULL && _showHeader)
		{
			int diff = mPt.x - _dragStartPt.x;

			// ���ѹ̶����,���ƶ�
			if (_hDragingCol->fixed)
				return;

			// ��ȡ�������Сֵ
			SHORT nAllowMinWidth = 0;
			size_t nChildSize = _hDragingCol->childColumn.size();
			if (nChildSize > 1)
			{
				for (size_t i = 0; i < nChildSize - 1; ++i)
					nAllowMinWidth += _hDragingCol->childColumn[i]->GetWidth();
			}

			// ������С���
			int nSetValue = _hDragingCol->GetWidth() + diff;
			if (nSetValue < nAllowMinWidth)
			{
				nSetValue = nAllowMinWidth;
			}

			if (_hDragingCol->GetWidth() != nSetValue)
			{
				_hDragingCol->SetWidth(nSetValue);
				_dragStartPt = mPt;
				UpdateScrollBar(SB_BOTH);
			}
		}
	}

	bool CTreeListCtrl::Create(const RECT& rect, CWnd* pParentWnd, UINT nID, DWORD dwStyle)
	{
		bool bSuccess = false;

		// ע��ؼ�����
		if (RegisterTreeList())
		{
			bSuccess = !!CWnd::Create(L"TreeListCtrl", NULL, dwStyle | WS_CLIPCHILDREN, rect, pParentWnd, nID);
		}

		// ��ʼ���ؼ���Ҫ����
		if (bSuccess)
		{
			InitControlData();
		}

		return bSuccess;
	}

	void CTreeListCtrl::SetDataSource(IListDataSource* pDataSource, bool bDelDataSource)
	{
		// ���ԭ������Դ
		if ((NULL != _pListDataSource) && _bDelDataSource)
		{
			delete _pListDataSource;
		}

		// ��ֵ������Դ
		_pListDataSource = pDataSource;
		_bDelDataSource = bDelDataSource;
	}

	bool CTreeListCtrl::LoadConfig(const CString& strCfg, const CString& strCfgName)
	{
		if (_pConfig != NULL)
			delete _pConfig;

		_pConfig = new CTreeListConfig(this);
		return _pConfig->LoadConfig(strCfg, strCfgName);
	}

	void CTreeListCtrl::SetImageList(CImageList* pImageList, bool bAutoDel)
	{
		if (_bDelImageList && _pImageList)
		{
			delete _pImageList;
			_pImageList = NULL;
		}

		_bDelImageList = bAutoDel;
		_pImageList = pImageList;
	}

	void CTreeListCtrl::SetNofityWnd(HWND hNotifyWnd)
	{
		_hNofigyWnd = hNotifyWnd;
	}

	void CTreeListCtrl::SetSingleSelect(bool bSingleSelect)
	{
		_bSingleSelect = bSingleSelect;
	}

	void CTreeListCtrl::SetFocusItem(size_t nSelectIndex)
	{
		if (!_listDataSource.empty() && nSelectIndex >= _listDataSource.size())
			nSelectIndex = _listDataSource.size() - 1;

		int nCount = -1;
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin(); iter != endIter; ++iter)
		{
			if ((++nCount) == nSelectIndex)
			{
				iter->second->seleced = true;
				_nLastSelectItem = (int)nSelectIndex;
			}
			else
			{
				iter->second->seleced = false;
			}
		}

		// ȷ����ʾ
		MakeRowVisible(int(nSelectIndex));

		NotifyParent(LCN_SELECTED);
	}

	void CTreeListCtrl::SetFocusItemByDataSource(IListDataSource* pDataSource)
	{
		if (pDataSource)
		{
			SetFocusItemByKey(pDataSource->GetKey());
		}
		else
		{
			SetFocusItem();
		}
	}

	HCOLUMNDATA CTreeListCtrl::InsertColumn(size_t nCol, HCOLUMNDATA hParentCol)
	{
		ColumnDataVector& columnVector = hParentCol
			? hParentCol->childColumn : _columnVector;

		// ��������Ϸ���
		if (nCol < 0 || nCol > columnVector.size())
			return NULL;

		// ���������
		DeleteAllItem();

		// �½���
		HCOLUMNDATA hColData = new COLUMNDATA();
		hColData->hParent = hParentCol;
		columnVector.insert(columnVector.begin() + nCol, hColData);

		return hColData;
	}

	void CTreeListCtrl::DeleteColumn(size_t nCol, HCOLUMNDATA hParentCol)
	{
		ColumnDataVector& columnVector = hParentCol
			? hParentCol->childColumn : _columnVector;

		// ��������Ϸ���
		if (nCol < 0 || nCol > columnVector.size())
			return;

		// ���������
		DeleteAllItem();

		// ɾ����
		delete columnVector[nCol];
		columnVector.erase(columnVector.begin() + nCol);
	}

	void CTreeListCtrl::DeleteAllColumn()
	{
		// ���������
		DeleteAllItem();

		size_t sz = _columnVector.size();
		for (size_t nCol = 0; nCol < sz; ++nCol)
		{
			DeleteAllColumn(_columnVector[nCol]);
		}
		_columnVector.clear();
	}

	double CTreeListCtrl::GetFontScale()
	{
		HDC screen = ::GetDC(NULL);

		double hPixelsPerInch = GetDeviceCaps(screen, LOGPIXELSX);
		double vPixelsPerInch = GetDeviceCaps(screen, LOGPIXELSY);
		::ReleaseDC(NULL, screen);

		double dpi = (hPixelsPerInch + vPixelsPerInch) * 0.5;
		dpi = dpi / 96;
		if (dpi == 1)
			return dpi;
		else
			return dpi * 0.935;
	}

	void CTreeListCtrl::DeleteAllColumn(HCOLUMNDATA hParentCol)
	{
		size_t sz = hParentCol->childColumn.size();
		for (size_t nCol = 0; nCol < sz; ++nCol)
		{
			DeleteAllColumn(hParentCol->childColumn[nCol]);
		}
		delete hParentCol;
	}

	IListDataSource* CTreeListCtrl::GetSelectedItem()
	{
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin(); iter != endIter; ++iter)
		{
			if (iter->second->seleced)
			{
				return iter->second->pDataSource;
			}
		}

		return NULL;
	}

	void CTreeListCtrl::GetSelectedItems(DataSourceArray &datasourceArray)
	{
		// ���������;
		datasourceArray.clear();

		// ������ǰѡ��ļ�¼;
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin(); iter != endIter; ++iter)
		{
			if (iter->second->seleced)
			{
				datasourceArray.push_back(iter->second->pDataSource);
			}
		}
	}

	void CTreeListCtrl::GetDataSourceArray(DataSourceArray &datasourceArray)
	{
		// ���������;
		datasourceArray.clear();

		// ������ǰѡ��ļ�¼;
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin(); iter != endIter; ++iter)
		{
			datasourceArray.push_back(iter->second->pDataSource);
		}
	}

	int CTreeListCtrl::GetSelectedIndex()
	{
		int nSelIndex = -1;

		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin();
			iter != endIter; ++iter, ++nSelIndex)
		{
			if (iter->second->seleced)
			{
				return ++nSelIndex;
			}
		}

		return -1;
	}

	size_t CTreeListCtrl::GetTotalRowCount()
	{
		return _listDataSource.size();
	}


	HCOLUMNDATA CTreeListCtrl::GetColumn(size_t nCol, HCOLUMNDATA hColumnData)
	{
		ColumnDataVector& columnVector = hColumnData
			? hColumnData->childColumn : _columnVector;

		// ��������Ϸ���
		if (nCol < 0 || nCol > columnVector.size())
			return NULL;

		return columnVector[nCol];
	}

	size_t CTreeListCtrl::GetColumnCount(HCOLUMNDATA hColumnData)
	{
		if (NULL == hColumnData)
		{
			return _columnVector.size();
		}
		else
		{
			return hColumnData->childColumn.size();
		}
	}

	/***********************��Ϣ��Ӧ***********************/

	void CTreeListCtrl::OnPaint()
	{
		CPaintDC dc(this);

		// ��ͼ����
		CRect rcClient;
		GetClientRect(&rcClient);

		// �ڴ��ͼDC
		CMemoryDC dcMemory(&dc, rcClient);
		COLORREF bkColor = _bkColor;
		if (!IsWindowEnabled())
			bkColor = DISABLE_BK_COLOR;

		dcMemory.FillSolidRect(rcClient, bkColor);

		// ������ͷ
		CRect rcHeader = CalcHeaderRect();
		DrawHeader(dcMemory, rcHeader);

		// �ų���ͷ��������
		dcMemory.ExcludeClipRect(rcHeader);

		// �����б���
		CRect rcListRow = CalcListRect();
		DrawRow(dcMemory, rcHeader, rcListRow);

		// �������Ѹ���
		_lockTipUpdate = false;
	}

	BOOL CTreeListCtrl::OnEraseBkgnd(CDC* pDC)
	{
		return true;
	}

	void CTreeListCtrl::OnMouseMove(UINT nFlags, CPoint point)
	{
		CWnd::OnMouseMove(nFlags, point);

		// ǿ�����ý���(��ֹ�����ؼ�������)
		/*if (::GetFocus() != m_hWnd)
			SetFocus();*/

			// ��������뿪
		if (!_bMouseOver)
		{
			_bMouseOver = true;

			TRACKMOUSEEVENT trkMouse;
			trkMouse.cbSize = sizeof(TRACKMOUSEEVENT);
			trkMouse.dwFlags = TME_LEAVE;
			trkMouse.hwndTrack = m_hWnd;
			::TrackMouseEvent(&trkMouse);
		}

		// ִ���ƶ���ͷ
		DoDragColumn();

		// ����������
		if (UpdateHitTest(false))
		{
			InvalidateRect(NULL);
		}

		// ����Ԫ����ʾ��Ϣ
		ProcessCellTooltip();
	}

	BOOL CTreeListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		CWnd::OnMouseWheel(nFlags, zDelta, pt);

		// �������ƶ���������Ϊ����ֻ��OnPaint�Ÿ�����ȷ
		_lockTipUpdate = true;

		// ������ʾ��Ϣ
		_cellToolTip.Reset();

		// ������ڱ༭��ȡ��
		CancelEdit();

		SCROLLINFO infoScroll;
		infoScroll.cbSize = sizeof(SCROLLINFO);
		infoScroll.fMask = SIF_ALL;

		if (!GetScrollInfo(SB_VERT, &infoScroll))
			return TRUE;

		int nNewPos = infoScroll.nPos - (zDelta / 5);

		infoScroll.fMask = SIF_POS;
		infoScroll.nPos = nNewPos;
		SetScrollInfo(SB_VERT, &infoScroll);

		InvalidateRect(NULL);

		return TRUE;
	}

	void CTreeListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
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

		CWnd::OnLButtonDown(nFlags, point);
	}

	void CTreeListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// �ͷŲ������
		ReleaseCapture();
		_bBtnDown = false;

		bool bDragIng = (NULL != _hDragingCol);

		// ����������
		UpdateHitTest(false);

		if (!bDragIng)
			UpdateColumnSortState();

		// ������ʾ�ı�ʱ�������������
		SendMessage(WM_PAINT);

		UpdateScrollBar(SB_VERT);
		InvalidateRect(NULL);

		// ����ѡ����;
		if (_hHoverRow != NULL)
		{
			CRect rect;
			int nCol = -1, nRow = 0;
			HCOLUMNDATA hColumnData = NULL;
			IListDataSource* pDataSource = NULL;
			GetFocusRect(nCol, nRow, hColumnData, rect, pDataSource, &point);
			NotifyParent(LCN_LEFTCLICK, nCol, nRow, &hColumnData->editConfig);
		}

		CWnd::OnLButtonUp(nFlags, point);
	}

	void CTreeListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		CWnd::OnLButtonDblClk(nFlags, point);

		// ������ʾ
		_cellToolTip.ShowWindow(SW_HIDE);

		// ����ѡ����;
		UpdateHitTest(false);
		if (_hHoverRow != NULL)
		{
			// ���õ�ѡ����
			if (SetItemSelectFlag(_hHoverRow))
			{
				NotifyParent(LCN_SELECTED);
			}
		}
		InvalidateRect(NULL);

		// ����ѡ����;
		if (_hHoverRow != NULL)
		{
			CRect rect;
			int nCol = -1, nRow = 0;
			HCOLUMNDATA hColumnData = NULL;
			IListDataSource* pDataSource = NULL;
			GetFocusRect(nCol, nRow, hColumnData, rect, pDataSource, &point);

			// ����˫���¼�;
			LRESULT pResult = NotifyParent(LCN_DBLCLICK, nCol, nRow, &hColumnData->editConfig);

			//������Ĭ��ֵ0����ִ�б༭
			if(!pResult)
				EditItemByPoint(point, true);
		}
	}

	void CTreeListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
	{
		CWnd::OnRButtonDown(nFlags, point);

		// ������ʾ
		_cellToolTip.ShowWindow(SW_HIDE);

		InvalidateRect(NULL);
		SetFocus();

		// �Ƕ�ѡ������£������¼�

		// ����ѡ����;
		UpdateHitTest(false);

		if (_hHoverRow != NULL)
		{
			// ���õ�ѡ����
			if (!_hHoverRow->seleced && SetItemSelectFlag(_hHoverRow))
			{
				NotifyParent(LCN_SELECTED, -1, -1, 0, L"", 0, 1);
			}
		}
		InvalidateRect(NULL);

		// ����ѡ����;
		if (_hHoverRow != NULL)
		{
			// ����ѡ����;
			ShowRightMenu();

			CRect rect;
			int nCol = -1, nRow = 0;
			HCOLUMNDATA hColumnData = NULL;
			IListDataSource* pDataSource = NULL;
			GetFocusRect(nCol, nRow, hColumnData, rect, pDataSource, &point);

			// ������Ϣ;
			NotifyParent(LCN_RIGHTCLICK, nCol, nRow, &hColumnData->editConfig);
		}
	}

	LRESULT CTreeListCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
	{
		_bMouseOver = false;

		CPoint curPt;
		GetCursorPos(&curPt);
		ScreenToClient(&curPt);

		// ����������,�����ж�
		if (UpdateHitTest(false))
		{
			InvalidateRect(NULL);
		}

		return TRUE;
	}

	LRESULT CTreeListCtrl::OnMouseHover(WPARAM wParam, LPARAM lParam)
	{
		SetFocus();
		return TRUE;
	}

	LRESULT CTreeListCtrl::OnEndEdit(WPARAM wParam, LPARAM lParam)
	{
		if (!IsWindowVisible())
			return TRUE;

		if (_listTreeCombo)
			_listTreeCombo.ResetItemData();

		IListDataSource* pSelectDataSource = GetSelectedItem();
		ATLASSERT(pSelectDataSource != NULL);
		if (pSelectDataSource != NULL)
		{
			ColumnDataVector leafColumnVector;
			GetColumnAllLeafStruct(leafColumnVector);

			if ((size_t)_nEditColIndex >= leafColumnVector.size())
				return FALSE;

			HCOLUMNDATA hColumnData = leafColumnVector[_nEditColIndex];

			// ��ȡ�޸ĺ��ֵ�븽������;
			CString strVal = LPCTSTR(wParam);
			CString strData = LPCTSTR(lParam);
			if (_bIsTrim)
			{
				strVal.Trim();
			}


			// ��ȡ��Ԫ������;
			CELLINFO cellInfo;
			EDITCONFIG editConfig;
			editConfig.isEditMode = true;
			pSelectDataSource->GetCellData(_nEditColIndex, _nEditRowIndex, hColumnData, &cellInfo, &editConfig, _pConfig);

			CString strOldText = pSelectDataSource->GetCellText(_nEditColIndex, _nEditRowIndex, &editConfig, _pConfig);
			CString strOldData = _pConfig->GetTempData();

			// ��ֵ��û���޸�
			if (strOldText == strVal && strOldData == strData)
			{
				NotifyParent(LCN_CANCELEDIT, (int)_nEditColIndex, (int)_nEditRowIndex, &editConfig, strOldText, &strVal);
				return FALSE;
			}

			if (!OnEndEdit((int)_nEditColIndex, (int)_nEditRowIndex, &editConfig, strOldText, strVal))
				return FALSE;

			// ������Ϣ֪ͨ����״̬����;
			if (LCNR_OK != NotifyParent(LCN_ENDEDIT, (int)_nEditColIndex, (int)_nEditRowIndex, &editConfig, strOldText, &strVal))
				return FALSE;

			// ������ʱ����
			_pConfig->SetTempData(strData);

			pSelectDataSource->SetCellText(_nEditColIndex, _nEditRowIndex, &editConfig, strVal, _pConfig);

			// ��ɱ༭
			NotifyParent(LCN_ENDEDITDONE, (int)_nEditColIndex, (int)_nEditRowIndex, &editConfig, strOldText, &strVal);

			InvalidateRect(NULL);
		}

		return TRUE;
	}

	void CTreeListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
	{
		CWnd::OnVScroll(nSBCode, nPos, pScrollBar);

		// ������ڱ༭��ȡ��
		CancelEdit();

		SCROLLINFO infoScroll;
		infoScroll.cbSize = sizeof(SCROLLINFO);
		infoScroll.fMask = SIF_ALL;

		if (!GetScrollInfo(SB_VERT, &infoScroll))
			return;

		int nNewPos = infoScroll.nPos;
		switch (nSBCode)
		{
		case SB_TOP:
			nNewPos = infoScroll.nMin;
			break;
		case SB_LINEUP:
			nNewPos = max(infoScroll.nPos - 5, infoScroll.nMin);
			break;
		case SB_PAGEUP:
			nNewPos = max(infoScroll.nPos - int(infoScroll.nPage), infoScroll.nMin);
			break;
		case SB_BOTTOM:
			nNewPos = infoScroll.nMax;
			break;
		case SB_LINEDOWN:
			nNewPos = min(infoScroll.nPos + 5, infoScroll.nMax);
			break;
		case SB_PAGEDOWN:
			nNewPos = min(int(infoScroll.nPos + infoScroll.nPage), infoScroll.nMax);
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			nNewPos = infoScroll.nTrackPos;
			break;
		}

		infoScroll.fMask = SIF_POS;
		infoScroll.nPos = nNewPos;
		SetScrollInfo(SB_VERT, &infoScroll);

		InvalidateRect(NULL);
	}

	void CTreeListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
	{
		CWnd::OnHScroll(nSBCode, nPos, pScrollBar);

		// ������ڱ༭��ȡ��
		CancelEdit();

		SCROLLINFO infoScroll;
		infoScroll.cbSize = sizeof(SCROLLINFO);
		infoScroll.fMask = SIF_ALL;

		if (!GetScrollInfo(SB_HORZ, &infoScroll))
			return;

		int nNewPos = infoScroll.nPos;
		switch (nSBCode)
		{
		case SB_LEFT:
			nNewPos = infoScroll.nMin;
			break;
		case SB_LINELEFT:
			nNewPos = max(infoScroll.nPos - 5, infoScroll.nMin);
			break;
		case SB_PAGELEFT:
			nNewPos = max(infoScroll.nPos - int(infoScroll.nPage), infoScroll.nMin);
			break;
		case SB_RIGHT:
			nNewPos = infoScroll.nMax;
			break;
		case SB_LINERIGHT:
			nNewPos = min(infoScroll.nPos + 5, infoScroll.nMax);
			break;
		case SB_PAGERIGHT:
			nNewPos = min(int(infoScroll.nPos + infoScroll.nPage), infoScroll.nMax);
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			nNewPos = infoScroll.nTrackPos;
			break;
		}

		infoScroll.fMask = SIF_POS;
		infoScroll.nPos = nNewPos;
		SetScrollInfo(SB_HORZ, &infoScroll);

		InvalidateRect(NULL);
	}

	void CTreeListCtrl::OnSize(UINT nType, int cx, int cy)
	{
		CWnd::OnSize(nType, cx, cy);

		if (NULL != m_hWnd)
		{
			CancelEdit();

			AutoColumnWidth();

			UpdateScrollBar(SB_BOTH);
		}
	}

	/***********************��ͷ����***********************/

	CRect CTreeListCtrl::CalcHeaderRect()
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		CRect rcHeader = rcClient;

		if (_showHeader)
		{
			int nMaxLevel = 0;
			GetMaxColumnLevel(nMaxLevel);

			rcHeader.bottom = rcHeader.top + _nHeaderHeight*nMaxLevel;
		}
		else
		{
			rcHeader.bottom = rcHeader.top;
		}

		return rcHeader;
	}

	void CTreeListCtrl::DrawHeader(CMemoryDC& dcMemory, const CRect& rcHeader)
	{
		// �е������
		int nIncreaseWidth = 0;

		// ʣ����ͷ����
		CRect rcReaminColumn;
		rcReaminColumn.SetRectEmpty();
		int nHorzPos = GetScrollPos(SB_HORZ);

		HGDIOBJ hOldFont = dcMemory.SelectObject(_treeListFont);

		// ��ȡ��ͷ���Խṹ
		ColumnDataVector columnVector;
		GetColumnLinearityStruct(columnVector);

		// ����������
		size_t nCount = columnVector.size();
		for (size_t i = 0; i < nCount; ++i)
		{
			HCOLUMNDATA hColumnData = columnVector[i];

			// �����л�������
			CRect rcColumn = rcHeader;
			bool bNoParent = (NULL == hColumnData->hParent);

			// ���㸸��ͷ����
			if (bNoParent)
			{
				rcColumn.left = nIncreaseWidth - nHorzPos + rcHeader.left;
				rcColumn.right = rcColumn.left + hColumnData->GetWidth();
				rcColumn.bottom = rcColumn.top + _nHeaderHeight;
			}
			else // ��������ͷ����
			{
				CRect& rcParentCol = hColumnData->hParent->colRect;
				ColumnDataVector& childColumns = hColumnData->hParent->childColumn;

				rcColumn.top = rcParentCol.bottom;
				rcColumn.left = rcParentCol.left;

				// ����ƫ��ʼֵ
				size_t nChildCol = childColumns.size();
				for (size_t j = 0; j < nChildCol; ++j)
				{
					if (childColumns[j] == hColumnData)
						break;

					rcColumn.left += childColumns[j]->GetWidth();
				}

				rcColumn.bottom = rcColumn.top + _nHeaderHeight;
				rcColumn.right = rcColumn.left + hColumnData->GetWidth();
			}

			// û������ͷ�����±����ͷ����
			if (0 == hColumnData->childColumn.size())
				rcColumn.bottom = rcHeader.bottom;

			// ������ͷ����
			hColumnData->colRect = rcColumn;

			// �е���(ֻ�����һ����ͷ)
			if (bNoParent)
			{
				nIncreaseWidth += hColumnData->GetWidth();
			}

			// ������ʾ����Χ���򲻻���(�ӿ�����)
			if (!_showHeader || (rcColumn.left < rcHeader.left && rcColumn.right < rcHeader.left)
				|| (rcColumn.left > rcHeader.right && rcColumn.right > rcHeader.right))
			{
				continue;
			}

			// ��ʱ�洢�����
			if (NULL == hColumnData->hParent)
			{
				rcReaminColumn = rcColumn;
			}

			// ������ͷ��
			DrawColumn(dcMemory, rcColumn, hColumnData);
		}

		// �Ƿ���ʣ����ͷ����Ҫ����
		if (_showHeader && (rcReaminColumn.right < rcHeader.right))
		{
			rcReaminColumn.left = rcReaminColumn.right;
			rcReaminColumn.right = rcHeader.right;
			rcReaminColumn.bottom = rcHeader.bottom;

			// ����ʣ����ͷ��
			DrawColumn(dcMemory, rcReaminColumn, NULL);
		}

		dcMemory.SelectObject(hOldFont);
	}

	void CTreeListCtrl::DrawColumn(CMemoryDC& dcMemory, const CRect& rcColumn, HCOLUMNDATA hColumnData)
	{
		// ��ͷ��߾�
		int headerItemMargin = 6;

		// �ж�����ʾ���
		int nState = HIS_NORMAL;

		if (NULL == hColumnData)
		{
			nState = HIS_NORMAL;
		}
		else if (hColumnData == _hPressCol)
		{
			nState = HIS_PRESSED;
		}
		else if (hColumnData == _hHoverCol)
		{
			nState = HIS_HOT;
		}

		// ���ƴ�Ƥ����ͷ
		if (!_headerTheme.IsThemeNull())
		{
			_headerTheme.DrawThemeBackgroundEx(dcMemory, HP_HEADERITEM, nState, rcColumn, NULL);

			CPen pLinePen;
			pLinePen.CreatePen(PS_SOLID, 1, RGB(229, 229, 229));
			HGDIOBJ hOldPen = dcMemory.SelectObject(pLinePen.GetSafeHandle());
			dcMemory.MoveTo(rcColumn.TopLeft());
			dcMemory.LineTo(CPoint(rcColumn.right, rcColumn.top));
			dcMemory.SelectObject(hOldPen);
		}
		else
		{
			dcMemory.FillSolidRect(rcColumn, GetSysColor(COLOR_BTNFACE));
			dcMemory.Draw3dRect(rcColumn, GetSysColor(COLOR_3DHIGHLIGHT), GetSysColor(COLOR_3DSHADOW));
		}

		// ������ͷ�ǲ���Ҫ����������ͼ��
		if (NULL == hColumnData)
			return;

		// �Ƿ������ͼ��
		bool bDrawIcon = false;

		// ����ͼ������
		CRect rcIcon = rcColumn;
		rcIcon.DeflateRect(headerItemMargin, 0, headerItemMargin, 0);
		rcIcon.top = rcIcon.CenterPoint().y - _iconSize.cy / 2;

		// ����ͼ��
		if (rcIcon.IsRectEmpty())
		{
			bDrawIcon = false;
		}
		else if (_pImageList && (hColumnData->image != -1))
		{
			bDrawIcon = true;
			_pImageList->DrawEx(&dcMemory, hColumnData->image, rcIcon.TopLeft(), _iconSize,
				CLR_DEFAULT, CLR_DEFAULT, ILD_IMAGE);
		}

		// ����������
		CRect rcText = rcColumn;
		if (bDrawIcon)
		{
			rcText.left = (rcIcon.left + _iconSize.cx + headerItemMargin / 2);
		}
		else
		{
			rcText.DeflateRect(headerItemMargin, 0, headerItemMargin, 0);
		}

		// ��������
		if (NULL != hColumnData && !rcText.IsRectEmpty())
		{
			dcMemory.SetBkMode(TRANSPARENT);
			dcMemory.SetTextColor(hColumnData->textColor);

			bool bHasDrawText = false;

			// �Զ�����
			if (_bColumnWordWarp)
			{
				UINT nFormat = hColumnData->format | DT_EDITCONTROL | DT_WORDBREAK | DT_NOPREFIX;

				CRect rcCalc = rcText;
				int nHeight = dcMemory.DrawText(hColumnData->title, rcCalc, nFormat | DT_CALCRECT);

				if (rcCalc.Height() <= rcText.Height())
				{
					bHasDrawText = true;
					rcText.OffsetRect(0, (rcText.Height() - nHeight) / 2);
					dcMemory.DrawText(hColumnData->title, rcText, nFormat);
				}
			}

			if (!bHasDrawText)
			{
				dcMemory.DrawText(hColumnData->title, rcText,
					hColumnData->format | DT_SINGLELINE | DT_VCENTER | DT_WORD_ELLIPSIS | DT_NOPREFIX);
			}
		}

		// ��������ͼ��(����ͷ�Ϸ��м����)
		if (hColumnData != NULL && hColumnData->sortType != TLC_NO_SORT
			&& hColumnData->IsLeafCol())
		{
			const int sortIcoHeight = 5; //����ͼ��5���ظ�

			CPen sortPen(PS_SOLID, 1, hColumnData->textColor);
			HGDIOBJ hOldPen = dcMemory.SelectObject(&sortPen);

			CPoint topCt(rcColumn.left + rcColumn.Width() / 2, rcColumn.top + 1);

			// ����
			if (hColumnData->sortType == TLC_ASC_SORT)
			{
				dcMemory.MoveTo(topCt);
				dcMemory.LineTo(topCt.x - sortIcoHeight + 1, topCt.y + sortIcoHeight - 1);
				dcMemory.MoveTo(topCt);
				dcMemory.LineTo(topCt.x + sortIcoHeight - 1, topCt.y + sortIcoHeight - 1);
			}
			else if (hColumnData->sortType == TLC_DSC_SORT) // ����
			{
				dcMemory.MoveTo(topCt.x, topCt.y + sortIcoHeight - 1);
				dcMemory.LineTo(topCt.x - sortIcoHeight + 1, topCt.y);
				dcMemory.MoveTo(topCt.x, topCt.y + sortIcoHeight - 1);
				dcMemory.LineTo(topCt.x + sortIcoHeight - 1, topCt.y);
			}
		}
	}

	/***********************�л���***********************/

	CRect CTreeListCtrl::CalcListRect()
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		CRect rcHeader = CalcHeaderRect();

		CRect rcListRow = rcClient;
		rcListRow.top = rcListRow.top + rcHeader.Height();

		return rcListRow;
	}

	void CTreeListCtrl::DrawRow(CMemoryDC& dcMemory, const CRect& rcHeader, const CRect& rcList)
	{
		// û����ͷ
		if (0 == _columnVector.size())
			return;

		// ��ȡ��ͷҶ�ӽڵ�
		ColumnDataVector leafColumnVector;
		GetColumnAllLeafStruct(leafColumnVector);

		// �е����߶�
		int nIncreaseHeight = 0;
		int nVertPos = GetScrollPos(SB_VERT);

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
			hItemData->expandRect.SetRectEmpty(); // Fix:bw-136479

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

	void CTreeListCtrl::DrawRowBackground(CMemoryDC& dcMemory, HITEMDATA hItemData,
		const CRect& rcRow, ColumnDataVector& leafColumnVector, bool bFirstRow)
	{
		// ����ѡ��ʱ����
		if (hItemData->seleced)
		{
			CRect backgroundArea = rcRow;

			// �ų���������һ������
			if (_hasGrid)
				backgroundArea.top += 1;

			if (!_headerTheme.IsThemeNull())
			{
				// û��������ʱ���Ʊ߿�,��ñ���������û�߿�
				if (!_hasGrid)
				{
					CBrush borderBrush;
					borderBrush.CreateSolidBrush(_selBorderColor);
					dcMemory.FrameRect(backgroundArea, &borderBrush);
				}
			}
		}
		else if (_hHoverRow == hItemData)  // �����б���
		{
			CRect backgroundArea = rcRow;

			// �ų���������һ������
			if (_hasGrid)
				backgroundArea.top += 1;

			// û��������ʱ���Ʊ߿�
			if (!_hasGrid)
			{
				CBrush borderBrush;
				borderBrush.CreateSolidBrush(_hotBorderColor);
				dcMemory.FrameRect(backgroundArea, &borderBrush);
			}
		}

		// ��������
		if (_hasGrid)
		{
			CPen solidPen;
			solidPen.CreatePen(PS_SOLID, 1, _gridColor);

			HGDIOBJ hOldPen = dcMemory.SelectObject(solidPen);

			// ����ˮƽ����
			if (bFirstRow)
			{
				dcMemory.MoveTo(rcRow.left, rcRow.top);
				dcMemory.LineTo(rcRow.right, rcRow.top);
			}

			dcMemory.MoveTo(rcRow.left, rcRow.bottom);
			dcMemory.LineTo(rcRow.right, rcRow.bottom);

			bool bHasBorderStyle = !!(GetStyle() & WS_BORDER);

			CRect rcClient;
			GetClientRect(&rcClient);

			// ���ƴ�ֱ����
			size_t nCount = leafColumnVector.size();
			for (size_t i = 0; i < nCount; ++i)
			{
				HCOLUMNDATA hColumnData = leafColumnVector[i];
				const CRect& rcCell = hColumnData->colRect;

				// ��ֹ��߿��ص�
				if (i == 0 && !bHasBorderStyle)
				{
					dcMemory.MoveTo(rcCell.left, rcRow.top);
					dcMemory.LineTo(rcCell.left, rcRow.bottom);
				}

				// ��ֹ��߿��ص�
				if ((i == nCount - 1) && bHasBorderStyle
					&& rcCell.right == rcClient.right)
					continue;

				dcMemory.MoveTo(rcCell.right - 1, rcRow.top);
				dcMemory.LineTo(rcCell.right - 1, rcRow.bottom);
			}

			dcMemory.SelectObject(hOldPen);
		}
	}

	void CTreeListCtrl::DrawCell(CMemoryDC& dcMemory, const CRect& rcCell, bool bTreeNode, bool bFirstCell,
		HITEMDATA hItemData, HCELLINFO hCellInfo, HEDITCONFIG hEditConfig, HCOLUMNDATA hColumnData, const CString& strCellText)
	{
		/*
		* ע���޸Ĵ˷���ʱ���鿴�Ƿ���Ҫͬ���޸�CalcCellTextOutRect����
		*/
		int leftMargin = 4;	// ��Ԫ�����߾�
		int rightMargin = 4;   // ��Ԫ���Ҳ�߾�

		CRect backgroundArea = rcCell;

		// ������ʱ������������
		if (_hasGrid)
		{
			backgroundArea.top += 1;
			backgroundArea.right -= 1;

			if (bFirstCell)
				backgroundArea.left += 1;
		}

		// ���Ƶ�Ԫ�񱳾�
		if (!IsWindowEnabled())
			dcMemory.FillSolidRect(backgroundArea, DISABLE_BK_COLOR);
		else
		{
			short topr = GetRValue(hCellInfo->backColor);
			short topg = GetGValue(hCellInfo->backColor);
			short topb = GetBValue(hCellInfo->backColor);
			short bottomR = GetRValue(hCellInfo->backColor);
			short bottomG = GetGValue(hCellInfo->backColor);
			short bottomB = GetBValue(hCellInfo->backColor);
			if (hItemData->seleced)
			{
				topr = topr * GetRValue(_selTopColor) / 255;
				topg = topg * GetGValue(_selTopColor) / 255;
				topb = topb * GetBValue(_selTopColor) / 255;
				bottomR = bottomR * GetRValue(_selBottomColor) / 255;
				bottomG = bottomG * GetGValue(_selBottomColor) / 255;
				bottomB = bottomB * GetBValue(_selBottomColor) / 255;
			}
			else if (_hHoverRow == hItemData)
			{
				topr = topr * GetRValue(_hotTopColor) / 255;
				topg = topg * GetGValue(_hotTopColor) / 255;
				topb = topb * GetBValue(_hotTopColor) / 255;
				bottomR = bottomR * GetRValue(_hotBottomColor) / 255;
				bottomG = bottomG * GetGValue(_hotBottomColor) / 255;
				bottomB = bottomB * GetBValue(_hotBottomColor) / 255;
			}
			dcMemory.GradientVert(backgroundArea, RGB(topr, topg, topb), RGB(bottomR, bottomG, bottomB));
		}
			

		// ��ǰ�����ڵ㣬 ������Ǽ����ı�����
		if (bTreeNode)
		{
			int dotLineSpace = _hasLine ? 12 : 9; // ���ṹ�߼��
			int dashLineSpace = 15; // ���ṹ�����߳�

			// �������ṹ��
			if (_hasLine)
			{
				COLORREF dotColor = GetSysColor(COLOR_ACTIVEBORDER);

				// ������ʼλ��
				int startPos = dotLineSpace;
				for (int nLevel = 0; nLevel < hItemData->treeLevel; ++nLevel)
				{
					bool bIsLastLevel = (nLevel == hItemData->treeLevel - 1);

					// ����Ҷ�ӽڵ�����Ҳ�һ������
					if (hItemData->lastChild && bIsLastLevel)
					{
						dcMemory.DotVLine(rcCell.left + startPos, rcCell.top + 1, rcCell.Height() / 2, dotColor);
					}
					// �����ǰ���ƵĲ㼶�����ڵ㣬�򲻻���
					else if (!hItemData->IsLevelLastChild(hItemData->treeLevel - nLevel - 1))
					{
						dcMemory.DotVLine(rcCell.left + startPos, rcCell.top, rcCell.Height(), dotColor);
					}

					startPos += dotLineSpace;
				}

				// ���ƺ���������
				if (hItemData->treeLevel != 0)
				{
					CPoint cPt = rcCell.CenterPoint();
					dcMemory.DotHLine(rcCell.left + dotLineSpace*hItemData->treeLevel + 2, cPt.y, dashLineSpace, dotColor);
				}
			}

			// ���ӽڵ�����Ҫ����+-��
			if (hItemData->hasChild)
			{
				int startPos = (hItemData->treeLevel + 1)*dotLineSpace;

				// ����+1�Ǹ���ʵ��Ч��΢���õ�����ֵ
				CRect rcGlyph(CPoint(rcCell.left + startPos + 1, rcCell.CenterPoint().y + 1), CSize(0, 0));
				rcGlyph.InflateRect(dotLineSpace, dotLineSpace);

				CPoint ptCenter = rcGlyph.CenterPoint();
				DrawIconEx(dcMemory, ptCenter.x - 8, ptCenter.y - 8,
					hItemData->expand ? _hIconCollapse : _hIconExpand, 16, 16, 0, NULL, DI_NORMAL);

				// ��¼����ͼ������;
				hItemData->expandRect = rcGlyph;
				hItemData->expandRect.DeflateRect(1, 1, 1, 1);
			}

			// �������ͽ�����ʼ�߾�
			leftMargin = hItemData->treeLevel*dotLineSpace + dashLineSpace + rightMargin + 2;
		}

		// �Ƿ������ͼ��
		bool bDrawIcon = false;

		// ����ͼ������
		CRect rcIcon = rcCell;
		rcIcon.DeflateRect(leftMargin, 0, rightMargin, 0);
		rcIcon.top = rcIcon.CenterPoint().y - _iconSize.cy / 2;

		// ����ͼ��
		if (rcIcon.IsRectEmpty())
		{
			bDrawIcon = false;
		}
		else if (_pImageList)
		{
			if (hEditConfig->image != -1)
			{
				bDrawIcon = true;

				if (hEditConfig->bImageCenter)
					rcIcon.left = rcIcon.CenterPoint().x - _iconSize.cx / 2;		//����

				_pImageList->DrawEx(&dcMemory, hEditConfig->image, rcIcon.TopLeft(), _iconSize,
					CLR_DEFAULT, CLR_DEFAULT, ILD_IMAGE | ILD_TRANSPARENT);
			}
		}

		// ���Ƹ�ѡ��;
		int nOption = hEditConfig->option;
		if ((nOption & eCheckBoxEdit) || (nOption & eCheckBox3StateEdit))
		{
			CRect rcCheckBox;
			rcCheckBox.left = ((backgroundArea.left + backgroundArea.right) / 2) - (_iconSize.cx / 2) - 1;
			rcCheckBox.right = min(rcCheckBox.left + _iconSize.cx, rcCell.right);
			rcCheckBox.top = ((rcCell.top + rcCell.bottom) / 2) - (_iconSize.cy / 2);
			rcCheckBox.bottom = min(rcCheckBox.top + _iconSize.cy, rcCell.bottom);

			int nCheckValue = _ttoi(strCellText);

			if (nOption & eCheckBoxEdit)
			{
				// ��ͨ��ѡ��;
				dcMemory.DrawFrameControl(rcCheckBox, DFC_BUTTON,
					nCheckValue ? DFCS_CHECKED | DFCS_FLAT : DFCS_BUTTONCHECK | DFCS_FLAT);
			}
			else if (nOption & eCheckBox3StateEdit)
			{
				// ��̬��ѡ��;
				UINT BtnStyle = DFCS_FLAT;
				if (nCheckValue < 0)
					BtnStyle |= DFCS_BUTTONCHECK;
				else if (nCheckValue > 0)
					BtnStyle |= DFCS_CHECKED;
				else
					BtnStyle |= DFCS_BUTTONPUSH;

				dcMemory.DrawFrameControl(rcCheckBox, DFC_BUTTON, BtnStyle);
			}

			// ���Ʊ߿������ڸ� DrawFrameControl �������ı߿�;
			COLORREF crFrame = hCellInfo->readonly ? GetSysColor(COLOR_3DSHADOW) : GetSysColor(COLOR_HIGHLIGHT);
			for (int i = 0; i < 2; i++)
			{
				dcMemory.Draw3dRect(rcCheckBox.left + i, rcCheckBox.top + i,
					rcCheckBox.right - rcCheckBox.left - i * 2, rcCheckBox.bottom - rcCheckBox.top - i * 2,
					crFrame, crFrame);
			}

			return;
		}
		else if (nOption & eProgressEdit)
		{
			// ��ȡ��Ԫ����������
			CRect rcPrg = rcCell;

			// ת��Ϊ���������ݼ�����
			int nProgess = _ttoi(strCellText);
			if (nProgess > 100)
			{
				nProgess = 100;
			}

			if (!_progressTheme.IsThemeNull())
			{
				// ���ƽ��������
				rcPrg.DeflateRect(1, 2, 2, 1);
				_progressTheme.DrawThemeBackground(dcMemory, PP_BAR, 0, rcPrg);

				// ���ƽ��������
				rcPrg.right -= rcPrg.Width() * (100 - nProgess) / 100;
				_progressTheme.DrawThemeBackground(dcMemory, PP_CHUNK, 0, rcPrg);
			}
			else
			{
				rcPrg.DeflateRect(1, 2, 2, 1);
				CRect rcFrame = rcPrg;

				// ���ƽ��������
				rcPrg.right -= rcPrg.Width() * (100 - nProgess) / 100;
				dcMemory.FillSolidRect(rcPrg, _selBottomColor);

				// ���ƽ��������
				dcMemory.FrameRect(rcFrame, &CBrush(_selBorderColor));
			}

			// ��ʾ����
			if (nOption & ePrgShowText)
			{
				CString strProg;
				strProg.Format(_T("%d%%"), nProgess);
				rcPrg = rcCell;

				// ���־��У�����͸��
				dcMemory.SetBkMode(TRANSPARENT);
				dcMemory.DrawText(strProg, rcPrg, DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_WORD_ELLIPSIS | DT_NOPREFIX);
			}
			return;
		}

		if (nOption & eHyperLinkEdit)
		{
			dcMemory.SelectObject(_underlineFont);
			dcMemory.SetTextColor(RGB(0, 102, 204));
		}
		else
		{
			dcMemory.SetTextColor(hCellInfo->textColor);
		}

		// ����������
		CRect rcText = rcCell;
		if (bDrawIcon)
		{
			rcText.left = (rcIcon.left + _iconSize.cx + rightMargin / 2);
		}
		else
		{
			rcText.DeflateRect(leftMargin, 0, rightMargin, 0);
		}

		if (hEditConfig->bImageCenter)
			return;

		// ��������
		if (!rcText.IsRectEmpty() && !strCellText.IsEmpty())
		{
			dcMemory.SetBkMode(TRANSPARENT);

			if (_bRowWordWarp)
			{
				rcText.OffsetRect(0, (rcText.Height() - hCellInfo->wpHeight) / 2);
				dcMemory.DrawText(strCellText, rcText, hColumnData->format | DT_EDITCONTROL | DT_WORDBREAK | DT_NOPREFIX);
			}
			else
			{
				if (hEditConfig->option & eDiffColText)
					dcMemory.DrawColorText(strCellText, rcText,
						hColumnData->format | DT_SINGLELINE | DT_VCENTER | DT_WORD_ELLIPSIS | DT_NOPREFIX);
				else
					dcMemory.DrawText(strCellText, rcText,
						hColumnData->format | DT_SINGLELINE | DT_VCENTER | DT_WORD_ELLIPSIS | DT_NOPREFIX);
			}
		}
	}

	BOOL CTreeListCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
	{
		if (_hDragingCol != NULL)
		{
			// �����ƶ���ͷ���
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
			return TRUE;
		}
		else if (_hHoverRow != NULL)  // ���ó��������ƹ��
		{
			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);

			CRect rect = _hHoverRow->rowRect;

			// ��ȡ��ͷҶ�ӽڵ�
			ColumnDataVector leafColumnVector;
			GetColumnAllLeafStruct(leafColumnVector);

			size_t nCount = leafColumnVector.size();
			for (size_t i = 0; i < nCount; ++i)
			{
				HCOLUMNDATA hColumnData = leafColumnVector[i];

				// �����Ƿ�������;
				rect.left = hColumnData->colRect.left;
				rect.right = hColumnData->colRect.right;

				// ��굥��ʱλ���Ƿ��ڿؼ�������;
				if (rect.PtInRect(point))
				{
					CELLCONFIG cellCfg;
					_hHoverRow->pDataSource->GetCellData(i, _nHoverRowIndex, hColumnData, &cellCfg.cellInfo, &cellCfg.editConfig, _pConfig);
					if (cellCfg.editConfig.option & eHyperLinkEdit && !cellCfg.cellInfo.readonly)
					{
						SetCursor(LoadCursor(NULL, IDC_HAND));
						return TRUE;
					}
				}
			}
		}

		return CWnd::OnSetCursor(pWnd, nHitTest, message);
	}

	bool CTreeListCtrl::SetItemSelectFlag(HITEMDATA hItemSelect)
	{
		bool bChange = !_bCheckSelChange;
		short nCtrlState = 0;
		short nShiftState = 0;

		// ��ѡʱ���Ctrl��Shift������״̬
		if (!_bSingleSelect)
		{
			nCtrlState = GetKeyState(VK_CONTROL);
			nShiftState = GetKeyState(VK_SHIFT);
		}

		ListDataSourceIter endIter = _listDataSource.end();

		if (nShiftState >> 8)
		{
			// ����Shift���
			int nSelectRow = -1;
			ListDataSourceIter iter = _listDataSource.begin();
			for (int nRow = 0; iter != endIter; ++iter, ++nRow)
			{
				// �ҵ�ѡ���е��к�
				if (iter->second == hItemSelect)
				{
					nSelectRow = nRow;
				}
			}

			iter = _listDataSource.begin();
			for (int nRow = 0; iter != endIter; ++iter, ++nRow)
			{
				// ��ǰѡ��״̬������SHIFT����
				if (nSelectRow < 0 || _nLastSelectItem < 0)
				{
					// ֻѡ�е������
					if (iter->second == hItemSelect)
					{
						if (!hItemSelect->seleced)
						{
							bChange = true;
							hItemSelect->seleced = true;
						}

						_nLastSelectItem = nRow;
						break;
					}

					continue;
				}

				if ((nRow <= nSelectRow && nRow >= _nLastSelectItem)
					|| (nRow <= _nLastSelectItem && nRow >= nSelectRow))
				{
					// �ڵ���к���һѡ����֮�����ȫ��ѡ��
					if (!iter->second->seleced)
					{
						iter->second->seleced = true;
						bChange = true;
					}
				}
				else
				{
					// �������������в�ѡ��
					if (iter->second->seleced)
					{
						iter->second->seleced = false;
						bChange = true;
					}
				}
			}
		}
		else if (nCtrlState >> 8)
		{
			// ����Ctrl���
			ListDataSourceIter iter = _listDataSource.begin();
			for (int nRow = 0; iter != endIter; ++iter, ++nRow)
			{
				// ֻҪ����˶�ѡ��
				if (iter->second == hItemSelect)
				{
					bChange = true;

					// CTRL����ѡ��Ҳ����ȡ��
					hItemSelect->seleced = (!hItemSelect->seleced);

					if (hItemSelect->seleced)
					{
						// ���һ�Ρ�ѡ�С����и���Ϊ��һѡ����
						_nLastSelectItem = nRow;
					}
				}
			}
		}
		else
		{
			// �������״̬
			ListDataSourceIter iter = _listDataSource.begin();
			for (int nRow = 0; iter != endIter; ++iter, ++nRow)
			{
				// ѡ�е���У�ȥ�������е�ѡ��״̬
				if (iter->second == hItemSelect)
				{
					if (!iter->second->seleced)
						bChange = true;

					hItemSelect->seleced = true;
					_nLastSelectItem = nRow;
				}
				else
				{
					if (iter->second->seleced)
						bChange = true;
					iter->second->seleced = false;
				}
			}
		}

		return bChange;
	}

	LRESULT CTreeListCtrl::NotifyParent(UINT nMessage, int nCol, int nRow, HEDITCONFIG hEditCfg,
		const CString& strCellText, CString* pStrNewText, int nClickType)
	{
		CTreeListNotify notify;
		notify.hdrNotify.hwndFrom = m_hWnd;
		notify.hdrNotify.idFrom = GetDlgCtrlID();
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

	void CTreeListCtrl::DeleteControl()
	{
		if (_pControl)
		{
			if (IsWindow(_pControl->GetSafeHwnd()))
			{
				HWND hChild = _pControl->m_hWnd;

				// ֧���Ӵ��ڶ��Ƕ��,���3��
				for (int i = 0; i < 3; ++i)
				{
					HWND hParent = ::GetParent(hChild);
					if (hParent == m_hWnd)
					{
						::DestroyWindow(hChild);
						break;
					}
					hChild = hParent;
				}
			}

			_pControl = NULL;
		}
	}

	LRESULT CTreeListCtrl::OnHyperLink(WPARAM wParam, LPARAM lParam)
	{
		int nCol = int(wParam);
		int nRow = int(lParam);

		size_t nSelRow = GetSelectedIndex();
		if (nRow != nSelRow)
			return TRUE;

		// ���뵽����Ϣʱ��������Դ�������޸�
		IListDataSource* pSelectDataSource = GetSelectedItem();
		if (pSelectDataSource == NULL)
			return TRUE;

		ColumnDataVector leafColumnVector;
		GetColumnAllLeafStruct(leafColumnVector);

		HCOLUMNDATA hColumnData = leafColumnVector[nCol];

		// ��ȡ��Ԫ������
		CELLINFO cellInfo;
		EDITCONFIG editConfig;
		editConfig.isEditMode = true;
		pSelectDataSource->GetCellData(nCol, nRow, hColumnData, &cellInfo, &editConfig, _pConfig);

		if (cellInfo.readonly)
			return TRUE;

		CString strEventHandle = editConfig.eventHandle;
		if (!strEventHandle.IsEmpty())
		{
			/*IEventHandle *pHandle = (IEventHandle*)GET_OSGIOBJECT((LPCTSTR)strEventHandle);
			_bLinkOn = true;
			pHandle->ExcuteHandle(this, nCol, nRow, pSelectDataSource, &editConfig, _pConfig);
			_bLinkOn = false;
			delete pHandle;*/

			return TRUE;
		}

		_bLinkOn = true;
		// �����ӣ�������Ϣ���û��Լ�����;
		NotifyParent(LCN_HYPERLINK, (int)nCol, (int)nRow, &editConfig);
		_bLinkOn = false;

		return TRUE;
	}

	void CTreeListCtrl::EditFocusItem(int nCol)
	{
		CRect rect;
		int nRow = 0;
		HCOLUMNDATA hColumnData = NULL;
		IListDataSource* pDataSource = NULL;

		if (!GetFocusRect(nCol, nRow, hColumnData, rect, pDataSource, NULL))
			return;

		EditItemByParam(pDataSource, nRow, nCol, rect, hColumnData, true);
	}

	void CTreeListCtrl::EditItemByPoint(CPoint ptMs, bool bIsDbClk)
	{
		if (_hHoverRow == NULL)
			return;

		CRect rect;
		int nCol = -1, nRow = 0;
		HCOLUMNDATA hColumnData = NULL;
		IListDataSource* pDataSource = NULL;

		if (!GetFocusRect(nCol, nRow, hColumnData, rect, pDataSource, &ptMs))
			return;

		EditItemByParam(pDataSource, nRow, nCol, rect, hColumnData, bIsDbClk);
	}

	void CTreeListCtrl::EditItemByParam(IListDataSource* pDataSource,
		int nRow, int nCol, CRect rect, HCOLUMNDATA hColumnData, bool bIsDbClk)
	{
		// ��ȡ��Ԫ������
		CELLINFO cellInfo;
		EDITCONFIG editConfig;
		editConfig.isEditMode = true;
		pDataSource->GetCellData(nCol, nRow, hColumnData, &cellInfo, &editConfig, _pConfig);

		if (cellInfo.readonly)
			return;

		_nEditRowIndex = nRow;
		_nEditColIndex = nCol;

		// �޸������С�뵽���Դ����������޸�
		rect.top += 2;
		rect.right -= 1;
		rect.bottom -= 1;

		int nOption = editConfig.option;

		CString strNewText;
		CString strOldText = pDataSource->GetCellText(nCol, nRow, &editConfig, _pConfig);
		CString strOldData = _pConfig->GetTempData();

		if (!OnBeginEdit((int)nCol, (int)nRow, &editConfig, strOldText))
			return;

		if (NotifyParent(LCN_BEGINEDIT, (int)nCol, (int)nRow, &editConfig, strOldText, NULL) != LCNR_OK)
			return;

		if (!bIsDbClk)
		{
			if ((nOption & eCheckBoxEdit) || (nOption & eCheckBox3StateEdit))
			{
				if ((nOption & eCheckBoxEdit))
				{
					// ��ͨ��ѡ��;
					strNewText = _ttoi(strOldText) > 0 ? _T("0") : _T("1");
				}
				else
				{
					// ��̬��ѡ��;
					int nCheckImage = _ttoi(strOldText);
					if (nCheckImage < 0)
						strNewText = _T("0");
					else if (nCheckImage > 0)
						strNewText = _T("-1");
					else
						strNewText = _T("1");
				}

				// û���޸�
				if (strNewText == strOldText)
					return;

				if (!OnEndEdit((int)nCol, (int)nRow, &editConfig, strOldText, strNewText))
					return;

				if (LCNR_OK != NotifyParent(LCN_ENDEDIT, (int)nCol, (int)nRow, &editConfig, strOldText, &strNewText))
					return;

				pDataSource->SetCellText((int)nCol, (int)nRow, &editConfig, strNewText, _pConfig);

				// ��ɱ༭
				NotifyParent(LCN_ENDEDITDONE, (int)_nEditColIndex, (int)_nEditRowIndex, &editConfig, strOldText, &strNewText);
			}
			else if (nOption & eHyperLinkEdit)
			{
				// �����ӣ�������Ϣ���û��Լ�����;
				// ������Ϣ���Լ����õ����Ϣ�ӳٴ��������������༭�ؼ������༭
				PostMessage(LCN_HYPERLINK, nCol, nRow);
			}
		}
		// �����༭�ؼ�
		else if (bIsDbClk)
		{
			CreateEditorControl(nOption, editConfig, rect, strOldText, strOldData);
		}
	}

	void CTreeListCtrl::CreateEditorControl(int nOption,
		EDITCONFIG editConfig,
		CRect rect,
		const CString& strDefaultValue,
		const CString& strDefaultData)
	{
		if ((nOption & eNormalEdit) || (nOption & eValidEdit) || (nOption & eFileNameEdit))
		{
			DeleteControl();
			if (!_listEdit.Create(this, rect, strDefaultValue, _bRowWordWarp))
				return;

			_pControl = &_listEdit;
			_listEdit.SetFont(&_treeListFont);
			_listEdit.SetEditFlag(editConfig.option);
			_listEdit.SetDotNum(editConfig.dotNum);

			// ����������ʾ���򣬱�������ES_MULTILINE���
			CRect rcRect;
			_listEdit.GetRect(&rcRect);
			rcRect.DeflateRect(4, 5, 0, -5);
			_listEdit.SetRect(rcRect);

			_listEdit.ShowWindow(SW_SHOW);
			_listEdit.SetFocus();
		}
		else if (nOption & eDropListCobEdit || nOption & eDropDownCobEdit)
		{
			DeleteControl();
			bool bDropList = !!(editConfig.option & eDropListCobEdit);

			// �����ؼ�;
			if (!_listCombo.Create(this, rect, bDropList, strDefaultValue))
				return;

			// ������������
			_listCombo.SetFont(&_treeListFont);
			CString strXmlFile = CPathConfig::GetSystemPath() + editConfig.comboDataFile;
			if (!_listCombo.LoadXmlData(strXmlFile))
				_listCombo.LoadStringVector(editConfig.comboList);

			_pControl = &_listCombo;

			// ��û����������ʱ����ʾ̫����������
			if (_listCombo.GetCount() == 0)
			{
				CRect rc;
				_listCombo.GetWindowRect(&rc);
				rc.bottom = rc.top + 50;
				_listCombo.GetParent()->ScreenToClient(&rc);
				_listCombo.MoveWindow(rc);
			}

			// �����༭��λ��
			CWnd* pWndEdit = _listCombo.GetWindow(GW_CHILD);
			if (!bDropList && (NULL != pWndEdit))
			{
				CRect rc;
				pWndEdit->GetWindowRect(&rc);
				rc.DeflateRect(2, 4, 0, -2);
				_listCombo.ScreenToClient(&rc);
				pWndEdit->MoveWindow(rc);
			}
			_listCombo.ShowWindow(SW_SHOW);
			_listCombo.SetSelAndFocus();
		}
		else if (nOption & eDateTimeEdit)
		{
			DeleteControl();

			bool bSuccess = false;
			if (eDateYear & editConfig.option)
				bSuccess = _listDataTime.Create(this, rect, strDefaultValue, true);
			else
				bSuccess = _listDataTime.Create(this, rect, strDefaultValue);

			if (!bSuccess)
				return;

			_pControl = &_listDataTime;
			_listDataTime.SetFont(&_treeListFont);

			if (eDateSlashYMD & editConfig.option)
				_listDataTime.SetFormat(L"yyyy/MM/dd");
			else if (eDateChineseYMD & editConfig.option)
				_listDataTime.SetFormat(L"yyyy��MM��dd��");
			else if (eDateDashYMD & editConfig.option)
				_listDataTime.SetFormat(L"yyyy-MM-dd");
			else if (eDateYear & editConfig.option)
			{
				_listDataTime.SetFormat(L"yyyy");
			}

			_listDataTime.ShowWindow(SW_SHOW);
			_listDataTime.SetFocus();
		}
		else if (nOption & eAngleEdit)
		{
			DeleteControl();
			if (!_listAngleEdit.Create(this, rect, strDefaultValue))
				return;

			_pControl = &_listAngleEdit;
			_listAngleEdit.SetFont(&_treeListFont);

			// ����������ʾ���򣬱�������ES_MULTILINE���
			CRect rcRect;
			_listAngleEdit.GetRect(&rcRect);
			rcRect.DeflateRect(4, 5, -4, -5);
			_listAngleEdit.SetRect(rcRect);

			_listAngleEdit.ShowWindow(SW_SHOW);
			_listAngleEdit.SetEditFocus();
		}
		else if (nOption & eTreeComboEdit || (nOption & eTreeComboManualEdit))
		{
			DeleteControl();

			_listTreeCombo.SetCheckMode(false);
			_listTreeCombo.SetSplitChar(editConfig.splitChar);

			// ����Ӧ��Ȼ���ռ���
			if (nOption&eTreeAutoWidth)
				_listTreeCombo.SetDroppedWidth(0);
			else
				_listTreeCombo.SetDroppedWidth(-1);

			if (nOption&eTreeSelNotByText)
				_listTreeCombo.SetSelectByText(false);
			else
				_listTreeCombo.SetSelectByText(true);

			// �����ؼ�;
			bool bDropList = !!(editConfig.option & eTreeComboEdit);
			if (!_listTreeCombo.CreateCtrl(this, rect, strDefaultValue, strDefaultData, bDropList))
				return;

			// ������������
			CString strXmlFile = CPathConfig::GetSystemPath();
			strXmlFile += editConfig.comboDataFile;

			// ���ȼ����ļ�
			if (editConfig.comboDataFile.IsEmpty())
			{
				_listTreeCombo.LoadStringVector(editConfig.comboList);
			}
			else if (CFileTool::FileExist((LPCTSTR)strXmlFile))
			{
				_listTreeCombo.LoadXmlData(strXmlFile, !!(nOption&eTreeHasNoLimit));
			}
			else // ����XML�ַ���
			{
				_listTreeCombo.LoadXmlData(editConfig.comboDataFile, !!(nOption&eTreeHasNoLimit));
			}

			_pControl = &_listTreeCombo;
			_listTreeCombo.SetFont(&_treeListFont);
			_listTreeCombo.SetSelectData(strDefaultValue, strDefaultData);
			_listTreeCombo.ShowWindow(SW_SHOW);
			_listTreeCombo.SetFocus();
		}
		else if (nOption & eTreeCheckComboEdit || (nOption & eTreeCheckComboManualEdit))
		{
			DeleteControl();

			_listTreeCombo.SetCheckMode(true);
			_listTreeCombo.SetSplitChar(editConfig.splitChar);

			// ����Ӧ���
			_listTreeCombo.SetDroppedWidth(0);

			if (nOption&eTreeSelNotByText)
				_listTreeCombo.SetSelectByText(false);
			else
				_listTreeCombo.SetSelectByText(true);

			// �����ؼ�;
			bool bDropList = !!(editConfig.option & eTreeCheckComboEdit);
			if (!_listTreeCombo.CreateCtrl(this, rect, strDefaultValue, strDefaultData, bDropList))
				return;

			// ������������
			CString strXmlFile = CPathConfig::GetSystemPath() + editConfig.comboDataFile;

			// ���ȼ����ļ�
			if (editConfig.comboDataFile.IsEmpty())
			{
				_listTreeCombo.LoadStringVector(editConfig.comboList, !!(nOption & eTreeHasSelAll));
			}
			else if (CFileTool::FileExist((LPCTSTR)strXmlFile))
			{
				_listTreeCombo.LoadXmlData(strXmlFile, !!(nOption & eTreeHasSelAll));
			}
			else // ����XML�ַ���
			{
				_listTreeCombo.LoadXmlData(editConfig.comboDataFile, !!(nOption & eTreeHasSelAll));
			}

			_pControl = &_listTreeCombo;
			_listTreeCombo.SetFont(&_treeListFont);
			_listTreeCombo.ShowWindow(SW_SHOW);
			_listTreeCombo.SetFocus();
		}
		else if (nOption & eAutoSearchCombo)
		{
			DeleteControl();

			// �����ؼ�;
			if (!_autoCombo.Create(this, rect, false, strDefaultValue))
				return;

			// ������������
			_autoCombo.SetFont(&_treeListFont);

			CString strXmlFile = CPathConfig::GetSystemPath();
			strXmlFile += editConfig.comboDataFile;
			if (!_autoCombo.LoadXmlData(strXmlFile))
				_autoCombo.LoadStringVector(editConfig.comboList);

			_pControl = &_autoCombo;

			// ��û����������ʱ����ʾ̫����������
			if (_autoCombo.GetCount() == 0)
			{
				CRect rc;
				_autoCombo.GetWindowRect(&rc);
				rc.bottom = rc.top + 50;
				_autoCombo.GetParent()->ScreenToClient(&rc);
				_autoCombo.MoveWindow(rc);
			}

			// �����༭��λ��
			CWnd* pWndEdit = _autoCombo.GetWindow(GW_CHILD);

			if (pWndEdit)
			{
				CRect rc;
				pWndEdit->GetWindowRect(&rc);
				rc.DeflateRect(2, 4, 0, -2);
				_autoCombo.ScreenToClient(&rc);
				pWndEdit->MoveWindow(rc);
			}

			_autoCombo.ShowWindow(SW_SHOW);
			_autoCombo.SetSelAndFocus();
		}
	}

	bool CTreeListCtrl::GetFocusRect(int &nCol, int &nRow, HCOLUMNDATA& hColData,
		CRect &rect, IListDataSource* &pDataSource, CPoint* ptMs)
	{
		// ȷ��ѡ����
		nRow = -1;
		HITEMDATA hItemData = NULL;
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin();
			iter != endIter; ++iter)
		{
			++nRow;
			if (iter->second->seleced)
			{
				hItemData = iter->second;
				break;
			}
		}

		if (NULL == hItemData)
			return false;

		rect = hItemData->rowRect;
		pDataSource = hItemData->GetDataSource();

		// ��ȡ��ͷҶ�ӽڵ�
		ColumnDataVector leafColumnVector;
		GetColumnAllLeafStruct(leafColumnVector);

		size_t nCount = leafColumnVector.size();
		if (-1 != nCol)
		{
			if (nCol < 0 || nCol >= int(nCount))
				return false;

			HCOLUMNDATA hColumnData = leafColumnVector[nCol];

			// �����Ƿ�������;
			rect.left = hColumnData->colRect.left;
			rect.right = hColumnData->colRect.right;
			hColData = hColumnData;

			return true;
		}

		if (NULL == ptMs)
			return false;

		// ������ͷ
		for (size_t i = 0; i < nCount; ++i)
		{
			HCOLUMNDATA hColumnData = leafColumnVector[i];

			// �����Ƿ�������;
			rect.left = hColumnData->colRect.left;
			rect.right = hColumnData->colRect.right;

			// ��굥��ʱλ���Ƿ��ڿؼ�������;
			if (rect.PtInRect(*ptMs))
			{
				nCol = (int)i;
				hColData = hColumnData;
				return true;
			}
		}

		return false;
	}

	bool CTreeListCtrl::OnBeginEdit(int nCol, int nRow,
		HEDITCONFIG hEditCfg, const CString& strOldCellText)
	{
		return true;
	}

	bool CTreeListCtrl::OnEndEdit(int nCol, int nRow,
		HEDITCONFIG hEditCfg, const CString& strOldCellText, CString& strNewCellText)
	{
		return true;
	}

	bool CTreeListCtrl::ShowRightMenu()
	{
		return true;
	}

	void CTreeListCtrl::SetFocusItemByKey(size_t nKey)
	{
		size_t nRow = 0;
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin(); iter != endIter; ++iter)
		{
			if (iter->second->pDataSource->GetKey() == nKey)
			{
				SetFocusItem(nRow);
				break;
			}
			nRow++;
		}
	}

	void CTreeListCtrl::ShowHeader(bool bShow)
	{
		_showHeader = bShow;
	}

	void CTreeListCtrl::SetHasLine(bool hasLine)
	{
		_hasLine = hasLine;
	}

	void CTreeListCtrl::SetHasGrid(bool bShow)
	{
		_hasGrid = bShow;
	}

	int CTreeListCtrl::GetCtrlHeight()
	{
		int nHeight = 0;

		if (_showHeader)
		{
			nHeight += CalcHeaderRect().Height();
		}

		// ͳ�����ܸ߶�
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin();
			iter != endIter; ++iter)
		{
			HITEMDATA hParentData = iter->second->hParentData;
			if (NULL != hParentData && hParentData->IsCollapse())
				continue;

			CRect& rcRow = iter->second->rowRect;

			// ��û�л��Ƴ�ʼ��ʱ����ʹ��Ĭ�ϸ߶�
			if (_bRowWordWarp && rcRow.Height() != 0)
				nHeight += rcRow.Height();
			else
				nHeight += _nRowHeight;
		}

		return nHeight + 1;  ///< ��1��ֹ����������
	}

	void CTreeListCtrl::SetHeadItemHeight(int nHeight)
	{
		if (nHeight <= 0)
			return;

		_nHeaderHeight = nHeight;
	}

	void CTreeListCtrl::SetTreeColumn(int nColumnIndex /*= 0*/)
	{
		_treeColumn = nColumnIndex;
	}

	void CTreeListCtrl::EnableColumnSort(bool bEnable)
	{
		_bColumnSort = bEnable;
	}

	void CTreeListCtrl::CalcCellTextOutRect(CDC* pDc, const CString& strText,
		CRect& rcCell, bool bTreeNode, HITEMDATA hItemData, HEDITCONFIG hEditConfig,
		HCOLUMNDATA hColumnData, CRect& rcTextOut)
	{
		CMemoryDC* pDcTest = (CMemoryDC*)pDc;

		int leftMargin = 4;	// ��Ԫ�����߾�
		int rightMargin = 4;   // ��Ԫ���Ҳ�߾�
		int dotLineSpace = _hasLine ? 12 : 9; // ���ṹ�߼��; // ���ṹ�߼��
		int dashLineSpace = 15; // ���ṹ�����߳�

		// ��ǰ�����ڵ㣬 // �������ͽ�����ʼ�߾�
		if (bTreeNode)
		{
			leftMargin = hItemData->treeLevel*dotLineSpace + dashLineSpace + rightMargin + 2;
		}

		// �Ƿ������ͼ��
		bool bDrawIcon = false;

		// ����ͼ������
		CRect rcIcon = rcCell;
		rcIcon.DeflateRect(leftMargin, 0, rightMargin, 0);
		rcIcon.top = rcIcon.CenterPoint().y - _iconSize.cy / 2;

		// ����ͼ��
		if (rcIcon.IsRectEmpty())
		{
			bDrawIcon = false;
		}
		else if (_pImageList)
		{
			if (hEditConfig->image != -1)
				bDrawIcon = true;
		}

		// ����������
		if (bDrawIcon)
		{
			rcCell.left = (rcIcon.left + _iconSize.cx + rightMargin / 2);
		}
		else
		{
			rcCell.DeflateRect(leftMargin, 0, rightMargin, 0);
		}

		rcTextOut = rcCell;

		if (!_bRowWordWarp)
		{
			if (hEditConfig->option & eDiffColText)
				pDcTest->DrawColorText(strText, rcTextOut, hColumnData->format | DT_SINGLELINE | DT_VCENTER | DT_CALCRECT | DT_NOPREFIX);
			else
				pDcTest->DrawText(strText, rcTextOut, hColumnData->format | DT_SINGLELINE | DT_VCENTER | DT_CALCRECT | DT_NOPREFIX);

			rcTextOut.bottom = rcCell.bottom + 1;
		}
		else
		{
			pDcTest->DrawText(strText, rcTextOut, hColumnData->format | DT_EDITCONTROL | DT_WORDBREAK | DT_NOPREFIX | DT_CALCRECT);
		}
	}

	void CTreeListCtrl::ProcessCellTooltip()
	{
		if (_lockTipUpdate || (NULL == _hHoverRow)
			|| (-1 == _nHoverRowIndex) || _bLinkOn || _bRowWordWarp)
		{
			return;
		}

		// ��ȡ���λ��
		CPoint mPt;
		GetCursorPos(&mPt);
		ScreenToClient(&mPt);

		CRect rcWnd;
		GetWindowRect(&rcWnd);
		ScreenToClient(&rcWnd);

		// �������Ƿ��ڴ��������ڣ��Ŵ�����ʾ��Ϣ
		if (!rcWnd.PtInRect(mPt))
			return;

		int nHoverColIndex = -1;
		CRect rcCell = _hHoverRow->rowRect;

		HCOLUMNDATA hColumnData = NULL;

		// ��ȡ��ͷҶ�ӽڵ�
		ColumnDataVector leafColumnVector;
		GetColumnAllLeafStruct(leafColumnVector);

		// ������ͷ
		size_t nCount = leafColumnVector.size();
		for (size_t i = 0; i < nCount; ++i)
		{
			hColumnData = leafColumnVector[i];

			// �����Ƿ�������;
			rcCell.left = hColumnData->colRect.left;
			rcCell.right = hColumnData->colRect.right;

			// ��굥��ʱλ���Ƿ��ڿؼ�������;
			if (rcCell.PtInRect(mPt))
			{
				nHoverColIndex = (int)i;
				break;
			}
		}

		// û�ҵ���ͷ
		if (-1 == nHoverColIndex)
			return;

		CELLINFO cellInfo;
		EDITCONFIG editConfig;
		_hHoverRow->GetDataSource()->GetCellData(nHoverColIndex, _nHoverRowIndex,
			hColumnData, &cellInfo, &editConfig, _pConfig);

		// ����ʾ��ʾ��Ϣ������Ҫȡ�ı���Ϣ
		if (!editConfig.isShowTips)
			return;

		// ��ȡ��Ԫ�����ı�
		CString strCellText = _hHoverRow->GetDataSource()->GetCellText(nHoverColIndex,
			_nHoverRowIndex, &editConfig, _pConfig);

		// ��������ʾ����Ϊ�㣬�����һ����ʾtooltip���޸ĳɶ����ƺ��ٴ���ʾ��������
		_cellToolTip.SetRect(CRect(0, 0, 0, 0), CRect(0, 0, 0, 0));

		// �ı�Ϊ���Ҳ����ڱ༭״̬
		if (strCellText.IsEmpty() || (_pControl != NULL && _pControl->GetSafeHwnd() != NULL && _pControl->IsWindowVisible()))
			return;

		CClientDC dc(this);
		CFont* pOldFont = dc.SelectObject(&_treeListFont);

		// �ж��Ƿ���Ҫ������ʾ��Ϣ
		CRect rcTipRect;
		CalcCellTextOutRect(&dc, strCellText, rcCell, (nHoverColIndex == _treeColumn && (!_bNoChild || _hHoverRow->hParentData != NULL)),
			_hHoverRow, &editConfig, hColumnData, rcTipRect);
		dc.SelectObject(pOldFont);

		if (!editConfig.bImageCenter)
		{
			if (rcTipRect.Width() <= rcCell.Width())
				return;
		}
		else
		{
			//ͼƬ������ʾ
			double dWidth = rcTipRect.Width();
			rcTipRect.left = rcCell.right;
			rcTipRect.right = rcTipRect.left + dWidth;
		}

		_cellToolTip.SetClrText(!!(editConfig.option&eDiffColText));
		_cellToolTip.SetTextMode(hColumnData->format);
		_cellToolTip.SetTipText(strCellText);
		_cellToolTip.SetRect(rcCell, rcTipRect);
	}

	void CTreeListCtrl::AutoColumnWidth()
	{
		CRect rcNowClient;
		GetClientRect(&rcNowClient);

		if (!_bAutoColumnWidth)
		{
			return;
		}

		size_t nCount = _columnVector.size();
		int nSumColumnWidth = 0;

		// ��ȡ���ۼƿ��
		for (size_t i = 0; i < nCount; ++i)
		{
			nSumColumnWidth += _columnVector[i]->GetWidth();
		}

		std::vector<int> vecWidthArr;

		int nMinWidth = rcNowClient.Width();

		// �����������п�
		for (size_t i = 0; i < nCount; ++i)
		{
			double dScale = (double)_columnVector[i]->GetWidth() / nSumColumnWidth;

			int nNewWidth = (int)(dScale * rcNowClient.Width());

			// �ҵ���С�п�
			if (nNewWidth < nMinWidth)
			{
				nMinWidth = nNewWidth;
			}

			// ��ø��º���п�
			vecWidthArr.push_back(nNewWidth);
		}

		// �������п�����С�ģ����в���
		int nDiff = nMinWidth - 35;
		if (nDiff < 0)
		{
			nDiff = 35 - nMinWidth;
		}
		else
		{
			nDiff = 0;
		}

		for (size_t i = 0; i < nCount; ++i)
		{
			_columnVector[i]->SetWidth(vecWidthArr.at(i) + nDiff);
		}
	}

	void CTreeListCtrl::SetAutoColumnWidth(bool bIsAutoColumnWidth /*= true*/)
	{
		_bAutoColumnWidth = bIsAutoColumnWidth;
	}

	bool CTreeListCtrl::SetExpandBySelectItem(bool bExpand /*= true*/)
	{
		bool bFlag = false;

		// ������ǰѡ��ļ�¼;
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin(); iter != endIter; ++iter)
		{
			// ѡ����״̬�޸�
			if (iter->second->seleced)
			{
				iter->second->expand = bExpand;
				bFlag = true;
			}
		}

		return bFlag;
	}

	bool CTreeListCtrl::SetExpandItemByKey(size_t nKey, bool bExpand /*= true*/, bool bParent /*= false*/)
	{
		bool bFlag = false;

		// ��������Դ���ҵ���ӦKEY
		ListDataSourceIter endIter = _listDataSource.end();
		for (ListDataSourceIter iter = _listDataSource.begin(); iter != endIter; ++iter)
		{
			if (iter->first == nKey)
			{
				iter->second->expand = bExpand;
				bFlag = true;

				// �ݹ鸸�ڵ㲢����չ��״̬
				HITEMDATA ParentInfo = iter->second->hParentData;
				while (bParent && ParentInfo != NULL)
				{
					ParentInfo->expand = bExpand;
					ParentInfo = ParentInfo->hParentData;
				}

				break;
			}
		}

		return bFlag;
	}

	BOOL CTreeListCtrl::PreTranslateMessage(MSG* pMsg)
	{
		// ���°�����־λ�÷�
		_bUpDownFlag = false;

		// �����̰��µ��¼���Ϣ
		if (pMsg->message == WM_KEYDOWN &&
			(_pControl == NULL || _pControl->GetSafeHwnd() == NULL || !_pControl->IsWindowVisible()))
		{
			// ���ӿؼ���ʾʱ�����°�������Ӧ
			switch (pMsg->wParam)
			{
			case VK_UP:
				// ���¼���־λ
				_bUpDownFlag = true;

				// ����ѡ��
				SetSelRowByKey(false);

				// ˢ��
				Invalidate(TRUE);
				break;
			case VK_DOWN:
				_bUpDownFlag = true;
				SetSelRowByKey(true);
				Invalidate(TRUE);
				break;
			default:
				break;
			}
		}

		// ��ʾ��Ϣ
		if (_cellToolTip.GetSafeHwnd())
		{
			_cellToolTip.RelayEvent(pMsg);
		}

		return CWnd::PreTranslateMessage(pMsg);
	}

	void CTreeListCtrl::SetSelRowByKey(bool bNextRow)
	{
		if (_listDataSource.empty())
		{
			return;
		}

		// ����������
		int nSelIndex = GetSelectedIndex();
		ListDataSourceIter iter = _listDataSource.begin();
		ListDataSourceIter enditer = _listDataSource.end();
		for (int i = 0; i < nSelIndex && nSelIndex > 0; ++i)
		{
			iter++;
		}

		int nNextRow = nSelIndex;
		size_t nCount = _listDataSource.size();

		while (true)
		{
			if (bNextRow)
			{
				nNextRow = int((nNextRow + 1) % nCount);
				if (++iter == enditer)
				{
					iter = _listDataSource.begin();
				}
			}
			else
			{
				nNextRow = (nNextRow < 0) ? 0 : nNextRow;
				nNextRow = int((nNextRow - 1 + nCount) % nCount);
				if (iter == _listDataSource.begin())
				{
					iter = enditer;
				}
				--iter;
			}

			HITEMDATA hItemData = iter->second;
			HITEMDATA hParentData = hItemData->hParentData;

			// ���ڽڵ��ϲ�������,��չ��
			if (NULL == hParentData || !hParentData->IsCollapse())
			{
				break;
			}
		}

		SetFocusItem(nNextRow);
	}

	bool CTreeListCtrl::SetFocusItemByCString(const CString& strSel)
	{
		if (_listDataSource.empty())
		{
			return false;
		}

		ColumnDataVector leafColumnVector;
		GetColumnAllLeafStruct(leafColumnVector);

		// ������
		ListDataSourceIter iter = _listDataSource.begin();
		ListDataSourceIter enditer = _listDataSource.end();
		for (int i = 0; iter != enditer; ++iter, ++i)
		{
			HITEMDATA hItemData = iter->second;
			HCOLUMNDATA hColumnData = leafColumnVector[0];
			CELLINFO cellInfo;
			EDITCONFIG editConfig;
			hItemData->pDataSource->GetCellData(i, 0, hColumnData, &cellInfo, &editConfig, _pConfig);
			CString strText = hItemData->pDataSource->GetCellText(i, 0, &editConfig, _pConfig);
			if (strSel == strText)
			{
				SetFocusItem(i);
				return true;
			}
		}

		return false;
	}

	void CTreeListCtrl::OnKillFocus(CWnd* pNewWnd)
	{
		// ��ʧ����ʱ���ж��Ƿ������¼�
		if (_bUpDownFlag)
		{
			// ���������û���
			SetFocus();
			_bUpDownFlag = false;
		}
		else if (NULL != _cellToolTip)
		{
			// �����ʾ��
			_cellToolTip.Reset();
		}
	}

	LRESULT CTreeListCtrl::OnThemeChanged()
	{
		// ������ĺ����¼���Ƥ������
		_headerTheme.CloseThemeData();
		_headerTheme.OpenThemeData(m_hWnd, L"HEADER");

		_progressTheme.CloseThemeData();
		_progressTheme.OpenThemeData(m_hWnd, L"PROGRESS");

		return 0;
	}

	void CTreeListCtrl::SetColumnWordWarp(bool bWorldWarp)
	{
		_bColumnWordWarp = bWorldWarp;
	}

	void CTreeListCtrl::SetRowWordWarp(bool bWorldWarp)
	{
		_bRowWordWarp = bWorldWarp;
	}

	void CTreeListCtrl::MakeRowVisible(int nDataRowIndex)
	{
		if (nDataRowIndex < 0 || nDataRowIndex >= int(_listDataSource.size()))
			return;

		SCROLLINFO infoScroll;
		infoScroll.cbSize = sizeof(SCROLLINFO);
		infoScroll.fMask = SIF_ALL;
		if (GetScrollInfo(SB_VERT, &infoScroll))
		{
			infoScroll.fMask = SIF_POS;

			HITEMDATA hItemData = NULL;
			ListDataSourceIter endIter = _listDataSource.end();
			for (ListDataSourceIter iter = _listDataSource.begin();
				iter != endIter; ++iter)
			{
				if (nDataRowIndex == 0)
				{
					hItemData = iter->second;
					break;
				}

				nDataRowIndex--;
			}

			if (hItemData == NULL)
				return;

			CRect rcHead = CalcHeaderRect();
			CRect rcItem = hItemData->rowRect;
			rcItem.top = rcItem.top - rcHead.Height() + infoScroll.nPos;
			rcItem.bottom = rcItem.bottom - rcHead.Height() + infoScroll.nPos;

			// ��ǰѡ�еĲ�����ʾ��Χ��
			if (!(rcItem.top >= LONG(infoScroll.nPos) &&
				rcItem.bottom <= LONG(infoScroll.nPos + infoScroll.nPage)))
			{
				// ���¶�λ
				if (rcItem.top > infoScroll.nPos)
				{
					infoScroll.nPos = min(LONG(rcItem.bottom - infoScroll.nPage), LONG(infoScroll.nMax - infoScroll.nPage + 1));
				}
				else // ���϶�λ
				{
					infoScroll.nPos = min(rcItem.top, LONG(infoScroll.nMax - infoScroll.nPage + 1));
				}
			}

			SetScrollInfo(SB_VERT, &infoScroll);
		}
	}

	void CTreeListCtrl::SelectFirstLeafNode(bool bFocusOnTop)
	{
		ListDataSource::const_iterator iterRowEnd = _listDataSource.end();
		for (ListDataSource::const_iterator iterRowData = _listDataSource.begin();
			iterRowData != iterRowEnd; ++iterRowData)
		{
			if (!iterRowData->second->HasChildNode())
			{
				SetFocusItemByDataSource(iterRowData->second->GetDataSource());
				// ����Ĭ��ѡ�е�һ��Ҷ�ӽڵ�
				break;
			}
		}

		if (bFocusOnTop)
		{
			SendMessage(WM_VSCROLL, SB_TOP, NULL);
		}
	}

	void CTreeListCtrl::GetMaxColumnLevel(int& nMaxLevel, HCOLUMNDATA hColumnData, int nCurLevel)
	{
		// ��¼���㼶
		if (nCurLevel > nMaxLevel)
			nMaxLevel = nCurLevel;

		ColumnDataVector& columnVector = hColumnData
			? hColumnData->childColumn : _columnVector;

		size_t sz = columnVector.size();
		for (size_t nCol = 0; nCol < sz; ++nCol)
		{
			GetMaxColumnLevel(nMaxLevel, columnVector[nCol], nCurLevel + 1);
		}
	}

	void CTreeListCtrl::GetColumnAllLeafStruct(ColumnDataVector& leafColumnVector,
		HCOLUMNDATA hColumnData)
	{
		// Ҷ�ӽڵ�
		if (hColumnData && 0 == hColumnData->childColumn.size())
			leafColumnVector.push_back(hColumnData);

		ColumnDataVector& columnVector = hColumnData
			? hColumnData->childColumn : _columnVector;

		size_t sz = columnVector.size();
		for (size_t nCol = 0; nCol < sz; ++nCol)
		{
			GetColumnAllLeafStruct(leafColumnVector, columnVector[nCol]);
		}
	}

	void CTreeListCtrl::GetColumnLinearityStruct(ColumnDataVector& outColumnVector,
		HCOLUMNDATA hColumnData)
	{
		if (NULL != hColumnData)
		{
			outColumnVector.push_back(hColumnData);
		}

		ColumnDataVector& columnVector = hColumnData
			? hColumnData->childColumn : _columnVector;

		size_t sz = columnVector.size();
		for (size_t nCol = 0; nCol < sz; ++nCol)
		{
			GetColumnLinearityStruct(outColumnVector, columnVector[nCol]);
		}
	}

	void CTreeListCtrl::SetTrim(bool bTrim)
	{
		_bIsTrim = bTrim;
	}

	void CTreeListCtrl::SetSelectChangeCheck(bool bCheck)
	{
		_bCheckSelChange = bCheck;
	}

	void CTreeListCtrl::SetCollapseStyle(bool bStyle /*= false*/)
	{
		_bCollapseStyle = bStyle;
	}

}
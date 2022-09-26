#include "StdAfx.h"
#include "TreeComboBox.h"

namespace ControlUI
{
	static bool bComBoxChange = false;

	CComboBoxTree::CComboBoxTree() : _pCombo(NULL)
	{
	}

	CComboBoxTree::~CComboBoxTree()
	{
	}

	BEGIN_MESSAGE_MAP(CComboBoxTree, CTreeCtrl)
		ON_WM_MOUSEMOVE()
		ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnKillfocus)
		ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	END_MESSAGE_MAP()

	void CComboBoxTree::Display(CRect rect)
	{
		if (NULL != GetSafeHwnd())
		{
			CWnd* pTopParent = GetParent();
			SetWindowPos(NULL, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);

			if (NULL != pTopParent)
			{
				pTopParent->SendMessage(WM_NCACTIVATE, TRUE);
			}

			SetCapture();
		}
	}

	void CComboBoxTree::CloseTree(int nTag)
	{
		ReleaseCapture();
		::PostMessage(_pCombo->m_hWnd, UM_DROP_CLOSE, (WPARAM)nTag, (LPARAM)0);
	}

	BOOL CComboBoxTree::PreTranslateMessage(MSG* pMsg)
	{
		if (pMsg->hwnd == m_hWnd && WM_SYSKEYDOWN == pMsg->message && VK_F4 == pMsg->wParam)
			return TRUE;

		if ((pMsg->hwnd == m_hWnd) && (WM_KEYDOWN == pMsg->message) && (VK_ESCAPE == pMsg->wParam))
		{
			CloseTree();
			return TRUE;
		}
		if ((pMsg->hwnd == m_hWnd) && (WM_LBUTTONDOWN == pMsg->message))
		{
			CRect rcClient;
			GetClientRect(&rcClient);
			ClientToScreen(&rcClient);
			if (!rcClient.PtInRect(pMsg->pt))
			{
				CloseTree();
				return TRUE;
			}
		}

		return CTreeCtrl::PreTranslateMessage(pMsg);
	}

	void CComboBoxTree::OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult)
	{
		CloseTree();
	}

	void CComboBoxTree::OnMouseMove(UINT nFlags, CPoint point)
	{
		CTreeCtrl::OnMouseMove(nFlags, point);

		if (_pCombo->IsCheckMode())
			return;

		UINT uFlags;
		HTREEITEM hItem = HitTest(point, &uFlags);
		if (NULL != hItem)
		{
			SelectItem(hItem);
		}
	}

	void CComboBoxTree::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);

		UINT uFlags;
		HTREEITEM hItem = HitTest(point, &uFlags);
		if (hItem == NULL)
			return;

		if (_pCombo->IsCheckMode())
		{
			SelectItem(hItem);

			if (!(uFlags & TVHT_ONITEMSTATEICON))
				return;

			BOOL bCheck = !GetCheck(hItem);
			if (_pCombo->IsSingleCheck() && ItemHasChildren(hItem))
			{
				*pResult = 1;
				return;
			}

			SetCheck(hItem, bCheck);

			// ��������ѡ��״̬
			ConsistentChildCheck(hItem);

			// ���¸���ѡ��״̬
			ConsistentParentCheck(hItem);

			// ����ѡ��
			SetCheck(hItem, !bCheck);

			bComBoxChange = true;

			CWnd* pParent = _pCombo->GetParent();
			if (NULL != pParent && NULL != pParent->GetSafeHwnd())
			{
				::SendMessage(pParent->GetSafeHwnd(), UM_CHECK_EDIT, (WPARAM)hItem, (LPARAM)this);
			}
		}
		else
		{
			//ֻ��ѡ��Ҷ�ӽڵ�
			if ((NULL != _pCombo) && (hItem != NULL) && (uFlags & TVHT_ONITEM) && !ItemHasChildren(hItem))
			{
				DWORD_PTR pData = GetItemData(hItem);
				CString strText = GetItemText(hItem);

				// ���Ϳؼ�ѡ����ӳ�䵽��Ͽ�ѡ����
				// ѭ�����ң����������븽�����ݶ���ͬ����Ϊֹ
				int nIndex = CB_ERR, subIndex = CB_ERR;
				do
				{
					subIndex = _pCombo->FindStringExact(nIndex, strText);

					if (subIndex <= nIndex)
						break;

					// �жϸ��������Ƿ����
					if (_pCombo->GetItemData(subIndex) == pData)
						break;

					nIndex = subIndex;
				} while (true);

				if (subIndex > nIndex)
				{
					bComBoxChange = _pCombo->GetCurSel() != subIndex;
					_pCombo->SetCurSel(subIndex);
				}

				// �ر���������
				CloseTree(1);
			}
		}

		*pResult = 0;
	}

	void CComboBoxTree::ConsistentChildCheck(HTREEITEM hItem)
	{
		BOOL bCheck = GetCheck(hItem);

		// ����ѡһ��ʱ����������ѡ����ȥ��
		if (_pCombo->IsSingleCheck())
		{
			HTREEITEM hParentItem = GetParentItem(hItem);
			if (hParentItem == NULL)
				return;

			HTREEITEM hChildItem = GetChildItem(hParentItem);
			while (hChildItem != NULL)
			{
				if (hChildItem != hItem)
					SetCheck(hChildItem, FALSE);
				hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
			}
		}
		else if (ItemHasChildren(hItem))
		{
			HTREEITEM hChildItem = GetChildItem(hItem);
			while (hChildItem != NULL)
			{
				SetCheck(hChildItem, bCheck);

				ConsistentChildCheck(hChildItem);

				hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
			}
		}
	}

	void CComboBoxTree::ConsistentParentCheck(HTREEITEM hItem)
	{
		HTREEITEM hParentItem = GetParentItem(hItem);
		if (hParentItem != NULL)
		{
			HTREEITEM hChildItem = GetChildItem(hParentItem);
			while (hChildItem != NULL)
			{
				if (GetCheck(hChildItem) == FALSE)
				{
					SetCheck(hParentItem, FALSE);

					return ConsistentParentCheck(hParentItem);
				}

				hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
			}

			SetCheck(hParentItem, TRUE);

			return ConsistentParentCheck(hParentItem);
		}
	}

	void CComboBoxTree::OnDestroy()
	{
		CImageList *pImageNormal = GetImageList(TVSIL_NORMAL);
		if (pImageNormal != NULL)
			pImageNormal->DeleteImageList();

		CImageList *pImageState = GetImageList(TVSIL_STATE);
		if (pImageState != NULL)
			pImageState->DeleteImageList();

		CTreeCtrl::OnDestroy();
	}

	LRESULT CComboBoxTree::OnAcadKeepFocus(WPARAM wParam, LPARAM lParam)
	{
		return 1;
	}



	const CString CTreeComboBox::s_strNoData = L"NODATA";

	IMPLEMENT_DYNAMIC(CTreeComboBox, CComboBox)

		CTreeComboBox::CTreeComboBox() :_nDroppedHeight(150), _nDroppedWidth(-1)
	{
		_pOwner = NULL;
		_bInCreate = false;
		_bControlActive = FALSE;
		_bCheckMode = false;
		_bShowComboList = false;
		_bDelItemData = false;
		_bInShowDropDown = false;
		_bSigleCheck = false;
		_bSelectByText = true;
	}

	CTreeComboBox::~CTreeComboBox()
	{
	}

	BEGIN_MESSAGE_MAP(CTreeComboBox, CComboBox)
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONDBLCLK()
		ON_MESSAGE(UM_DROP_CLOSE, OnCloseControl)
		ON_WM_CREATE()
		ON_WM_DESTROY()
	END_MESSAGE_MAP()

	void CTreeComboBox::PreSubclassWindow()
	{
		CComboBox::PreSubclassWindow();

		if (!_bInCreate)
			InitDropTree();
	}

	BOOL CTreeComboBox::PreTranslateMessage(MSG* pMsg)
	{
		if (WM_KEYDOWN == pMsg->message && VK_DOWN == pMsg->wParam)
		{
			DisplayTree();
			return TRUE;
		}

		if (WM_MOUSEWHEEL == pMsg->message && IsCheckMode())
		{
			return TRUE;
		}

		return CComboBox::PreTranslateMessage(pMsg);
	}

	static void GetTreeLeafValueString(CTreeCtrl& treeCtrl, HTREEITEM hParent, std::vector<CString>& leftValues, bool bAll = false)
	{
		// �����ӽڵ�
		if (treeCtrl.ItemHasChildren(hParent))
		{
			HTREEITEM hChildItem = treeCtrl.GetChildItem(hParent);
			while (hChildItem != NULL)
			{
				// �ݹ��Ӽ�
				GetTreeLeafValueString(treeCtrl, hChildItem, leftValues);
				hChildItem = treeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
			}
		}
		else if (treeCtrl.GetCheck(hParent) || bAll)
		{
			CString strText = treeCtrl.GetItemText(hParent);
			leftValues.push_back((LPCTSTR)strText);
		}
	}

	static void GetTreeLeafDataString(CTreeCtrl& treeCtrl, HTREEITEM hParent, std::vector<CString>& leftDatas)
	{
		// �����ӽڵ�
		if (treeCtrl.ItemHasChildren(hParent))
		{
			HTREEITEM hChildItem = treeCtrl.GetChildItem(hParent);
			while (hChildItem != NULL)
			{
				// �ݹ��Ӽ�
				GetTreeLeafDataString(treeCtrl, hChildItem, leftDatas);
				hChildItem = treeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
			}
		}
		else if (treeCtrl.GetCheck(hParent))
		{
			CString *pData = (CString*)(treeCtrl.GetItemData(hParent));

			if (pData)
				leftDatas.push_back((LPCTSTR)*pData);
			else
				leftDatas.push_back(L"");
		}
	}

	static void GetTreeLeafValueString(CTreeCtrl& treeCtrl, std::vector<CString>& leftValues, bool bAll = false)
	{
		CString strText;
		HTREEITEM rootItem = treeCtrl.GetRootItem();
		while (rootItem != NULL)
		{
			GetTreeLeafValueString(treeCtrl, rootItem, leftValues, bAll);
			rootItem = treeCtrl.GetNextItem(rootItem, TVGN_NEXT);
		}
	}

	static void GetTreeLeafDataString(CTreeCtrl& treeCtrl, std::vector<CString>& leftDatas)
	{
		CString strText;
		HTREEITEM rootItem = treeCtrl.GetRootItem();
		while (rootItem != NULL)
		{
			GetTreeLeafDataString(treeCtrl, rootItem, leftDatas);
			rootItem = treeCtrl.GetNextItem(rootItem, TVGN_NEXT);
		}
	}


	CString CTreeComboBox::GetControlText()
	{
		CString strText;
		if (!_bCheckMode || !_bShowComboList)
		{
			GetWindowText(strText);
		}
		else
		{
			std::vector<CString> leatValues;
			GetTreeLeafValueString(_dropTree, leatValues);
			if (leatValues.empty() && !((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST))
			{
				GetWindowText(strText);

				if (!strText.IsEmpty())
				{
					std::vector<CString> strSplitStrings;
					CStringTool::SplitString((LPCTSTR)strText, strSplitStrings, (LPCTSTR)GetSplitChar());

					GetTreeLeafValueString(_dropTree, leatValues, true);
					CString strLeafValue = CStringTool::BuildSplitString(leatValues, (LPCTSTR)GetSplitChar());

					for (size_t i = 0; i < strSplitStrings.size();)
					{
						std::vector<CString>::iterator iterFind = std::find(strSplitStrings.begin(), strSplitStrings.end(), strSplitStrings[i]);
						if (iterFind != strSplitStrings.end())
							strSplitStrings.erase(iterFind);
						else
							++i;
					}

					strText = CStringTool::BuildSplitString(strSplitStrings, (LPCTSTR)GetSplitChar());
				}

			}
			else
			{
				strText = CStringTool::BuildSplitString(leatValues, (LPCTSTR)GetSplitChar());
			}
		}

		return strText;
	}

	bool CTreeComboBox::SearchDataByText(CTreeCtrl &treeCtrl, HTREEITEM hParent, CString &curText, CString *curData)
	{
		// �����ӽڵ�
		if (treeCtrl.ItemHasChildren(hParent))
		{
			HTREEITEM hChildItem = treeCtrl.GetChildItem(hParent);
			while (hChildItem != NULL)
			{
				// �ݹ��Ӽ�
				if (!SearchDataByText(treeCtrl, hChildItem, curText, curData))
					hChildItem = treeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
				else
					return true;
			}

			return false;
		}
		else
		{
			CString Text = treeCtrl.GetItemText(hParent);

			if ((Text == curText))
			{
				DWORD_PTR data = (treeCtrl.GetItemData(hParent));
				if (data != NULL)
				{
					*curData = *((CString*)data);
					return true;
				}
			}

			return false;
		}
	}

	bool CTreeComboBox::CheckDataExist(CTreeCtrl &treeCtrl, HTREEITEM hParent, CString *curData, bool *isExist, CString strShow)
	{
		if (treeCtrl.ItemHasChildren(hParent))
		{
			HTREEITEM hChildItem = treeCtrl.GetChildItem(hParent);
			while (hChildItem != NULL)
			{
				// �ݹ��Ӽ�
				if (!CheckDataExist(treeCtrl, hChildItem, curData, isExist, strShow))
					hChildItem = treeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
				else
					return true;
			}

			return false;
		}
		else
		{
			DWORD_PTR data = (treeCtrl.GetItemData(hParent));
			CString strText = treeCtrl.GetItemText(hParent);
			if (data && *((CString*)data) == *curData && (strText == strShow))
			{
				*isExist = true;
				return true;
			}

			return false;
		}
	}

	CString CTreeComboBox::GetDataFromText(CString curText)
	{
		// �ж�data�Ƿ���ڣ��Ҷ�Ӧ��չ��ֵ�Ƿ�ؼ���ʾֵһ��
		if (!_strCurSelData.IsEmpty())
		{
			bool bDataExistCheck = false;
			HTREEITEM rootItem = _dropTree.GetRootItem();
			while (rootItem != NULL)
			{
				if (!CheckDataExist(_dropTree, rootItem, &_strCurSelData, &bDataExistCheck, curText))
					rootItem = _dropTree.GetNextItem(rootItem, TVGN_NEXT);
				else
					break;
			}

			// ���һ�£���ֱ�ӷ���
			if (bDataExistCheck)
				return _strCurSelData;
		}

		// ��һ�£�����Ҫͨ��չ��ֵ���Ҷ�Ӧ��dataֵ
		CString Data;
		if (_bSelectByText)
		{
			Data = GetDataByText(curText);

		}
		return Data;
	}

	CString CTreeComboBox::GetCurrentSelData()
	{
		if (!_strCurSelData.IsEmpty())
			return _strCurSelData;

		CString strText;
		if (!_bCheckMode /*|| !_bShowComboList*/)
		{
			int nSel = GetCurSel();
			if (LB_ERR != nSel)
			{
				CString* pStrData = (CString*)GetItemData(nSel);
				if (NULL != pStrData)
					strText = *pStrData;
			}
		}
		else
		{
			std::vector<CString> leftDatas;
			GetTreeLeafDataString(_dropTree, leftDatas);
			strText = CStringTool::BuildSplitString(leftDatas, (LPCTSTR)GetSplitChar());
		}

		return strText;
	}

	CString CTreeComboBox::GetCurrentSelText()
	{
		if (!_strCurSelText.IsEmpty())
			return _strCurSelText;

		CString strText;
		if (!_bCheckMode || !_bShowComboList)
		{
			int nSel = GetCurSel();
			if (LB_ERR != nSel)
			{
				GetLBText(nSel, strText);
			}
		}
		else
		{
			std::vector<CString> leftDatas;
			GetTreeLeafValueString(_dropTree, leftDatas);
			strText = CStringTool::BuildSplitString(leftDatas, (LPCTSTR)GetSplitChar());
		}

		return strText;
	}

	void CTreeComboBox::OnLButtonDown(UINT nFlags, CPoint point)
	{
		SetFocus();
		_bControlActive = !_bControlActive;

		if (_bControlActive)
			DisplayTree();
	}

	void CTreeComboBox::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		OnLButtonDown(nFlags, point);
	}

	LRESULT CTreeComboBox::OnCloseControl(WPARAM wParam, LPARAM lParam)
	{
		SetFocus();

		if (_bCheckMode)
		{
			int nLast = GetCount();
			if (nLast > 0)
				DeleteString(nLast - 1);

			CString strText = GetControlText();
			int nSel = AddString(strText);
			if (LB_ERR != nSel)
			{
				SetCurSel(nSel);

				std::vector<CString> leftDatas;
				GetTreeLeafDataString(_dropTree, leftDatas);
				_strCurSelData = CStringTool::BuildSplitString(leftDatas, (LPCTSTR)GetSplitChar());
				_strCurSelText = strText;
			}

			// ��ʱ�������ѡʱ�������ݣ������Ҫ�����
		}

		if (wParam == 1)
		{
			_strCurSelText = L"";
			_strCurSelData = L"";
		}

		// ����ѡ����Ϣ
		CWnd* pParent = GetParent();
		if (bComBoxChange && (pParent != NULL) && (NULL != pParent->GetSafeHwnd()))
		{
			WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(), CBN_SELCHANGE);
			pParent->SendMessage(WM_COMMAND, wParam, (LPARAM)m_hWnd);
			bComBoxChange = false;
		}

		if (NULL != _dropTree.GetSafeHwnd())
		{
			_dropTree.ShowWindow(SW_HIDE);
		}

		_bControlActive = FALSE;

		return 1;
	}

	CString CTreeComboBox::GetCheckString()
	{
		if (!_strCurSelText.IsEmpty())
			return _strCurSelText;

		int nSel = GetCurSel();
		CString strSelText;
		if (LB_ERR != nSel)
		{
			GetLBText(nSel, strSelText);
		}

		return strSelText;
	}

	void CTreeComboBox::SetCheckString(const CString& strCheck)
	{
		int nSel = AddString(strCheck);
		if (LB_ERR != nSel)
		{
			SetCurSel(nSel);
		}
	}

	void CTreeComboBox::SetSplitChar(const CString& ch)
	{
		_splitCh = ch;
	}

	CString CTreeComboBox::GetSplitChar() const
	{
		return _splitCh.IsEmpty() ? L"," : _splitCh;
	}

	HTREEITEM CTreeComboBox::FindItemByText(HTREEITEM hRoot, CString strItem, CString strData)
	{
		while (NULL != hRoot)
		{
			CString strFindData;
			CString strFindItem = _dropTree.GetItemText(hRoot);
			CString *pStrFindData = (CString*)(_dropTree.GetItemData(hRoot));

			if (pStrFindData != NULL)
				strFindData = *pStrFindData;

			// �ȽϹؼ����Ƿ���ͬ
			if (strData == strFindData && (!_bSelectByText || (_bSelectByText && strFindItem == strItem)))
				return hRoot;

			//���ݶ�λ��ֻ����Ч��dataֵ
			if (strItem.IsEmpty() && !strData.IsEmpty() && strData == strFindData)
				return hRoot;

			// �����ӽڵ�
			HTREEITEM hFindItem = FindItemByText(_dropTree.GetNextItem(hRoot, TVGN_CHILD), strItem, strData);
			if (hFindItem != NULL)
				return hFindItem;

			hRoot = _dropTree.GetNextSiblingItem(hRoot);
		}

		return NULL;
	}

	void CTreeComboBox::CollapseAllTreeItem(HTREEITEM hRoot)
	{
		while (NULL != hRoot)
		{
			_dropTree.Expand(hRoot, TVE_COLLAPSE);
			CollapseAllTreeItem(_dropTree.GetNextItem(hRoot, TVGN_CHILD));
			hRoot = _dropTree.GetNextSiblingItem(hRoot);
		}
	}

	void CTreeComboBox::GetShowItem(HTREEITEM hRoot, int& nCount)
	{
		while (NULL != hRoot)
		{
			// ��ǰûչ���򲻼���
			if (TVIS_EXPANDED & _dropTree.GetItemState(hRoot, TVIS_EXPANDED))
			{
				GetShowItem(_dropTree.GetNextItem(hRoot, TVGN_CHILD), nCount);
			}

			nCount++;
			hRoot = _dropTree.GetNextSiblingItem(hRoot);
		}
	}

	void CTreeComboBox::DisplayTree()
	{
		if (NULL != this->GetSafeHwnd())
		{
			CWnd* pParent = this->GetParent();
			if (NULL != pParent)
			{
				::SendMessage(pParent->m_hWnd, WM_COMMAND, MAKEWPARAM(this->GetDlgCtrlID(), CBN_DROPDOWN), (LPARAM)this->GetSafeHwnd());
			}
		}

		_bInShowDropDown = true;

		CRect rect;
		GetWindowRect(rect);

		CAtlArray<HTREEITEM> checkItems;

		// �Ƕ�ѡ��ģʽ
		if (!IsCheckMode())
		{
			// �����������ڵ�
			CollapseAllTreeItem(_dropTree.GetRootItem());

			// ѡ�����ڵ�
			CString strSelText = GetControlText();
			CString strSelData = GetDataFromText(strSelText);
			HTREEITEM hSelItem = FindItemByText(_dropTree.GetRootItem(), strSelText, strSelData);
			if (NULL == hSelItem)
			{
				GetWindowText(strSelText);
				strSelData = GetCurrentSelData();
				hSelItem = FindItemByText(_dropTree.GetRootItem(), strSelText, strSelData);
			}

			if (NULL == hSelItem)
			{
				hSelItem = FindItemByText(_dropTree.GetRootItem(), GetCheckString(), strSelData);
			}

			if (NULL != hSelItem)
			{
				_dropTree.EnsureVisible(hSelItem);
				_dropTree.SelectItem(hSelItem);
			}
			else
			{
				_dropTree.PostMessage(WM_VSCROLL, SB_TOP, NULL);
			}
		}
		else
		{
			// ѡ�����ڵ�
			int nSel = GetCurSel();
			CString strSelText, strSelData;
			if (LB_ERR != nSel)
				GetLBText(nSel, strSelText);
			else
			{
				strSelText = GetCurrentSelText();
			}

			std::vector<CString> strSelects, strDatas;
			strSelData = GetCurrentSelData();
			CStringTool::SplitString((LPCTSTR)strSelText, strSelects, (LPCTSTR)GetSplitChar());
			CStringTool::SplitString((LPCTSTR)strSelData, strDatas, (LPCTSTR)GetSplitChar());

			size_t nSize = strSelects.size();
			for (size_t i = 0; i < nSize; ++i)
			{
				CString strData = i >= strDatas.size() ? _T("") : strDatas[i];
				HTREEITEM hSelItem = FindItemByText(_dropTree.GetRootItem(), strSelects[i], strData);
				if (NULL != hSelItem)
				{
					_dropTree.EnsureVisible(hSelItem);
					checkItems.Add(hSelItem);
				}
			}

			if (nSize == 0)
				_dropTree.PostMessage(WM_VSCROLL, SB_TOP, NULL);

			// �޸�XP��������ʼλ�ò������������
			_dropTree.SendMessage(WM_HSCROLL, SB_LEFT, NULL);
		}

		// ����������߶�
		CRect rt;
		SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rt, 0);
		int nScreenHeight = rt.Height();

		int nCtrlHeight = rect.Height();
		int nDroppedHeight = _nDroppedHeight;
		if (NULL != _dropTree.GetSafeHwnd())
		{
			int nCount = 0;
			GetShowItem(_dropTree.GetRootItem(), nCount);

			if (nCount > 1)
			{
				int nDesiredDroppedHeight = nCount * _dropTree.GetItemHeight();
				if (nDesiredDroppedHeight > (nScreenHeight - nCtrlHeight) / 2)
					nDesiredDroppedHeight = (nScreenHeight - nCtrlHeight) / 2;
				if (nDroppedHeight < nDesiredDroppedHeight)
					nDroppedHeight = nDesiredDroppedHeight;
			}
		}

		if (rect.bottom + nDroppedHeight > nScreenHeight)
		{
			rect.top = rect.top - nDroppedHeight;
			rect.bottom = nDroppedHeight + 1;
		}
		else
		{
			rect.top = rect.bottom;
			rect.bottom = nDroppedHeight;
		}

		rect.right = GetDroppedWidth();

		// ����ģ̬�Ի�������ʾ�󣬻�ʹ���ӿؼ�����Ϊ������
		if (!_dropTree.IsWindowEnabled())
		{
			_dropTree.EnableWindow(TRUE);
		}

		_dropTree.Display(rect);

		// ��Ҫ����ʾ�ؼ�������ѡ��״̬����Ч
		size_t nSize = checkItems.GetCount();
		HTREEITEM hSelItemInTree = _dropTree.GetSelectedItem();

		if (nSize == 0)
		{
			_dropTree.SetCheck(_dropTree.GetRootItem(), false);
		}

		for (size_t i = 0; i < nSize; ++i)
		{
			_dropTree.SelectItem(checkItems[i]);
			_dropTree.SetCheck(checkItems[i], true);
			_dropTree.ConsistentParentCheck(checkItems[i]);
		}

		_bShowComboList = true;
		_bInShowDropDown = false;

	}

	// ��������
	void FillTreeCtrl(CComboBoxTree& treeCtrl, CTreeComboBox& combobox, HTREEITEM hParent, CXmlElement* pElm)
	{
		CXmlElements *pChilds = pElm->GetChildElements();
		size_t nChild = pChilds->GetCount();
		for (size_t i = 0; i < nChild; ++i)
		{
			CXmlElement* pChildElm = pChilds->GetAt(i);
			CString value = pChildElm->GetAttrValue(L"Name");
			CString strCheck = pChildElm->GetAttrValue(L"Check", _T("1"));
			HTREEITEM hNewItem = treeCtrl.InsertItem(value, hParent);
			treeCtrl.SetCheck(hNewItem, (strCheck == _T("0") ? FALSE : TRUE));

			// �ݹ��ӽڵ�
			FillTreeCtrl(treeCtrl, combobox, hNewItem, pChildElm);

			// ���Ҷ�ӽڵ㵽��Ͽ���,��������ʹ��Combobox������ȡѡ����
			if (pChildElm->GetChildElementCount() == 0)
			{
				int nItem = combobox.AddString(value);

				// ����и��������������
				CString strData = pChildElm->GetAttrValue(L"Data");
				if (!strData.IsEmpty())
				{
					CString* pStrData = new CString(strData);
					combobox.SetItemData(nItem, DWORD_PTR(pStrData));
					treeCtrl.SetItemData(hNewItem, DWORD_PTR(pStrData));
				}
			}
		}
	}

	bool CTreeComboBox::LoadXmlData(const CString& xmlFile, bool bNoLimitOrSelAll)
	{
		// �����ͷŹ�����������
		_bDelItemData = true;

		CXmlDocument xmlDoc;

		if (CFileTool::FileExist((LPCTSTR)xmlFile))
		{
			// �����ļ�ʧ��
			if (!xmlDoc.LoadFile(xmlFile, fmtXML))
				return false;
		}
		// ���Խ���XML�ַ���
		else if (!xmlDoc.SetXmlString(xmlFile))
		{
			return false;
		}

		return LoadXmlData(xmlDoc.GetElementRoot(), bNoLimitOrSelAll);
	}

	bool CTreeComboBox::LoadXmlData(CXmlElement* pElm, bool bNoLimitOrSelAll)
	{
		if (IsCheckMode())
		{
			ResetContent();
			_dropTree.DeleteAllItems();
			HTREEITEM hRootItem = TVI_ROOT;

			if (bNoLimitOrSelAll)
			{
				hRootItem = _dropTree.InsertItem(_T("ȫѡ"), TVI_ROOT);
				_dropTree.SetCheck(hRootItem);
			}

			SetRedraw(FALSE);
			_dropTree.SetRedraw(FALSE);
			FillTreeCtrl(_dropTree, *this, hRootItem, pElm);
			SetRedraw(TRUE);
			_dropTree.SetRedraw(TRUE);
		}
		else
		{
			SetRedraw(FALSE);
			_dropTree.SetRedraw(FALSE);

			ResetContent();
			_dropTree.DeleteAllItems();
			FillTreeCtrl(_dropTree, *this, TVI_ROOT, pElm);

			if (bNoLimitOrSelAll)
			{
				AddString(L"����");
				HTREEITEM hNewItem = _dropTree.InsertItem(L"����", TVI_ROOT);
			}

			SetRedraw(TRUE);
			_dropTree.SetRedraw(TRUE);
		}

		return true;
	}

	void CTreeComboBox::LoadStringVector(CStringVector& listData, bool bNoLimitOrSelAll, const CString strSelAll)
	{
		if (IsCheckMode())
		{
			ResetContent();
			_dropTree.DeleteAllItems();

			HTREEITEM hRootItem = TVI_ROOT;

			if (bNoLimitOrSelAll)
			{
				if (strSelAll.IsEmpty())
				{
					hRootItem = _dropTree.InsertItem(_T("ȫѡ"), TVI_ROOT);
				}
				else
				{
					hRootItem = _dropTree.InsertItem(strSelAll, TVI_ROOT);
				}

				_dropTree.SetCheck(hRootItem);
			}

			// ��������б�����;
			CStringVectorIter endIter = listData.end();
			for (CStringVectorIter beginIter = listData.begin(); beginIter != endIter; ++beginIter)
			{
				const CString& strString = (*beginIter);
				_dropTree.InsertItem(strString, hRootItem);
			}
		}
		else
		{
			ResetContent();
			_dropTree.DeleteAllItems();

			// ��������б�����;
			CStringVectorIter endIter = listData.end();
			for (CStringVectorIter beginIter = listData.begin(); beginIter != endIter; ++beginIter)
			{
				const CString& strString = (*beginIter);
				_dropTree.InsertItem(strString, TVI_ROOT);
			}

			if (bNoLimitOrSelAll)
			{
				if (strSelAll.IsEmpty())
				{
					AddString(L"����");
				}
				else
				{
					AddString(strSelAll);
				}

				HTREEITEM hNewItem = _dropTree.InsertItem(L"����", TVI_ROOT);
			}
		}
	}

	void CTreeComboBox::SaveXmlData(CXmlElement* pElm)
	{
		if (!IsCheckMode())
			return;

		HTREEITEM rootItem = _dropTree.GetRootItem();
		while (rootItem != NULL)
		{
			SaveTreeCtrl(_dropTree, rootItem, pElm);
			rootItem = _dropTree.GetNextItem(rootItem, TVGN_NEXT);
		}
	}

	void CTreeComboBox::SaveTreeCtrl(CTreeCtrl& treeCtrl, HTREEITEM hParent, CXmlElement* pElm)
	{
		int nCount = pElm->GetChildElementCount();
		CXmlElement *pChildElement = pElm->GetChildElements()->InsertAt(nCount);
		pChildElement->SetElementName(_T("Item"));
		pChildElement->SetAttrValue(_T("Name"), _dropTree.GetItemText(hParent));

		// ���渽������
		DWORD_PTR hItemData = _dropTree.GetItemData(hParent);
		if (NULL != hItemData)
		{
			CString *pData = (CString*)hItemData;
			pChildElement->SetAttrValue(_T("Data"), *pData);
		}

		// �����ӽڵ�
		if (_dropTree.ItemHasChildren(hParent))
		{
			HTREEITEM hChildItem = _dropTree.GetChildItem(hParent);
			while (hChildItem != NULL)
			{
				// �ݹ��Ӽ�
				SaveTreeCtrl(treeCtrl, hChildItem, pChildElement);
				hChildItem = _dropTree.GetNextItem(hChildItem, TVGN_NEXT);
			}
		}
	}

	HTREEITEM CTreeComboBox::InsertItem(const CString& strText,
		CString strData, HTREEITEM hParent, bool isLeafNode)
	{
		_bDelItemData = true;

		HTREEITEM hItem = _dropTree.InsertItem(strText, hParent);

		// ֻ��Ҷ�ӽڵ���и�������
		if (isLeafNode)
		{
			int nIndex = AddString(strText);
			CString *pData = new CString(strData);
			SetItemData(nIndex, (DWORD_PTR)pData);
			_dropTree.SetItemData(hItem, (DWORD_PTR)pData);
		}

		return hItem;
	}

	BOOL CTreeComboBox::PreCreateWindow(CREATESTRUCT& cs)
	{
		_bInCreate = true;
		return CComboBox::PreCreateWindow(cs);
	}

	void CTreeComboBox::InitDropTree()
	{
		//��ȡ���㸸����
		CWnd *pParentWnd = this->GetParent();
		do
		{
			if (pParentWnd == NULL)
				break;

			if (!(pParentWnd->GetStyle() & WS_CHILD))
				break;

			pParentWnd = pParentWnd->GetParent();
		} while (TRUE);

		CRect rcClient(0, 0, 0, 0);

		// �����������ؼ�
		DWORD dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_BORDER | TVS_DISABLEDRAGDROP | TVS_HASLINES
			| TVS_LINESATROOT | TVS_HASBUTTONS | TVS_FULLROWSELECT;

		if (_bCheckMode)
			dwStyle |= TVS_CHECKBOXES;

		CWnd* pWnd = &_dropTree;

		pWnd->CreateEx(0, WC_TREEVIEW, NULL, dwStyle, rcClient, pParentWnd, 0, NULL);

		_dropTree.Init(this);

		_bShowComboList = false;
	}

	int CTreeComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CComboBox::OnCreate(lpCreateStruct) == -1)
			return -1;

		InitDropTree();

		_bInCreate = false;

		return 0;
	}

	void CTreeComboBox::ResetContent()
	{
		if (!_bDelItemData)
		{
			CComboBox::ResetContent();
			return;
		}

		// ɾ����������
		int nCount = GetCount();
		for (int i = 0; i < nCount; ++i)
		{
			DWORD_PTR pData = GetItemData(i);
			// ����й��������������
			if (pData != NULL)
			{
				CString* pStrData = (CString*)(pData);
				delete pStrData;
			}
		}
		CComboBox::ResetContent();
	}

	void CTreeComboBox::ResetItemContent()
	{
		ResetContent();

		if (IsCheckMode())
		{
			_dropTree.DeleteAllItems();
		}
	}

	void CTreeComboBox::OnDestroy()
	{
		CComboBox::OnDestroy();
		_dropTree.DestroyWindow();

		// ǿ��ɾ����������ո��������ڴ�
		ResetContent();

		_bControlActive = FALSE;
	}

	CTreeCtrl& CTreeComboBox::GetTreeCtrl()
	{
		return _dropTree;
	}

	BOOL CTreeComboBox::IsControlActive() const
	{
		return _bControlActive;
	}

	int GetTreeMaxWidth(CTreeCtrl& treeCtrl, CDC* pDc, HTREEITEM hParent, int nLevel)
	{
		CString strText = treeCtrl.GetItemText(hParent);

		// ������
		CSize size = pDc->GetTextExtent(strText, strText.GetLength());
		int nMaxWidth = size.cx + nLevel * 40 + 4;

		// �����Ӽ�
		HTREEITEM hChildItem = treeCtrl.GetChildItem(hParent);
		while (hChildItem != NULL)
		{
			int nWidth = GetTreeMaxWidth(treeCtrl, pDc, hChildItem, nLevel + 1);
			if (nWidth > nMaxWidth)
				nMaxWidth = nWidth;

			hChildItem = treeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
		}

		return nMaxWidth;
	}

	int GetTreeMaxWidth(CTreeCtrl& treeCtrl)
	{
		int nMaxWidth = 0;

		// ׼��CDC
		CFont* font = treeCtrl.GetFont();
		CDC* dc = treeCtrl.GetDC();
		CFont* oldFont = dc->SelectObject(font);

		// �������ڵ�
		HTREEITEM rootItem = treeCtrl.GetRootItem();
		while (rootItem != NULL)
		{
			int nWidth = GetTreeMaxWidth(treeCtrl, dc, rootItem, 1);
			if (nWidth > nMaxWidth)
				nMaxWidth = nWidth;

			rootItem = treeCtrl.GetNextItem(rootItem, TVGN_NEXT);
		}

		// ��ԭ����
		dc->SelectObject(oldFont);
		treeCtrl.ReleaseDC(dc);

		return nMaxWidth;
	}

	int CTreeComboBox::GetDroppedWidth()
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		// ����Ӧ���
		if (_nDroppedWidth == 0)
		{
			int nMaxWidth = GetTreeMaxWidth(_dropTree);
			if (nMaxWidth < rcClient.Width())
				return rcClient.Width();
			else
				return nMaxWidth;
		}
		// ���ؼ����
		else if (_nDroppedWidth == -1)
		{
			return rcClient.Width();
		}

		return _nDroppedWidth;
	}

	int CTreeComboBox::GetDroppedHeight() const
	{
		return _nDroppedHeight;
	}

	void CTreeComboBox::SetDroppedWidth(const int nWidth)
	{
		_nDroppedWidth = nWidth;
	}

	void CTreeComboBox::SetDroppedHeight(const int nHeight)
	{
		_nDroppedHeight = nHeight;
	}

	bool CTreeComboBox::IsCheckMode()
	{
		return _bCheckMode;
	}

	void CTreeComboBox::SetCheckMode(bool bCheckModel)
	{
		_bCheckMode = bCheckModel;
	}

	void CTreeComboBox::SetParentOwner(CWnd* pOwner)
	{
		_pOwner = pOwner;
	}

	CWnd* CTreeComboBox::GetParentOwner()
	{
		return (_pOwner != NULL) ? _pOwner : GetParent();
	}

	void CTreeComboBox::ResetItemData()
	{
		_strCurSelData = L"";
		_strCurSelText = L"";
	}

	const CString CTreeComboBox::NoData()
	{
		return CTreeComboBox::s_strNoData;
	}

	CString CTreeComboBox::GetDataByText(CString &text)
	{
		CString Data;

		HTREEITEM rootItem = _dropTree.GetRootItem();
		while (rootItem != NULL)
		{
			if (!SearchDataByText(_dropTree, rootItem, text, &Data))
				rootItem = _dropTree.GetNextItem(rootItem, TVGN_NEXT);
			else
				break;
		}

		return Data;
	}

	void CTreeComboBox::SetCheckSelectByData(CString strData)
	{
		HTREEITEM rootItem = _dropTree.GetRootItem();

		std::vector<CString> strDatas;
		CStringTool::SplitString((LPCTSTR)strData, strDatas, (LPCTSTR)GetSplitChar());

		for (auto data : strDatas)
		{
			HTREEITEM checkItem = FindItemByText(rootItem, L"", data);
			_dropTree.SelectItem(checkItem);
			_dropTree.SetCheck(checkItem, true);
			_dropTree.ConsistentParentCheck(checkItem);

		}
	}

	void CTreeComboBox::SetShowText(CString strText)
	{
		int nSel = AddString(strText);
		SelectString(nSel, strText);
	}
}
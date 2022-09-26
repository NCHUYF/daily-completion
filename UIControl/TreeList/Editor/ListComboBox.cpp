#include "StdAfx.h"
#include "ListComboBox.h"

namespace ControlUI
{
	IMPLEMENT_DYNAMIC(CListComboBox, CComboBox)

		static LRESULT CALLBACK CoboboxEditProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		CListComboBox *pCob = reinterpret_cast<CListComboBox*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (NULL != pCob)
		{
			if (message == WM_KEYDOWN)
			{
				pCob->ProcessKeyDown((UINT)wParam, 0, 0);
			}
			else if (message == WM_KILLFOCUS)
			{
				pCob->DoKillFocus(CWnd::FromHandle((HWND)wParam));
				return TRUE;
			}

			return pCob->_pEditProc(hWnd, message, wParam, lParam);
		}
		else
		{
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	BEGIN_MESSAGE_MAP(CListComboBox, CComboBox)
		ON_WM_KILLFOCUS()
		ON_WM_KEYDOWN()
	END_MESSAGE_MAP()

	CListComboBox::CListComboBox()
	{
		_bCandel = false;
		_bDropList = false;

		_crNormal = GetSysColor(COLOR_WINDOW);
		_crSelected = GetSysColor(COLOR_HIGHLIGHT);
		_crText = GetSysColor(COLOR_WINDOWTEXT);

		_pEditProc = NULL;
	}

	CListComboBox::~CListComboBox()
	{
	}

	bool CListComboBox::Create(CWnd* pParent, CRect& rect, bool bDropList, LPCTSTR sInitText)
	{
		_bCandel = false;
		_bDropList = bDropList;
		_strInitText = sInitText;

		if (!_container.Create(rect, pParent))
			return false;

		// ����ʾ�߿�;
		CRect rc(-1, -2, rect.Width() + 1, 226);
		DWORD dwEditStyle = WS_CHILD | CBS_AUTOHSCROLL | CBS_HASSTRINGS | WS_VSCROLL | CBS_OWNERDRAWVARIABLE
			| CBS_NOINTEGRALHEIGHT | (_bDropList ? CBS_DROPDOWNLIST : CBS_DROPDOWN);
		if (!CComboBox::Create(dwEditStyle, rc, &_container, 0xffff))
			return false;

		// ����Edit��Ϣ����
		CWnd* pWndEdit = GetWindow(GW_CHILD);
		if (!_bDropList && (NULL != pWndEdit))
		{
			::SetWindowLongPtr(pWndEdit->m_hWnd, GWLP_USERDATA, LONG_PTR(this));
			_pEditProc = (WNDPROC)::SetWindowLongPtr(pWndEdit->m_hWnd, GWLP_WNDPROC, LONG_PTR(CoboboxEditProcedure));
		}

		return true;
	}

	void CListComboBox::SetSelAndFocus()
	{
		SetFocus();

		if (!_bDropList)
		{
			SetEditSel(0, -1);
		}
	}

	void CListComboBox::DrawItem(HDC hDC, const CRect& rcItem, int iItem, int iState)
	{
		CRect rcText = rcItem;
		CDC dcContext;
		dcContext.Attach(hDC);

		// ѡ������ɫ
		if (iState & ODS_SELECTED && !(iState & ODS_COMBOBOXEDIT))
		{
			dcContext.SetTextColor((0x00FFFFFF & ~(_crText)));
			dcContext.SetBkColor(_crSelected);
			dcContext.FillSolidRect(&rcText, _crSelected);
		}
		else
		{
			dcContext.SetTextColor(_crText);
			dcContext.SetBkColor(_crNormal);
			dcContext.FillSolidRect(&rcText, _crNormal);	// �������
		}

		// ѡ�б����뽹����
		if (iState & ODS_FOCUS && !(iState & ODS_COMBOBOXEDIT))
		{
			dcContext.DrawFocusRect(&rcText);
		}

		// ������������������;
		rcText.left += 2;
		if (iItem != -1)
		{
			TCHAR iText[MAX_PATH];
			GetLBText(iItem, iText);

			dcContext.SetBkMode(TRANSPARENT);
			dcContext.DrawText(iText, lstrlen(iText), rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
		}

		dcContext.Detach();
	}

	void CListComboBox::OnKillFocus(CWnd* pNewWnd)
	{
		CComboBox::OnKillFocus(pNewWnd);

		DoKillFocus(pNewWnd);
	}

	void CListComboBox::DoKillFocus(CWnd* pWnd)
	{
		// ����Ǳ༩ģʽ����Ͽ򣬵���ȡ�������Լ��ı༩��ʱ��Ӧ���ٿؼ�;
		if (!_bDropList && (pWnd == GetWindow(GW_CHILD)))
			return;

		if (_bCandel)
			return;

		CWnd* pWndParent = NULL;
		if (GetParent() != NULL)
		{
			pWndParent = GetParent()->GetParent();
		}

		// �����޸��¼�;
		if (pWndParent != NULL)
		{
			CString strText;
			GetWindowText(strText);
			pWndParent->SendMessage(LIST_CTRL_END, (LPARAM)((LPCTSTR)strText), 0);
		}

		if (IsWindow(m_hWnd))
			_container.DestroyWindow();
	}

	void CListComboBox::ProcessKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		CWnd* pWndParent = NULL;
		if (GetParent() != NULL)
		{
			pWndParent = GetParent()->GetParent();
		}

		if (nChar == VK_ESCAPE)
		{
			_bCandel = true;
			if (IsWindow(m_hWnd))
				_container.DestroyWindow();

			if (pWndParent != NULL)
				pWndParent->SetFocus();
		}
		else if (nChar == VK_RETURN || nChar == VK_EXECUTE)
		{
			if (pWndParent != NULL)
				pWndParent->SetFocus();
		}
	}

	void CListComboBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		ProcessKeyDown(nChar, nRepCnt, nFlags);

		CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
	}


	void CListComboBox::MeasureItem(LPMEASUREITEMSTRUCT pMItem)
	{
		pMItem->itemHeight = 20;
	}

	void CListComboBox::DrawItem(LPDRAWITEMSTRUCT pDIStruct)
	{
		DrawItem(pDIStruct->hDC, pDIStruct->rcItem, pDIStruct->itemID, pDIStruct->itemState);
	}

	void CListComboBox::AutoSelectItem()
	{
		// ���Ĭ��ֵ��������Χ����ֱ�����õ�ǰѡ������;
		int nIndex = FindStringExact(-1, _strInitText);
		if (nIndex != CB_ERR)
		{
			SetCurSel(nIndex);
		}
		else
		{
			// �ɱ༭������Ĭ��ֵ����������Χ����ֱ��������ʾ�ı�;
			if (!_bDropList)
			{
				SetWindowText(_strInitText);
			}
		}
	}

	bool CListComboBox::LoadXmlData(const CString& strXmlFile)
	{
		ResetContent();

		CXmlDocument xmlDoc;
		if (!xmlDoc.LoadFile(strXmlFile, fmtXML))
			return false;

		// ���������������
		CXmlElements *pChilds = xmlDoc.GetElementRoot()->GetChildElements();
		size_t nChild = pChilds->GetCount();
		for (size_t i = 0; i < nChild; ++i)
		{
			CXmlElement* pChildElm = pChilds->GetAt(i);
			CString value = pChildElm->GetAttrValue(L"Name");

			AddString(value);
		}

		AutoSelectItem();

		// ��������������������������;
		CAutoWidthComboBox::ComboxAutoWidth(*this);

		return true;
	}

	void CListComboBox::LoadStringVector(CStringVector& listData)
	{
		ResetContent();

		// ��������б�����;
		CStringVectorIter endIter = listData.end();
		for (CStringVectorIter beginIter = listData.begin(); beginIter != endIter; ++beginIter)
		{
			const CString& strString = (*beginIter);
			AddString(strString);
		}

		AutoSelectItem();

		// ��������������������������;
		CAutoWidthComboBox::ComboxAutoWidth(*this);
	}

	void CListComboBox::CancelEdit()
	{
		_bCandel = true;

		CWnd* pParent = _container.GetParent();
		if (NULL != pParent)
		{
			_container.DestroyWindow();
			pParent->SetFocus();
		}
	}
}

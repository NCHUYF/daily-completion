#include "stdafx.h"
#include "ComboAnyOne.h"
#define EDIT_CTRL_ID 110
#define TIME_ID 2048
#include "resource.h"

// ================================== CComboPanel ==================================
CString CComboPanel::s_ClassName = L"";
BEGIN_MESSAGE_MAP(CComboPanel, CWnd)
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

CComboPanel::CComboPanel(IPopupCtrl *subWnd) : m_pubWnd(subWnd)
{
}

CComboPanel::~CComboPanel()
{
}

void CComboPanel::PopupComboPanel()
{
	// 1. �ݴ�
	if (!m_pubWnd)
		return;

	// 2. ��ʾ����
	// 2.1 ��ʾ����ǰ��֪ͨ�����ؼ����������б������
	CString txt;
	GetParent()->GetWindowText(txt);
	m_pubWnd->OnPreShowCtrl(txt);
	
	// 2.2 ��ʾ���ڲ�����
	ShowWindow(SW_SHOW);
	SetActiveWindow();
	ReleaseCapture();
	SetFocus();
}

void CComboPanel::EndEdit()
{
	// 1. �ݴ�����Ѿ������˴��ڣ��򲻽�������༭ʱ�䣬��ֹ��Ϣѭ�����롣
	if (FALSE == IsWindowVisible() && m_pubWnd)
		return;

	// 2. ���ش���
	ShowWindow(SW_HIDE);

	// ���¸��������ݼ�Combo�༭�������
	CString txt = m_pubWnd->GetCtrlTextForShow();
	SetWindowText(txt);
	auto parent = GetOwner();
	parent->SendMessage(WM_END_EDIT);
}

void CComboPanel::CreateWnd(CWnd *pParent)
{
	CRect rtWnd(0, 0, 100, 100);
	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, ::LoadCursor(NULL, IDC_ARROW));
	CreateEx(0, className, L"", WS_POPUP | WS_BORDER | WS_VISIBLE, rtWnd, pParent, 0);
	SetOwner(pParent);
}

CWnd* CComboPanel::GetSafeSubWnd()
{
	CWnd *pWnd = m_pubWnd->GetWnd(this);
	return (pWnd && ::IsWindow(pWnd->GetSafeHwnd())) ? NULL : pWnd;
}

void CComboPanel::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// ʵʱ�����Ӵ��ڴ�С
	CWnd *pSubWnd = GetSafeSubWnd();
	if (!pSubWnd)
		return;
	if (::IsWindow(pSubWnd->GetSafeHwnd()))
	{
		CRect rtWnd;
		GetClientRect(rtWnd);		
		pSubWnd->MoveWindow(rtWnd);
	}
}

void CComboPanel::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if (nState == WA_INACTIVE)
	{
		EndEdit();
	}
}
// =================CComboAnyOne=================
CString CComboAnyOne::s_ClassName = L"";

BEGIN_MESSAGE_MAP(CComboAnyOne, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

CComboAnyOne::CComboAnyOne(IPopupCtrl *subWnd):m_Panel(subWnd), m_pSubWnd(subWnd)
{
	m_pSubWnd->SetOwner(this);
	m_ComboStatus = PBS_NORMAL;

	INIT_RESHANDLE()

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_CONTROL_IMAGES);
	m_Images.Create(16, 16, ILC_COLOR32 | ILC_MASK, 1, 1);
	m_Images.Add(&bitmap, RGB(0, 0, 0));
	m_nDropDownListHeight = 128;
	m_Font.Attach((HFONT)GetStockObject(DEFAULT_GUI_FONT));
}

CComboAnyOne::~CComboAnyOne()
{
	delete m_pSubWnd;
}

void CComboAnyOne::CreateWnd(CWnd *pParent, LPRECT rt, UINT uId /*= 0*/)
{
	CRect rtWnd(0, 0, 1, 1);
	if (rt == NULL)
		rt = &rtWnd;
	if (s_ClassName == L"")
		s_ClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);
	CWnd::Create(s_ClassName, L"tab23", WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, *rt, pParent, 0);
	m_Panel.CreateWnd(this);
	if (uId != 0)
		SetDlgCtrlID(uId);

	EnableToolTips(TRUE);
	m_TipCtrl.Create(this, TTS_ALWAYSTIP);
	m_TipCtrl.Activate(TRUE);

	m_NotifyWnd = pParent->GetSafeHwnd();

	MSG msg;
	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		PreTranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

BOOL CComboAnyOne::PreTranslateMessage(MSG* pMsg)
{
	auto retVal = __super::PreTranslateMessage(pMsg);
	if (::IsWindow(m_TipCtrl.GetSafeHwnd()))
	{
		m_TipCtrl.RelayEvent(pMsg);
	}
	return retVal;
}


CString CComboAnyOne::GetSelectionText()
{
	CString showTxt = m_pSubWnd->GetCtrlTextForShow();
	showTxt = TranslateSelection(showTxt);
	return showTxt;
}

void CComboAnyOne::SetNotifyWnd(CWnd *pNewWnd)
{
	m_NotifyWnd = pNewWnd ? pNewWnd->GetSafeHwnd() : GetParent()->GetSafeHwnd();
	m_pSubWnd->SetNotifyWnd(CWnd::FromHandle(m_NotifyWnd));
}

CString CComboAnyOne::TranslateSelection(LPCTSTR szDefTxt)
{
	CString retTxt;
	retTxt = (szDefTxt == NULL || szDefTxt[0] == NULL) ? L"��" : szDefTxt;
	return retTxt;
}

void CComboAnyOne::UpdateWndSize()
{
	if (FALSE == ::IsWindow(m_hWnd))
		return;

	// 1. ���㰴ťλ��
	CRect rtWnd;
	GetClientRect(rtWnd);
	m_BtnRect = rtWnd;
	m_BtnRect.left = rtWnd.right - m_BtnSize;
	m_BtnRect.top = rtWnd.CenterPoint().y - m_BtnSize / 2;
	m_BtnRect.bottom = m_BtnRect.top + m_BtnSize;
	m_BtnRect.OffsetRect(-m_nMarin, 0);

	// 2. �����������С
	if (!m_pSubWnd)
		return;
	CSize sz = m_pSubWnd->GetBestSize();
	ClientToScreen(rtWnd);
	m_DropListRect = rtWnd;
	m_DropListRect.top = rtWnd.bottom - 1;
	m_DropListRect.left += 1;
	m_DropListRect.right -= 1;

	if (sz.cx > m_DropListRect.Width())
		m_DropListRect.right = m_DropListRect.left + sz.cx;

	m_DropListRect.bottom = m_DropListRect.top + sz.cy;
}

void CComboAnyOne::DropDownSubCtrl()
{
	UpdateWndSize();
	m_Panel.MoveWindow(m_DropListRect);
	m_Panel.PopupComboPanel();
}

CRect CComboAnyOne::GetTxtRect()
{
	CRect rtWnd;
	GetClientRect(rtWnd);
	CRect rtTxt = rtWnd;
	rtTxt.left += 4;
	rtTxt.right = m_BtnRect.left;
	return rtTxt;
}

void CComboAnyOne::OnPaint()
{
	// ���Ʊ���
	CPaintDC dc(this);
	CRect rtWnd;
	GetClientRect(rtWnd);

	// ���������...
	HTHEME hTheme = OpenThemeData(GetSafeHwnd(), L"Button");
	if (!hTheme)
		return;

	// ���Ʊ���
	DrawThemeBackground(hTheme, dc.GetSafeHdc(), BP_PUSHBUTTON, m_ComboStatus, &rtWnd, NULL);

	// �����ı�
	auto rtTxt = GetTxtRect();
	CString showTxt = GetSelectionText();
	UINT dwStyle = DT_SINGLELINE | DT_VCENTER | DT_LEFT ;
	dc.SelectObject(m_Font.GetSafeHandle());
	DrawThemeText(hTheme, dc.GetSafeHdc(), BP_PUSHBUTTON, m_ComboStatus, showTxt, showTxt.GetLength(), dwStyle, NULL, rtTxt);

	// ���ư�ť
	m_Images.Draw(&dc, m_nDropBtPos, m_BtnRect.TopLeft(), ILS_NORMAL);
	CloseThemeData(hTheme);
}

void CComboAnyOne::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	UpdateWndSize();
	Invalidate();
}

void CComboAnyOne::OnMouseMove(UINT nFlags, CPoint point)
{
	__super::OnMouseMove(nFlags, point);
	// �ȼ�鵱ǰcombo�Ƿ��ڷǼ���״̬(PBS_NORMAL)
	if (m_ComboStatus == PBS_NORMAL)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = 10;
		::_TrackMouseEvent(&tme);
	}
	m_ComboStatus = nFlags & MK_LBUTTON ? PBS_PRESSED : PBS_HOT;

	auto showText = GetSelectionText();
	auto rtTxt = GetTxtRect();
	m_TipCtrl.AddTool(this, showText, rtTxt, m_nTipId);
	m_TipCtrl.UpdateTipText(showText, this);

	Invalidate();
}

void CComboAnyOne::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ComboStatus = PBS_PRESSED;
	Invalidate();

	bool bPanelShowed = m_Panel.IsWindowVisible();
	__super::OnLButtonDown(nFlags, point);
	if (bPanelShowed)
		m_Panel.EndEdit();
	else
		DropDownSubCtrl();// �����ӶԻ���
}

void CComboAnyOne::OnLButtonUp(UINT nFlags, CPoint point)
{
	__super::OnLButtonUp(nFlags, point);
	m_ComboStatus = PBS_HOT;
	Invalidate();
}

void CComboAnyOne::OnMouseLeave()
{
	m_ComboStatus = PBS_NORMAL;
	__super::OnMouseLeave();
	Invalidate();
}

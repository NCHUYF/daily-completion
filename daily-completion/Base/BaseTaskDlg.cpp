#include "pch.h"
#include "BaseTaskDlg.h"
#include "afxdialogex.h"
#include "../Resource.h"

BEGIN_MESSAGE_MAP(CBaseTaskDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SHOWTASK, onShowTask)
	ON_MESSAGE(WM_HIDETOTASKBAR, OnHideToTaskbar)
	ON_MESSAGE(WM_SHOWFROMTASKBAR, OnShowFromTaskbar)
END_MESSAGE_MAP()

void CBaseTaskDlg::HideToTaskbar()
{
	PostMessage(WM_HIDETOTASKBAR, 0, 0);
}

void CBaseTaskDlg::ShowFromTaskbar()
{
	PostMessage(WM_SHOWFROMTASKBAR, 0, 0);
}

LRESULT CBaseTaskDlg::OnHideToTaskbar(WPARAM wParam, LPARAM lParam)
{
	if (!_bVisible) return 0;
	_bVisible = false;
	ToTray();
	GetWindowRect(&_tmpRect);
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	AfxGetApp()->GetMainWnd()->ShowWindow(SW_HIDE);
	AfxGetMainWnd()->MoveWindow(-_tmpRect.right, -_tmpRect.bottom, _tmpRect.Width(), _tmpRect.Height(), true);
	ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CBaseTaskDlg::OnShowFromTaskbar(WPARAM wParam, LPARAM lParam)
{
	if (_bVisible)return 0;
	_bVisible = true;
	AfxGetMainWnd()->MoveWindow(_tmpRect.left, _tmpRect.top, _tmpRect.Width(), _tmpRect.Height(), true);
	::Shell_NotifyIcon(NIM_DELETE, &m_nid);
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	AfxGetApp()->GetMainWnd()->ShowWindow(SW_SHOW);
	ShowWindow(SW_SHOW);
	return 0;
}

void CBaseTaskDlg::SetTaskbarTip(const CString & strTip)
{
	_strTaskbarTip = strTip;
}

void CBaseTaskDlg::ToTray()
{
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;

	//自定义的消息名称 WM_SHOWTASK 头函数中定义为WM_USER+1
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, _strTaskbarTip);//当鼠标放在上面时，所显示的内容
	Shell_NotifyIcon(NIM_ADD, &m_nid);//在托盘区添加图标
}

LRESULT CBaseTaskDlg::onShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"退出");
		//确定弹出式菜单的位置
		SetForegroundWindow();
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		//资源回收
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK://双击左键的处理
	{
		ShowFromTaskbar();
	}
	break;
	}
	return 0;
}

CBaseTaskDlg::CBaseTaskDlg(UINT nIDTemplate, CWnd * pParent)
	: CDialogEx(nIDTemplate, pParent)
{
}

void CBaseTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CBaseTaskDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	ShowFromTaskbar();
}

BOOL CBaseTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置默认提示为程序名称
	CString filename;
	TCHAR AppPath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, AppPath, MAX_PATH);
	TCHAR *beg = _tcsrchr(AppPath, _T('\\'));
	beg++;
	TCHAR *end = _tcsrchr(AppPath, _T('.'));
	*end = _T('\0');
	filename = beg;
	SetTaskbarTip(filename);
	_bVisible = true;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

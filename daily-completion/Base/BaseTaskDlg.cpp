#include "pch.h"
#include "BaseTaskDlg.h"
#include "afxdialogex.h"
#include "../Resource.h"

BEGIN_MESSAGE_MAP(CBaseTaskDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SHOWTASK, onShowTask)
END_MESSAGE_MAP()

void CBaseTaskDlg::Hide2Taskbar(bool bHide)
{
	static CRect TmpRect;
	if (bHide && !_bHideWnd)
	{
		GetWindowRect(&TmpRect);
		ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
		AfxGetApp()->GetMainWnd()->ShowWindow(SW_HIDE);
		ShowWindow(SW_HIDE);
		AfxGetMainWnd()->MoveWindow(-TmpRect.right, -TmpRect.bottom, TmpRect.Width(), TmpRect.Height(), true);
		_bHideWnd = true;
	}
	else if(!bHide && _bHideWnd)
	{
		ShowWindow(SW_HIDE);
		AfxGetMainWnd()->MoveWindow(TmpRect.left, TmpRect.top, TmpRect.Width(), TmpRect.Height(), true);
		::Shell_NotifyIcon(NIM_DELETE, &m_nid);
		ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
		AfxGetApp()->GetMainWnd()->ShowWindow(SW_SHOW);
		ShowWindow(SW_SHOW);
		_bHideWnd = false;
	}
}

void CBaseTaskDlg::SetTaskbarTip(const CString & strTip)
{
	_strTaskbarTip = strTip;
	ToTray();
}

void CBaseTaskDlg::ToTray()
{
	::Shell_NotifyIcon(NIM_DELETE, &m_nid);
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;

	//�Զ������Ϣ���� WM_SHOWTASK ͷ�����ж���ΪWM_USER+1
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, _strTaskbarTip);//������������ʱ������ʾ������
	Shell_NotifyIcon(NIM_ADD, &m_nid);//�����������ͼ��
}

LRESULT CBaseTaskDlg::onShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա�
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//�õ����λ��
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"�˳�");
		//ȷ������ʽ�˵���λ��
		SetForegroundWindow();
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		//��Դ����
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK://˫������Ĵ���
	{
		Hide2Taskbar(false);
	}
	break;
	}
	return 0;
}

CBaseTaskDlg::CBaseTaskDlg(UINT nIDTemplate, CWnd * pParent)
	: CDialogEx(nIDTemplate, pParent)
{
	_bHideWnd = false;
}

void CBaseTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CBaseTaskDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	Hide2Taskbar(false);
}

BOOL CBaseTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ����Ĭ����ʾΪ��������
	CString filename;
	TCHAR AppPath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, AppPath, MAX_PATH);
	TCHAR *beg = _tcsrchr(AppPath, _T('\\'));
	beg++;
	TCHAR *end = _tcsrchr(AppPath, _T('.'));
	*end = _T('\0');
	filename = beg;
	SetTaskbarTip(filename);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

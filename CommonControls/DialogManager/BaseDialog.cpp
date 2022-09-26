/*****************************************************
*    �ļ����ƣ�    BaseDialog.CPP
*    ����������    �����Ի���
*    ������ʶ��    �ƺ�ǿ  2018/11/14 17:48
*
*    �޸ı�ʶ��
*    �޸�������
*****************************************************/

#include "stdafx.h"
#include "BaseDialog.h"

CBaseDialog::CBaseDialog(UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/, bool bIsMutex, const CString& strDialogName)
	: CDialogEx(nIDTemplate, pParentWnd), CMSRegDlg(bIsMutex, strDialogName)
{

}

BOOL CBaseDialog::OnInitDialog()
{
	__super::OnInitDialog();
	HICON hIcon = CDefImage::LoadSysIcon();
	SetIcon(hIcon, TRUE);  // ���ô�ͼ��
	SetIcon(hIcon, FALSE);  // ����Сͼ��
	return TRUE;
}

void CBaseDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);

	switch (nID)
	{
	case SC_MINIMIZE:
	{
		CWnd *pWnd = AfxGetMainWnd();
		CRect pParentRect;
		pWnd->GetWindowRect(&pParentRect);

		CRect curRect;
		GetWindowRect(&curRect);
		CRect minRect;
		minRect.bottom = pParentRect.bottom;
		minRect.top = pParentRect.bottom - (curRect.bottom - curRect.top);
		minRect.left = pParentRect.left;
		minRect.right = pParentRect.left + (curRect.right - curRect.left);
		MoveWindow(minRect);
		break;
	}
	default:
		break;
	}
}

BOOL CBaseDialog::DestroyWindow()
{
	HICON hIcon = GetIcon(true);
	if (hIcon != nullptr)
	{
		DestroyIcon(hIcon);
		hIcon = nullptr;
	}
	hIcon = GetIcon(false);
	if (hIcon != nullptr)
	{
		DestroyIcon(hIcon);
		hIcon = nullptr;
	}
	return __super::DestroyWindow();
}

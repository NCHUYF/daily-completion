/*****************************************************
*    �ļ����ƣ�    BaseDialog.H
*    ����������	   �����Ի���
*    ������ʶ��    �ƺ�ǿ  2018/11/14 17:42
*
*    �޸ı�ʶ��
*    �޸�������
*****************************************************/

#pragma once
#include "afxdialogex.h"

class COMMONCONTROLS_API CBaseDialog : public CDialogEx, public CMSRegDlg
{
public:
	/**
	*  �������ܣ�   ����Ի���
	*  �������룺  UINT nIDTemplate �Ի���ID
	*  �������룺  bool bIsMutex   trueΪ����Ի���flaseΪ����Ի���
	*  �������룺  CWnd * pParentWnd
	*  ���������    
	*  ����ֵ��     
	*/
	CBaseDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL, bool bIsMutex = true, const CString& strDialogName = L"");

	/**
	*  ��������:    ��ʼ���Ի���
	*  ����ֵ:   	BOOL
	*/
	virtual BOOL OnInitDialog();

	virtual void CloseDialog() = 0;

	// ���ٶԻ���
	virtual BOOL DestroyWindow();

	virtual afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};


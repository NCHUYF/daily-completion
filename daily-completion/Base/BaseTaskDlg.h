#pragma once

#define WM_SHOWTASK WM_USER+666

class CBaseTaskDlg : public CDialogEx
{
public:
	CBaseTaskDlg(UINT nIDTemplate, CWnd *pParent = nullptr);
	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAILYCOMPLETION_DIALOG };
#endif
public:
	// �Ƿ����ش��ڵ�����
	void Hide2Taskbar(bool bHide = true);
	void SetTaskbarTip(const CString &strTip);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
protected:
	// ���ɵ���Ϣӳ�亯��
	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT onShowTask(WPARAM wParam, LPARAM lParam);
	void ToTray();
protected:
	NOTIFYICONDATA m_nid;
	bool _bHideWnd;
	CString _strTaskbarTip;
};



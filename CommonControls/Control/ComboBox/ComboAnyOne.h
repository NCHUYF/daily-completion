#pragma once
#include "afxwin.h"
#ifndef WM_END_EDIT
#define WM_END_EDIT (WM_USER+1)
#endif

// �ؼ�����
class IPopupCtrl
{
public:

	IPopupCtrl()
	{
		m_pOwner = NULL;
		m_pNotifyWnd = NULL;
	}

	virtual ~IPopupCtrl() {}

public:
	// ���ش���
	virtual CWnd* GetWnd(CWnd *pOnwer) = 0;

	// ������Ҫ��Combo����ʾ������
	virtual CString GetCtrlTextForShow() = 0;

	// ֪ͨ�ؼ���ʾ
	virtual void OnPreShowCtrl(LPCTSTR curComboTxt) = 0;

	// ���ؿؼ�����ʾ�������ĳߴ�
	virtual CSize GetBestSize() = 0;

	// ����������
	void SetOwner(CWnd *pCombo)
	{
		m_pOwner = pCombo;
	}

	// ������Ϣ֪ͨ���մ��ڣ�һ��ΪWM_NOTIFY��WM_COMMAND��Ϣ�Ĵ�����
	void SetNotifyWnd(CWnd *pWnd)
	{
		m_pNotifyWnd = pWnd;
	}

protected:
	void UpdateOwner()
	{
		m_pOwner->Invalidate();
	}

protected:
	CWnd *m_pOwner;
	CWnd *m_pNotifyWnd;
};

// COMBO������壬�����������
class COMMONCONTROLS_API CComboPanel : public CWnd
{
public:
	// �������
	CComboPanel(IPopupCtrl *subWnd);

	// �����������
	~CComboPanel();

	// �����������
	void PopupComboPanel();

	// �����༭
	void EndEdit();

	// ��������
	void CreateWnd(CWnd *pParent);

	DECLARE_MESSAGE_MAP()

protected:
	// ���ذ�ȫ���Ӵ���ָ�룬����Ӵ��ڲ����ڣ��򷵻�NULL
	CWnd* GetSafeSubWnd();

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

protected:
	IPopupCtrl *m_pubWnd;
	static CString s_ClassName;
};

// ��������ؼ�
class COMMONCONTROLS_API CComboAnyOne : public CWnd
{
public:
	CComboAnyOne(IPopupCtrl *subWnd);
	~CComboAnyOne();

public:
	// ��������
	void CreateWnd(CWnd *pParent, LPRECT rt, UINT uId = 0);

	// ����֪ͨ���ڣ�Ĭ���Ǹ�����,һ��ΪWM_NOTIFY��WM_COMMAND��Ϣ�Ĵ�����
	void SetNotifyWnd(CWnd *pNewWnd);

	// ��ʾ�ı�ת������
	virtual CString TranslateSelection(LPCTSTR szDefTxt);

protected:
	// �����Ҫ�ߴ�
	void UpdateWndSize();

	// ���������ӿؼ�
	void DropDownSubCtrl();

	// �����ı�����
	CRect GetTxtRect();

	// ������ϢԤ������
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	CString GetSelectionText();
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
protected:
	CComboPanel  m_Panel;				// ���
	CToolTipCtrl m_TipCtrl;				// ��ʾ��Ϣ
	IPopupCtrl  *m_pSubWnd;				// �����ؼ�����
	HWND		 m_NotifyWnd;			// ֪ͨ����
	CRect		 m_BtnRect;				// ��ť��С
	CRect		 m_DropListRect;		// ������λ��
	CFont		 m_Font;				// ������ʽ
	int			 m_ComboStatus;			// ������״̬
	int			 m_nDropDownListHeight;	// ������߶�
	static const int m_BtnSize = 16;
	static const int m_nMarin = 4;
	static const int m_nDropBtPos = 3;
	static const int m_nTipId = 1;
	static CString s_ClassName;
	CImageList m_Images;
};


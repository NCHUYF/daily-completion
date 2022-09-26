#pragma once
#include "InputEdit.h"
#include <vector>



class COMMONCONTROLS_API CEditableTabCtrl : public CWnd
{
	enum ButtonStatus { eDefStatus, eHightLightStatus, ePushDownSatus };
public:
	CEditableTabCtrl(DWORD dwStyle = TCS_ENABLEEDIT | TCS_SHOWADDBTN | TCS_SHOWCLOSEBTN);
	~CEditableTabCtrl();
	DECLARE_MESSAGE_MAP()
	
public:
	// ������ʽ
	void SetDisplayStyle(DWORD dwStyle);

	void SetNotifyWnd(HWND hWnd);

	// ���ص�ǰ��ʽ
	DWORD GetDisplayStyle();

	// �����Զ���༭��
	void SetCustomEdit(CInputEdit *pEdit);

	// ��������
	void CreateWnd(CWnd *pParent, LPRECT rt, UINT uId = 0);

	// ����ҳǩ
	int InsertItem(LPCTSTR labelName, CWnd *pChildren, int nIndex = -1);
	
	// �Ƴ�ҳǩ
	void RemoveItem(int nIndex);
	
	// ��õ�ǰѡ����
	int GetCurSel();

	// ����ҳǩ��С
	bool GetItemRect(int nIndex, LPRECT retRect);

	// ����ҳǩ���ı�
	void SetItemText(int nIndex, LPCTSTR newTxt);

	// ���ҳǩ���ı�
	CString GetItemText(int nIndex);

	// ѡ����
	void SelectItem(int nIndex);

	int GetItemCount();

	// �������Tab
	void ClearAll();

protected:
	CInputEdit* GetInputEditor();
	void UpdateItemRect();
	void UpdateTipInfo();

	CRect GetAddButtonPos();
	CRect GetContainerPos();
	CRect GetTabContainerPos(bool bIncludeBtn);

	// ����tabҳǩ�������
	void GetTabCorner(const TabInfo& tabInfo, CPoint& leftTop, CPoint& rightTop, CPoint &leftBottom, CPoint &rightBottom);

	// ����tabҳǩ������Ч��
	void DrawTabItemFrame(CDC *pDC, const TabInfo& info);
	void DrawTabItemText(CDC *pDC, const TabInfo& info);
	void DrawTabCloseButton(CDC *pDC, const TabInfo& info);

	// ����tabҳǩЧ��
	void DrawTabItem(CDC *pDC, const TabInfo& info);

	// ������Ӱ�ť
	void DrawAddButton(CDC *pDC, ButtonStatus btInfo);

	// �����Ƿ������tabҳǩ�����û�е��а�ť���򷵻�-1;
	int HitTest(CPoint pt);

	// ���Ե������Ǹ�tabҳǩ�Ĺرհ�ť�����û�е����κιرհ�ť������-1;
	int HitCloseBtTest(CPoint pt);
	void UpdateCloseButtonStatus(CPoint msPt);
	bool CheckMouseInAddButtonArea(CPoint msPt);

	// ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnEndEdit(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	CInputEdit  m_DefInputEditor;		// tab���Ʊ༭��
	CInputEdit  *m_pInputEditor;		// �Զ���tab���Ʊ༭��
	TabInfoList m_TabList;				// ���е�tab��¼
	int			m_CurSel;				// ��ǰѡ����
	int			m_nTabHeight;			// Tab�߶�
	CRect		m_TabRect;				// ��ǰtab�����С
	int			m_nMinTabWidth;			// Tab��С���
	int			m_nMaxTabWidth;			// Tab�����
	int			m_nTabPoDu;				// Tabҳǩ���¶�
	int			m_nButtonWidth;			// ��Ӱ�ť�Ŀ��
	int			m_nButtonSpan;			// ��Ӱ�ť��������ť��Ԥ�����
	int			m_nTabToContainer;		// Tab������֮��ľ���
	COLORREF	m_crTabBkColor;			// Tabҳǩ�ı�����ɫ
	COLORREF    m_crTabHightBkColor;	// Tabҳǩ��������ɫ
	COLORREF	m_crTabFrameColor;		// Tab��߿���ɫ
	COLORREF	m_crContainerColor;		// �������ɫ
	COLORREF	m_crTabContainerColor;	// Tab���������ɫ
	int			m_nCloseBtSize;			// �رհ�ť��С
	int			m_nIconSize;			// ͼ���С
	int			m_nIconOffset;			// ͼ��������ߵ�ƫ��
	static CString s_ClassName;			// ��������
	CImageList	m_Images;				// ͼ���б�
	CImageList	m_AddButtonImgs;		// ��ť��ʽ
	ButtonStatus m_ButtonStatus;		// ��ť״̬��Ϣ
	CToolTipCtrl m_TipCtrl;				// ��ʾ��Ϣ
	DWORD		 m_nDisStyle;			// ��ʾ��ʽ
	HWND		m_NotifyWnd;			// ֪ͨ����
	CFont		m_TabFnt;				// Tab��������
};


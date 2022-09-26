//*****************************************************
//    
//    @copyright      ���������
//    @version        v3.0
//    @file           TabContainerCtrl.H
//    @author         mahaidong
//    @date           2015/4/2 17:38
//    @brief          tabѡ��ؼ�;
//*****************************************************

#pragma once

// TAB����ѡ����Ϣ������TRUE����ֹѡ��
#define TAB_SELECTING (WM_USER+2016)

// TABѡ����Ϣ
#define TAB_SELECT (WM_USER+2017)

// TAB��Ϣ��Ӧ�¼�
#define TAB_TOOLTIPS (WM_USER + 2018)

// ����
// m_tab.Create(WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE|TCS_SINGLELINE|TCS_TABS|TCS_RIGHTJUSTIFY, rc, this, id);
// ͷ�ļ����� afx_msg LRESULT OnTabSelect(WPARAM, LPARAM);
// CPP��BEGIN_MESSAGE_MAP������Ϣ��Ӧ ON_MESSAGE(TAB_SELECT, OnTabSelect)
// ����WPARAM Ϊ��ǰTAB���ھ������Ϊ���TAB�ؼ��жϣ�LPARAM ��ǰѡ���TAB����

// ��ǩ�ؼ���Ϣ���ݽṹ��
struct CTabContainerNotify
{
	NMHDR hdrNotify;			///< ֪ͨ��Ϣ�ṹ
	int nSelItem;				///< ��ѡ�еı�ǩҳ���
};


class COMMONCONTROLS_API CTabContainer : public CTabCtrl
{
public:
	/**
	*  @brief    ���캯��;
	*
	*/
	CTabContainer();

	/**
	*  @brief    ��������;
	*
	*/
	virtual ~CTabContainer();

public:
	/**
	*  @brief    ������������ѡ�е�tabѡ�;
	*
	*  @param    int nItem ��Ҫѡ�е�tabѡ�����;
	*  @return   int
	*/
	int SetCurSel(int nItem);

	/**
	*  @brief    ����ѡ�
	*
	*  @param    int nItem ��������;
	*  @param    LPCTSTR lpszItem ѡ���ʾ����;
	*  @param    HWND hWnd ���ھ��;
	*  @return   LONG
	*/
	LONG InsertItem(int nItem, LPCTSTR lpszItem, HWND hWnd);

	/**
	*  @brief    ����ѡ�;
	*
	*  @param    int nItem ��������;
	*  @param    LPCTSTR lpszItem ѡ���ʾ����;
	*  @param    HWND hWnd ���ھ��;
	*  @param    int nImage ��ʾͼ������;
	*  @return   LONG 
	*/
	LONG InsertItem(int nItem, LPCTSTR lpszItem, HWND hWnd, int nImage);

	/**
	*  @brief    ��������ɾ��ѡ�;
	*
	*  @param    int nItem Ҫɾ��ѡ�������;
	*/
	void DeleteItem(int nItem);

	/**
	*  @brief    ɾ��ȫ��ѡ�;
	*
	*/
	void DeleteAllItems();

	/**
	*  @brief    ���ý�����Ϣ�Ĵ��ھ��;
	*
	*  @param    CWnd * pParent �����ھ��;
	*/
	void SetMsgParent(CWnd* pParent);

	/**
	*  @brief    ���ñ�ǩ��ʾ�ı�;
	*
	*  @param    int nItem ��ǩ����;
	*  @param    LPCTSTR lpStrText ��ǩ��ʾ�ı�;
	*/
	void SetTabText(int nItem, LPCTSTR lpStrText);

	/**
	*  @brief    ��ñ�ǩ�ı�;
	*
	*  @param    int nItem ��ǩ����;
	*  @return   CString ��ǩ��ʾ�ı�;
	*/
	CString GetTabText(int nItem);

	/**
	*  @brief    �����Ƿ���ʾ�رհ�ť����ť�����ֻ��������¼������رձ�ǩ��
	*
	*  @param    bool bNeedCloseButton	�Ƿ���ʾ
	*/
	void SetItemCloseButton(bool bNeedCloseButton = true);

protected:
	/**
	*  @brief    function_description
	*
	*/
	void InitFont();
	/**
	*  @brief    function_description
	*
	*  @param    int nItem
	*/
	void MakeVisible(int nItem);

	/**
	*  @brief    function_description
	*
	*/
	void AdjustChildPos();

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTcnSelChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelChanging(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMClickTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()

protected:
	virtual void DrawMainBorder(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DrawItemBorder(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual COLORREF GetTabColor(BOOL bSelected = FALSE);
	virtual COLORREF GetTabTextColor(BOOL bSelected = FALSE);
	virtual void PreSubclassWindow();

protected:
	CWnd*	_pParent;
	COLORREF m_crBack;
	COLORREF m_tabColor;
	COLORREF m_tabTextColor;
	CFont	 m_fontTab;
	int _nLastCurItem;			///< ��һ��ѡ�б�ǩ
	CString _strCloseSign;		///< �ر��ַ�ռλ
	CRect _rcCloseSign;			///< �ر��ַ�����
	bool _bNeedCloseButton;		///< �Ƿ���ʾ�رհ�ť
	bool _bTabItemChange;		///< �л��˱�ǩҳ��ʶ
};
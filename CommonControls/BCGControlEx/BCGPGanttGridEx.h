#pragma once

////////////////////////////////////////////////////////////////////////////\
// CBCGPGridDateTimeItem object

class CONTROLSAPI_EXPORT CBCGPGanttFirstItem : public CBCGPGridItem
{
	//DECLARE_DYNAMIC(CBCGPGridItemEx)
	DECLARE_SERIAL(CBCGPGanttFirstItem)
// Construction
protected:
	CBCGPGanttFirstItem();

public:
	CBCGPGanttFirstItem(const _variant_t& varValue, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
		LPCTSTR lpszValidChars = NULL);

	virtual ~CBCGPGanttFirstItem();

// Overrides
public:
	virtual void OnDrawValue(CDC* pDC, CRect rect);

// ��չ��������
	void SetRect(CRect rect);
	
	// ���հ�����
	void SetLeftRect(CRect rect);
	CRect GetLeftRect();
	
	// ����������
	void DrawExpandBox(CDC* pDC);

	// �����༭����
	virtual void AdjustInPlaceEditRect(CRect& rectEdit, CRect& rectSpin);
// Attributes
public:

protected:
	CRect _leftRect;
};

//////////////////////////////////////////////////////////////////////////////////////
class CONTROLSAPI_EXPORT CBCGPGanttGridRowEx : public CBCGPGridRow
{
	friend class CBCGPGanttControlEx;
	friend class CBCGPGridCtrlEx;
	DECLARE_DYNAMIC(CBCGPGanttGridRowEx)

public:
	// Simple item
	CBCGPGanttGridRowEx(int nColumns = 0)
		: CBCGPGridRow(nColumns)
	{
	}

	// Group constructor
	CBCGPGanttGridRowEx(const CString& strGroupName)
		: CBCGPGridRow(strGroupName)
	{
	}

	virtual ~CBCGPGanttGridRowEx()
	{
	}

public:
	// �����׸�Item
	virtual void DrawFirstItemValue(CDC* pDC, CRect rect, BOOL bGroupUnderline);
	virtual void OnExpand(BOOL bExpand);

	void SwapSubItems(CBCGPGridRow* pRow1, CBCGPGridRow* pRow2);
	bool HasChild();
};

////////////////////////////////////////////////////////////////////////////////////////\

static UINT BCGM_GRID_ITEM_DRAG = ::RegisterWindowMessage(_T("BCGM_GRID_ITEM_DRAG"));
class CONTROLSAPI_EXPORT CBCGPGanttGridEx : public CBCGPGanttGrid
{
	friend class CBCGPGanttControlEx;
	friend class CBCGPGanttGridRowEx;
	//friend class CBCGPGridRow;
	DECLARE_DYNCREATE(CBCGPGanttGridEx)

public:
	CBCGPGanttGridEx();
	virtual ~CBCGPGanttGridEx();

	// Overrides
public:
	// ������չ��CBCGPGridRowEx
	virtual CBCGPGridRow* CreateRow();
 	virtual CBCGPGridRow* CreateRow(CString strName);
	virtual CBCGPGridRow* CreateRow(int nColumns);
	virtual void InsertRowAfter(CBCGPGridRow* pParentRow, int nSubPos, CBCGPGridRow* pSubItem);
	virtual BOOL OnDrawItem(CDC* pDC, CBCGPGridRow* pItem);
	// ����ExpandBox ����λ��
	virtual int GetExtraHierarchyOffset() const;
	virtual int GetHierarchyLevelOffset() const;

protected:
	virtual BOOL OnTrackHeader()
	{
		return FALSE; // do not resize columns inside client area by mouse, only at header
	}

public:
	// �������ؼ������� - ��δʵ��
	int GetTreeColumn();
	void SetTreeColumn(int nColumn);
	
	CBCGPGridRow* GetLastSelRow();
	// ���������С
	void SetFontSize(int nSize);
	void SetFontSizeScale(float fScale);

	// �����������������Ӵ�
	void SetBoldFontByHasChild(bool bBold = true);
	bool GetBoldFontByHasChild();

	// ������ק
	void SetDragDropRows();

	// ��չ	CBCGPGridCtrl �еı�������������
	DWORD GetMarkedIndexes() { return m_nMarkedIndexes;}
	int GetcxCurrText() { return m_cxCurrText; }

	virtual void OnRowHeaderDblClick(CBCGPGridRow* pRow, CPoint point, CRect rect);
	virtual CRect OnGetSelectionRect();
	virtual void OnDrawSelectionBorder(CDC* pDC);

	virtual BOOL DragItems(CPoint point);
	virtual BOOL DoDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL DoDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

	/**
	* �����༭
	* @param [in] pItem
	*/
	virtual void OnEndInplaceEdit(CBCGPGridItem* pItem);

	virtual BOOL EditItem(CBCGPGridRow* pItem, LPPOINT lptClick = NULL);

	/**
	* ���ÿ����˳��༭״̬����Ӧ�ַ�
	* @param [in] nChar ָ����Ӧ�ַ�
	* @param [in] nRepCnt 
	* @param [in] nFlags  
	*/
	virtual BOOL CanEndInplaceEditOnChar(UINT nChar, UINT nRepCnt, UINT nFlags) const;

	/**
	* ���ڵ���Ϣ
	* @param [in] message ָ����Ϣ���͡�
	* @param [in] wParam  ָ������ġ���Ϣ�ض�����Ϣ���ò�����������message����ֵ�йء�
	* @param [in] IParam  ָ������ġ���Ϣ�ض�����Ϣ���ò�����������message����ֵ�йء�
	* ����ֵ������ֵ������Ϣ�����������뷢�͵���Ϣ�йء�
	*/
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	/**
	*  ��:PreTranslateMessage�е��ã�����Դitem���ڱ༭״̬ʱ��������򣬽���Դitem�е�ֵ����Ϊԭ����
	*/
	void UpdateInplaceWnd();

protected:
	int _bBoldFontByHasChild;

protected:
	//{{AFX_MSG(CBCGPGanttGrid)
	//}}AFX_MSG
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnEndLabelEdit(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	int m_nIMECharSize;
	int m_nIMECharLeft;
};


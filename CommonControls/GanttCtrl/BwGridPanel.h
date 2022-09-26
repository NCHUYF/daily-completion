//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           BwGridPanel.h
//    @author         yf
//    @data           2021/01/20  
//    @brief          Grid�Ի���
//
//*****************************************************

#pragma once

#include "BwGanttGrid.h"
#include <vector>

COMMONCONTROLS_API extern UINT BW_GRIDDLG_EXPORT;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_IMPORT;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_BEFOREDELETE;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_DELETE;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_BIND;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_NEW;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_MOVE;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_SELCHANGE;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_ENDEDIT;
COMMONCONTROLS_API extern UINT BW_GRIDDLG_ENDEDITDONE;

class CBwGanttControl;
class CBwGanttChart;

class CBwGridPanel : public CWnd
{
	DECLARE_DYNCREATE(CBwGridPanel)
public:
	// ����ڵ���Ϣ
	struct stTaskInfo
	{
		CString _strName;
		COleDateTime _planStartTime;
		COleDateTime _planEndTime;
		COleDateTime _realStartTime;
		COleDateTime _realEndTime;
	};

	CBwGridPanel();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBwGridPanel();
public:
	// ��������
	void Create(CWnd *pParent, LPRECT rt, UINT uId = 0);

	// ����Gantt������
	void SetControl(CBwGanttControl *pControl);

	// ��ȡGantt������
	CBwGanttControl *GetControl();
	
	// ��ȡgrid�ؼ�
	CBwGanttGrid *GetGrid();

	// ����KNode���ڵ�
	void SetRoot(KNode *pRoot);

	// ��ȡKNode���ڵ�
	KNode * GetRoot();

	// �����Ƿ����
	bool IsNameExist(const CString &strCurName, KNode *pNode);

	// ��ҵ�����������ݵ����
	void LoadFromNode(bool bRedraw = true);

	// ����ҵ����󲢲��ҽڵ��±�
	int LoadAndFindIndex(KNode *pFind, bool bRedraw = true);

	// ��ȡ��ť������θ߶�
	int GetBtnAreaHeight();

	// ���ð�ť
	void EnableButtons(bool bEnable = true);

	// ��ȡ���ڷ�Χ
	void GetDateRange(COleDateTime &startTime, COleDateTime &endTime);

	// ��ȡѡ���±�
	int GetSelIndex();

	// ��ȡѡ�еĶ���±�
	std::set<int> GetSelIndexes();

	// ����ͼ���б�
	void SetImageList(CImageList *pImageList);

	// ��ʾ������
	void ShowToolbar(bool bShow);

	// ��ȡ������ʽ�ַ���
	CString GetGrowthPatternString(int nGrowthPattern);

	// ѡ����
	void SelectRow(int nIndex);
	void SelectRow();

	// �����༭
	bool OnEndEditGrid(CBCGPGridItem * pGridItem, KNode *pNode, const CBwGanttGrid::ColumnFormat &colFormat);
	void OnEndEditGridDone(CBCGPGridItem * pGridItem, KNode *pNode, const CBwGanttGrid::ColumnFormat &colFormat);

	// CBwGridPanel ���

#ifdef _DEBUG
	void AssertValid() const;
#ifndef _WIN32_WCE
	void Dump(CDumpContext& dc) const;
#endif
#endif //_DEBUG
protected:
	DECLARE_MESSAGE_MAP()

	// �̳��ڻ���ķ���
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	LRESULT OnClickGrid(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	// �����µ�����ڵ�
	KNode *CreateNewTaskNode(const stTaskInfo & taskInfo);

	void OnButtonClicked(UINT uId);

	// ����������
	KNode * CreateNewTask();

	// �����µ�������
	KNode *CreateNewChildTask();

	// ��
	void Bind();

	// ɾ����ǰ����
	void DeleteCurTask();

	// ����
	void MoveUp();

	// ����
	void MoveDown();

	// �ƶ���ǰ����
	void MoveCurTask(bool bUp = true);

	// ���õ�ǰ����
	void SetCurTime(const COleDateTime &curTime);

	// ����
	void Export();

	// ����
	void Import();

	// ���� 
	void Load();

	// ����Grid�ؼ�
	void CreateGrid();

	// ����������
	void CreateToolBar();

	// ��ȡChart�ؼ�
	CBwGanttChart *GetChart();

	// ������������
	CString CreateTaskName();

	// ��ȡ������ʽ���ͱ�ǩ
	int GetGrowthPatternTag(const CString &strGrowthPattern);

	// ���½��ȳ���ʱ��
	void UpdateDuringTime();

	// CStringת����
	COleDateTime CString2Datetime(CString strDate);

	// ����תCString
	CString Datetime2CString(COleDateTime dateTime);
	// ��ȡĬ��Task����
	stTaskInfo GetDefaultTaskInfo();

	// ��ҵ�����������ݵ����(����ֵΪ���صĽڵ����)
	int LoadFromNode(KNode *pRoot, KNode *pFind = NULL, int *pFindIndex = NULL, int nStartRow = 0, int nLevel = 0);

	// ��ȡ�Ӳ㼶������
	int GetAllSubItemCount(CBCGPGridRow *pRow);

	// ��ȡ���ڷ�Χ
	void GetDateRange(COleDateTime &startTime, COleDateTime &endTime, KNode *pParent);

	// ����������
	void AjustVScroll();
	
	// �Ƿ���Դ����µ��Ӽ�����
	bool CanCreateNewChildTask();

protected:
	KNode *_pRoot; // ���ȸ��ڵ�
	CBwGanttGrid *_pGrid; // grid�ؼ�����ָ��
	CBwGanttChart *_pChart; // ����ͼChart����ָ��
	CBwGanttControl * _pControl; // ����ͼ����������ָ��
	CFont _font; // �������ָ�루��Ҫ�־ô洢����Ȼû��Ч����

	CButton _btnNew; // �½���ť
	CButton _btnNewChild; // �½��Ӽ�
	CButton _btnDelete; // ɾ����ť
	CButton _btnBind; // �󶨰�ť
	CButton _btnImport; // ���밴ť
	CButton _btnExport; // ������ť
	CButton _btnUp; // ���ư�ť
	CButton _btnDown; // ���ư�ť

	std::vector<shared_ptr<TBBUTTON>> _arrBtns;

	static CString s_ClassName;	// ��������
	HWND m_NotifyWnd; // ֪ͨ����
	CToolTipCtrl m_TipCtrl; // ��ʾ��Ϣ
	COLORREF m_crTabContainerColor; // Tab���������ɫ

	CToolBarCtrl _toolBar;

	CImageList *_pImageList; // ͼ���б�
	bool _bShowToolBar; // �Ƿ���ʾ������

	int _nSelIndex; // ��ǰѡ����

	int _oldSel; // ��һ��ѡ����
	int _oldPos; // ��һ�δ�ֱ������λ��
};
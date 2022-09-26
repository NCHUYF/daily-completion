//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           BwGanttControl.h
//    @author         yf
//    @data           2020/12/16  
//    @brief          ����ͼ�ؼ�
//
//*****************************************************

#pragma once

#include "BCGPGanttControl.h"
#include "BwSplitCtrl.h"
#include <map>
#include <set>
#include "BwGridPanel.h"
#include "BwGanttChart.h"

//------------------------------------------------------

class COMMONCONTROLS_API CBwGanttControl : public CBCGPGanttControl
{
	friend class CBwGanttGrid;
	friend class CBwGanttChart;
public:
	CBwGanttControl();
	virtual ~CBwGanttControl();

	// ��������Ϣ
	struct BW_GANTT_INSERT_RESULT
	{
		BW_GANTT_INSERT_RESULT()
			:_nRow(-1)
			,_bRes(false)
		{

		}

		int _nRow;
		bool _bRes;
	};

	// ɾ�������Ϣ
	struct BW_GANTT_DELETE_RESULT
	{
		BW_GANTT_DELETE_RESULT()
			:_nRow(-1)
			, _bRes(false)
		{

		}

		int _nRow;
		bool _bRes;
	};

public:
	// ����
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// �����ؼ�
	virtual int  CreateControls();

	// ��ȡ�ָ���
	CBwSplitCtrl*       GetSplitter(); 

	// ����grid�ؼ�
	virtual void UpdateGridEx(bool bRedraw = true);

	// ���õ�ǰ���ڴ�ֱ����ɫ
	void SetCurTimeLineColor(COLORREF clr);

	// ���õ�ǰ����
	void SetCurTime(const COleDateTime &curTime);

	// ���ø��ڵ�
	void SetRoot(KNode *pRoot);

	// ��ҵ�����������ݵ����
	void LoadFromNode();

	// ���ð�ť
	void EnableButtons(bool bEnable = true);

	// ��ȡ���ڷ�Χ
	void GetDateRange(COleDateTime &startTime, COleDateTime &endTime);

	// ���ù�����ͼ���б�
	void SetToolBarImageList(CImageList *pImageList);

	// ��ʾ������
	void ShowToolbar(bool bShow = true);

	// ���û��������
	void SetSplitterWidth(int nWidth);

	// ���û�����λ��
	void SetSplitterPosPct(int nPos);

	// ���õ��н�����(bSingleΪtrue��ʾ���У�Ϊfalse��ʾ˫�У�
	void SetSingleProgressBar(bool bSingle = true);
	
	// ����ʱ���������
	void SetTimeDimension(CBwGanttChart::ETimeDimension td);

	// ��ȡʱ���������
	CBwGanttChart::ETimeDimension GetTimeDimension();

	// ���¹�����λ��
	void UpdateScrollPos();

	// ����KNode�ڵ�(bAddChild��ʾ�Ƿ�����Ӽ�)
	BW_GANTT_INSERT_RESULT InsertNode(KNode *pNode, bool bAddChild = false);

	// ɾ��KNode�ڵ�
	BW_GANTT_DELETE_RESULT DeleteNode(KNode *pNode);

	// ����Grid����
	void UpdateGridItem(KNode *pNode);

	// ͨ��KNode��ȡGanttItem
	CBwGanttChart::CBwGanttItemInfo GetGanttItemByKNode(KNode *pNode);

	// ͨ��KNode����GanttItem
	CBwGanttItem *CreateGanttItemByKNode(KNode *pParent, KNode *pNode);
	
	// �ı����нڵ�ı༭״̬
	void ModifyAllRowEditState();

	// ʹ��ڵ��пɱ༭
	void ModifyRowEditState(CBCGPGridRow* pRow);

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

	// ��Ϣ����
	afx_msg LRESULT OnNotifyStorageChanged(WPARAM, LPARAM);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual void DoItemsChange     (CWnd* pSender, const BCGP_GANTT_STORAGE_UPDATE_INFO& updateInfo);
	virtual CBwGanttGrid* CreateGanttGrid();
	virtual CBwGanttChart* CreateGanttChart();

	// ����Grid����
	void UpdateGridItem(CBCGPGanttItem* pItem, CBCGPGridRow* pRow);

	// ��ӦGrid���ݸ���
	virtual void OnGridItemChanged(CBCGPGridItem* pGridItem, int nRow, int nColumn);
	
	// ��Ӧ��ֱ�޸ĳߴ�
	virtual void DoVerticalResize(CWnd* pSender);

	// ����Chart��ͷ
	void AdjustChartHeadHeight();
protected:
	CBwSplitCtrl m_wndSplitter; // �ָ����ؼ�
	std::set<int *> _arrCols; // ���±�map
	CBwGridPanel _gridPanel; // Grid�ؼ��Ի���

	CBwGanttChart::ETimeDimension _eTimeDimension; // ʱ���������
};



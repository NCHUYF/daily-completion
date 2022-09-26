/*---------------------------------------------------------------------
*�ļ����ƣ�TimeFrameListCtrl.h
*����������ʱ��֡�ؼ�
*������ʶ��������2021.9.18.
*
*�޸ı�ʶ��
*�޸�������
----------------------------------------------------------------------*/
#pragma once

//ʱ��֡����֪ͨ�ṹ
struct CTimeFrameNotify
{
	NMHDR hdrNotify;										// ֪ͨ��Ϣ�ṹ
	int row;												// ������
	int col;												// ������
	ITimeLineCtrlDataSource *timeLineCtrlDataSource;		// ����������Դ
};

// ������ɫ�б�
typedef std::vector<COLORREF> VecColor;

// ��������������
typedef std::set<int> SetCollapseRow;
typedef SetCollapseRow::iterator SetCollapseRowIter;

class COMMONCONTROLS_API CTimeFrameListCtrl :public CWnd
{
public:
	CTimeFrameListCtrl(void);
	virtual ~CTimeFrameListCtrl(void);

protected:
	DECLARE_DYNAMIC(CTimeFrameListCtrl)
	DECLARE_MESSAGE_MAP()

public:
	/* 
	* �������ܣ�����ʱ��֡�б�ؼ�
	* ���������const RECT& rect �ؼ�����
	*			CWnd* pParentWnd ������
	*			CTimeLineCtrl* timeLineCtrl ���ڵ�ʱ����ؼ�
	*			UINT nID(0xfff0) �ؼ�ID
	*			DWORD dwStyle(WS_BORDER | WS_CHILD | WS_VISIBLE) �ؼ����
	* ���������void
	* ����ֵ  ��bool �Ƿ񴴽��ɹ�
	*/
	bool Create(const CRect &rect, CWnd *pParentWnd, CTimeLineCtrl *pTimeLineCtrl, UINT nID = NULL,
		DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE);

	/*
	* �������ܣ���ʼ���ؼ�����
	* ���������const CStirng & strCfg �����ļ�·��
	* ���������void
	* ����ֵ  ��void
	*/
	void LoadConfig(const CString& strCfg);

	/*
	* �������ܣ����¿ؼ�
	* ���������void
	* ���������void
	* ����ֵ  ��void
	*/
	void UpdateCtrl(void);

	/*
	* �������ܣ������¼�֪ͨ������
	* ���������void
	* ���������CWnd * pParent	�����ھ��
	* ����ֵ  ��void
	*/
	void SetNofityWnd(HWND hNotifyWnd);

	/*
	* �������ܣ����������Ӧ�жϽӿ�
	* ���������IMouseResponseJudgment *pMouseResponseJudgement �����Ӧ�жϽӿ�
	* ���������void
	* ����ֵ  ��void
	*/
	void SetMouseResponseJudgment(IMouseResponseJudgment *pMouseResponseJudgement);

	/*
	* �������ܣ�����ʱ��֡�̶ȵĳ���
	* ���������int nTimeFrameLength ʱ��֡�̶ȵĳ���
	* ���������void
	* ����ֵ  ��void
	*/
	void SetTimeFrameLength(int nTimeFrameLength);

	/*
	* �������ܣ���ȡʱ��֡�̶ȵĳ���
	* ���������void
	* ���������void
	* ����ֵ  ��int ʱ��֡�̶ȵĳ���
	*/
	int GetTimeFrameLength(void);

	/*
	* �������ܣ�����ʱ��֡��������
	* ���������int nItemCount ʱ��֡��������
	* ���������void
	* ����ֵ  ��void
	*/
	void SetItemCount(int nItemCount);

	/*
	* �������ܣ���ȡ��Ԫ��߶�
	* ���������void
	* ���������void
	* ����ֵ  ��int ��Ԫ��߶�
	*/
	int GetCellHeight(void);
	/*
	* �������ܣ���ȡ��ͷ�ĸ߶�
	* ���������void
	* ���������void
	* ����ֵ  ��int ��ͷ�ĸ߶�
	*/
	int GetHeadHeight(void);
	/*
	* �������ܣ���ȡ��ͷ�͵�Ԫ��Ŀ��
	* ���������void
	* ���������void
	* ����ֵ  ��int ��ͷ�͵�Ԫ��Ŀ��
	*/
	int GetWidth(void);

	/*
	* �������ܣ���ȡ��Ԫ�������
	* ���������void
	* ���������void
	* ����ֵ  ��int ��Ԫ�������
	*/
	int GetItemCount(void);

public:
	/*
	* �������ܣ����ùؼ�֡
	* ���������int nRow ��Ԫ���к�
	*			TimeFrameRowInfoMap &mapTimeFrameInfo �кŶ�Ӧ��ʱ��֡��Ϣ�б�
	* ���������void
	* ����ֵ  ��void
	*/
	void SetKeyFrame(int nRow, TimeFrameRowInfoMap &mapTimeFrameInfo, CMemoryDC& dcMemory);
	/*
	* �������ܣ����ùؼ�֡
	* ���������int nRow ��Ԫ���к�
	*			int nCol ��Ԫ���к�
	* ���������void
	* ����ֵ  ��void
	*/
	void SetKeyFrame(int nRow, int nCol, CMemoryDC& dcMemory);
	/*
	* �������ܣ����ò��䶯��
	* ���������int nRow ��Ԫ���к�
	*			TimeFrameRowInfoMap &mapTimeFrameInfo �кŶ�Ӧ��ʱ��֡��Ϣ�б�
	* ���������void
	* ����ֵ  ��void
	*/
	void SetTweenAnimation(int nRow, TimeFrameRowInfoMap &mapTimeFrameInfo, CMemoryDC& dcMemory);
	/*
	* �������ܣ����ò��䶯��
	* ���������int nRow ��Ԫ���к�
	*			int nCol ��Ԫ���к�
	* ���������void
	* ����ֵ  ��void
	*/
	void SetTweenAnimation(int nRow, int nCol, CMemoryDC& dcMemory);

	CTimeLineCtrl* GetTimeLineCtrl() { return _timeLineCtrl; }

protected:
	/*
	* �������ܣ���ȡ��Ԫ������(�����кź��к�)
	* ���������int nRow ��Ԫ���к�
	*			int nCol ��Ԫ���к�
	* ���������void
	* ����ֵ  ��void
	*/
	CRect GetCellRect(int nRow, int nCol);
	/*
	* �������ܣ���ȡ��Ԫ���������ĵ�(�����кź��к�)
	* ���������int nRow ��Ԫ���к�
	*			int nCol ��Ԫ���к�
	* ���������void
	* ����ֵ  ��void
	*/
	CPoint GetCellPoint(int nRow, int nCol);
	/*
	* �������ܣ���ȡ��Ԫ���������ĵ�(���ݵ�Ԫ������)
	* ���������CRect rect ��Ԫ������
	* ���������void
	* ����ֵ  ��void
	*/
	CPoint GetCellPoint(CRect rect);

	/*
	* �������ܣ����Ƶ��ʶ(����Ϊ�ؼ�֡)
	* ���������CPoint centerPoint ��ʶ������λ��
	*			COLORREF &colorSpot �����ɫ
	*			CMemoryDC &dcMemory ˫����dc
	* ���������void
	* ����ֵ  ��void
	*/
	void DrawSpot(CPoint centerPoint, COLORREF &colorSpot, CMemoryDC &dcMemory);

	/*
	* �������ܣ�����ʱ��֡
	* ���������CMemoryDC &dcMemory ˫����dc
	* ���������void
	* ����ֵ  ��void
	*/
	void DrawTimeFrame(CMemoryDC& dcMemory);

protected:
	/*
	* �������ܣ��򸸼�����Notify֪ͨ��Ϣ
	* ���������UINT nMessage ��ϢID
	*			int &nRow(-1) ��Ԫ��������
	*			int &nCol(-1) ��Ԫ��������
	*			ITimeLineCtrlDataSource *timeLineCtrlDataSource(NULL) ��Ԫ����������Դ
	* ���������void
	* ����ֵ  ��LRESULT �¼�֪ͨ���
	*/
	LRESULT NotifyParent(UINT nMessage, int nRow = -1, int nCol = -1,
		ITimeLineCtrlDataSource *timeLineCtrlDataSource = NULL);

	/*
	* �������ܣ���ȡ��ǰ���ָ���λ��
	* ���������CPoint* pPtMs ��ǰ���ͻ�����
	* ���������int &nRow ���ָ�����(-1��ʾ�ڱ�ͷ)
	*			int &nCol ���ָ�����
	* ����ֵ  ��bool �����ڿؼ���Χ���򷵻�true�����򷵻�false
	*/
	bool GetFocusPos(int &nRow, int &nCol, CPoint* ptMs = NULL);

	/*
	* �������ܣ���ȡ��ǰ���ָ��λ�ö�Ӧ������Դ
	* ���������int nRow ��Ԫ��������
	* ���������void
	* ����ֵ  ��ITimeLineCtrlDataSource* ��ǰ���ָ��λ�ö�Ӧ������Դ
	*/
	ITimeLineCtrlDataSource* GetFocusDataSource(int nRow);

	/*
	* �������ܣ���ȡ��������ʾ��Ӧ����ʵ������
	* ���������int nRow ��������ʾ������
	* ���������void
	* ����ֵ  ��int ��������ʾ��Ӧ����ʵ������
	*/
	int GetRowAfterCollapse(int nRow);

	/*
	* �������ܣ���ȡ��������ʾ������
	* ���������int nRow ��������ʾ��Ӧ����ʵ������
	* ���������void
	* ����ֵ  ��int ��������ʾ������
	*/
	int GetCollapseDisplayRow(int nRow);

	/*
	* �������ܣ��ƶ���ǰ֡
	* ���������CPoint ptMs ����λ��
	* ���������void
	* ����ֵ  ��void
	*/
	void MoveCurrentFrame(CPoint ptMs);

protected:
	/*
	* �������ܣ�����ͷ����ɫ
	* ���������CMemoryDC &dcMemory ˫����dc
	*			CRect rcHead ��������
	* ���������void
	* ����ֵ  ��void
	*/
	void FillHeadBkColor(CMemoryDC &dcMemory, CRect rcHead);
	/*
	* �������ܣ�����ʱ��֡�б���ͷ�̶�
	* ���������CMemoryDC &dcMemory ˫����dc
	*			CRect rcHead ���Ƶ�����
	*			bool bFirst �������Ƿ������һ��
	*			bool bLast �������Ƿ�������һ��
	* ���������void
	* ����ֵ  ��void
	*/
	void DrawTimeFrameHeadLine(CMemoryDC &dcMemory, CRect rcHead, bool bFirst, bool bLast);
	/*
	* �������ܣ�����ʱ��֡�б���ͷ�ı�
	* ���������CMemoryDC &dcMemory ˫����dc
	*			CRect rcHeadText �����ı�������
	*			int nText �����ı�������
	* ���������void
	* ����ֵ  ��void
	*/
	void DrawTimeFrameHeadText(CMemoryDC &dcMemory, CRect rcHeadText, int nText);
	/*
	* �������ܣ�����ʱ��֡�б���ͷ
	* ���������CMemoryDC &dcMemory ˫����dc
	* ���������void
	* ����ֵ  ��void
	*/
	void DrawTimeFrameHead(CMemoryDC &dcMemory);

	/*
	* �������ܣ�����ʱ��֡�б�Ԫ��
	* ���������CMemoryDC &dcMemory ˫����dc
	* ���������void
	* ����ֵ  ��void
	*/
	void DrawTimeFrameCell(CMemoryDC &dcMemory);

	/*
	* �������ܣ����Ƶ�ǰ֡
	* ���������CMemoryDC &dcMemory ˫����dc
	* ���������void
	* ����ֵ  ��void
	*/
	void DrawCurrentFrame(CMemoryDC &dcMemory);

	/*
	* �������ܣ�����ѡ�еĵ�Ԫ��
	* ���������CMemoryDC &dcMemory ˫����dc
	* ���������void
	* ����ֵ  ��void
	*/
	void DrawSelectCell(CMemoryDC &dcMemory);

	/*
	* �������ܣ����¹�����
	* ���������void
	* ���������void
	* ����ֵ  ��void
	*/
	void UpdateScrollBar(void);

protected:
	/*
	* �������ܣ���ȡ�ַ�����ɫ
	* ���������const CString & strColor �ַ�����ɫ
	* ���������void
	* ����ֵ  ��COLORREF �ַ�����ɫ
	*/
	COLORREF GetStringColor(const CString& strColor);
	/*
	* �������ܣ���ȡ�ַ�����ɫ�б�
	* ���������const CString & strColor �ַ�����ɫ�б�
	* ���������void
	* ����ֵ  ��VecColor �ַ�����ɫ�б�
	*/
	VecColor GetStringColorVec(const CString& strColor);

protected:
	/*
	* �������ܣ�ע��ؼ���
	* ���������void
	* ���������void
	* ����ֵ  ��bool �Ƿ�ɹ�ע��
	*/
	virtual bool RegisterTimeFrameList(void);

protected:
	//�Ի���Ӧ�¼�
	afx_msg void OnPaint(void);
	//�������Ƶı���ɫ
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//����ƶ���Ӧ�¼�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//������������Ӧ�¼�
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//������������Ӧ�¼�
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//������˫����Ӧ�¼�
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//����Ҽ�������Ӧ�¼�
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//�����������Ӧ�¼�
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//���ڳߴ��С�仯��Ӧ�¼�
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	CTimeLineCtrl*				_timeLineCtrl;					// ��Ӧ��ʱ����ؼ�

protected:
	HWND						_hNofigyWnd;					// �¼�֪ͨ����

	int							_nLength;						// ʱ��֡�̶ȵĳ���
	int							_nItemCount;					// ��Ԫ�������
	int							_nWidth;						// ��ͷ�͵�Ԫ��Ŀ��
	int							_nHeadHeight;					// ��ͷ�ĸ߶�
	int							_nCellHeight;					// ��Ԫ��ĸ߶�
	int							_nKeyFrameSpotSizePercent;		// �ؼ�֡���С�İٷֱ�

	int							_nCurrentFrameCol;				// ��ǰ֡���ڵ���
	bool						_bPressDownCurrentFrame;		// �Ƿ�ס��ǰ֡

	IMouseResponseJudgment*		_pMouseResponseJudgment;		// �����Ӧ�ж�
	int							_nSelRow;						// �����Ӧ�жϵ�ѡ����
	bool						_bResponseMoveKeyFrame;			// �Ƿ���Ӧ�ƶ��ؼ�֡

	COLORREF					_colorHead;						// ��ͷ����ɫ
	COLORREF					_colorTimePoint;				// ʱ�̵����ɫ
	COLORREF					_colorCurrentFrame;				// ��ǰ֡��ܵ���ɫ
	COLORREF					_colorCurrentFrameBack;			// ��ǰ֡������ɫ
	VecColor					_vecColorKeyFrame;				// �ؼ�֡����ɫ�б�
	VecColor					_vecColorTweenAnimation;		// ���䶯������ɫ�б�

	CRect						_rcHeadText;					// ��ͷʱ�̵�����
	int							_nHeadText;						// ��ͷ��ʾ����Ŀ�ʼʱ�̵��ı�

	int							_arrSelCellRowAndCol[2];		// ѡ�е�Ԫ�����(0)����(1)

	SetCollapseRow				_setCollapseRow;				// ����������
};
/*---------------------------------------------------------------------
*�ļ����ƣ�TimeLineTreeListCtrl.h
*����������ʱ����ؼ���Ҫ�����������б�ؼ�
*������ʶ��������2021.9.28.
*
*�޸ı�ʶ��
*�޸�������
----------------------------------------------------------------------*/
#pragma once

class CTimeLineTreeListCtrl :public CTreeListCtrl
{
public:
	CTimeLineTreeListCtrl(void);

protected:
	DECLARE_MESSAGE_MAP()

public:
	/*
	* �������ܣ���ȡ����Դ��ʶ��ؼ�����(��¼״̬����)
	* ���������void
	* ���������void
	* ����ֵ  ��ListDataSource ����Դ��ʶ��ؼ�����(��¼״̬����)
	*/
	ListDataSource GetListDataSource(void);

	/*
	* �������ܣ����¹�����
	* ���������int scrollMode ��Ҫ���µĹ�����
	* ���������void
	* ����ֵ  ��void
	*/
	virtual void UpdateScrollBar(int scrollMode = SB_HORZ) override;

	/*
	* �������ܣ�������
	* ���������CMemoryDC & dcMemory �ڴ�DC
	*			const CRect& rcHeader ��ͷ��������
	*			const CRect& rcList ��ȥ��ͷ�Ļ�������
	* ���������void
	* ����ֵ  ��void
	*/
	virtual void DrawRow(CMemoryDC& dcMemory, const CRect& rcHeader,
		const CRect& rcList) override;

public:
	/*
	* �������ܣ����ö�Ӧ��ʱ����ؼ��е��Ҳ�ʱ��֡�ؼ�
	* ���������CTimeFrameListCtrl *pTimeFrameCtrl ��Ӧ��ʱ����ؼ��е��Ҳ�ʱ��֡�ؼ�
	* ���������void
	* ����ֵ  ��void
	*/
	void SetCorrespondingTimeFrameCtrl(CTimeFrameListCtrl *pTimeFrameCtrl);

protected:
	//������������Ӧ�¼�
	void OnLButtonDown(UINT nFlags, CPoint point);
		
	/**
	*  @brief    �������Notify֪ͨ��Ϣ
	*
	*  @param    UINT nMessage ��ϢID
	*  @param    int nClickType ��� = 0���һ� = 1
	*  @param    int nCol �༭��
	*  @param    int nRow �༭��
	*  @param    HEDITCONFIG hEditCfg ��Ԫ����Ϣ
	*  @param    const CString&  strOldText �޸�ǰ��Ԫ���ı�
	*  @param    CString* pStrNewText �޸ĺ�Ԫ���ı�ָ��
	*  @return   LRESULT �¼�֪ͨ���
	*/
	LRESULT NotifyParent(UINT nMessage, int nCol = -1, int nRow = -1, HEDITCONFIG hEditCfg = NULL,
		const CString& strCellText = L"", CString* pStrNewText = NULL, int nClickType = 0);


protected:
	CTimeFrameListCtrl*				_pTimeLineCtrl;					// ��Ӧ��ʱ����ؼ��е��Ҳ�ʱ��֡�ؼ�
};
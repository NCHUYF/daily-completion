/*---------------------------------------------------------------------
*�ļ����ƣ�TimeLineSplitCtrl.h
*����������ʱ����ؼ���Ҫ��������ָ����ؼ�
*������ʶ��������2021.9.28.
*
*�޸ı�ʶ��
*�޸�������
----------------------------------------------------------------------*/
#pragma once

class CTimeLineSplitCtrl :public CSplitCtrl
{
public:
	CTimeLineSplitCtrl(void);

protected:
	DECLARE_MESSAGE_MAP()

public:
	/*
	* �������ܣ����¹�����
	* ���������void
	* ���������void
	* ����ֵ  ��void
	*/
	void UpdateScrollBar(void);

	/*
	* �������ܣ����ö�Ӧ��ʱ����ؼ��е��Ҳ�ʱ��֡�ؼ�
	* ���������CTimeFrameListCtrl *pTimeFrameCtrl ��Ӧ��ʱ����ؼ��е��Ҳ�ʱ��֡�ؼ�
	* ���������void
	* ����ֵ  ��void
	*/
	void SetCorrespondingTimeFrameCtrl(CTimeFrameListCtrl *pTimeFrameCtrl);

protected:
	//�����������Ӧ�¼�
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:
	CTimeFrameListCtrl*				_pTimeLineCtrl;					// ��Ӧ��ʱ����ؼ��е��Ҳ�ʱ��֡�ؼ�
};
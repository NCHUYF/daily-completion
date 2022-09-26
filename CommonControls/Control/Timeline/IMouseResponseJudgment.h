/*---------------------------------------------------------------------
*�ļ����ƣ�IMouseResponseJudgment.h
*���������������Ӧ�жϽӿ�
*������ʶ��������2021.10.11.
*
*�޸ı�ʶ��
*�޸�������
----------------------------------------------------------------------*/
#pragma once

class IMouseResponseJudgment
{
public:
	/*
	* �������ܣ���갴����Ӧ�жϣ��Ƿ�֧����ק
	* ���������ITimeLineCtrlDataSource *timeLineCtrlDataSource ������е�����Դ
	*			int nCol ���������
	* ���������void
	* ����ֵ  ��bool �Ƿ�֧����ק
	*/
	virtual bool BeginDrag(ITimeLineCtrlDataSource *timeLineCtrlDataSource, int nCol) = 0;

	/*
	* �������ܣ���굯����Ӧ�жϣ��Ƿ������ק
	* ���������ITimeLineCtrlDataSource *timeLineCtrlDataSource ������е�����Դ
	*			int nCol ����ƶ�������
	* ���������void
	* ����ֵ  ��void
	*/
	virtual void EndDrag(ITimeLineCtrlDataSource *timeLineCtrlDataSource, int nCol) = 0;
};
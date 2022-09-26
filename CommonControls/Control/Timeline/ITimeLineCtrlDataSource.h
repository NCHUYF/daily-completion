/*---------------------------------------------------------------------
*�ļ����ƣ�ITimeLineCtrlDataSource.h
*����������ʱ����ؼ�����Դ
*������ʶ��������2021.9.23.
*
*�޸ı�ʶ��
*�޸�������
----------------------------------------------------------------------*/
#pragma once

//ʱ��֡״̬
struct  TimeFrameStatus
{
	TimeFrameStatus(void)
	{
		bKeyFrame = false;
		bTweenAnimation = false;
	}

	bool bKeyFrame;						// �Ƿ�Ϊ�ؼ�֡
	bool bTweenAnimation;				// �Ƿ�Ϊ���䶯��
};
// ʱ��֡��Ϣ�б�(key ֵΪ��λ��������value ֵΪʱ��֡״̬)
typedef std::map<int, std::shared_ptr<TimeFrameStatus>> TimeFrameRowInfoMap;

typedef std::shared_ptr<TimeFrameRowInfoMap> TimeFrameRowInfoPtr;
typedef std::vector<TimeFrameRowInfoPtr> TimeFrameRowInfoPtrVec;
typedef std::map<int, TimeFrameRowInfoPtr> TimeFrameRowInfoPtrMap;	// key Ϊ��ǰͼ����λ������

class ITimeLineCtrlDataSource :public IListDataSource
{
	friend class CTimeLineCtrl;
public:
	virtual ~ITimeLineCtrlDataSource(void) {}

public:
	/*
	* �������ܣ���ȡʱ��֡����Ϣ�б�
	* ���������size_t nRow ��Ԫ��������
	* ���������void
	* ����ֵ  ��TimeFrameRowInfoMap ʱ��֡����Ϣ�б�
	*/
	virtual TimeFrameRowInfoMap& GetTimeFrameRowInfoMap() = 0;

	/*
	* �������ܣ�����ʱ��֡��Ϣ�б�
	* ���������size_t nRow ��Ԫ��������
	*			const TimeFrameRowInfoMap &timeFrameInfoMap �µ�ʱ��֡����Ϣ�б�
	* ���������void
	* ����ֵ  ��bool ����true���޸ĳɹ�
	*/
	virtual bool SetTimeFrameRowInfo(size_t nRow, const TimeFrameRowInfoMap &timeFrameRowInfoMap) = 0;
};
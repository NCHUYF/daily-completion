//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           CGanttNode.h
//    @author         �Ϸ�
//    @data           2020/12/28  
//    @brief          4D���Ƚڵ�
//
//*****************************************************
#pragma once

#define MERGE_COL_JHJD _T("�ƻ�����")
#define MERGE_COL_SJJD _T("ʵ�ʽ���")

#define COL_NAME _T("����")
#define COL_ANIMNAME _T("��������")
#define COL_PLAN_DURINGTIME _T("�ƻ�����ʱ��")
#define COL_PLAN_STARTTIME _T("�ƻ���ʼʱ��")
#define COL_PLAN_ENDTIME _T("�ƻ�����ʱ��")
#define COL_REAL_DURINGTIME _T("ʵ�ʳ���ʱ��")
#define COL_REAL_STARTTIME _T("ʵ�ʿ�ʼʱ��")
#define COL_REAL_ENDTIME _T("ʵ�ʽ���ʱ��")

#define COL_PLAN_PRIMARY_COLOR _T("�ƻ�δ�����ɫ")
#define COL_PLAN_FINISH_COLOR _T("�ƻ������ɫ")
#define COL_REAL_PRIMARY_COLOR _T("ʵ��δ�����ɫ")
#define COL_REAL_FINISH_COLOR _T("ʵ�������ɫ")

#define COL_GROWTH_PATTERN _T("������ʽ")
#define COL_MODEL_NUM _T("ģ������")
#define COL_OPERATION _T("����")

#define COL_LAYER _T("�㼶")

#define COL_PRETASK _T("ǰ������")
#define COL_RESOURCELIST _T("��Դ�б�")
#define COL_RESOURCEEFFECT _T("��Դ���")


#define GROWTH_BOTTOM2TOP	1
#define GROWTH_TOP2BOTTOM	2
#define GROWTH_LEFT2RIGHT	3
#define GROWTH_RIGHT2LEFT	4
#define GROWTH_MIDDLE2SIDES 5

#define OPERATION_RELEASEBIND _T("���")

#define STR_BOTTOM2TOP _T("��������")
#define STR_TOP2BOTTOM _T("��������")
#define STR_LEFT2RIGHT _T("��������")
#define STR_RIGHT2LEFT _T("��������")
#define STR_MIDDLE2SIDES _T("������������")

#define SAVE_FILE_NAME _T("ʩ�����ȷ�����¼.xml")

#define e4DProgressNode 40000

class COMMONCONTROLS_API CGanttNode : public PlatformKernel::BnsWrapper
{
public:
	CGanttNode() {};
	CGanttNode(KNode* pNode) : BnsWrapper(pNode)
	{
		VERIFY(pNode == nullptr || pNode->GetTag() == e4DProgressNode);
		_pNode = pNode;
	}
	virtual ~CGanttNode() {};

public:
	DefinePropertyT(Name, COL_NAME, CString);
	DefinePropertyT(PlanPrimaryColor, COL_PLAN_PRIMARY_COLOR, int);
	DefinePropertyT(PlanFinishColor, COL_PLAN_FINISH_COLOR, int);
	DefinePropertyT(RealPrimaryColor, COL_REAL_PRIMARY_COLOR, int);
	DefinePropertyT(RealFinishColor, COL_REAL_FINISH_COLOR, int);
	DefinePropertyT(GrowthPattern, COL_GROWTH_PATTERN, int);
	DefinePropertyT(ModelNum, COL_MODEL_NUM, int);
	DefinePropertyT(Operation, COL_OPERATION, CString);

	DefinePropertyT(PreTask, COL_PRETASK, CString);
	DefinePropertyT(ResourceList, COL_RESOURCELIST, CString);
	DefinePropertyT(ResourceEffect, COL_RESOURCEEFFECT, CString);

	virtual CString GetGrowthPatternString();

	// ����������ʽ
	virtual void SetGrowthPattern(const CString &strPattern);

	// ��ȡʵ�ʳ���ʱ��
	virtual int GetRealDuringTime() const
	{
		return (int)_pNode->GetData(COL_REAL_DURINGTIME);
	}

	// ����ʵ�ʳ���ʱ��
	virtual void SetRealDuringTime(int nDuring)
	{
		if (_pNode->HasData(COL_REAL_DURINGTIME) && nDuring == GetRealDuringTime())
			return;
		if (nDuring < 1)
		{
			nDuring = 1;
		}
		else if (nDuring > 9999)
		{
			nDuring = 9999;
		}
		_pNode->SetData(COL_REAL_DURINGTIME, nDuring);
		if(_pNode->HasData(COL_REAL_STARTTIME))
			SetRealEndTime(GetRealStartTime() + nDuring - 1);
	}

	// ��ȡ�ƻ�����ʱ��
	virtual int GetPlanDuringTime() const
	{
		return (int)_pNode->GetData(COL_PLAN_DURINGTIME);
	}

	// ���üƻ�����ʱ��
	virtual void SetPlanDuringTime(int nDuring)
	{
		if (_pNode->HasData(COL_PLAN_DURINGTIME) && nDuring == GetPlanDuringTime())
			return;
		if (nDuring < 1)
		{
			nDuring = 1;
		}
		else if (nDuring > 9999)
		{
			nDuring = 9999;
		}
		_pNode->SetData(COL_PLAN_DURINGTIME, nDuring);
		if (_pNode->HasData(COL_PLAN_STARTTIME))
			SetPlanEndTime(GetPlanStartTime() + nDuring - 1);
	}

	// ��ȡ�ƻ�����ʱ��
	virtual double GetPlanEndTime() const
	{
		return (double)_pNode->GetData(COL_PLAN_ENDTIME);
	}

	// ��ȡʵ�ʽ���ʱ��
	virtual double GetRealEndTime() const
	{
		return (double)_pNode->GetData(COL_REAL_ENDTIME);
	}

	// ��ȡ�ƻ���ʼʱ��
	virtual double GetPlanStartTime() const
	{
		return (double)_pNode->GetData(COL_PLAN_STARTTIME);
	}

	// ��ȡʵ�ʿ�ʼʱ��
	double GetRealStartTime() const 
	{
		return (double)_pNode->GetData(COL_REAL_STARTTIME);
	}

	// ���üƻ���ʼʱ��
	virtual void SetPlanStartTime(double datetime)
	{
		if (_pNode->HasData(COL_PLAN_STARTTIME) && (int)datetime == (int)GetPlanStartTime())
			return;
		if (_pNode->HasData(COL_PLAN_ENDTIME) && datetime < GetPlanEndTime() - 9999 + 1)
		{
			datetime = GetPlanEndTime() - 9999 + 1;
		}
		_pNode->SetData(COL_PLAN_STARTTIME, CDataConvert::FloatQuZheng(datetime));
		
		if (_pNode->HasData(COL_PLAN_DURINGTIME) && _pNode->HasData(COL_PLAN_ENDTIME) && datetime > GetPlanEndTime())
		{
			SetPlanEndTime(datetime + GetPlanDuringTime() - 1);
		}
		if(_pNode->HasData(COL_PLAN_STARTTIME) && _pNode->HasData(COL_PLAN_ENDTIME))
			SetPlanDuringTime(GetPlanEndTime() - GetPlanStartTime() + 1);
	}

	// ����ʵ�ʿ�ʼʱ��
	virtual void SetRealStartTime(double datetime)
	{
		if (_pNode->HasData(COL_REAL_STARTTIME) && (int)datetime == (int)GetRealStartTime())
			return;
		if (_pNode->HasData(COL_REAL_ENDTIME) && datetime < GetRealEndTime() - 9999 + 1)
		{
			datetime = GetRealEndTime() - 9999 + 1;
		}
		_pNode->SetData(COL_REAL_STARTTIME, CDataConvert::FloatQuZheng(datetime));
		
		if (_pNode->HasData(COL_REAL_DURINGTIME) && _pNode->HasData(COL_REAL_ENDTIME) && datetime > GetRealEndTime())
		{
			SetRealEndTime(datetime + GetRealDuringTime() - 1);
		}

		if (_pNode->HasData(COL_REAL_STARTTIME) && _pNode->HasData(COL_REAL_ENDTIME))
			SetRealDuringTime(GetRealEndTime() - GetRealStartTime() + 1);
	}

	// ���üƻ�����ʱ��
	virtual void SetPlanEndTime(double datetime)
	{
		if (_pNode->HasData(COL_PLAN_ENDTIME) && (int)datetime == (int)GetPlanEndTime())
			return;
		if (_pNode->HasData(COL_PLAN_STARTTIME) && _pNode->HasData(COL_PLAN_ENDTIME) && GetPlanEndTime() >= GetPlanStartTime() + 9999)
		{
			datetime = GetPlanStartTime() + 9999 - 1;
		}
		COleDateTime tempTime = datetime;
		tempTime.SetDateTime(tempTime.GetYear(), tempTime.GetMonth(), tempTime.GetDay(), 23, 59, 59);
		_pNode->SetData(COL_PLAN_ENDTIME, (double)tempTime);

		if (_pNode->HasData(COL_PLAN_STARTTIME) && _pNode->HasData(COL_PLAN_ENDTIME) && GetPlanEndTime() < GetPlanStartTime())
		{
			SetPlanStartTime(datetime - GetPlanDuringTime() + 1);
		}
		if(_pNode->HasData(COL_PLAN_STARTTIME) && _pNode->HasData(COL_PLAN_ENDTIME))
			SetPlanDuringTime(GetPlanEndTime() - GetPlanStartTime() + 1);
	}

	// ����ʵ�ʽ���ʱ��
	virtual void SetRealEndTime(double datetime)
	{
		if (_pNode->HasData(COL_REAL_ENDTIME) && (int)datetime == (int)GetRealEndTime())
			return;
		if (_pNode->HasData(COL_REAL_ENDTIME) && _pNode->HasData(COL_REAL_STARTTIME) && GetRealEndTime() >= GetRealStartTime() + 9999)
		{
			datetime = GetRealStartTime() + 9999 - 1;
		}
		COleDateTime tempTime = datetime;
		tempTime.SetDateTime(tempTime.GetYear(), tempTime.GetMonth(), tempTime.GetDay(), 23, 59, 59);
		_pNode->SetData(COL_REAL_ENDTIME, (double)tempTime);
	
		if (_pNode->HasData(COL_REAL_ENDTIME) && _pNode->HasData(COL_REAL_STARTTIME) && GetRealEndTime() < GetRealStartTime())
		{
			SetRealStartTime(datetime - GetRealDuringTime() + 1);
		}
	
		if(_pNode->HasData(COL_REAL_ENDTIME) && _pNode->HasData(COL_REAL_STARTTIME))
			SetRealDuringTime(GetRealEndTime() - GetRealStartTime() + 1);
	}




	// ��ȡ��ɼƻ��ٷֱ�
	virtual float GetPlanPercent(double curTime);

	// ��ȡ���ʵ�ʰٷֱ�
	virtual float GetRealPercent(double curTime);

	// �ƻ�ʵ��ʱ��ͳһ�޸Ľӿ�
	virtual void SetStartTime(double dStartTime);
	virtual void SetEndTime(double dEndTime);
	virtual void SetDuringTime(int nDuring);
	virtual double GetStartTime() const;
	virtual double GetEndTime() const;
	virtual int GetDuringTime() const;
};

//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           BwGanttItem.h
//    @author         yf
//    @data           2020/12/16  
//    @brief          ����ͼ�ؼ�Item
//
//*****************************************************

#pragma once

#include "BCGPGanttItem.h"

class COMMONCONTROLS_API CBwGanttItem : public CBCGPGanttItem
{
	friend class CBwGanttChart;

public:
	CBwGanttItem();

	COleDateTime   GetFinishTime() const
	{
		COleDateTime tempTime = m_dtFinish;
		tempTime.SetDateTime(tempTime.GetYear(), tempTime.GetMonth(), tempTime.GetDay(), 23, 59, 59);

		return tempTime;
	}

	// ���ʵ�ʿ�ʼʱ��
	COleDateTime   GetRealStartTime() const
	{
		return m_dtRealStart;
	}

	// ���ʵ�����ʱ��
	COleDateTime   GetRealFinishTime() const
	{
		COleDateTime tempTime = m_dtRealFinish;
		tempTime.SetDateTime(tempTime.GetYear(), tempTime.GetMonth(), tempTime.GetDay(), 23, 59, 59);

		return tempTime;
	}

	// ����ʵ�ʿ�ʼ����ʱ��
	void	SetRealInterval(COleDateTime dtRealStart, COleDateTime dtRealFinish);

	// ����ʵ��δ�����ɫ
	void	SetRealPrimaryColor(COLORREF clr);
	COLORREF GetRealPrimaryColor() const
	{
		return m_clrRealPrimaryColor;
	}

	// ����ʵ�������ɫ
	void	SetRealCompleteColor(COLORREF clr);
	COLORREF GetRealCompleteColor() const
	{
		return m_clrRealCompleteColor;
	}

	// ����ʵ�ʽ���
	void	SetRealProgress(double dPercents);
	double	GetRealProgress() const
	{
		return m_dProgress;
	}

	// ����������ʽ
	void SetGrowthPattern(const CString &strGrowthPattern);
	CString GetGrowthPattern() const
	{
		return m_strGrowthPattern;
	}

	// ���ð󶨽ڵ�
	void SetNode(KNode *pNode);
	
	// ��ȡ�󶨽ڵ�
	KNode *GetNode()
	{
		return m_pNode;
	}
protected:
	COleDateTime	m_dtRealStart;
	COleDateTime	m_dtRealFinish;
	COLORREF		m_clrRealPrimaryColor;
	COLORREF		m_clrRealCompleteColor;
	double			m_dRealProgress; // 0.0 .. 1.0
	CString			m_strGrowthPattern;
	KNode *			m_pNode;
};

//*****************************************************
//    
//    @copyright      ���������;
//    @version        v3.0
//    @file           ListDataTime.H
//    @author         mahaidong;
//    @date           2015/4/10 15:45
//    @brief          �б����ڱ༭��;
//*****************************************************

#pragma once

#include "EditBase.h"
#include "EditContainer.h"

namespace ControlUI
{
	/**
	*  @class    CListDataTime
	*
	*  @brief    �б����ڱ༭��
	*/
	class CListDataTime : public CDateTimeCtrl, public IEditBase
	{
		DECLARE_DYNAMIC(CListDataTime)

	public:
		CListDataTime();
		virtual ~CListDataTime();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/**
		*  @brief    �����ؼ�;
		*
		*  @param    CWnd * pParent �����ھ��;
		*  @param    CRect & rect ��������;
		*  @param    LPCTSTR sInitText Ĭ����ʾ�ı�;
		*  @param	 bool bAdd    �����µ���ʽ  ֧�� �������	  ��Ҫ��Ӵ�true
		*  @return   bool �����ɹ�����true�����򷵻�false;
		*/
		bool Create(CWnd* pParent, CRect& rect, LPCTSTR sInitText, bool bAdd = false);

		/**
		*  @brief    ȡ���༭
		*
		*/
		void CancelEdit();

	public:
		afx_msg void OnKillFocus(CWnd* pNewWnd);
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	protected:
		bool			_bCandel;	  ///< �Ƿ�ȡ��
		CEditContainer	_container;   ///< �߿�����
	};
}
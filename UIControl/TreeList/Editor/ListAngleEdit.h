//*****************************************************
//    
//    @copyright      ���������;
//    @version        v3.0
//    @file           ListAngleEdit.H
//    @author         mahaidong;
//    @date           2015/4/10 15:45
//    @brief          �б�Ƕȱ༭��;
//*****************************************************

#pragma once

#include "EditBase.h"

namespace ControlUI
{

	/**
	*  @class    CListAngleEdit
	*
	*  @brief    �б�Ƕȱ༭��
	*/
	class CListAngleEdit : public CAngleEdit, public IEditBase
	{
		DECLARE_DYNAMIC(CListAngleEdit)

	public:
		CListAngleEdit();
		virtual ~CListAngleEdit();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/**
		*  @brief    �����ؼ�;
		*
		*  @param    CWnd * pParent �����ھ��;
		*  @param    CRect & rect ��������;
		*  @param    LPCTSTR sInitText �����ƽǶ�;
		*  @return   bool �����ɹ�����true�����򷵻�false;
		*/
		bool Create(CWnd* pParent, CRect& rect, LPCTSTR sInitText);

	protected:
		/**
		*  @brief    ȡ���༭
		*
		*/
		void CancelEdit();

		/**
		*  @brief    �����༭
		*
		*/
		void EndEdit();

		/**
		*  @brief    ʧȥ�����¼�;
		*
		*/
		afx_msg void OnKillFocus(CWnd* pNewWnd);

		/**
		*  @brief    ���̰����¼�;
		*
		*/
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	protected:
		bool				_bCancel;		///< �Ƿ�ȡ��;
	};
}
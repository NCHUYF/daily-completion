//*****************************************************
//    
//    @copyright      ���������;
//    @version        v3.0
//    @file           ListEdit.H
//    @author         mahaidong;
//    @date           2015/4/10 15:45
//    @brief          �б��У����ı��༭��;
//*****************************************************

#pragma once

#include "EditBase.h"

namespace ControlUI
{
	/**
	*  @class    CListEdit
	*
	*  @brief    �б��У����ı��༭��
	*/
	class CListEdit : public CValidEdit, public IEditBase
	{
		DECLARE_DYNAMIC(CListEdit)

	public:
		CListEdit();
		virtual ~CListEdit();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/**
		*  @brief    �����ؼ�;
		*
		*  @param    CWnd * pParent �����ھ��;
		*  @param    CRect & rect ��������;
		*  @param    LPCTSTR sInitText Ĭ����ʾ�ı�;
		*  @param    bool bWordWrap �Ƿ���ʾ����;
		*  @return   bool �����ɹ�����true�����򷵻�false;
		*/
		bool Create(CWnd* pParent, CRect& rect,
			LPCTSTR sInitText, bool bWordWrap = false);

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
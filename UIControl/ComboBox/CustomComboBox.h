//********************************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           CCustomComboBox.H
//    @author         wuxuelong
//    @date           2016/4/29 10:01
//    @brief          �Զ���Combo�������ø����ڣ�
//*********************************************************************

#pragma once

namespace ControlUI
{
	class CONTROL_UI CCustomComboBox : public CAutoWidthComboBox
	{
		DECLARE_DYNAMIC(CCustomComboBox)

	public:
		CCustomComboBox();
		~CCustomComboBox();

		DECLARE_MESSAGE_MAP()

	public:

		/**
		*  @brief    ������Ϣ������
		*
		*  @param    CWnd * pParent
		*/
		void SetMsgParent(CWnd* pParent);

		virtual int SetItemData(int nIndex, const TCHAR* strData);

		virtual void MoveWindow(int x, int y, int nWidth, int nHeight,
			BOOL bRepaint = TRUE);
		virtual void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);

	protected:
		afx_msg void OnComboSelected();

	private:
		std::vector<TCHAR*>	_arrStrData;
		CWnd*	_pParent;		///< ������
	};
}
////*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           EditXpVer.H
//    @author         LOL
//    @date           2015/12/14 9:15
//    @brief          ���XP��֧��CueBanner�������Edit�ؼ�
//*****************************************************

#pragma once

namespace ControlUI
{
	/**
	*  @class    XP�����CEdit
	*
	*  @brief    ���XP��֧��CueBanner�������Edit�ؼ�
	*/
	class CONTROL_UI CEditXpVer : public CEdit
	{
		DECLARE_DYNAMIC(CEditXpVer)
	public:
		CEditXpVer();
		virtual ~CEditXpVer();

		/**
		*  @brief    ������ʾ��Ϣ
		*
		*  @param    const CString & ��ʾ����
		*  @return   void
		*/
		void SetBannerText(const CString& str);

		CString GetBannerText();

		void SetWindowText(LPCTSTR lpszString);
		void GetInputText(CString& strTemp);

	protected:
		DECLARE_MESSAGE_MAP()

	protected:
		afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
		afx_msg void OnKillFocus(CWnd* pNewWnd);
		afx_msg void OnSetFocus(CWnd* pOldWnd);

	private:
		void WhenOnFocus();
		void WhenKillFocus();
	private:
		TCHAR   _chPass;				///< ������ʾ��
		COLORREF m_crText;				///< ��ʾ�������ɫ
		CString _strBannerText;			///< ��ʾ����
	};
}
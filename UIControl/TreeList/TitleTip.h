//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           TitleTip.H
//    @author         jzl
//    @data           2015/7/15 19:25
//    @brief          ������ʾ�ؼ�
//*****************************************************

#pragma once

namespace ControlUI
{
	/**
	*  @class    ������ʾ�ؼ���
	*
	*  @brief
	*/
	class CONTROL_UI CTitleTip : public CStatic
	{
	public:
		CTitleTip();
		~CTitleTip();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/**
		*  @brief    �����ؼ�
		*
		*  @return   bool �ɹ�����TRUE
		*/
		bool Create(CWnd* pParentWnd, CFont* pFont);

		/**
		*  @brief    ������ɫ
		*
		*/
		void SetColor(COLORREF clrBack, COLORREF clrBorder);

		/**
		*  @brief    �����ı�����ģʽ
		*
		*/
		void SetTextMode(int nTextMode);

		/**
		*  @brief    ������ʾ�ı�
		*
		*/
		void SetTipText(const CString& strTipText);

		/**
		*  @brief    ���ü������
		*
		*/
		void SetRect(CRect rcMonitor, CRect rcWnd);

		/*@brief    �����Ƿ���ɫ�ı�
		*
		*/
		void SetClrText(bool bClrText);

		/**
		*  @brief    ������ʾ��ʾ
		*
		*/
		void RelayEvent(PMSG pMsg);

		/**
		*  @brief    ������ʾ��Ϣ
		*
		*/
		void Reset();

	public:
		void OnPaint();
		BOOL OnEraseBkgnd(CDC* pDC);

	private:
		bool _bShow; ///< �Ƿ���ʾ
		CFont* _pFont; ///< ����
		CRect _rcMonitor; ///< ��������
		CRect _rcWnd;	///< �ؼ�����
		int _nTextMode; ///< ���ָ�ʽ
		bool _bClrText;	///< �Ƿ����ɫ�ı�
		CWnd* _pParent; ///< ���״���
		COLORREF _clrBack;	///< ����ɫ
		COLORREF _clrBorder; ///< �߿���ɫ
		CString _strTipText;	///< ��ʾ�ı�
	};
}
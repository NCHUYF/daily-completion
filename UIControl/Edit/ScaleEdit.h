//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           ScaleEdit.H
//    @author         zxw
//    @date           2015/10/15 17:50
//    @brief          �������༭��ؼ�(���У�)
//*****************************************************

#pragma once

namespace ControlUI
{
	/**
	*  @class    �����༭��ؼ���
	*
	*  @brief
	*/
	class CONTROL_UI CScaleEdit : public CEdit
	{
		DECLARE_DYNAMIC(CScaleEdit)
	public:
		CScaleEdit();
		virtual ~CScaleEdit();

	protected:
		DECLARE_MESSAGE_MAP()
	private:
		/**
		*  @brief    ����ɾ���ַ��߼�
		*
		*  @return   BOOL �ɹ�����TRUE
		*/
		BOOL ProcessDelChart();

		/**
		*  @brief    ���������ȷ��
		*
		*  @param    TCHAR inChar ��ǰ������ַ�
		*  @return   BOOL ������Ч����TRUE
		*/
		BOOL ValidateInput();

		/**
		*  @brief    ��������Ƿ���ȷ
		*
		*  @return	 bool �ɹ�����true
		*/
		bool CheckInvaildate();

		/*
		*  @brief    �ж������Ƿ���ȷ
		*
		*/
		virtual bool IsDigitValidate(CString strTex);

		/*
		*  @brief    �ж������Ƿ�������
		*
		*  @param	 const CString& strText  ����ı�
		*/
		virtual bool IsDigit(const CString& strText);

	public:
		afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	};
}
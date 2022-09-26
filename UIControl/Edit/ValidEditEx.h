//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           ValidEdit.H
//    @author         KG
//    @date           2015/3/7 10:41
//    @brief          У��༭�ؼ�
//*****************************************************

#pragma once

namespace ControlUI
{
	/**
	*  @class    У��༭�ؼ�
	*
	*  @brief
	*/
	class CONTROL_UI CValidEditEx : public CValidEdit
	{
	public:
		CValidEditEx();
		virtual ~CValidEditEx();

		/**
		*  @brief    ���������С����ֵ
		*
		*  @param	 double dblMax  ���ֵ
		*  @param	 double dblMin  ��Сֵ
		*  @param	 bMaxEnabled �Ƿ������������ֵ
		*  @param	 bMinEnabled �Ƿ�����������Сֵ
		*/
		void SetMaxMinValueValidate(double dblMax, double dblMin, bool bMaxEnabled = false, bool bMinEnabled = false);

		bool ValidateMaxMinValue();

	protected:
		DECLARE_MESSAGE_MAP()

		/**
		*  @brief    ʧȥ����
		*
		*  @param    CWnd * pNewWnd
		*  @return   void
		*/
		virtual void OnKillFocus(CWnd* pNewWnd);

	private:
		double				_dMaxValue;		///< ���ֵ 
		double				_dMinValue;		///< ��Сֵ
		bool				_bMaxEnabled;	///< �Ƿ������������ֵ
		bool				_bMinEnabled;	///< �Ƿ�����������Сֵ
	};
}
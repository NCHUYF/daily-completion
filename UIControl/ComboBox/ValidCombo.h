//********************************************
//
//	@copyright		������΢�¼������޹�˾
//	@file			ValidCombo.h
//	@author			����ǿ
//	@date			2019/6/6 8:30
//	@brief		    �ɱ༭У��������
//********************************************
#pragma once
namespace ControlUI
{
	class CONTROL_UI CValidCombo : public CAutoWidthComboBox
	{
		DECLARE_DYNAMIC(CValidCombo)
	public:
		CValidCombo();
	public:
		DECLARE_MESSAGE_MAP()
		
	public:
		/**
		*  @brief    ���ñ༭��־

		*  @param	 int flag	��־
		*/
		void SetEditFlag(int nFlag);

		/**
		* @brief ����С����λ��
		*
		* @param int nDotNum
		*
		* @return void
		*/
		void SetDotNum(int nDotNum);

		/**
		*  @brief    ��ȡ�༭��־

		*  @param	 int flag	��־
		*/
		int GetEditFlag() { return _nFlag; }

		/**
		*  @brief    ����ð����ʾ

		*  @param	 int flag	��־
		*/
		void DisableTip(bool bDisable) { 
			if (m_edit.GetSafeHwnd())
				m_edit.DisableTip(true);
		}

		/**
		*  @brief    �Ƿ�������ʾ��ʾ

		*  @param	 int flag	��־
		*/
		bool IsShowingTip() { 
			if (m_edit.GetSafeHwnd())
				return m_edit.IsShowingTip();
			else
				return false;
			}

		/**
		*  @brief    ��������ֵ�Ƿ���ȷ
		*/
		bool Validate() { 
			if (m_edit.GetSafeHwnd())
				return m_edit.Validate();
			else
				return true;
		}

	protected:
		afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		afx_msg void OnDestroy();

	private:
		CValidEditEx      m_edit;
		CListBox   m_listbox;
		int _nFlag;
		int _nDotNum;
	};
}

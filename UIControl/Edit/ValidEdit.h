//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           ValidEdit.H
//    @author         KG
//    @date           2015/3/7 10:41
//    @brief          У��༭�ؼ�
//*****************************************************

namespace ControlUI
{
#pragma once

	/**
	*  @class    У��༭�ؼ�
	*
	*  @brief
	*/
	class CONTROL_UI CValidEdit : public CEdit
	{
		DECLARE_DYNAMIC(CValidEdit)
	public:
		CValidEdit();
		virtual ~CValidEdit();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/**
		*  @brief    ��������Ƿ�Ϸ�(����Ƿ������)
		*
		*  @return	 bool ����Ϸ�����true
		*  @remark	 ������eValidEditNoZero��eValidEditFileNameʱ
		*			 ��Ҫ�ڴ��ڹر�ʱ���ý��м�⣬�������false����Ҫȡ���رմ���
		*/
		bool Validate();

		/**
		*  @brief    ���ñ༭��־

		*  @param	 int flag	��־
		*/
		void SetEditFlag(int nFlag);

		/**
		*  @brief    ����С��λ��
		*
		*  @param	 int nDotNum  С��λ��
		*/
		void SetDotNum(int nDotNum);

		/**
		*  @brief    ������ʾ��Ϣ
		*
		*/
		void ShowBalloonTip(const CString& strTitle,
			const CString& strContent, int tipIcon = TTI_INFO, DWORD dwTimeOut = 0);

		/**
		*  @brief    ������ʾ����
		*
		*/
		void SetTitleAndContent(const CString& strTitle, const CString& strContent) 
		{ 
			_strTitle = strTitle;
			_strContent = strContent;
		};

		/**
		*  @brief    ���������С����ֵ
		*
		*  @param	 double dblMax  �������ֵ
		*  @param	 double dblMin  ������Сֵ
		*  @param	 bool bShowLimitTip  �Ƿ���ʾ��Χ��ʾ��Ϣ
		*/
		void SetMaxMinValue(double dblMax, double dblMin, bool bShowLimitTip);

		/**
		*  @brief    ����Լ������
		*
		*  @param    const CString & strConstraint Լ������(�߼����ʽ)
		*  @param	 bool bShowLimitTip  �Ƿ���ʾ��Χ��ʾ��Ϣ
		*/
		void SetConstraint(const CString& strConstraint, bool bShowLimitTip);

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
			if (_bIsShowingTip)
			{
				_bIsShowingTip = false;
				Edit_HideBalloonTip(m_hWnd);
			}
			_bDisableTip = bDisable; 
		}

		/**
		*  @brief    �Ƿ�������ʾ��ʾ

		*  @param	 int flag	��־
		*/
		bool IsShowingTip() { return _bIsShowingTip; }

	protected:
		/**
		*  @brief    ��WM_PASTE��Ϣ��Ӧ����
		*/
		LRESULT OnPaste(WPARAM wParam, LPARAM lParam);

		/**
		*  @brief    ��WM_CHAR��Ϣ��Ӧ����
		*/
		LRESULT OnChar(WPARAM wParam, LPARAM lParam);

		/**
		*  @brief    ��ʱ��
		*/
		void OnTimer(UINT_PTR timer);

		/*
		*  @brief    �ж������Ƿ�������
		*
		*  @param	 const CString& strText  ����ı�
		*/
		virtual bool IsDigit(const CString& strText);

		/*
		*  @brief    �ж������Ƿ���ȷ
		*
		*  @param	 bool bRound  �Ƿ���������
		*/
		virtual bool IsDigitValidate(bool bRound = false);

		/**
		*  @brief    �ж������ֵ�Ƿ�������ķ�Χ�ڣ�������������ʾ
		*
		*  @return   bool �ڷ�Χ�ڷ���true�����򷵻�false
		*/
		virtual bool InRange();

		/*
		*  @brief    �ж��ļ����Ƿ�Ϸ�
		*
		*/
		virtual bool IsFileNameValidate();

		/**
		*  @brief    ��������Ƿ���ȷ
		*
		*  @param	 bool bRound  �Ƿ���������
		*  @return	 bool �ɹ�����true
		*/
		bool CheckInvaildate(bool bRound = false);

	protected:
		bool				_bInPaste;		///< �Ƿ�����ճ��
		int					_nFlag;			///< ���Ʊ��
		int					_dotNum;		///< ��������С��λ��
		double				_maxValue;		///< �����������ֵ 
		double				_minValue;		///< ����������Сֵ
		bool				_bShowLimitTip;	///< �Ƿ���ʾ��ֵ������ʾ
		bool				_bDisableTip;	///< ������ʾ��Ϣ
		bool				_bIsShowingTip;	///< �Ƿ�������ʾ��ʾ
		CString				_strConstraint;	///< Լ������
		CString				_strTitle;		///< ����
		CString				_strContent;	///< ����
	};
}
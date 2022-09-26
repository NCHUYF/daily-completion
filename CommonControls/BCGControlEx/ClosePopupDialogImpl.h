//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�ClosePopupDialogImpl.h
// �������������������������ؼ�����
// ������ʶ��������	2018\09\29
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////
#pragma once


/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! ���������������ؼ�����
		class CONTROLSAPI_EXPORT CClosePopupDialogImpl
		{
		public:
			controls::CClosePopupDialogImpl();
			~CClosePopupDialogImpl();

		public:
			/**
			* �ж��Ƿ����Ӵ���
			* @return ��:����TRUE
			*/
			BOOL IsHaveChildDlg() const;

			/**
			* ����Ӵ���
			* @param [in] bHaveChildDlg �Ӵ��ڱ��
			*/
			void SetChildDlg(BOOL bHaveChildDlg);

			/**
			* �رյ�������
			* @param [in] lpszEditValue �ؼ��ı�
			* @param [in] bOK			�ؼ��ı�
			* @param [in] dwUserData	������
			*/
			virtual void ClosePopupDlg(LPCTSTR lpszEditValue,
				BOOL		bOK,
				DWORD_PTR dwUserData);

			/**
			* ��ȡ���ؼ��ı�
			* @return ���ؼ��ı�
			*/
			virtual CString GetParentText() { return _T(""); }

			/**
			* ���ø��ؼ��ı�
			* @param [in] strText �ؼ��ı�
			* @return
			*/
			virtual void SetParentText(const CString& strText) { }

		protected:
			BOOL					_bHaveChildDlg;			// �Ƿ����ӶԻ���
		};
		/** * @} */
	}
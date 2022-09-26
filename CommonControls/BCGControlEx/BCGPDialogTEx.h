//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�BCGPDialogTEx.h
// �����������Ի��������չ��
// ������ʶ��������	2018\08\22
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////
#pragma once
#include "BCGPDialog.h"

#include "ClosePopupDialogImpl.h"

/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! BCGP�Ի��������չ
		class CONTROLSAPI_EXPORT CBCGPDialogTEx : public CBCGPDialog
		{
			DECLARE_DYNCREATE(CBCGPDialogTEx)

		public:
			controls::CBCGPDialogTEx();

			controls::CBCGPDialogTEx(UINT nIDTemplate, CWnd *pParent = NULL);

			controls::CBCGPDialogTEx(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);

		public:
			controls::CClosePopupDialogImpl* _pParentCtl;		//�����ؼ���Ϣ

		protected:
			afx_msg void OnDestroy();
			DECLARE_MESSAGE_MAP()
		};
		/** * @} */
	}
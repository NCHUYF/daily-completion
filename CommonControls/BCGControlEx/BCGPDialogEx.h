//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�BCGPDialogEx.h
// �����������Ի�����չ��
// ������ʶ��������	2018\08\22
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////
#pragma once
#include "BCGPDialog.h"

/** @addtogroup Controls
* @{
*/
	namespace controls {
		HMODULE GetSelfModuleHandle();

		class CChangeModule
		{
		public:
			CChangeModule();
			~CChangeModule();
		private:
			HINSTANCE _hInstance;
		};

		//! BCGP�Ի�����չ
		class CBCGPDialogEx : public CBCGPDialog
		{
			DECLARE_DYNCREATE(CBCGPDialogEx)
		public:
			controls::CBCGPDialogEx();

			controls::CBCGPDialogEx(UINT nIDTemplate, CWnd *pParent = NULL);

			controls::CBCGPDialogEx(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);

		public:
			BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd);
		};
		/** * @} */
	}
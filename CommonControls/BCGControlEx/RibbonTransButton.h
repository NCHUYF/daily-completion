//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�RibbonTransButton.h
// ����������͸���Ȳ˵���ť
// ������ʶ�������� 2018/12/10
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////
#pragma once
#include "ControlsExportDef.h"
#include "BCGPRibbonComboBox.h"

/** @addtogroup Controls
* @{
*/
namespace controls {

	//! ͸���Ȳ˵���ť
	class CONTROLSAPI_EXPORT CRibbonTransButton : public CBCGPRibbonComboBox
	{
		DECLARE_DYNCREATE(CRibbonTransButton)
	public:
		controls::CRibbonTransButton(UINT nID, const CString& strText, BOOL bHasEditBox = TRUE,
			int nWidth = -1, LPCTSTR lpszLabel = NULL, int nImage = -1,
			BCGP_RIBBON_COMBO_SORT_ORDER sortOrder = BCGP_RIBBON_COMBO_SORT_ORDER_NO_SORT);

		virtual ~CRibbonTransButton();

	public:
		controls::CRibbonTransButton();

	public:
		/**
		* �����ı���Ϣ
		* @param [in] strText �ı���Ϣ
		*/
		void SetText(const CString& strText);

		/**
		* ��ȡ�ı�
		* @param [in] strText �ı���Ϣ
		*/
		CString GetText() const;

	protected:
		/**
		* ���ƿؼ�
		* @param [in] pDC �豸������
		*/
		virtual void OnDraw(CDC* pDC);

		/**
		* �������
		* @param [in] point �����λ��
		*/
		virtual void OnLButtonDown(CPoint point);

	protected:
		CString		_strText;		// �ı�
	};
	/** * @} */
}
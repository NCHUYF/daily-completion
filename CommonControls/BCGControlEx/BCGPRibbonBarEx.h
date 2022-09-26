/*******************************************************************
* �ļ����ƣ�BCGPRibbonBarEx.h
* ����������������
* �ļ�������RibbonBar��չ��
* ����汾��
* ����ʱ�䣺2018-5-31
* Copyright (C) ������΢�¼������޹�˾ All rights reserved
*******************************************************************/
#pragma once

#include "BCGPRibbonBar.h"

class CBCGPBaseRibbonElement;
class CBCGPRibbonMainPanelEx;
/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! BCGP�������ؼ���չ
		class CONTROLSAPI_EXPORT CBCGPRibbonBarEx : public CBCGPRibbonBar
		{	
		public:
			controls::CBCGPRibbonBarEx();
			~CBCGPRibbonBarEx();

		public:
			/**
			* ��ʾ�Զ�������ڲ˵�
			* @param [in] pWnd  ���ڶ���
			* @param [in] x		�˵���ʾλ�õ�x����
			* @param [in] y		�˵���ʾλ�õ�y����
			* @param [in] pHit  Ribbon�ؼ�����
			* @return
			*/
			virtual BOOL OnShowRibbonContextMenu(CWnd *pWnd, int x, int y,
				CBCGPBaseRibbonElement *pHit);

			CBCGPRibbonMainPanelEx* AddMainCategoryEx(
				LPCTSTR		lpszName,
				UINT		uiSmallImagesResID,
				UINT		uiLargeImagesResID,
				CSize		sizeSmallImage = CSize(16, 16),
				CSize		sizeLargeImage = CSize(32, 32),
				CRuntimeClass*	pRTI = NULL);

			void SetmAutoDestroy(BOOL bAutoDestory);

			BOOL GetBackstageMode()
			{
				return m_bBackstageMode;
			}

			BOOL GetPrintPreviewMode()
			{
				return m_bPrintPreviewMode;
			}

			BOOL OnBeforeShowBackstageViewEx()
			{
				return OnBeforeShowBackstageView();
			}

			BOOL OnBeforeShowMainPanelEx()
			{
				return OnBeforeShowMainPanel();
			}

			virtual void RecalcLayout();
		};
		/** * @} */
	}
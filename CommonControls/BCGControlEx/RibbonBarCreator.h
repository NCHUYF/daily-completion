/*******************************************************************
* �ļ����ƣ�ControlsCreator.h
* ����������������
* �ļ������������Զ���ؼ�
* ����汾��
* ����ʱ�䣺2018-4-16
* Copyright (C) ������΢�¼������޹�˾ All rights reserved
*******************************************************************/

#pragma once
#include <vector>
#include "ControlsExportDef.h"
#include "BCGPRibbonInfo.h"

class CBCGPRibbonBar;

/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! �����Զ���ؼ�
		class CONTROLSAPI_EXPORT CRibbonBarCreator
		{
		public:
			/**
			* ���ؿؼ���Ϣ
			* @param [in] lpszFileName	��Դ·��
			* @param [in] pBar			RibbonBar
			* @return ���سɹ�����TRUE
			*/
			static  BOOL LoadFromResPath(LPCTSTR lpszFileName, CBCGPRibbonBar *pBar);
		};
		/** * @} */
	}
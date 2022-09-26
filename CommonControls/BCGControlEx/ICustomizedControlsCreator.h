/*******************************************************************
* �ļ����ƣ�ICustomizedControlsCreator.h
* ����������������
* �ļ��������Զ���ؼ��������ӿ�
* ����汾��
* ����ʱ�䣺2018-4-16
* Copyright (C) ������΢�¼������޹�˾ All rights reserved
*******************************************************************/

#pragma once
#include <atlstr.h>
#include "ControlsExportDef.h"
#include "BCGPRibbonInfo.h"
class CBCGPBaseRibbonElement;

// �Զ��ؼ�����������
class CBCGPRibbonConstructorEx;

/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! �Զ��ؼ�����������
		class CONTROLSAPI_EXPORT ICustomizedControlCreator
		{
		public:
			virtual ~ICustomizedControlCreator() {};

		public:
			/**
			* �����ؼ�
			* @param [in] strCustomizedDefine	�ؼ���Ϣ
			* @return CBCGPBaseRibbonElement* Ribbon�ؼ�
			*/
			virtual CBCGPBaseRibbonElement* CreateControl(const CBCGPRibbonInfo::XElement& info, CBCGPRibbonConstructorEx *pConstructor) = 0;
		};
		/** * @} */
	}
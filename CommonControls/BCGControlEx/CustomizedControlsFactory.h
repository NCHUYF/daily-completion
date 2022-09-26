/*******************************************************************
* �ļ����ƣ�CustomizedControlsFactory.h
* ����������������
* �ļ��������Զ���ؼ�����
* ����汾��
* ����ʱ�䣺2018-4-17
* Copyright (C) ������΢�¼������޹�˾ All rights reserved
*******************************************************************/

#pragma once

#include <map>
#include "ControlsExportDef.h"


/** @addtogroup Controls
* @{
*/
	namespace controls {
		class ICustomizedControlCreator;

		typedef std::map<CString, controls::ICustomizedControlCreator*> MapControlCreator;

		//! �Զ���ؼ�����
		class CONTROLSAPI_EXPORT CCustomizedControlFactory
		{
		public:
			controls::CCustomizedControlFactory();
			virtual ~CCustomizedControlFactory();

			/**
			* ���������ʵ��
			*/
			static controls::CCustomizedControlFactory* GetInstance();

			/**
			* �������
			* @return
			*/
			static void ClearData();
		public:

			/**
			* ��ȡ�Զ���ؼ�������
			* @param [in] strElemName �Զ���ؼ���
			* @return �����Զ���ؼ�������
			*/
			controls::ICustomizedControlCreator* GetCustomizedControlCreator(const CString& cstrElemName);

			/**
			* ע���Զ���ؼ�������
			* @param [in] strElemName �Զ���ؼ���
			* @param [in] pControlCreator �Զ���ؼ�������
			*/
			void RegCustomizedControlCreator(const CString& cstrElemName, controls::ICustomizedControlCreator* pControlCreator);

		private:
			static controls::CCustomizedControlFactory* _pCustomizedControlFactory;	// ��������ϵ���
			MapControlCreator m_mapControlCreator;							// �ؼ�������Map
		};
		/** * @} */
	}
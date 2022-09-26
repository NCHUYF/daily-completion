/*******************************************************************
* �ļ����ƣ�BCGPComboBoxEx.h
* ����������������
* �ļ�������BCGPComboBox����չ��
* ����汾��
* ����ʱ�䣺2018-6-8
* Copyright (C) ������΢�¼������޹�˾ All rights reserved
*******************************************************************/
#pragma once

#include "BCGPComboBox.h"


/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! BCGP��������չ
		class CONTROLSAPI_EXPORT CBCGPComboBoxEx : public CBCGPComboBox
		{
		public:
			controls::CBCGPComboBoxEx();
			virtual ~CBCGPComboBoxEx();

		public:
			/**
			* ����������
			* @param [in] lpDIS	�Ի�ؼ���Ϣ
			* @return
			*/
			virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

			/**
			* ���ڵ���Ϣ
			* @param [in] message ָ����Ϣ���͡�
			* @param [in] wParam  ָ������ġ���Ϣ�ض�����Ϣ���ò�����������message����ֵ�йء�
			* @param [in] IParam  ָ������ġ���Ϣ�ض�����Ϣ���ò�����������message����ֵ�йء�
			* ����ֵ������ֵ������Ϣ�����������뷢�͵���Ϣ�йء�
			*/
			virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

			/**
			* ����ĳ�в��ɵ��
			* @param [in] nRowIndex	������
			* @return
			*/
			void SetEnable(int nRowIndex);

			/**
			* ����Comboxʹ�õĵط�(Ŀǰд����1Ϊ������ʹ�õ�Combox,2Ϊ���ٷ�����ʹ�õ�Combox)
			* @param [in] nType
			* @return
			*/
			void SetEnableType(int nType);
		private:
			int _nIndex;			// ��ǰѡ�е���
			int _nEnableIndex;		// ���ɵ����������
			int _nType;				// ����(Ŀǰд����1Ϊ������ʹ�õ�Combox,2Ϊ���ٷ�����ʹ�õ�Combox)
		};
		/** * @} */
	}
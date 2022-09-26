/*******************************************************************
* �ļ����ƣ�BCGPSplitterWndEx.h
* ����������������
* �ļ��������ָ����չ��
* ����汾��
* ����ʱ�䣺2018-5-28
* Copyright (C) ������΢�¼������޹�˾ All rights reserved
*******************************************************************/
#pragma once
#include <afxext.h>
#include "BCGPSplitterWnd.h"


/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! BCGP�ָ����չ
		class CONTROLSAPI_EXPORT CBCGPSplitterWndEx : public  CBCGPSplitterWnd
		{
		public:
			controls::CBCGPSplitterWndEx() {}
			virtual ~CBCGPSplitterWndEx() {}

		public:
			/**
			* ���ش�����Ϣ
			* @param [in] pMsg ��Ϣ��Ϣ
			* @return
			*/
			virtual BOOL PreTranslateMessage(MSG* pMsg);

			virtual void StartTracking(int ht);

			void StopTracking(BOOL bAccept);
		protected:
			/**
			* ����ؼ�֪ͨ����Ϣӳ��
			* @param [in] wParam ָ������ġ���Ϣ�ض�����Ϣ
			* @param [in] lParam ָ������ġ���Ϣ�ض�����Ϣ
			* @param [in] pResult
			* @return
			*/
			virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
			virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
		protected:
			/**
			* �ָ���е����Կ��ĳ������ֵ�����仯
			* @param [in] wParam	ָ������ġ���Ϣ�ض�����Ϣ
			* @param [in] lParam	ָ������ġ���Ϣ�ض�����Ϣ
			* @return ����ֵ������Ϣ�����������뷢�͵���Ϣ�й�
			*/
			afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnGridDBLClick(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnEndLabelEdit(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnBeginLabelEdit(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnGridItemChange(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnGridSelectChange(WPARAM wParam, LPARAM lParam);
			DECLARE_MESSAGE_MAP()
		};
		/** * @} */
	}
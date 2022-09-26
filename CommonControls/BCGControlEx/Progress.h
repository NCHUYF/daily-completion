#pragma once
/*******************************************************************
* �ļ����ƣ�Progress.h
* ������������Ѷ�
* �ļ����������ȶԻ���
* ����汾��
* ����ʱ�䣺2018-9-18
* Copyright (C) ������΢�¼������޹�˾ All rights reserved
*******************************************************************/

#include "ProductSDK.h"
#include <spring\commkit\TimeTrigger.h>
#include "ControlsExportDef.h"
#include <Toolkit\include\IProgressEvent.h>


class ITaskThread;

/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! ���ȶԻ���
		class CONTROLSAPI_EXPORT CProgress : public CDialog, public toolkit::deskface::IProgressEvent, public spring::commkit::ITimeListenner
		{
		public:
			/**
			* ���캯��
			* @param [in]		thread		����ִ���߳�
			* @param [in]		pParent		��������
			*/
			controls::CProgress(toolkit::deskface::ITaskThread* thread, CString strTaskName, CWnd* pParent = NULL);

			/**
			* ��������
			*/
			virtual ~CProgress();

		protected:
			void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
			BOOL OnInitDialog();

			virtual BOOL PreTranslateMessage(MSG* pMsg);

		public:
			/**
			* ʱ��ѭ��
			*/
			void OnTime();

			/**
			* ���ȿ�ʼ
			* @param [in]		strTask			��������
			* @param [in]		iStepMax		�������ֵ
			*/
			void Begin(LPCTSTR strTask, int iStepMax);

			/**
			* ���Ƚ���
			*/
			void End();

			/**
			* �������ӣ�Ĭ��һ����λֵ1��
			* @param [in]		strMsg= NULL	��������
			*/
			void Step(LPCTSTR strMsg = NULL);

			/**
			* ��������iPos��ֵ
			* @param [in]		iPos			����ֵ
			* @param [in]		strMsg = NULL	��������
			*/
			void StepAt(int iPos, LPCTSTR strMsg /*= NULL*/);

			/**
			* ����һ���߶��ľ���
			* @param [in] nSize
			*/
			void SetStepSize(int iSize);

			/**
			* �رս������ؼ�
			*/
			void Close();

			/**
			* ��ʾ�Ի���
			* @param [in] thread ����ֵ
			* @param [in] strTaskName ��������
			*/
			static void ShowDalog(toolkit::deskface::ITaskThread* thread, CString strTaskName, CWnd* parent = nullptr);

		protected:
			CProgressCtrl						_ProgressBar;		// �������ؼ�
			CStatic								_TaskMsgCtrl;		// ����������ʾ��ǩ
			spring::commkit::CTimeTrigger		_Timer;				// ʱ��ѭ��������
			toolkit::deskface::ITaskThread*		_TaskThread;		// ����ִ���߳�
			int									_iStep;				// һ������
			CString								_strTaskName;		// ��������
			CString								_strLastMsg;		// ��һ����Ϣ
		};
		/** * @} */
	}
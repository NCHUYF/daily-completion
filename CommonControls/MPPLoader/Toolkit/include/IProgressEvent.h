//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�ProgressEvent.h
// �����������������¼�
// ������ʶ��������	2018.09.17
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////

#pragma once

#include "ProductSDK.h"

namespace toolkit {
	namespace deskface {

		/** @addtogroup Toolkit
		* @{
		*/
		//! �������¼�
		class IProgressEvent
		{
		public:
			~IProgressEvent() {}

			/**
			* ���ȿ�ʼ
			* @param [in] task	��������
			* @param [in] StepMax	�������ֵ
			*/
			virtual void Begin(LPCTSTR strTask, int nStepMax) {}

			/**
			* ���Ƚ���
			*/
			virtual void End(void) {}

			/**
			* �������ӣ�Ĭ��һ����λֵ1��
			* @param [in] strMsg = NULL
			*/
			virtual void Step(LPCTSTR strMsg = NULL) {}

			/**
			* ��������nPos��ֵ
			* @param [in] nPos	����ֵ
			* @param [in] strMsg = NULL ��������
			*/
			virtual void StepAt(int nPos, LPCTSTR strMsg = NULL) {}

			/**
			* ����һ���߶��ľ���
			* @param [in] nSize
			*/
			virtual void SetStepSize(int nSize) = 0;
		};/** * @} */

		/** @addtogroup Toolkit
		* @{
		*/
		//! �����߳�
		class ITaskThread : public spring::commkit::CThreadImpl<ITaskThread>
		{
		public:
			virtual ~ITaskThread() {}

			/**
			* ִ��
			*/
			virtual DWORD Run(void) = 0;

			/**
			* ��ȡ������Ϣ
			*/
			virtual LPCTSTR GetLastError(void) = 0;

			/**
			* �����б�
			* @param [in out] �����б�
			*/
			virtual void GetErrorList(std::vector<LPCTSTR> &errList) {}

			/**
			* ʱ������(����ʵ���Զ��߽����������Ҫʵ��ʵ�ʽ��Ȳ�ʵ�ִ˷������ɣ�
			*/
			virtual void TimeTick(void) {};

			/**
			* ��ȡ�����¼�
			* return �����¼�����
			*/
			virtual IProgressEvent *GetProgressEvent() = 0;

			/**
			* ���ý����¼�
			* @param [in] p �����¼�����
			*/
			virtual void SetProgressEvent(IProgressEvent *p) = 0;
		};/** * @} */




	}
}

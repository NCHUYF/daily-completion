//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�ToolBarCreator.h
// ����������������������
// ������ʶ��������	2018/04/18
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////
#pragma once
#include "ControlsExportDef.h"

class CToolBarCtrl;
class CBCGPToolBar;
#define ID_USER_TOOLBAR_BEGIN                    48000
#define ID_USER_TOOLBAR_END						50000

/** @addtogroup Controls
* @{
*/
	namespace controls {

		//! ������������
		class CONTROLSAPI_EXPORT CToolBarCreator
		{
			class CData;
		public:
			controls::CToolBarCreator();
			~CToolBarCreator();

			/**
			* ���������ļ�����ToolBar
			* @param [in] pToolBar	BCG��ToolBar
			* @param [in] xmlFile
			* @return
			*/
			bool CreateToolBar(CBCGPToolBar *pToolBar, LPCTSTR xmlFile);

			/**
			* ��ȡ�����ַ���
			* @param [in] id
			* @return
			*/
			LPCTSTR GetCommandString(int id);

			/**
			* ��ȡ�����ַ���
			* @param [in] id
			* @return
			*/
			LPCTSTR GetEnableString(int id);

		private:
			CData						*_pData;
		};
		/** * @} */
	}
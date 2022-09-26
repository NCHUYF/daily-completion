#pragma once
//#include "ToolkitExportDef.h"
namespace BwProj {
	namespace toolkit {

		/** @addtogroup Toolkit
		* @{
		*/

		//! �ļ�������ֹ�����û����ļ����д���
		class COMMONTOOLS_API CFileMonopolize
		{
		public:
			CFileMonopolize();
			~CFileMonopolize();

			/**
			* ����
			* @param [in] vFilenames		�ļ�
			*/
			bool Reset(CString strFilenames);

			/**
			* �ر�
			*/
			void Release(void);

			/**
			* ����ļ��Ƿ��д�����ڴ�ǰ�ļ��
			*/
			static bool IsReadable(LPCTSTR szFileName);

			/**
			* ����ļ��Ƿ��д�����ڱ���ǰ�ļ��
			*/
			static bool IsWritable(LPCTSTR szFileName);
		protected:
			/** �ļ���� */
			HANDLE _handle;
		};

		//! �ļ�д����������
		class COMMONTOOLS_API CFileMonopolizeHelper
		{
		public:
			CFileMonopolizeHelper(LPCTSTR szFileName, bool bAnyFile = false);
			~CFileMonopolizeHelper();

		private:
			HANDLE _handle;
		};
		/** * @} */
	}
}

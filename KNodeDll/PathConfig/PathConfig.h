//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           PathConfig.h
//    @author         JZL
//    @data           2017/12/29 10:45
//    @brief          ƽ̨·��������
//
//*****************************************************

#pragma once

namespace CommBase
{
	class COMMBASE_API CPathConfig
	{
	public:
		/**
		*  @brief    ��ȡ���Ŀ¼
		*
		*  @param	 ����Plugin·��(����\\)
		*/
		static CString GetPluginPath();

		/**
		*  @brief    ��ȡAppStart����Ŀ¼
		*
		*  @param	 ����AppStart.exe����·��(����\\)
		*/
		static CString GetAppStartPath();

		/**
		*  @brief    ��ȡƽ̨����Ŀ¼
		*
		*  @param	 ����ƽ̨Workspace����·��(����\\)
		*/
		static CString GetWorkspacePath();

		/**
		*  @brief    ��ȡ���ϵͳĿ¼
		*
		*  @return   CString ���ض�Ӧ·��(��\��β)
		*/
		static CString GetSystemPath();

		/**
		*  @brief    ��ȡ����Ŀ¼
		*
		*  @param	 ����ƽ̨����·��(����\\)
		*/
		static CString GetProjectsPath();

		/**
		*  @brief    ��ȡ��Դ��Ŀ¼
		*
		*  @return	 ������Դ��·��(����\\)
		*/
		static CString GetResourceLibPath();

		/**
		*  @brief    ��ȡ�����ԴĿ¼
		*
		*  @return   CString �����ԴĿ¼
		*/
		static CString GetResourcePath();
		
		/**
		*  @brief    ��ȡ������ԴĿ¼
		*
		*  @return   CString ������ԴĿ¼
		*/
		static CString GetMaterialPath();

		/**
		*  @brief    ��ȡ�����ļ��洢Ŀ¼
		*
		*  @return   CString �����ļ��洢Ŀ¼
		*/
		static CString GetDumpPath();
	};
}
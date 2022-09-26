//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           LogOutput.H
//    @author         fanHong
//    @date           2017/11/1 11:12
//    @brief          ��־���
//
//*****************************************************

#pragma once

namespace CommBase
{
	/*
	* ��־��¼����
	*/
	enum ELogType
	{
		eLogError = 1,		  //д������Ϣ(��¼��ִ����������֪����)
		eLogWarning = 2,     //д������Ϣ(��¼���ܵ�������������Ϣ)
		eLogInfo = 4,		  //дһ����Ϣ(��¼ҵ���߼������Ϣ)
		eLogSystem = 8,	  //дϵͳ��Ϣ(��¼ƽ̨���������Ϣ)
	};

	/**
	*  @class    ��־�����
	*
	*  @brief
	*/
	class COMMBASE_API CLog
	{
	public:
		/**
		*  @brief    ��ʼ����־
		*
		*  @param    LPCWSTR lpLogPath ��־Ŀ¼(��\��β)
		*  @param    int nLogType ��¼��־����
		*  @return
		*/
		static bool InitLog(LPCWSTR lpLogPath, int nLogType =
			(eLogError | eLogWarning | eLogInfo | eLogSystem));

		/**
		*  @brief    ����ʼ����־
		*
		*  @return
		*/
		static void UninitLog();

	public:
		/**
		*  @brief    д������Ϣ
		*
		*  @param    LPCTSTR pszLog ��־��Ϣ
		*  @param    ...
		*/
		static void LogErrorV(LPCTSTR pszLog, ...);

		/**
		*  @brief    д������Ϣ
		*
		*  @param    LPCWSTR lpLog ��־��Ϣ
		*/
		static void LogError(LPCWSTR lpLog);

		/**
		*  @brief    д������Ϣ
		*
		*  @param    LPCTSTR pszLog ��־��Ϣ
		*  @param    ...
		*/
		static void LogWarningV(LPCTSTR pszLog, ...);

		/**
		*  @brief    д������Ϣ
		*
		*  @param    LPCWSTR lpLog ��־��Ϣ
		*/
		static void LogWarning(LPCWSTR lpLog);

		/**
		*  @brief    дһ����Ϣ
		*
		*  @param    LPCTSTR pszLog ��־��Ϣ
		*  @param    ...
		*/
		static void LogInfoV(LPCTSTR pszLog, ...);

		/**
		*  @brief    дһ����Ϣ
		*
		*  @param    LPCWSTR lpLog ��־��Ϣ
		*/
		static void LogInfo(LPCWSTR lpLog);

		/**
		*  @brief    дϵͳ��Ϣ
		*
		*  @param    LPCTSTR pszLog ��־��Ϣ
		*  @param    ...
		*/
		static void LogSystemV(LPCTSTR pszLog, ...);

		/**
		*  @brief    дϵͳ��Ϣ
		*
		*  @param    LPCWSTR lpLog ��־��Ϣ
		*/
		static void LogSystem(LPCWSTR lpLog);

		/**
		*  @brief    ����д��־����
		*
		*  @param    int nLogType ��־��¼���
		*/
		static void SetLogType(int nLogType);

		/**
		*  @brief    ��������
		*
		*  @param    bDone true��ʾ��ʾ���
		*/
		static void LogPerfermance(bool bDone = false);

	private:
		/**
		*  @brief    д��־���ļ�
		*
		*  @param    LPCWSTR lpLog
		*/
		static void LogToFile(LPCWSTR lpLog);

		/**
		*  @brief    ������־�ļ�
		*
		*  @return   bool �ɹ�����true
		*/
		static bool GenerateLogFile();
	};
}
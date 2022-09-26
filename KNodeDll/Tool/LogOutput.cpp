#include "StdAfx.h"
#include "LogOutput.h"

#pragma warning(disable:4091)
#include <shlobj.h>
#pragma comment(lib, "shlwapi")

namespace CommBase
{
	/*
	* ���徲̬����
	*/
	static CAtlFile s_logFile;
	static CString s_strLogPath;	///< ��¼��־·��
	static bool s_bOpenLog = false;		///< �Ƿ������־
#ifdef SAFE_LOGOUTPUT
	static CRITICAL_SECTION s_cs = { 0 }; ///< �߳�ͬ���ٽ���
#endif
	static int s_nLogType = (eLogError | eLogWarning | eLogInfo | eLogSystem); //��־��¼����

	bool CLog::InitLog(LPCWSTR lpLogPath, int nLogType)
	{
		s_bOpenLog = false;
		s_nLogType = nLogType;
		s_strLogPath = lpLogPath;

		// ȷ��·������
		SHCreateDirectoryEx(NULL, s_strLogPath, NULL);

		//��ʼ���ٽ�������
#ifdef SAFE_LOGOUTPUT
		InitializeCriticalSection(&s_cs);
#endif

		//������־�ļ���
		return GenerateLogFile();
	}

	void CLog::UninitLog()
	{
#ifdef SAFE_LOGOUTPUT
		DeleteCriticalSection(&s_cs);
#endif

		s_logFile.Close();
		s_bOpenLog = false;
		s_strLogPath.Empty();
	}

	void CLog::LogErrorV(LPCTSTR pszLog, ...)
	{
		if (!(s_nLogType&eLogError))
			return;

		CString strFormatLog;
		va_list argList;
		va_start(argList, pszLog);
		strFormatLog.FormatV(pszLog, argList);
		va_end(argList);

		// ��ȡ��Ϣʱ��
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogMsg;
		strLogMsg.Format(L"(%d:%d:%d)", st.wHour, st.wMinute, st.wSecond);

		LogToFile(L"������Ϣ" + strLogMsg + L"---" + strFormatLog + L"\r\n");
	}

	void CLog::LogError(LPCWSTR lpLog)
	{
		if (!(s_nLogType&eLogError))
			return;

		// ��ȡ��Ϣʱ��
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogMsg;
		strLogMsg.Format(L"������Ϣ(%d:%d:%d)---%s\r\n", st.wHour, st.wMinute, st.wSecond, lpLog);

		LogToFile(strLogMsg);
	}

	void CLog::LogWarningV(LPCTSTR pszLog, ...)
	{
		if (!(s_nLogType&eLogWarning))
			return;

		CString strFormatLog;
		va_list argList;
		va_start(argList, pszLog);
		strFormatLog.FormatV(pszLog, argList);
		va_end(argList);

		// ��ȡ��Ϣʱ��
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogMsg;
		strLogMsg.Format(L"(%d:%d:%d)", st.wHour, st.wMinute, st.wSecond);

		LogToFile(L"������Ϣ" + strLogMsg + L"---" + strFormatLog + L"\r\n");
	}

	void CLog::LogWarning(LPCWSTR lpLog)
	{
		if (!(s_nLogType&eLogWarning))
			return;

		// ��ȡ��Ϣʱ��
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogMsg;
		strLogMsg.Format(L"������Ϣ(%d:%d:%d)---%s\r\n", st.wHour, st.wMinute, st.wSecond, lpLog);

		LogToFile(strLogMsg);
	}

	void CLog::LogInfoV(LPCTSTR pszLog, ...)
	{
		if (!(s_nLogType&eLogInfo))
			return;

		CString strFormatLog;
		va_list argList;
		va_start(argList, pszLog);
		strFormatLog.FormatV(pszLog, argList);
		va_end(argList);

		// ��ȡ��Ϣʱ��
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogMsg;
		strLogMsg.Format(L"(%d:%d:%d)", st.wHour, st.wMinute, st.wSecond);

		LogToFile(L"һ����Ϣ" + strLogMsg + L"---" + strFormatLog + L"\r\n");
	}

	void CLog::LogInfo(LPCWSTR lpLog)
	{
		if (!(s_nLogType&eLogInfo))
			return;

		// ��ȡ��Ϣʱ��
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogMsg;
		strLogMsg.Format(L"һ����Ϣ(%d:%d:%d)---%s\r\n", st.wHour, st.wMinute, st.wSecond, lpLog);

		LogToFile(strLogMsg);
	}

	void CLog::LogSystemV(LPCTSTR pszLog, ...)
	{
		if (!(s_nLogType&eLogSystem))
			return;

		CString strFormatLog;
		va_list argList;
		va_start(argList, pszLog);
		strFormatLog.FormatV(pszLog, argList);
		va_end(argList);

		// ��ȡ��Ϣʱ��
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogMsg;
		strLogMsg.Format(L"(%d:%d:%d)", st.wHour, st.wMinute, st.wSecond);

		LogToFile(L"ϵͳ��Ϣ" + strLogMsg + L"---" + strFormatLog + L"\r\n");
	}

	void CLog::LogSystem(LPCWSTR lpLog)
	{
		if (!(s_nLogType&eLogSystem))
			return;

		// ��ȡ��Ϣʱ��
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogMsg;
		strLogMsg.Format(L"ϵͳ��Ϣ(%d:%d:%d)---%s\r\n", st.wHour, st.wMinute, st.wSecond, lpLog);

		LogToFile(strLogMsg);
	}

	void CLog::SetLogType(int nLogType)
	{
		s_nLogType = nLogType;
	}

	void CLog::LogToFile(LPCWSTR lpInfo)
	{
		if (NULL == lpInfo || !s_bOpenLog)
			return;

		try
		{
			//�����ٽ���
#ifdef SAFE_LOGOUTPUT
			EnterCriticalSection(&s_cs);
#endif

			// д����־��Ϣ
			s_logFile.Write(lpInfo, lstrlen(lpInfo) * sizeof(TCHAR));
			s_logFile.Flush();

			//�뿪�ٽ���
#ifdef SAFE_LOGOUTPUT
			LeaveCriticalSection(&s_cs);
#endif
		}
		catch (...)
		{
#ifdef SAFE_LOGOUTPUT
			LeaveCriticalSection(&s_cs);
#endif
		}
	}

	bool CLog::GenerateLogFile()
	{
		if (s_bOpenLog)
			return false;

		// ����ʱ���ʽ������־�ļ���
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CString strLogFile;
		strLogFile.Format(L"%d-%d-%d.log", st.wYear, st.wMonth, st.wDay);

		// ����־�ļ�
		if (s_logFile.Create(s_strLogPath + strLogFile, GENERIC_READ | GENERIC_WRITE,
			0, OPEN_ALWAYS) != S_OK)
		{
			return false;
		}

		// �½��ļ�д��UNICODEͷ��
		ULONGLONG nLen = 0;
		s_logFile.GetSize(nLen);
		if (!nLen)
		{
			WORD unicodeHead = 0xFEFF;
			s_logFile.Write(&unicodeHead, sizeof(WORD));
		}

		s_bOpenLog = true;

		// ׷����־
		s_logFile.Seek(0, FILE_END);

		// д����־��Ϣͷ
		LogToFile(L"---------------------��־��¼---------------------\r\n");

		return true;
	}

	void CLog::LogPerfermance(bool bDone)
	{
		static LARGE_INTEGER frq, tm1, tm2;
		if (!bDone)
		{
			// ��ȡCPU ʼ������
			::QueryPerformanceFrequency(&frq);
			// ��ȡCPU����
			::QueryPerformanceCounter(&tm1);
		}
		else
		{
			// ��ȡCPU����
			::QueryPerformanceCounter(&tm2);
			double dTime = (double)(tm2.QuadPart - tm1.QuadPart) / (double)frq.QuadPart;
			CString msg;
			msg.Format(_T("\n������ʱ %f ms\n"), dTime * 1000);
			OutputDebugString(msg);
			LogInfo(msg);
		}
	}
}
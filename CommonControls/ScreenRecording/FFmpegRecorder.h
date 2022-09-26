//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           FFmpegRecorder.h
//    @author         yf
//    @data           2020/10/29  
//    @brief          ��Ļ¼����
//
//*****************************************************

#pragma once

#ifdef COMMONCONTROLS_API
#define CFFmpegRecorder_API COMMONCONTROLS_API
#else
#define CFFmpegRecorder_API 
#endif 

class CFFmpegRecorder_API CFFmpegRecorder
{
public:
	// ¼����Ϣ
	struct stFFMPEGInfo
	{
		int _x;						// �������Ͻ�x����
		int _y;						// �������Ͻ�y����
		int _width;					// ���ڿ�
		int _height;				// ���ڸ�
		BOOL _bMouse;				// �Ƿ���ʾ���
		CString _strTitle;			// ��������
		CString _tempPath;			// ��ʱ·��
		CString _savePath;			// ����·��
		int _fps;					// ֡��
		PROCESS_INFORMATION _pi;	// ������Ϣ
		CWnd *_pCurWnd;				// ��ǰ����
		bool _bFullScreen;			// �Ƿ�ȫ��
		CString _strFFmpegPath;		// ffmpegӦ�ó���·��
	};	
public:
	CFFmpegRecorder();
	~CFFmpegRecorder();
public:

	/**
	*  @brief    ����ffmpegӦ�ó���·��
	*
	*  @param
	*  @return
	*/
	void SetFFmpegPath(const CString &strPath);

	/**
	*  @brief    ��ȡffmpegӦ�ó���·��
	*
	*  @param
	*  @return
	*/
	CString GetFFmpegPath();

	/**
	*  @brief    ��ʼ¼��
	*
	*  @param    
	*  @return   
	*/
	bool StartRecording();

	/**
	*  @brief    ����¼��
	*
	*  @param    
	*  @return   
	*/
	void StopRecording();

	/**
	*  @brief    ���ý�ȡ��Ļ����
	*
	*  @param    rect ��Ļ����
	*  @return   
	*/
	void SetScreenRect(const CRect & rect);

	/**
	*  @brief    ���ý�ȡ��Ļ����
	*
	*  @param    rect ��Ļ����
	*  @return
	*/
	void SetScreenRect(CWnd *pWnd);

	/**
	*  @brief    ����Ҫץȡ�Ĵ��ڵı���
	*
	*  @param    const CString &strTitle
	*  @return
	*/
	void SetCatchWndTitle(const CString &strTitle);

	/**
	*  @brief    �����ļ��洢·��
	*
	*  @param    strSavePath �ļ��洢·��
	*  @return   
	*/
	void SetSaveFileName(const CString &strSavePath);

	/**
	*  @brief   ����Ĭ��֡�� 
	*
	*  @param    nFPS ÿ�����֡
	*  @return   
	*/
	void SetFPS(int nFPS);

	/**
	*  @brief   ��ȡĬ��֡��
	*
	*  @param    nFPS ÿ�����֡
	*  @return
	*/
	int GetFPS();

	/**
	*  @brief   ����ȫ��
	*
	*  @param    bFullScreen �Ƿ�ȫ��
	*  @return
	*/
	void SetFullScreen(bool bFullScreen = true);

	/**
	*  @brief   ��ʾ���
	*
	*  @param    bShow �Ƿ���ʾ
	*  @return
	*/
	void ShowMouse(bool bShow = true);

	/**
	*  @brief    ��ȡ��ǰ����ָ��
	*
	*  @return   CWnd *
	*/
	CWnd * GetCurWnd();

private:
	/**
	*  @brief    ת��ѹ������
	*
	*  @return   BOOL
	*/
	BOOL TranscodingVideo();

	/**
	*  @brief   ץȡ�߳�
	*
	*  @param
	*  @return
	*/
	static unsigned __stdcall ReleaseThread(void *pParam);

	/**
	*  @brief    �ͷ�
	*
	*  @return   BOOL
	*/
	BOOL Release();
private:
	stFFMPEGInfo _ffmpegInfo; // ¼����Ϣ
	HANDLE _releaseThread;	// �ͷž��
};


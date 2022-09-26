//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           CScreenRecording.h
//    @author         yf
//    @data           2020/10/29  
//    @brief          ��Ļ¼����
//
//*****************************************************

#pragma once

#include<memory>

//FFPEG��������
struct AVFormatContext;
struct AVCodecContext;
struct AVCodec;
struct AVStream;
struct AVFrame;
struct AVPacket;
struct CCaptureScreen;
class COMMONCONTROLS_API CScreenRecorder
{
public:
	CScreenRecorder();

	/**
	*  @brief    ���ι���
	*
	*  @param    strSavePath ����·��
	*  @param    rect ��ȡ����
	*  @param    pWnd ��ȡ����
	*  @return   
	*/
	CScreenRecorder(const CString & strSavePath, const CRect & rect);
	~CScreenRecorder();
public:

	/**
	*  @brief    ��ʼ¼��
	*
	*  @param    
	*  @return   
	*/
	void StartRecording();

	/**
	*  @brief    ����¼��
	*
	*  @param    
	*  @return   
	*/
	void StopRecording();

	/**
	*  @brief    ��ӱ�������
	*
	*  @param	stVideoFilePath ��Ƶ�ļ�·��
	*  @param	strMusicFilePath ���������ļ�·��
	*  @param	strTargetFilePath �ϳ��ļ�����·��
	*  @return
	*/
	void AddBGMusic(const CString &strVideoFilePath, const CString &strMusicFilePath, const CString &strTargetFilePath);

	/**
	*  @brief    ��ȡ��һ����Ƶ�ı���·��
	*
	*  @return	CString
	*/
	CString GetLastVideoPath();

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
	*  @brief   ��ȡ��Ļ����λ��
	*
	*  @param
	*  @return
	*/
	CSize GetTextPos();

	/**
	*  @brief   ������Ļ����λ��
	*
	*  @param
	*  @return
	*/
	void SetTextPos(const CSize &pos);

	/**
	*  @brief   ��ȡ��Ļ����
	*
	*  @param
	*  @return
	*/
	const CString &GetText();

	/**
	*  @brief   ������Ļ����
	*
	*  @param
	*  @return
	*/
	void SetText(const CString &strText);

	/**
	*  @brief    ��ʼ��ץ��
	*
	*  @return   bool
	*/
	bool InitCapture();
	
	/**
	*  @brief    ץ��һ֡
	*
	*  @return   bool
	*/
	bool Capture();
	
	/**
	*  @brief    ֡д���ļ�
	*
	*  @return   bool
	*/
	bool WriteFrame();

	/**
	*  @brief    ��ȡ��ǰ����ָ��
	*
	*  @return   CWnd *
	*/
	CWnd * GetCurWnd();
private:
	/**
	*  @brief   ץȡ�߳�
	*
	*  @param    
	*  @return
	*/
	static unsigned __stdcall CaptureThread(void *pParam);

	/**
	*  @brief   д���߳�
	*
	*  @param    
	*  @return
	*/
	static unsigned __stdcall WriteThread(void *pParam);

	/**
	*  @brief   ��ʼ���߳�����
	*
	*  @param
	*  @return bool
	*/
	bool InitRecording();

	/**
	*  @brief   ¼����������ݴ���
	*
	*  @param
	*  @return
	*/
	void AfterRecording();

	/**
	*  @brief   ��ʼ������
	*
	*  @param
	*  @return
	*/
	void InitData();

	
private:
	CString _strSaveFileName;	// ����·��
	CRect _rect;				// ��������
	int _nDefFps;				// �֡��	
	int _nCurFps;				// ��ǰ֡��
	volatile bool _bStop = true;// �Ƿ�ֹͣ�߳�
	bool _bFullScreen = true;	// �Ƿ�ȫ��
	bool _bShowMouse = true;	//�Ƿ���ʾ���
	HANDLE _capThread;			// ץȡ�߳̾��
	HANDLE _wrtThread;			// д���߳̾��
private:

	std::queue<BYTE*> _ImageQueue;		//֡����
	CRITICAL_SECTION _Section;			//֡�����ٽ���
	
	// ¼���������
	int _Width = 0;
	int _Height = 0;

	CWnd *_pCurWnd; // ��ǰ����

	//FFMPEG���¼������
	AVFormatContext* _avFormCtx_Out = nullptr;
	AVCodecContext* _avCodecCtx_Out = nullptr;
	AVCodec* _avCodec = nullptr;
	AVStream* _avStream = nullptr;
	AVFrame* _avframe = nullptr;
	AVPacket* _packet = nullptr;
	BYTE* _outbuffer = nullptr;
	std::shared_ptr<CCaptureScreen> _CaptureScreen = nullptr;//ץȡ��Ļ��ͼ��
	int _frameNumber = 0;//��ǰ֡���

	// ֡�ʼ������
	double _dDefOneFrameTime = 0; // Ĭ��ÿ֡ʱ��
	long _nTotaltime = 0; // ��ʱ��
	long _nStartTime = 0; // ��ʼʱ��
	long _nLastTime = 0; // �ϴ�ʱ��

	CString _strLastVideoPath; // ��һ����Ƶ��·��

	CSize _txtPos; // ����λ��
	CString _strText; // ��Ļ����
};


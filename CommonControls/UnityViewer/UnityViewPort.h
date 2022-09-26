//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           UnityViewPort.h
//    @author         yf
//    @data           2021/08/06  
//    @brief          unity��ͼ
//
//*****************************************************

#pragma once

#define IDD_UNITY_VIEWPORT              126

// CUnityViewPort �Ի���
class IUnityMsgListener;
class COMMONCONTROLS_API CUnityViewPort
	: public CBaseDialog
	, public CSingletonBase
{
	DECLARE_SINGLE_CLASS2(CUnityViewPort, L"CUnityViewPort")
	// ����
public:
	CUnityViewPort(CWnd* pParent = NULL);	// ��׼���캯��
	enum {
		IDD = IDD_UNITY_VIEWPORT
	};

	// ��Ϣѭ����Ϣ
	struct UNITY_MESSAGE_LOOP_INFO
	{
		SOCKET  *_pSocket;
		std::list<IUnityMsgListener *> *_pListenerList;
	};

	// socket������Ϣ
	struct SOCKET_CONNECT_INFO
	{
		SOCKET  *_pSocket;
		SOCKADDR_IN _addrTo;
	};

public:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	/**
	* ���unity��Ϣ������
	* @return
	*/
	bool AddUnityMsgListener(IUnityMsgListener *pListener);
	
	/**
	* �Ƴ�unity��Ϣ������
	* @return
	*/
	bool RemoveUnityMsgListener(IUnityMsgListener *pListener);

	/**
	* �������unity��Ϣ������
	* @return
	*/
	bool ClearUnityMsgListener(IUnityMsgListener *pListener);

	/**
	* ��unity������Ϣ
	* @return
	*/
	void SendMsgToUnity(const std::string szMsg);

	/**
	* ������mfc��������Ϣ
	* @return
	*/
	void SendMsgToSelf(const std::string szMsg);

	/**
	* ��ʼ��
	* @return
	*/
	virtual bool Init();

	/**
	* ��ȡunity��ִ��·��
	* @return
	*/
	CString GetUnityExecutePath();

	/**
	* ����unity��ִ��·��
	* @return
	*/
	void SetUnityExecutePath(const CString &strPath);

	/**
	* �رնԻ���
	* @return
	*/
	virtual void CloseDialog() override;

	/**
	* ����unity
	* @return BOOL
	*/
	void RestartUnity();

	/**
	* Ƕ��unity
	* @return BOOL
	*/
	bool EmbedUnity();

	/**
	* �Ƴ�unity������
	* @return BOOL
	*/
	void RemoveUnityDlg();

	/**
	* �ƻ�unity���ڲ���ʾ
	* @return BOOL
	*/
	void TakeBackUnityDlg();
protected:
	/**
	* ��ʼ���׽���
	* @return BOOL
	*/
	BOOL InitSocket();

	/**
	* ����Unity
	* @return BOOL
	*/
	BOOL Connect();

	/**
	* ���unity����
	* @return BOOL
	*/
	BOOL KillUnityTask();

	/**
	* ��Ϣѭ��unity�߳�
	* @return BOOL
	*/
	static unsigned __stdcall MessageLoop(void * pParam);

	/**
	* socket�����߳�
	* @return BOOL
	*/
	static unsigned __stdcall SocketConnectLoop(void * pParam);
// ʵ��
protected:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	HANDLE StartProcess(LPCTSTR program, LPCTSTR args);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

protected:
	SOCKET  _socket; //�׽�������������
	HANDLE hProcess; // unity���̾��
	static HWND apphWnd; // unity���ھ��
	CString _strUnityExecutePath; // unityִ��·��
	DWORD _ipAddress; // ����ip

	std::list<IUnityMsgListener *> _listenerList; // �������б�
	HANDLE _hMsgLoopThread; // ��Ϣѭ���߳�
	HANDLE _hSocketConnectThread; // socket�����߳�
	UNITY_MESSAGE_LOOP_INFO _infoMsgLoop; // ��Ϣѭ����Ϣ
	SOCKET_CONNECT_INFO _infoSocketConnect; // socket������Ϣ

	bool _bMouseTracking; // �Ƿ������
	CWnd *_pUnityWnd;
};

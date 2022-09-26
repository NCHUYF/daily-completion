//*****************************************************
//    
//    @copyright      ��ά�����
//    @version        v1.0
//    @file           IProgress.H
//    @author         ZSX
//    @data           2018/8/29 11:48
//    @brief          ������Ӧ
//*****************************************************

#pragma once

//messagebox��ʽ
typedef struct MessageBoxInfo
{
	CString strContent;            //����
	CString strTitle = _T("��ʾ");  //����
	UINT uType = MB_OK;            //�������
	LRESULT lResult = 0;           //MessageBox����ֵ
}MessageBoxInfo; 

// ģ̬����Ϣ
typedef struct ModalProgressInfo
{
	ModalProgressInfo() :
		hParent(0), hProgressHwnd(0), bComplete(false),
		bAutoAdd(true), bPause(false), nCurStep(0), nMaxStep(100),
		bChangeText(false), strTitle(L""), strText(L"���ڼ��أ����Ե�..."),
		pDefinePara(NULL), pThreadPt(NULL)
	{}

	HWND hParent;		// ģ̬�򸸴��ھ��
	HWND hProgressHwnd; // ���������ھ��
	bool bComplete;		// ��ɱ�־λ
	
	bool bAutoAdd;		// �Զ����ӽ��ȣ�����nCurStep��
	bool bPause;        // ��ͣ����
	int nCurStep;		// ��ǰ����
	int nMaxStep;		// ������

	bool bChangeText;	// ��Ҫ�޸�����
	CString strTitle;	// ��������
	CString strText;	// ��������

	void *pDefinePara;  // �Զ������
	_beginthreadex_proc_type pThreadPt;  // �߳�ִ�к���ָ��
}ModalProgressInfo;



/**
*  @class    IProgressListen
*
*  @brief    ���ȼ����ӿ�
*/
class COMMONCONTROLS_API IProgressListener
{
public:
	virtual void OnStep(int nStep) = 0;
};

/**
*  @class    IProgress
*
*  @brief    ���Ƚӿ�
*/
class COMMONCONTROLS_API IProgress
{
public:
	IProgress();

	virtual ~IProgress();

public:
	/**
	*  @brief    ���ȿ�ʼ
	*
	*  @return   void
	*/
	virtual void OnStart();

	/**
	*  @brief    ����ֹͣ
	*
	*  @return   void
	*/
	virtual void OnStop();

	/**
	*  @brief    �������
	*
	*  @return   void
	*/
	virtual void OnComplete();

	/**
	*  @brief    ���ý���
	*
	*  @param    USHORT step
	*  @return   void
	*/
	virtual void OnStep(int nStep);

	/**
	*  �������� ���ӽ���
	*
	*  �������� int nStep
	*  ����ֵ   void
	*/
	virtual void IncrementStep(int nStep, int nMaxLimit = 100);

	/**
	*  @brief    ��ȡ����
	*
	*  @return   int
	*/
	virtual int GetStep();

	/**
	*  �������� �Ƿ����
	*
	*  ����ֵ   bool
	*/
	virtual bool IsComplete();

	/**
	*  @brief    ���ü�����Ӧ
	*
	*  @param    IProgressListen* notify
	*  @return   void
	*/
	virtual void SetNotify(IProgressListener* pListener);

protected:
	int _useStep;					///< ����
	IProgressListener *_pListener;	///< �󶨼�����Ӧ
};

class CProgressDlg;

class COMMONCONTROLS_API CProgressAgentStopEvent
{
public:
	CProgressAgentStopEvent() {};
	virtual ~CProgressAgentStopEvent(){};
public:

	//����ֹͣ
	virtual  bool StopParser() = 0;

	//��ȡ�Ƿ���ֹͣ
	virtual  bool IsStopedParser() = 0;

};

/**
*  @class    CProgress
*
*  @brief    ������������ʾ�������Ի���
*/
class COMMONCONTROLS_API CProgressAgent : public IProgress
{
public:
	/**
	*  �������� ���������(��ģ̬)
	*
	*  �������� const CString& sTitle	����
	*  �������� const CString& sText		��ʾ����
	*  �������� CWnd * pParent			������
	*  ����ֵ   
	*/
	CProgressAgent(const CString& sTitle = L"", 
		const CString& sText = L"���ڼ��أ����Ե�...", CWnd *pParent = NULL);
		
	virtual ~CProgressAgent();

public:

	/**
	*  �������� ���������(ģ̬�����߳�)
	*
	*  �������� ModalProgressInfo& proInfo
	*  �������� bCancel			�Ƿ�����ж��߳�
	*  ����ֵ
	*/
	static int ModalProgress(ModalProgressInfo& proInfo, bool bCancel = false, CProgressAgentStopEvent* pEvent = nullptr);

	/*
	* �������ܣ� ��������ģ̬Messagebox
	* ��������� ModalProgressInfo& proInfo ������������Ϣ
	* ��������� CString strContent messagebox����
	* ��������� CString strTitle messagebox����
	* ��������� UINT uType messagebox��ť���
	* ����ֵ: LRESULT messagebox����ֵ
	*/
	static LRESULT ModalMessageBox(ModalProgressInfo* proInfo, CString strContent, CString strTitle, UINT uType);

private:
	CProgressDlg* _pdlg;	// �������Ի���
	CProgressAgentStopEvent * pStopEvent;//��ֹ������Ϣ
};

//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0H
//    @file           LockClientDialog.H
//    @author         KG
//    @date           2015/09/14 10:26
//    @brief          ���Ի���
//*****************************************************

#pragma once

#include "LicenceAccess.h"
//#include "resource.h"
//#include "..\HyperLink\HyperLink.h"

// ���ճ�����к���Ϣ
#define WM_COMPLETE_PASTE	WM_USER + 22

/*
* �Ի����˳�����
*/
enum ENotFoundMode
{
	eShowLic = 12,	// ��ʾ���֤����
	eNetLogin = 15,	// ���������½
	eRetryDet = 17,	// ���¼����
	eQuitLock = 19,	// �˳������
	eQuitDown = 21,	// �˳����
};

/**
*  @class    �Ҳ��������ʾ��
*
*  @brief
*/
class CNoFoundLienceDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
public:
	enum { IDD = IDD_LOCK_TIP };
	CNoFoundLienceDlg(CWnd *pParent = NULL);

	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnStnClickedAddLic();
	afx_msg void OnBtnRetry();
	afx_msg void OnBtnNetLogin();
	afx_msg void OnCheckManualLogin();
public:
	/*
	*	��ʼ��
	*/
	virtual BOOL OnInitDialog();

	/*
	*	��ȡ�Ի����˳�����
	*/
	ENotFoundMode GetNoFoundMode();

	/*
	*	��ȡ�Ƿ��ֶ���½
	*/
	BOOL IsManualLoginIn();

	/**
	*  @brief    ��ϢԤ����;
	*
	*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	CHyperLink _addLisLink; // ������֤
	ENotFoundMode _noFoundMode;	// �Ի����˳�����
	CButton _checkManualLogin;
	BOOL _bIsManualLoginIn = FALSE;
public:
	afx_msg void OnClose();
};

/**
*  @class    ������֤����Ի���
*
*  @brief
*/
class CServerLicenceMgrDlg : public CDialog
{
public:
	enum { IDD = IDD_LICENCEMGR };
	CServerLicenceMgrDlg(CWnd *pParent = NULL);
	~CServerLicenceMgrDlg();

	DECLARE_MESSAGE_MAP()

public:
	/*
	*	��ʼ��
	*/
	BOOL OnInitDialog();

	/*
	*	�Զ�������֤��
	*/
	void OnAutoAddLience();

	/*
	*	�ֶ�������֤��
	*/
	void OnAddLience();

	/*
	*	ȷ��
	*/
	void OnOK();

	/*
	*	�˳�
	*/
	void OnCancel();

	/*
	*	ѡ����
	*/
	void OnSelLockItem();

	/*
	*	������֤
	*/
	bool AddLicence(CString strSelLockLabel);

private:
	/*
	*	ȡ��Ĭ�Ϲ�˾����
	*/
	CString GetDefaultCorpName();

	/*
	*	���ݱ�ǩ�����豸ID
	*/
	bool FindLockByLabel(IBooLockClientServicePtr& service,
		LPCTSTR label, IBooReadLockInfoPtr& lock);

protected:
	CListCtrl		_licListCtrl;	// ������б�
};


/**
*  @class    ע��ű༭�ؼ�
*
*  @brief
*/
class CLicenceEdit : public CEdit
{
	DECLARE_MESSAGE_MAP()
public:
	CLicenceEdit();
	~CLicenceEdit();

	/*
	*	����ճ��ע���
	*/
	LRESULT OnPaste(WPARAM wParam, LPARAM lParam);

	/*
	*	��ϵͳ���а��л�ȡ����
	*/
	bool GetDataFromClipboard(CString& strResult);

	/*
	*	�������ݸ�ʽ�Ƿ��������ճ��Ҫ��(��ʱ�����Ƹ�ʽ)
	*/
	bool IsCorrectFormat(LPCTSTR strLicence)
	{
		CString temp(strLicence);
		return temp.Find(_T('-')) > -1;
	}
};

/**
*  @class    ������֤�ŶԻ���
*
*  @brief
*/
class CAddLienceDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_ADDLIENCE };
	CAddLienceDlg(CWnd *pWnd = NULL);
	afx_msg void OnOK();
	afx_msg void OnCancel();

public:
	/*
	*	��ʼ��
	*/
	virtual BOOL OnInitDialog();

	/*
	*	����������ֳ�������ʱ������һ�������
	*/
	void OnEditLienceChange1();

	/*
	*	����������ֳ�������ʱ������һ�������
	*/
	void OnEditLienceChange2();

	/*
	*	����������ֳ�������ʱ������һ�������
	*/
	void OnEditLienceChange3();

	/*
	*	����������ֳ�������ʱ������һ�������
	*/
	void OnEditLienceChange4();

	/*
	*	����ճ������
	*/
	LRESULT OnCompletePaste(WPARAM wParam, LPARAM lParam);

public:
	CString			_strCorpname;
	CString			_strLicence;
	CLicenceEdit	_licenceEdit;
};

/**
*  @class    ��������½�Ի���
*
*  @brief    
*/
class CNetLoginDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
public:
	enum { IDD = IDD_DLG_NETLOGIN };
	CNetLoginDlg(CLicenceAccess *pLinc, CWnd *pParent = NULL);

public:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	/*
	*	ȷ��
	*/
	void OnOK();

	/*
	*	�˳�
	*/
	void OnCancel();

	/**
	*  @brief    �ж��Ƿ��½�ɹ�
	*
	*  @return   BOOL
	*/
	BOOL LoginSucceed();
private:
	/**
	*  @brief    �޸�AppStarter.ini����
	*
	*  @param    const CString&  Service��Ӧ�ֶ�
	*  @param    const CString&  account��Ӧ�ֶ�
	*  @param    const CString&  password��Ӧ�ֶ�
	*  @return   BOOL
	*/
	BOOL SetNetLockInfo(const CString& strServer, const CString& strAccount, const CString& strPassword);

private:
	CEdit _netAddrEdit;		///<�����ַ�༭��
	CEdit _adminEdit;		///<�û����༭��
	CEdit _passEdit;		///<����༭��
	CLicenceAccess *_pLinc; ///<���������
	BOOL  _eSucc;	///<<�Ƿ�ɹ���½
};
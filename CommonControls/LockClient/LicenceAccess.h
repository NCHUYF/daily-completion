//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0H
//    @file           LicenceAccess.H
//    @author         KG
//    @date           2015/09/14 15:26
//    @brief          ���������
//*****************************************************

#pragma once

#include <map>
#include "ILicenceAccess.h"

//������
#ifndef _WIN64
#import "..\..\..\ThirdPart\LockClientService\LockClientService.tlb" rename_namespace("BwLockClient")
#else
#import "..\..\..\ThirdPart\LockClientService\LockClientService64.tlb" rename_namespace("BwLockClient")
#endif

using namespace BwLockClient;

IUnknown* CreateLockObject(UUID uuidof);

// ֧�ֵ����֤�б�
typedef std::map<int, CString> SupportLicMap;

/**
*  @class    �����������
*
*  @brief
*/
class CLicenceAccess
{
private:
	CLicenceAccess();

public:
	/*
	*	��ȡ��ʵ������
	*/
	static CLicenceAccess* GetInstance();

	/*
	*	�ͷ���ʵ��
	*/
	static void ReleaseInstance();

	/*
	*	��ȡ����������
	*/
	static IBooLockClientServicePtr GetNatServer();

public:
	/*
	*	������
	*/
	bool CreateLock();

	/*
	*	�ͷű�����
	*/
	void ReleaseLock();

	/*
	*	�������Ƿ��Ѵ���
	*/
	void IsLockCreate();

public:
	/*
	*	��ⵥ�������֤���
	*/
	bool CheckNatLock();

	/*
	*	������������֤���
	*/
	bool CheckNetLock();

	/*
	*	������������֤���
	*/
	bool AppNetLogin();

	/*
	*	��ȡ������Ϣ
	*/
	CString GetLastError();

	/*
	*	������ģʽ
	*/
	void SetLockLicMode(int nMode);

	/*
	*	��ȡ��ģʽ
	*/
	int GetLockLicMode();

	/*
	*	����ָ���������֤�Ƿ����
	*/
	bool CheckFunctionLicence(int nLockLicMode);

	/*
	*	��ȡ֧�ֵ����֤�б�
	*/
	SupportLicMap GetAppSupperLicenceMap();

private:
	/*
	*	ȡ�ñ�ϵͳMODE��Ӧ�����֤�ַ�
	*/
	CString GetSupportLicenceByMode(int nMode);

private:
	/*
	*	���������Ƿ�ͨ��
	*/
	bool CheckLicence(IBooLockClientManagerPtr pLockPtr, CString strLic,
		bool bAddLicence, bool bNativeLock);

	/*
	*	���������Ƿ����ָ�������֤
	*/
	bool IsLicenceExist(LPCTSTR licence, IBooLockClientManagerPtr pLockPtr, bool bNativeLock);

protected:
	bool _bNetLogin;	// �����֤�Ƿ�Ϊ�����½
	int _nLockLicMode;	// �����֤ģʽ(���ģʽ���)
	CString _strLastError;	// ������Ϣ
	IBooLockClientManagerPtr _pNetLock;	//������
	IBooLockClientManagerPtr _pNatLock;	//������
	static CLicenceAccess* s_pLicAccess; // ������
};

/*
*	��ȡ��ǰģ��·��
*/
CString GetModulePath();

/*
*	�������ļ���������½��Ϣ
*/
void GetNetLockInfo(CString& strServer, CString& strAccount, CString& strPassword);

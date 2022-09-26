#pragma once

#include "LicenceCtx.h"

class COMMONCONTROLS_API CLockClientService
{
public:
	DECLARE_SINGLE_CLASS(CLockClientService)

public:
	CLockClientService();
	~CLockClientService();

public:
	/**
	*  @brief    ���ָ�������֤�Ƿ����;
	*
	*  @param    nMode �����֤�ĺ궨�壬�ο�GetSupportLicenceByModeʵ��
	*/
	static bool CheckLicence(int nMode = LOCK_LIC_MASTER);

public:

// 	/**
// 	*  @brief    ��ǳ�ʼ�������ڴ�
// 	*
// 	*  @return   void
// 	*/
// 	void InitStartFlagAndInstance();

	/**
	*  @brief    ��ʼ�����
	*
	*  @return   void
	*/
	void InitLockDetect();

	static UINT LockInitial(LPVOID lpParam);
	
	static void CALLBACK LockDetectProc(HWND, UINT, UINT_PTR, DWORD);

	void LockFirst();

	/**
	*  @brief    function_description
	*
	*  @return   void
	*/
	void UninitLockDetect();

public:
	CWinThread*	_pLockInitThread; ///<������߳�
	static UINT_PTR s_nCheckTm; ///< �������ʱ��
	static int s_nLockInitStatus; ///< ����ʼ��״̬
	static CAtlFileMapping<AppCtx> s_instanceMapping; ///< ������������
	static bool _bNetLogin; // �Ƿ�ʹ����������½
};

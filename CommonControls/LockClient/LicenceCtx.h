
#pragma once

#pragma pack (push, 8)

//ʵ��������
typedef struct tag_AppCtx
{
	// ����ʹ��(���32��64λ�ڴ湲���С����)
	INT hWnd;		// ��ǰ���е�CAD�����ھ��
	TCHAR filePath[MAX_PATH * 2] = {0}; // ���ڴ򿪵��ļ�·��
	INT hPrjDesignWnd; // ��Ŀ���������

	tag_AppCtx()
	{
		hWnd = NULL;
		hPrjDesignWnd = NULL;
	}

	void SetFilePath(const CString& filePathIn)
	{
		lstrcpyn(filePath, filePathIn.GetString(), MAX_PATH * 2);
	}
}AppCtx;

//��½������
typedef struct tag_LoginCtx
{
	int  nlockLicMode;   // ������������ģʽ
	bool bInitSuccess;	// �������Ƿ������ɹ�

	tag_LoginCtx()
	{
		nlockLicMode = 1; //LOCK_LIC_MODE1
		bInitSuccess = false;
	}
}LoginCtx;

#pragma pack (pop)

// ֪ͨ��Ŀ�˳���ƽ���
#define UM_QUIT_APP (WM_USER+1400)

// ��ģʽ���û�������ʹ��
#define LOCK_LIC_MASTER		1	// �����֤�����
#define LOCK_LIC_MODE1		2	// �������������֤ģʽ1
#define LOCK_LIC_MODE2	4	// �������������֤ģʽ2
#define LOCK_LIC_MODE3	8	// �������������֤ģʽ3

class CLockTool
{
public:
	CLockTool(){}

	static CString GetLockCfgFile();

};
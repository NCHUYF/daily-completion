//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�MsgTipMng.h
// ������������ʾ���ڹ�����
// ������ʶ������ 2019/10/19
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////
#pragma once
#include "ControlsExportDef.h"

//  #define SHOW_TIP_MSG(hWnd, lpText, lpCaption, uType) \
//  	::MessageBox(hWnd, lpText, lpCaption, uType);

#define SHOW_TIP_MSG(hWnd, lpText, lpCaption, uType) \
	CMsgTipMng::GetInst()->AddTipWindow(hWnd, lpText);

#define SHOW_TIP_MSG_TIME(hWnd, lpText, lpCaption, uType, nTime) \
	CMsgTipMng::GetInst()->AddTipWindow(hWnd, lpText, nTime);

class CMsgTipDlg;
class CONTROLSAPI_EXPORT CMsgTipMng
{
public:
	CMsgTipMng();
	~CMsgTipMng();

	static CMsgTipMng* GetInst();

	/**
	* �ͷ���������ڴ�
	*/
	static void FreeInst();

	/**
	* �����ʾ��Ϣ
	* @param [in] strTipInfo ��ʾ��Ϣ
	* @param [in] nTime ��ʾʱ��
	* @return
	*/
	void AddTipWindow(HWND hWnd, const CString& strTipInfo, int nTime = 0);

	/**
	* ���ٵ�ǰ��ʾ����
	* @return
	*/
	void DestroyTipDialog();

private:
	static CMsgTipMng		*_pInst;
	CMsgTipDlg* _TipDialog;
};


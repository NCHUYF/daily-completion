#include "stdafx.h"
#include "BCGPDialogEx.h"

using namespace controls;
IMPLEMENT_DYNCREATE(CBCGPDialogEx, CBCGPDialog)

controls::CBCGPDialogEx::CBCGPDialogEx()
{
	CommonConstruct();
}

controls::CBCGPDialogEx::CBCGPDialogEx(UINT nIDTemplate, CWnd *pParent/*= NULL*/)
	:CBCGPDialog(nIDTemplate, pParent)

{
	CommonConstruct();
}

controls::CBCGPDialogEx::CBCGPDialogEx(LPCTSTR lpszTemplateName, CWnd *pParentWnd/*= NULL*/)
	:CBCGPDialog(lpszTemplateName, pParentWnd)
{
	CommonConstruct();
}

BOOL controls::CBCGPDialogEx::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	CChangeModule dl;
	return CDialog::Create(lpszTemplateName, pParentWnd);
}

controls::CChangeModule::CChangeModule()
{
	_hInstance = AfxGetResourceHandle();

	HINSTANCE dll_hInstance = controls::GetSelfModuleHandle();
	AfxSetResourceHandle(dll_hInstance); //�л���Դ״̬Ϊ��ǰdll
}

controls::CChangeModule::~CChangeModule()
{
	AfxSetResourceHandle(_hInstance); // �ָ���Դ״̬
}

HMODULE controls::GetSelfModuleHandle()
{
	MEMORY_BASIC_INFORMATION mbi;
	return ((::VirtualQuery(controls::GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0)
		? (HMODULE)mbi.AllocationBase : NULL);
}
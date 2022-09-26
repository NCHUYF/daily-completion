#include "stdafx.h"
#include "..\include\EMailToolkit.h"
#include <Mapi.h>

using namespace BwProj::toolkit;

// ���ñ����ʼ������͸���
bool CEMailToolkit::SendFileToEmail(LPCTSTR filePath)
{
	// ��ȡ MAPISendMail ����
	HMODULE hMod = LoadLibrary(L"MAPI32.DLL");
	if (hMod == NULL) return false;

	ULONG(PASCAL *lpfnSendMail)(ULONG, ULONG, MapiMessageW*, FLAGS, ULONG);
	(FARPROC&)lpfnSendMail = GetProcAddress(hMod, "MAPISendMailW");
	if (lpfnSendMail == NULL) {
		FreeLibrary(hMod);
		return false;
	}

	CAtlArray<CString> m_list;

	m_list.Add(filePath);
	int nFileCount = m_list.GetCount ();
	//�����ڴ汣�渽����Ϣ ����ʹ�þ�̬���飬��Ϊ��֪��Ҫ���͸����ĸ���
	MapiFileDescW* pFileDesc = (MapiFileDescW*)malloc(sizeof(MapiFileDescW) * nFileCount);
	memset(pFileDesc, 0, sizeof(MapiFileDescW) * nFileCount);

	//�����ڴ汣�渽���ļ�·��
	TCHAR pTchPath[10][MAX_PATH] = { 0 };// new TCHAR[nFileCount][MAX_PATH];// (TCHAR**)malloc(MAX_PATH * nFileCount);
	CString szText;
	for (int i = 0; i < min(nFileCount, 10); i++)
	{
		szText = m_list.GetAt(i);
		_tcscpy_s(pTchPath[i], MAX_PATH, szText);
		(pFileDesc + i)->nPosition = (ULONG)-1;
		(pFileDesc + i)->lpszPathName = pTchPath[i];
		(pFileDesc + i)->lpszFileName = pTchPath[i];
	}

	//�ռ��˽ṹ��Ϣ
	MapiRecipDescW recip = { 0 };
	//memset(&recip, 0, sizeof(MapiRecipDescW));
	//recip.lpszAddress = L"";// m_szEmailMAPI.GetBuffer(0);
	recip.ulRecipClass = MAPI_TO;

	//�ʼ��ṹ��Ϣ
	MapiMessageW message;
	memset(&message, 0, sizeof(message));
	message.nFileCount = min(nFileCount, 10);
	//�ļ�����
	message.lpFiles = pFileDesc;
	////�ļ���Ϣ
	//message.nRecipCount = 1;
	////�ռ��˸���
	//message.lpRecips = &recip;
	////�ռ���
	//message.lpszSubject = L"";// m_szSubject.GetBuffer(0);
	////����
	//message.lpszNoteText = L"";// m_szText.GetBuffer(0);
	//��������

	//�����ʼ�
	int nError = lpfnSendMail(0, 0, &message, MAPI_LOGON_UI | MAPI_DIALOG, 0);
	bool bOk = !(nError != SUCCESS_SUCCESS && nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE);

	//��Ҫ�����ͷŷ�����ڴ�
	free(pFileDesc);
	//delete pTchPath[];
	FreeLibrary(hMod);

	return bOk;
}
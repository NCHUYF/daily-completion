#ifndef _CCAPTURE_SCREEN_HH
#define _CCAPTURE_SCREEN_HH

#include<time.h>
#include <d3d9.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>

#include <tchar.h>
#include <winbase.h>
#include <winreg.h>
#include <Strsafe.h>

class CScreenRecorder;

//
// ---ץ����----
//
class COMMONCONTROLS_API CCaptureScreen
{
public:
	CCaptureScreen(CScreenRecorder *pSR);
	CCaptureScreen(CScreenRecorder *pSR, int width, int height);
	~CCaptureScreen(void);

public:
	/*-----------�����ⲿ���ú���-----------*/
	int Init();//��ʼ��
	void GetSize(int &nWidth, int &nHeight); // ��ȡ���
	BYTE* CaptureImage(); //ץȡ��Ļ
	BYTE* CaptureImage(int left, int top, int width, int height); //ץȡ��Ļ
	void ShowMouse(bool bShow = true); // ��ʾ���
private:
	/*-----------�����ڲ����ú���-----------*/
	void AddText(PRGBTRIPLE hdib, int left, int top, int width, int height); // �������
	void* CaptureScreenFrame(int, int, int, int);//ץ��
	void DrawMouse(int left = 0, int top = 0); // �������
	HCURSOR FetchCursorHandle(); //��ȡ�����

private:
	/*-----------����˽�б���-----------*/
	int m_width;
	int m_height;
	UINT   wLineLen;
	DWORD  dwSize;
	DWORD  wColSize;

	//�豸���
	HDC hScreenDC;
	HDC hMemDC;
	//ͼ��RGB�ڴ滺��
	//λͼͷ��Ϣ�ṹ��
	BITMAPINFO pbi;

	HBITMAP hbm;
	//�����
	HCURSOR m_hSavedCursor;

	bool _bFullScreen = true;
	HCURSOR _hcur = nullptr;
	ICONINFO _iconinfo;
	bool _bShowMouse = true;
	CScreenRecorder *_pSR; // ¼��������ָ��
};

#endif //--_CCAPTURE_SCREEN_HH
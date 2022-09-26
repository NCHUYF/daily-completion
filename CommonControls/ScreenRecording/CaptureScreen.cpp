#include "stdafx.h"  // #include "stdafx.h" // #include "pch.h" // Ԥ����ͷ
#include "CaptureScreen.h"
#include "ScreenRecorder.h"

CCaptureScreen::CCaptureScreen(CScreenRecorder *pSR)
{
	// ȫ�����ã�ȱʡ��
	m_hSavedCursor = NULL;
	hScreenDC = NULL;
	hMemDC = NULL;
	hbm = NULL;
	_bFullScreen = true;
	_pSR = pSR;
	FetchCursorHandle();
	Init();
}

CCaptureScreen::CCaptureScreen(CScreenRecorder *pSR, int width, int height)
{
	// �������ã��вΣ�
	m_hSavedCursor = NULL;
	hScreenDC = NULL;
	hMemDC = NULL;
	hbm = NULL;

	m_width = width;
	m_height = height;
	_bFullScreen = false;
	_pSR = pSR;
	FetchCursorHandle();
	Init();
}
//
// �ͷ���Դ
//
CCaptureScreen::~CCaptureScreen(void)
{
	DeleteObject(hbm);
	if (hScreenDC){

		::ReleaseDC(NULL, hScreenDC);
	}
	if (hMemDC) {

		DeleteDC(hMemDC);
	}
	if (hbm)
	{
		DeleteObject(hbm);
	}
	// ��ȡ��Ļdc
	auto pWnd = _pSR ? _pSR->GetCurWnd() : NULL;
	auto hWnd = pWnd ? pWnd->GetSafeHwnd() : NULL;

	::ReleaseDC(hWnd ? hWnd : GetDesktopWindow(), hMemDC);
}

//
// ��ʼ��
//
int CCaptureScreen::Init()
{
	// ��ȡ��Ļdc
	auto pWnd = _pSR ? _pSR->GetCurWnd() : NULL;
	auto hWnd = pWnd ? pWnd->GetSafeHwnd() : NULL;

	hScreenDC = ::GetDC(hWnd ? hWnd : GetDesktopWindow());
	if (hScreenDC == NULL) return 0;

	int m_nMaxxScreen = GetDeviceCaps(hScreenDC, HORZRES);
	int m_nMaxyScreen = GetDeviceCaps(hScreenDC, VERTRES);

	hMemDC = ::CreateCompatibleDC(hScreenDC);
	if (hMemDC == NULL) return 0;

	if (_bFullScreen)
	{
		m_width = m_nMaxxScreen;
		m_height = m_nMaxyScreen;
	}
	// ��λΪ4�ı���
	if (m_width % 4 != 0 || m_height % 4 != 0)
	{
		m_width = m_width - m_width % 4;
		m_height = m_height - m_height % 4;
	}

	hbm = CreateCompatibleBitmap(hScreenDC, m_width, m_height);
	SelectObject(hMemDC, hbm);

	wLineLen = ((m_width * 24 + 31) & 0xffffffe0) / 8;
	wColSize = sizeof(RGBQUAD)* ((24 <= 8) ? 1 << 24 : 0);
	dwSize = (DWORD)(UINT)wLineLen * (DWORD)(UINT)m_height;

	//λͼͷ��Ϣ�ṹ��
	pbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbi.bmiHeader.biWidth = m_width;
	pbi.bmiHeader.biHeight = m_height;
	pbi.bmiHeader.biPlanes = 1;
	pbi.bmiHeader.biBitCount = 24;
	pbi.bmiHeader.biCompression = BI_RGB;
	pbi.bmiHeader.biSizeImage = dwSize;

	_hcur = LoadCursor(NULL, IDC_ARROW);

	return 1;
}

void CCaptureScreen::GetSize(int & nWidth, int & nHeight)
{
	nWidth = m_width;
	nHeight = m_height;
}

//ץȡ��Ļ����
BYTE* CCaptureScreen::CaptureImage()
{

	VOID*  alpbi = CaptureScreenFrame(0, 0, m_width, m_height);
	return (BYTE*)(alpbi);
}

BYTE* CCaptureScreen::CaptureImage(int left, int top, int width, int height)
{

	VOID*  alpbi = CaptureScreenFrame(left, top, width, height);
	return (BYTE*)(alpbi);
}
void CCaptureScreen::ShowMouse(bool bShow)
{
	_bShowMouse = bShow;
}

void CCaptureScreen::AddText(PRGBTRIPLE hdib, int left, int top, int width, int height)
{
	if (_pSR == NULL)
		return;

	CFont font;
	CSize fontSize;

	// ���ִ�С
	fontSize.cx = 20;
	fontSize.cy = 40;

	// ����λ��
	CSize fontPos;
	fontPos = _pSR->GetTextPos();

	if (fontPos.cx == 0 && fontPos.cy == 0)
	{
		// ����Ĭ����Ļλ��
		fontPos = CSize(left + width / 2, top + height * 7 / 8);
	}

	font.CreateFont(fontSize.cy, fontSize.cx, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FF_SWISS, L"����");
	SelectObject(hMemDC, font);

	// ͨ��DC�����ȡDC����ָ��
	CDC *pDC = CDC::FromHandle(hMemDC);
	if (pDC == NULL)
		return;

	// �������ֱ���͸��
	pDC->SetBkMode(TRANSPARENT);

	// ����������ɫ
	pDC->SetTextColor(RGB(100, 175, 100));

	// �������־���
	pDC->SetTextAlign(TA_CENTER);

	// ������ֵ�ָ��λ��
	pDC->TextOut(fontPos.cx, fontPos.cy, _pSR->GetText());



	GetDIBits(hMemDC, hbm, 0, m_height, hdib, (LPBITMAPINFO)&pbi, DIB_RGB_COLORS);
}

void* CCaptureScreen::CaptureScreenFrame(int left, int top, int width, int height)
{

	if (hbm == NULL || hMemDC == NULL || hScreenDC == NULL) return NULL;

	BitBlt(hMemDC, 0, 0, width, height, hScreenDC, left, top, SRCCOPY);
	
	if(_bShowMouse)
		DrawMouse(left, top);

	//��̬������ڴ�
	PRGBTRIPLE hdib = (PRGBTRIPLE)malloc(pbi.bmiHeader.biSizeImage);//24λͼ���С
	GetDIBits(hMemDC, hbm, 0, m_height, hdib, (LPBITMAPINFO)&pbi, DIB_RGB_COLORS);

	// �������
	AddText(hdib, left, top, width, height);

	return hdib;
}

// �������
void CCaptureScreen::DrawMouse(int left, int top)
{
	/*-------------------------�������-------------------------------*/
	{
		POINT xPoint;
		GetCursorPos(&xPoint);
		
		xPoint.x -= left;
		xPoint.y -= top;

		BOOL ret;
		ret = GetIconInfo(_hcur, &_iconinfo);
		if (ret) {
			xPoint.x -= _iconinfo.xHotspot;
			xPoint.y -= _iconinfo.yHotspot;

			if (_iconinfo.hbmMask) DeleteObject(_iconinfo.hbmMask);
			if (_iconinfo.hbmColor) DeleteObject(_iconinfo.hbmColor);
		}
		/*�����*/
		::DrawIcon(hMemDC, xPoint.x, xPoint.y, _hcur);
	}
}

//
// ��ȡ���������
//
HCURSOR CCaptureScreen::FetchCursorHandle()
{
	if (m_hSavedCursor == NULL)
	{
		m_hSavedCursor = GetCursor();
	}
	return m_hSavedCursor;
}
#include "stdafx.h"// #include "stdafx.h" // #include "pch.h" // Ԥ����ͷ
#include "FFmpegRecorder.h"


CFFmpegRecorder::CFFmpegRecorder()
{
	_ffmpegInfo._pCurWnd = NULL;
	_ffmpegInfo._fps = 50;
	_ffmpegInfo._bFullScreen = true;
	_ffmpegInfo._bMouse = TRUE;
}

CFFmpegRecorder::~CFFmpegRecorder()
{
	TerminateProcess(_releaseThread, -1);
	//WaitForSingleObject(_releaseThread, INFINITE);
	char cmd[] = "taskkill /t /im ffmpeg.exe"; // /f����ǿ�ƽ������̣����ܵ���ȱ֡��
	WinExec(cmd, SW_HIDE);
	Release();
	if (_releaseThread)
	{
		//CloseHandle(_releaseThread);
		delete _releaseThread;
		_releaseThread = NULL;
	}
}

void CFFmpegRecorder::SetFFmpegPath(const CString & strPath)
{
	_ffmpegInfo._strFFmpegPath = strPath;
}

CString CFFmpegRecorder::GetFFmpegPath()
{
	return _ffmpegInfo._strFFmpegPath;
}

bool CFFmpegRecorder::StartRecording()
{
	Release();
	
	CString exe = GetFFmpegPath();
	if (exe.IsEmpty())
	{
		return false;
	}
	exe.Append(L" -f gdigrab -framerate 50 -offset_x ");
	CString strVal;
	strVal.Format(L"%d", _ffmpegInfo._x);
	exe.Append(strVal);//��ȡ�����Ͻ�x
	exe.Append(L" -offset_y ");
	strVal.Format(L"%d", _ffmpegInfo._y);
	exe.Append(strVal);//��ȡ�����Ͻ�y
	exe.Append(L" -video_size ");
	strVal.Format(L"%d", _ffmpegInfo._width);
	exe.Append(strVal);
	exe.Append(L"x");
	strVal.Format(L"%d", _ffmpegInfo._height);
	exe.Append(strVal);
	strVal.Format(L"%d", _ffmpegInfo._bMouse);
	exe.Append(L" -draw_mouse " + strVal + L" ");


	exe.Append(L" -i title=CFFmpegRecorderWnd ");

	/*exe.Append(L"-s $(xwininfo -id " + _ffmpegInfo._strId + L" | awk \'/geometry/ {print $2}\' | awk 'BEGIN {FS=\" + \"}");
	exe.Append(L" {print $1}\') $(xwininfo -id " + _ffmpegInfo._strId + L" | awk \'/Absolute upper-left X/ {print $4}\'),$(xwininfo -id " + _ffmpegInfo._strId + L" | awk \'/Absolute upper-left Y/ {print $4}\')\") ");
*/
	exe.Append(_ffmpegInfo._tempPath);

	STARTUPINFO si = { sizeof(si) };

	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = FALSE;
	auto szEXE = exe.GetBuffer();
	if (!CreateProcess(NULL, szEXE, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &_ffmpegInfo._pi))
	{
		exe.ReleaseBuffer();
		
		return false;
	}

	exe.ReleaseBuffer();
	
	return true;
}


void CFFmpegRecorder::StopRecording()
{
	char cmd[] = "taskkill /f /t /im ffmpeg.exe"; // /f����ǿ�ƽ������̣����ܵ���ȱ֡��
	//char cmd[] = "taskkill ffmpeg.exe"; // /f����ǿ�ƽ������̣����ܵ���ȱ֡��
	WinExec(cmd, SW_HIDE);

	_releaseThread = (HANDLE)_beginthreadex(NULL, 0, &CFFmpegRecorder::ReleaseThread, (LPVOID)this, 0, NULL);
	if (_ffmpegInfo._pCurWnd)
	{
		_ffmpegInfo._pCurWnd->SetWindowText(_ffmpegInfo._strTitle);
	}

}

void CFFmpegRecorder::SetScreenRect(const CRect & rect)
{
	_ffmpegInfo._x = rect.left;
	_ffmpegInfo._y = rect.top;

	_ffmpegInfo._width = rect.Width();
	_ffmpegInfo._height = rect.Height();

	// ��λΪ4�ı���
	if (_ffmpegInfo._width % 4 != 0 || _ffmpegInfo._height % 4 != 0)
	{
		_ffmpegInfo._width = _ffmpegInfo._width - _ffmpegInfo._width % 4;
		_ffmpegInfo._height = _ffmpegInfo._height - _ffmpegInfo._height % 4;
	}

	_ffmpegInfo._bFullScreen = false;
}

void CFFmpegRecorder::SetScreenRect(CWnd * pWnd)
{
	if (!pWnd)
		return;
	//// ����¼������
	CRect rcDlg;
	pWnd->GetClientRect(&rcDlg);
	//pWnd->ClientToScreen(&rcDlg);
	SetScreenRect(rcDlg);
	_ffmpegInfo._pCurWnd = pWnd;

	CString strTitle;
	pWnd->GetWindowText(strTitle);
	SetCatchWndTitle(strTitle);
	pWnd->SetWindowText(_T("CFFmpegRecorderWnd"));
}

void CFFmpegRecorder::SetCatchWndTitle(const CString & strTitle)
{
	_ffmpegInfo._strTitle = strTitle;

	_ffmpegInfo._pCurWnd = CWnd::FindWindow(NULL, _ffmpegInfo._strTitle);
	if (_ffmpegInfo._pCurWnd == NULL)
		return;

	CRect rcWnd;
	_ffmpegInfo._pCurWnd->GetClientRect(&rcWnd);
	_ffmpegInfo._x = rcWnd.left;
	_ffmpegInfo._y = rcWnd.top;
	_ffmpegInfo._width = rcWnd.Width() - rcWnd.Width() % 4;
	_ffmpegInfo._height = rcWnd.Height() - rcWnd.Height() % 4;
}

void CFFmpegRecorder::SetSaveFileName(const CString & strSaveFileName)
{
	// ���ñ���·��
	_ffmpegInfo._savePath = strSaveFileName;
	
	// ������ʱ·��
	_ffmpegInfo._tempPath = strSaveFileName;
	int nExtIndex = _ffmpegInfo._tempPath.ReverseFind(_T('.'));
	int nExtLength = _ffmpegInfo._tempPath.GetLength() - nExtIndex;
	_ffmpegInfo._tempPath.Replace(_ffmpegInfo._tempPath.Right(nExtLength), _T(".mpg"));
}

void CFFmpegRecorder::SetFPS(int nFPS)
{
	_ffmpegInfo._fps = nFPS;
}

int CFFmpegRecorder::GetFPS()
{
	return _ffmpegInfo._fps;
}

void CFFmpegRecorder::SetFullScreen(bool bFullScreen)
{
	_ffmpegInfo._bFullScreen = bFullScreen;
}

void CFFmpegRecorder::ShowMouse(bool bShow)
{
	_ffmpegInfo._bMouse = bShow;
}

CWnd * CFFmpegRecorder::GetCurWnd()
{
	return _ffmpegInfo._pCurWnd;
}

BOOL CFFmpegRecorder::Release()
{
	TerminateProcess(_ffmpegInfo._pi.hProcess, -1);
	return TRUE;
}

BOOL CFFmpegRecorder::TranscodingVideo()
{
	CString strCmd;
	strCmd.Format(_T("%s -i %s -vcodec libx264 -acodec aac %s"), _ffmpegInfo._strFFmpegPath, _ffmpegInfo._tempPath, _ffmpegInfo._savePath);
	auto szCommandLine = strCmd.GetBuffer();

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION  pi;
	si.wShowWindow = FALSE;
	si.dwFlags = STARTF_USESHOWWINDOW;
	if (!::CreateProcess(NULL, szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		strCmd.ReleaseBuffer();
		return false;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);//�ȴ��������
	//if (PathFileExists(_ffmpegInfo._tempPath))
	//{
	//	if (!DeleteFile(_ffmpegInfo._tempPath))
	//	{
	//		// �м��ļ���ռ��
	//		return FALSE;
	//	}
	//}
	strCmd.ReleaseBuffer();

	return true;
}

unsigned __stdcall CFFmpegRecorder::ReleaseThread(void * pParam)
{
	CFFmpegRecorder *pSR = (CFFmpegRecorder *)pParam;
	if (pSR == NULL)
	{
		return 0;
	}
	Sleep(5000);
	pSR->Release(); // �ͷ�¼������
	char cmd2[] = "taskkill /f /t /im ffmpeg.exe"; // /f����ǿ�ƽ������̣����ܵ���ȱ֡��
	WinExec(cmd2, SW_HIDE);

	pSR->TranscodingVideo(); // ת����Ƶ

	return 0;
}



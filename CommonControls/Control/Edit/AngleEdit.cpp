#include "StdAfx.h"
#include "AngleEdit.h"
#include <cassert>

#define MAX_TEXT_CHAR 12

IMPLEMENT_DYNAMIC(CAngleEdit, CEdit)

BEGIN_MESSAGE_MAP(CAngleEdit, CEdit)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(SWITCH_TO_NEXT_PART, OnSwitchToNextPart)
END_MESSAGE_MAP()

CAngleEdit::CAngleEdit()
{
}

CAngleEdit::~CAngleEdit()
{
}

CString CAngleEdit::GetSeparatorCharPos(INT &degreeCharPos, INT &minuteCharPos, INT &secondCharPos)
{
	degreeCharPos = minuteCharPos = secondCharPos = -1;

	TCHAR textBuf[MAX_TEXT_CHAR] = { 0 };
	GetWindowText(textBuf, MAX_TEXT_CHAR);

	for (INT i = 0; i < MAX_TEXT_CHAR; ++i)
	{
		if (textBuf[i] == DEGREE_CHAR)
			degreeCharPos = i;
		else if (textBuf[i] == MINUTE_CHAR)
			minuteCharPos = i;
		else if (textBuf[i] == SECOND_CHAR)
			secondCharPos = i;
	}

	return textBuf;
}

void CAngleEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// ʹ�ð�ť�ƶ�����һ�������
	if (nChar == VK_SPACE || nChar == VK_DECIMAL)
	{
		// �Զ�ѡ����һ�������
		AutoSelectPart(TRUE);
		return;
	}

	//ֻ��ʹ�����Ұ����������ո񡢵��, ������Shift+��ͷѡ��
	if (((nChar == VK_LEFT || nChar == VK_RIGHT) && !(GetKeyState(VK_SHIFT) & 0x8000)) || nChar == VK_BACK)
	{
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CAngleEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bHandle = TRUE;
	if (nChar == 8 /*��*/)
	{
		// ����ɾ���ַ�
		bHandle = ProcessDelChart();
	}
	// ���������ַ�,ֻ������ 0-9 �� -��
	else if ((nChar >= 48/*0*/ && nChar <= 57/*9*/) || nChar == 45 || /* -��*/ nChar == 8 /*��*/)
	{
		// ���������ȷ��
		bHandle = ValidateInput(nChar);
	}

	if (!bHandle)
		CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CAngleEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	// �������ѡ��
}

void CAngleEdit::SetEditFocus(void)
{
	SetFocus();

	//���Ҷ��ַ�λ
	INT degreeCharPos, minuteCharPos, secondCharPos;
	GetSeparatorCharPos(degreeCharPos, minuteCharPos, secondCharPos);

	SetSel(0, degreeCharPos); /*ѡ�ж�*/
}

// ����˫ʱѡ�з�Χ
void CAngleEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// ��˫��λ���Զ�ѡ�������ı�
	AutoSelectPart();
}

void CAngleEdit::AutoSelectPart(BOOL isSwitch)
{
	// ��ȡѡ��λ��
	INT stPos, edPos;
	GetSel(stPos, edPos);

	INT ptCharPos = edPos;
	ATLASSERT(ptCharPos != -1);

	//���Ҷ��ַ�λ
	INT degreeCharPos, minuteCharPos, secondCharPos;
	GetSeparatorCharPos(degreeCharPos, minuteCharPos, secondCharPos);

	ATLASSERT(degreeCharPos != -1 && minuteCharPos != -1 && secondCharPos != -1);

	// �жϹ�����ĸ����ݷ�Χ��
	if (ptCharPos <= degreeCharPos)
	{
		isSwitch ? SetSel(degreeCharPos + 1, minuteCharPos) /*ѡ�з�*/ : SetSel(0, degreeCharPos); /*ѡ�ж�*/

	}
	else if (ptCharPos > degreeCharPos && ptCharPos <= minuteCharPos)
	{
		isSwitch ? SetSel(minuteCharPos + 1, secondCharPos)/*ѡ����*/ : SetSel(degreeCharPos + 1, minuteCharPos); /*ѡ�з�*/

	}
	else if (ptCharPos > minuteCharPos && ptCharPos <= secondCharPos)
	{
		isSwitch ? SetSel(0, degreeCharPos) /*ѡ�ж�*/ : SetSel(minuteCharPos + 1, secondCharPos); /*ѡ����*/

	}
	else if (ptCharPos >= secondCharPos)
	{
		SetSel(0, degreeCharPos); /*ѡ�ж�*/
	}
}

BOOL CAngleEdit::ProcessDelChart()
{
	// ��ȡѡ��λ��
	INT stPos, edPos;
	GetSel(stPos, edPos);

	INT ptCharPos = edPos;
	ATLASSERT(ptCharPos != -1);

	//���Ҷ��ַ�λ
	INT degreeCharPos, minuteCharPos, secondCharPos;
	GetSeparatorCharPos(degreeCharPos, minuteCharPos, secondCharPos);

	//���ɾ�����ַ�Ϊ�ָ�����ֻ�ƶ���ǰһ���������
	if (ptCharPos == (degreeCharPos + 1) || ptCharPos == (minuteCharPos + 1) || ptCharPos == (secondCharPos + 1))
	{
		SetSel(ptCharPos - 1, ptCharPos - 1);
		return TRUE;
	}

	//���ɾ������������һ������������ָĳ�0���ƶ���ǰһ���������
	//�жϹ�����ĸ����ݷ�Χ��
	if (ptCharPos <= degreeCharPos && degreeCharPos - edPos + stPos <= 1)
	{
		SetSel(0, degreeCharPos);
		ReplaceSel(L"0");
		SetSel(0, 1);
		return TRUE;
	}
	else if (ptCharPos > degreeCharPos && ptCharPos <= minuteCharPos &&
		(minuteCharPos - degreeCharPos - edPos + stPos <= 2))
	{
		SetSel(degreeCharPos + 1, minuteCharPos);
		ReplaceSel(L"0");
		SetSel(degreeCharPos, degreeCharPos);
		return TRUE;
	}
	else if (ptCharPos > minuteCharPos && ptCharPos <= secondCharPos &&
		(secondCharPos - minuteCharPos - edPos + stPos <= 2))
	{
		SetSel(minuteCharPos + 1, secondCharPos);
		ReplaceSel(L"0");
		SetSel(minuteCharPos, minuteCharPos);
		return TRUE;
	}
	else if (ptCharPos > secondCharPos)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CAngleEdit::ValidateInput(TCHAR inChar)
{
	//��ȡ�ı������Ҷ��ַ�λ
	INT degreeCharPos, minuteCharPos, secondCharPos;
	CString strText = GetSeparatorCharPos(degreeCharPos, minuteCharPos, secondCharPos);
	ATLASSERT(degreeCharPos != -1 && minuteCharPos != -1 && secondCharPos != -1);

	// ��ȡѡ��λ��
	INT stPos, edPos;
	GetSel(stPos, edPos);
	INT ptCharPos = edPos;

	//����ֻ���ʼ����
	if (inChar == 45 /*����*/ && stPos != 0)
		return TRUE;

	// ������������ַ�
	if (edPos >= strText.GetLength())
		return TRUE;

	// ɾ��ѡ���ַ��������������ַ�, ģ��༩��������
	strText.Delete(stPos, edPos - stPos);
	strText.Insert(stPos, inChar);

	// ����������λ��
	INT degreePos = strText.Find(DEGREE_CHAR, 0);
	INT minutePos = strText.Find(MINUTE_CHAR, degreePos);
	INT secondPos = strText.Find(SECOND_CHAR, minutePos);

	// ��������Ϸ���
	CString strDegree = strText.Left(degreePos);
	INT degreeVal = _ttoi(strDegree);
	if (degreeVal >= 180 || degreeVal <= -180)
		return TRUE; // ���벻�Ϸ�

	if (ptCharPos <= degreeCharPos)
	{
		// �����ַ��������4��
		if (strDegree.GetLength() > 4)
			return TRUE; // ���벻�Ϸ�

		// ��������0�Զ�����
		if (strDegree.Find(L"-") != -1)
		{
			if (strDegree.GetLength() > 2 && degreeVal >= -9)
				SetSel(1, 2);
		}
		else
		{
			if (strDegree.GetLength() > 1 && degreeVal <= 9)
				SetSel(0, 1);
		}

		// �Զ��л�����һ�����
		if (degreeVal > 99 || degreeVal < -99 || degreeVal >= 18 || degreeVal <= -18)
			PostMessage(SWITCH_TO_NEXT_PART, 0);

	}
	else if (ptCharPos > degreeCharPos && ptCharPos <= minuteCharPos)
	{
		// ��������Ϸ���
		CString strMinute = strText.Mid(degreePos + 1, minutePos - degreePos - 1);

		// �����ַ��������2��
		if (strMinute.GetLength() > 2)
			return TRUE; // ���벻�Ϸ�

		INT minuteVal = _ttoi(strMinute);
		if (minuteVal > 59 || minuteVal < 0)
			return TRUE; // ���벻�Ϸ�

		// ��������0�Զ�����
		if (strMinute.GetLength() > 1 && minuteVal <= 9)
			SetSel(degreeCharPos + 1, degreeCharPos + 2);

		// �Զ��л�����һ�����
		if (minuteVal > 9 || (minuteVal >= 6 && strMinute.GetLength() == 1))
			PostMessage(SWITCH_TO_NEXT_PART, 0);

	}
	else if (ptCharPos > minuteCharPos && ptCharPos <= secondCharPos)
	{
		// ��������Ϸ���
		CString strSecond = strText.Mid(minutePos + 1, secondPos - minutePos - 1);
		// �����ַ��������2��
		if (strSecond.GetLength() > 2)
			return TRUE; // ���벻�Ϸ�

		INT secondVal = _ttoi(strSecond);
		if (secondVal > 59 || secondVal < 0)
			return TRUE; // ���벻�Ϸ�

		// ��������0�Զ�����
		if (strSecond.GetLength() > 1 && secondVal <= 9)
			SetSel(minuteCharPos + 1, minuteCharPos + 2);

		// �Զ��л�����һ�����
		if (secondVal > 9 || (secondVal >= 6 && strSecond.GetLength() == 1))
			PostMessage(SWITCH_TO_NEXT_PART, 1);
	}

	return FALSE;
}

CString CAngleEdit::GetAngleText(void)
{
	CString strRetVal;
	CString strAngle, strMin, strSecond;

	// ��ȡ�Ƕ�ֵ
	GetAngleStrValue(strAngle, strMin, strSecond);

	if (strAngle.IsEmpty())
		strAngle = _T("0");

	if (strMin.IsEmpty())
		strMin = _T("0");

	if (strSecond.IsEmpty())
		strSecond = _T("0");

	strRetVal.Format(_T("%s��%s��%s��"), strAngle, strMin, strSecond);
	return strRetVal;
}

// ��ȡ�Ƕ�ֵ
void CAngleEdit::GetAngleStrValue(CString& degreeVal, CString& minuteVal, CString& secondVal)
{
	//���Ҷ��ַ�λ
	INT degreeCharPos, minuteCharPos, secondCharPos;
	GetSeparatorCharPos(degreeCharPos, minuteCharPos, secondCharPos);

	CString strText;
	GetWindowText(strText);
	degreeVal = strText.Left(degreeCharPos);
	minuteVal = strText.Left(minuteCharPos).Right(minuteCharPos - degreeCharPos - 1);
	secondVal = strText.Left(secondCharPos).Right(secondCharPos - minuteCharPos - 1);
}

LRESULT	CAngleEdit::OnSwitchToNextPart(WPARAM wParam, LPARAM lParam)
{
	if (!wParam)
	{
		AutoSelectPart(TRUE);
	}
	else
	{
		INT textLen = GetWindowTextLength();
		SetSel(textLen, textLen);
	}
	return TRUE;
}

double CAngleEdit::GetArcValue()
{
	// ��ȡ�Ƕ�ֵ
	CString degreeVal, minuteVal, secondVal;
	GetAngleStrValue(degreeVal, minuteVal, secondVal);

	long nAngle = _ttol(degreeVal);
	long nMin = _ttol(minuteVal);
	long nSec = _ttol(secondVal);

	if (nAngle < 0)
	{
		nMin = -nMin;
		nSec = -nSec;
	}

	return M_PI * ((double)nAngle + (double)nMin / 60.0f + (double)nSec / 3600.0f) / 180.0f;
}

void CAngleEdit::SetArcValue(double dVal)
{
// 	ASSERT(FALSE);
// 	int nAngle,nMin,nSec;
// 	CGeometry::ArcDegree2AngleDegree(dVal, nAngle, nMin, nSec);
// 
// 	CString strValue;
// 	strValue.Format(_T("%d��%d��%d��"), nAngle, dVal > 0 ? nMin : -nMin, dVal > 0 ? nSec : -nSec);
// 	if (dVal < 0 && nAngle == 0)
// 	{
// 		strValue.Insert(-1, _T("-"));
// 	}
// 	SetWindowText(strValue);
}

double CAngleEdit::GetAngleValue()
{
	// ��ȡ�Ƕ�ֵ
	CString degreeVal,minuteVal,secondVal;
	GetAngleStrValue(degreeVal, minuteVal, secondVal);

	long nAngle = _ttol(degreeVal);
	long nMin = _ttol(minuteVal);
	long nSec = _ttol(secondVal);

	if (nAngle < 0)
	{
		nMin = -nMin;
		nSec = -nSec;
	}

	return (double)nAngle + (double)nMin / 60.0f + (double)nSec / 3600.0f;
}

void CAngleEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	CString strDegree, strMinute, strSecond;
	GetAngleStrValue(strDegree, strMinute, strSecond);
	if (strDegree == _T("-"))
	{
		if ((strMinute == _T("0")) && (strSecond == _T("0")))
		{
			strDegree = _T("0");
		}
		else
		{
			strDegree = _T("-0");
		}
	}
	if (strDegree == _T("-0") && strMinute == _T("0") && strSecond == _T("0"))
	{
		strDegree = _T("0");
	}
	CString strValue;
	strValue.Format(_T("%s��%s��%s��"), strDegree, strMinute, strSecond);

	SetWindowText(strValue);
}

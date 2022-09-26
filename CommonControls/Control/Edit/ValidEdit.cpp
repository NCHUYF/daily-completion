#include "StdAfx.h"
#include "ValidEdit.h"

// �ر���ʾ��ʱ��
#define TM_BALLOONTIP 2015

IMPLEMENT_DYNAMIC(CValidEdit, CBCGPEdit)

CValidEdit::CValidEdit()
{
	_digitNum = 8;
	_dotNum = 8;
	_bInPaste = false;
	_nFlag = eNormalEdit;
	_maxValue = 1000000000000000;
	_minValue = -1000000000000000;
	_bShowLimitTip = false;
}

CValidEdit::~CValidEdit()
{
}

BEGIN_MESSAGE_MAP(CValidEdit, CBCGPEdit)
	ON_MESSAGE(WM_CHAR, OnChar)
	ON_MESSAGE(WM_PASTE, OnPaste)
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

void CValidEdit::SetEditFlag(int nFlag)
{
	_nFlag = nFlag;
}

void CValidEdit::SetDotNum(int nDotNum)
{
	_dotNum = nDotNum;
}

void CValidEdit::SetDigitNum(int nDigitNum)
{
	_digitNum = nDigitNum;
}

bool CValidEdit::Validate()
{
	CString strText;
	GetWindowText(strText);
	strText.Trim();

	if ((_nFlag & eFileNameEdit) && strText.IsEmpty())
	{
		ShowBalloonTip(L"�ļ�������Ϊ��", L"��������ȷ���ļ�����");
		return false;
	}
	if ((_nFlag & eVeNoEmpty) && strText.IsEmpty())
	{
		ShowBalloonTip(L"��ֵ����Ϊ��", L"��������ȷ����ֵ��");
		return false;
	}

	double dText = CStringToolkit::StrToDouble((LPCTSTR)strText);
	if ((_nFlag & eVeNoZero) && FLOAT_EQUAL8(dText, 0.0))
	{
		ShowBalloonTip(L"��ֵ����Ϊ��", L"��������ȷ����ֵ��");
		return false;
	}

	if (!(_nFlag & eFileNameEdit) && dText < _minValue)
	{
		double minValue = _minValue;

		if (!(_nFlag & eVeNegative) && minValue < 0)
		{
			minValue = 0;
		}

		CString strLimit, strFormat;

		strFormat.Format(L"��ֻ���ڴ˼��� %%.%df �� %%.%df ��Χ����ֵ��", _dotNum, _dotNum);
		strLimit.Format(strFormat, minValue, _maxValue);

		if (_bShowLimitTip)
			ShowBalloonTip(L"���ܽ��ܵ���ֵ��Χ", strLimit);

		return false;
	}

	return true;
}

LRESULT CValidEdit::OnPaste(WPARAM wParam, LPARAM lParam)
{
	// ��ͨ�༭��
	if (_nFlag & eNormalEdit)
	{
		Default();
		return 0;
	}

	// �������Ϸ���
	if ( !CheckInvaildate(true) )
	{
		_bInPaste = true;

		if (_nFlag & eFileNameEdit)
		{
			ShowBalloonTip(L"�ļ������ܰ��������κ��ַ�:", L"		\\ / : * ? \" < > |");
		}
		else
		{
			ShowBalloonTip(L"���ܽ��ܵĸ�ʽ", L"��ֻ���ڴ�ճ����ȷ����ֵ��");
		}
	}

	return 0;
}

LRESULT CValidEdit::OnChar(WPARAM wParam, LPARAM lParam)
{
	// ��ͨ�༭��
	if (_nFlag & eNormalEdit)
	{
		Default();
		return 0;
	}

	_bInPaste = false;

	if (wParam == L'��')
		wParam = L'.';

	// �����������ַ�(�ո���TAB����������)
	if (!(_nFlag & eFileNameEdit) 
			&& (wParam == L' ' || wParam > 127) )
	{
		ShowBalloonTip(L"���ܽ��ܵ��ַ�", L"��ֻ���ڴ˼�����ֵ��");
		return 0;
	}

	// �������Ϸ���
	CheckInvaildate();

	return 0;
}

bool CValidEdit::CheckInvaildate(bool bRound)
{
	bool bResult = false;

	CString strText;
	GetWindowText(strText);
	DWORD curSel = GetSel();

	SetRedraw(FALSE);
	Default();

	// ���������ϻ�ԭ
	if ((_nFlag & eFileNameEdit) ?
		!IsFileNameValidate() : !IsDigitValidate(bRound) )
	{
		SetWindowText(strText);
		SetSel(curSel);
	}
	else
	{
		bResult = true;

		// ����������ʾ,����ճ��ʱ
		if (!_bInPaste)
			Edit_HideBalloonTip(m_hWnd);
	}

	SetRedraw(TRUE);
	Invalidate();

	return bResult;
}

bool CValidEdit::IsFileNameValidate()
{
	CString strText;
	GetWindowText(strText);

	TCHAR* pStrInv = L"\\/:*?\"<>|";
	bool bResult = (-1 == strText.FindOneOf(pStrInv));

	if ( !bResult )
	{
		ShowBalloonTip(L"�ļ������ܰ��������κ��ַ�:", L"		\\ / : * ? \" < > |");
	}

	return bResult;
}

bool CValidEdit::IsDigit(const CString& strText)
{
	bool bFoundNum = false;
	if ( strText.IsEmpty() )
		return true; 

	if ( strText.GetLength() == 1 && strText == _T("-") )
		return true;

	if ( strText.Left(1) == _T("."))
		return false;

	int dotCt = 0; // ��ż��������ж������Ϊ��Ч
	UINT ct = strText.GetLength();
	for( UINT i = 0; i < ct; ++i )
	{
		const TCHAR chr = strText.GetAt(i);
		// ��ǰ�ַ�Ϊ����
		if (chr == 45/*"-"*/|| chr == 43 /*"+"*/)
		{
			// ���ڵ�һλ
			if ( i != 0 ) return false;
			continue;
		}
		// ��ż�����
		if ( chr == 46 /*"."*/ ) 
		{
			dotCt++;
			// ����������
			if ( dotCt > 1 ) return false;
			continue;
		}
		// ���ַ�Χ
		if ( chr < 48 || chr > 57 )
			return false;

		bFoundNum = true;
	}
	return bFoundNum;
}

bool CValidEdit::FloatEqual(double dOriValue, CString strTag, int nDec)
{
	CString strOri = CStringToolkitEx::DblToStr(dOriValue);
	if (strOri == strTag)
		return true;

	int nIndex = strOri.Find(L".");
	int nIndexTag = strTag.Find(L".");

	CString strOriNew, strTagNew;
	strOriNew = nIndex == -1 ? strOri : strOri.Left(nIndex + nDec + 1);
	strTagNew = nIndexTag == -1 ? strTag : strTag.Left(nIndexTag + nDec + 1);
	strOriNew.TrimRight(L".");
	strTagNew.TrimRight(L".");
	bool bRet = (strOriNew == strTagNew);
	return (strOriNew == strTagNew);
}

bool CValidEdit::IsDigitValidate(bool bRound)
{	
	CString strText;
	GetWindowText(strText);

	if ( strText.IsEmpty() )
		return true;

	// �ո���TAB����������
	if ( strText.Find(L" ") != -1 || strText.Find(L"\t") != -1 )
		return false;

	int nChDot = strText.Replace(L"��", L".");

	// ��������
	if ( !IsDigit(strText) )
	{
		ShowBalloonTip(L"���ܽ��ܵ��ַ�", L"��ֻ���ڴ˼�����ֵ��");
		return false;
	}

	// �������
	if ((strText.Left(1) != L"-") && (strText.Left(1) != L"0") && (_nFlag & eVeNotPositive))
	{
		ShowBalloonTip(L"���ܽ�������", L"��ֻ���ڴ˼��븺����");
		return false;
	}

	// �������
	if ( (strText.Left(1) == L"-") && !(_nFlag & eVeNegative) )
	{
		ShowBalloonTip(L"���ܽ��ܸ���", L"��ֻ���ڴ˼���������");
		return false;
	}

	// ���Ʒ�Χ
	if ((_ttof(strText) > 100 || _ttof(strText) < 0)
		&& (_nFlag & eVeLimitRange))
	{
		ShowBalloonTip(L"��ֵ������Χ", L"��ֻ���ڴ˼���0-100֮�������");
		return false;
	}

	if (!(_nFlag & eVePreZero))
	{
		// ����ǰ��0���
		if (!(_nFlag & eVeDecimal))
		{
			// ����������0ʱ���
			if (((strText.Left(1) == L"0" || strText.Left(2) == L"-0")
				&& (_nFlag & eVeNoZero))
				|| ((strText.Left(2) == L"-0" || (strText.GetLength() > 1
				&& strText.Left(1) == L"0")) && !(_nFlag & eVeNoZero))) // ��������0ʱ���
			{
				ShowBalloonTip(L"���ܽ��ܵĸ�ʽ", L"��ֻ���ڴ˼�����ȷ����ֵ��");
				return false;
			}
		}
		// С��ǰ��0���
		else if ((strText.Left(2) == L"-.")
			|| ((strText.Left(1) == L"0") &&
			(strText.GetLength() > 1 && strText.Mid(1, 1) != L"."))	//0x ���
			|| ((strText.Left(2) == L"-0") &&
			(strText.GetLength() > 2 && strText.Mid(2, 1) != L".")))  //-0x ���
		{
			ShowBalloonTip(L"���ܽ��ܵĸ�ʽ", L"��ֻ���ڴ˼�����ȷ��С����");
			return false;
		}
	}

	// ��ȡС��λ��
	int dotPos = strText.Find(L".");
	int dotNum = (dotPos!=-1)? strText.GetLength()-dotPos-1:0;

	// ��ȡ��ǰλ��
	int digitNum = strText.GetLength();

	// ���λ�����
	if (digitNum > _digitNum && (_nFlag & eVeDigitLimit))
	{
		CString strDigitNum;
		strDigitNum.Format(L"��ֻ���ڴ˼���%dλ��", _digitNum);
		ShowBalloonTip(L"���ܽ��ܵ����λ��", strDigitNum);
		return false;
	}

	// �������
	if ((dotNum > 0 || dotNum == 0 && dotPos != -1) && !(_nFlag & eVeDecimal))
	{
		ShowBalloonTip(L"���ܽ��ܵ��ַ�", L"��ֻ���ڴ˼���������");
		return false;
	}

	// С��λ�ü��
	if ( dotNum > _dotNum && (_nFlag & eVeDotNum) )
	{
		if ( !bRound )
		{
			CString strDotNum;
			strDotNum.Format(L"��ֻ���ڴ˼���%dλС����",_dotNum);
			ShowBalloonTip(L"���ܽ��ܵ�С��λ��", strDotNum);
			return false;
		}

		// ������������
		CString strFormat;
		strFormat.Format(L"%%.%df", _dotNum);

		double val = _wtof(strText);
		CString strValue;
		strValue.Format(strFormat, val);
		SetWindowText(strValue);

		return true;
	}
	
	double dblValue = _wtof(strText);
	int nIndex = strText.Find(L".");
	int nDot = nIndex == -1 ? 0 : strText.GetLength() - nIndex - 1;
	if (dblValue > _maxValue || (!DataConvert::FloatEqual(DBL_MIN, _minValue, nDot) && !FloatEqual(_minValue, strText, nDot) && dblValue < _minValue))
	{
		double minValue = _minValue;

		if (!(_nFlag & eVeNegative) && minValue < 0)
		{			
			minValue = 0;
		}

		CString strLimit,strFormat;

		strFormat.Format(L"��ֻ���ڴ˼��� %%.%df �� %%.%df ��Χ����ֵ��", _dotNum, _dotNum);
		strLimit.Format(strFormat, minValue, _maxValue);

		if (_bShowLimitTip)
			ShowBalloonTip(L"���ܽ��ܵ���ֵ��Χ", strLimit);

		return false;
	}

	if (nChDot == 1)
	{
		SetWindowText(strText);
		int nTextLength = strText.GetLength();
		SetSel(nTextLength, nTextLength, TRUE);
	}
	
	return true;
}

void CValidEdit::OnTimer(UINT_PTR timer)
{
	if (timer == TM_BALLOONTIP)
	{
		KillTimer(TM_BALLOONTIP);
		Edit_HideBalloonTip(m_hWnd);
	}
}

void CValidEdit::ShowBalloonTip(const CString& strTitle,
	const CString& strContent, int tipIcon, DWORD dwTimeOut)
{
	EDITBALLOONTIP info = {0};
	info.cbStruct = sizeof(EDITBALLOONTIP);
	info.pszTitle = strTitle;
	info.pszText = strContent;
	info.ttiIcon = tipIcon;

	// ��ʾ������ʾ
	Edit_ShowBalloonTip(m_hWnd, &info);

	// �����ر���ʾ
	if (dwTimeOut != 0)
	{
		SetTimer(TM_BALLOONTIP, dwTimeOut, NULL);
	}
}

void CValidEdit::SetMaxMinValue(double dblMax, double dblMin, bool bShowLimitTip)
{
	_maxValue = dblMax;
	_minValue = dblMin;
	_bShowLimitTip = bShowLimitTip;
}

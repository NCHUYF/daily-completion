#include "stdafx.h"
#include "NumEdit.h"

BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

CNumEdit::CNumEdit() :
	m_decimalNum(2),
	m_bIsPositiveNumber(false),
	m_bIsCanZero(true),
	m_bIsInteger(false),
	m_dMaxNum(DBL_MAX)
{
}


CNumEdit::~CNumEdit()
{
}

int CNumEdit::SetDecimalNum(unsigned int iNum)
{
	m_decimalNum = iNum;
	m_bIsInteger = false;
	return 0;
}

int CNumEdit::SetIsPositiveNumber(bool bIsOrNot)
{
	m_bIsPositiveNumber = bIsOrNot;

	return 0;
}

void CNumEdit::SetIsCanZero(bool bIsOrNot)
{
	m_bIsCanZero = bIsOrNot;
}

int CNumEdit::SetIsInteger(bool bIsOrNot)
{
	m_bIsInteger = bIsOrNot;

	return 0;
}

void CNumEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	CString str;
	GetWindowText(str);

	str = TrimString(str);
	SetWindowText(str);

	if (!m_bIsCanZero && str == L"0" && m_bIsPositiveNumber)
	{
		SetWindowText(L"");
		SetCueBanner(L"����������");
		// SetFocus(); // ��ʱ����Ҫ��ȡ����
	}
}

void CNumEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	return;
}

CString CNumEdit::TrimString(const CString& strText)
{
	CString strTmp = strText;
	size_t nCount = strTmp.GetLength(), nSt = 0, nEd = 0;
	for (size_t i = 0; i + 1 < nCount; ++i)
	{
		if (strTmp.GetAt(i) == L'.')
		{
			strTmp.Insert(0, L"0");
			break;
		}

		if (strTmp.GetAt(i) != L'0' || strTmp.GetAt(i + 1) == L'.')
		{
			break;
		}

		++nSt;
	}

	bool bEd = (strTmp.Find(L".") >= 0);
	nCount = strTmp.GetLength();
	nEd = nCount;
	for (size_t i = 0; i < nCount && bEd; ++i)
	{
		if (strTmp.GetAt(nCount - i - 1) == L'0')
		{
			--nEd;
		}
		else if (strTmp.GetAt(nCount - i - 1) == L'.')
		{
			--nEd;
			break;
		}
		else
		{
			break;
		}
	}

	return strTmp.Mid(nSt, nEd - nSt);
}

void CNumEdit::SetMaxNum(double dNum, const CString& strTitle, const CString& strText)
{
	m_dMaxNum = dNum;
	m_strTipTitle = strTitle;
	m_strTipText = strText;
}

void CNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	POINT cp = GetCaretPos(); // ��ȡ�������ڿؼ���λ��
	int pos = CharFromPos(cp); // ��ȡ���λ��

	CString strOrigin;
	GetWindowText(strOrigin);

	if (nChar == 0x08) // ����Backspace
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if (strOrigin == L"0" && nChar >= '0'&& nChar <= '9') // ��ֹ00...��01...���������
	{
		SetWindowText(L"");
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if (nChar == '.')
	{
		if (strOrigin == "" || pos < (strOrigin.GetLength() - 2) || m_bIsInteger) // ����С�������ʼ��������ı���ʱӦ���������λ������С����
		{
		}
		else if (-1 == strOrigin.Find('.')) // û��С����
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	else if ((nChar >= '0'&&nChar <= '9'))
	{
		if (-1 != strOrigin.Find('.') && (strOrigin.GetLength() - strOrigin.Find('.') > (int)m_decimalNum) && (pos > strOrigin.Find('.'))) // ֻ����С�������λ
		{
		}
		//else if (pos == 0 && strOrigin != L"" && nChar == '0') // ��ֹ����������ǰ��0
		//{
		//}
		else
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	else if ('-' == nChar && pos == 0 && (-1 == strOrigin.Find('-')) && (!m_bIsPositiveNumber)) // ����ֻ�����ʼ���ı���û���Ѵ��ڼ���
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}

	CString strRes;
	GetWindowText(strRes);
	double dNum = _wtof(strRes);
	if (dNum > m_dMaxNum)
	{
		ShowBalloonTip(m_strTipTitle, m_strTipText);
		SetWindowText(strOrigin);
		return;
	}
}

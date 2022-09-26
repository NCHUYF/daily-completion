#include "StdAfx.h"
#include "ScaleEdit.h"

#define DOT_NUM 3

IMPLEMENT_DYNAMIC(CScaleEdit, CEdit)

BEGIN_MESSAGE_MAP(CScaleEdit, CEdit)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

CScaleEdit::CScaleEdit()
{
}

CScaleEdit::~CScaleEdit()
{
}

void CScaleEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// ʹ�ð�ť�ƶ�����һ�������
	if (nChar == VK_SPACE || nChar == VK_DECIMAL)
		return;

	//ֻ��ʹ�����Ұ����������ո񡢵��, ������Shift+��ͷѡ��
	if (((nChar == VK_LEFT || nChar == VK_RIGHT) && !(GetKeyState(VK_SHIFT) & 0x8000)) || nChar == VK_BACK)
	{
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CScaleEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bHandle = TRUE;
	DWORD curSel = GetSel();
	if (nChar == 8 /*��*/)
	{
		// ����ɾ���ַ�
		bHandle = ProcessDelChart();
	}
	
	CheckInvaildate();
}

bool CScaleEdit::CheckInvaildate()
{
	bool bResult = false;	DWORD curBeforeSel = GetSel();

	CString strChangeBeforeText;
	GetWindowText(strChangeBeforeText);
	// ��ȡѡ��λ��
	INT stPos, edPos;
	GetSel(stPos, edPos);

	SetRedraw(FALSE);
	Default();

	CString strText;
	GetWindowText(strText);
	DWORD curSel = GetSel();

	INT scaleCharPos = strText.Find(SCALE_CHAR);
	INT endCharPos = strText.GetLength();

	if (scaleCharPos ==-1 )
	{
		SetWindowText(strChangeBeforeText);
		SetSel(edPos, edPos);
	}

	// ���������ϻ�ԭ
	if (!IsDigitValidate(strText.Left(scaleCharPos))
		|| !IsDigitValidate(strText.Right(endCharPos-scaleCharPos-1)))
	{
		SetWindowText(strChangeBeforeText);
		SetSel(curBeforeSel);
	}

 	else
	{
		bResult = true;
	}

	SetRedraw(TRUE);
	Invalidate();

	return bResult;
}

BOOL CScaleEdit::ProcessDelChart()
{
	CString strText;
	GetWindowText(strText);

	//�ַ�������
	int nLeng = strText.GetLength();

	// ��ȡѡ��λ��
	INT stPos, edPos;
	GetSel(stPos, edPos);

	INT ptCharPos = edPos;
	ATLASSERT(ptCharPos != -1);

	//���Ҷ��ַ�λ
	INT scaleCharPos = strText.Find(SCALE_CHAR);
	INT endCharPos = strText.GetLength();

	//���ɾ�����ַ�Ϊ�ָ�����ֻ�ƶ���ǰһ���������
	if (ptCharPos == (scaleCharPos + 1) || ptCharPos == (endCharPos + 1))
	{
		SetSel(ptCharPos - 1, ptCharPos - 1);
		return TRUE;
	}
	

	else if ((stPos == 0) && (edPos == nLeng))
	{
		SetSel(ptCharPos, ptCharPos);
		return TRUE;
	}
	
	return FALSE;
}

bool CScaleEdit::IsDigit(const CString& strText)
{
	bool bFoundNum = false;
	if (strText.IsEmpty())
		return true;

	if (strText.Left(1) == _T("."))
		return false;

	int dotCt = 0; // ��ż��������ж������Ϊ��Ч
	UINT ct = strText.GetLength();
	for (UINT i = 0; i < ct; ++i)
	{
		const TCHAR chr = strText.GetAt(i);
		// ��ǰ�ַ�Ϊ����
		if (chr == 45/*"-"*/ || chr == 43 /*"+"*/)
		{
			// ���ܴ��ڷ���
			return false;
		}
		// ��ż�����
		if (chr == 46 /*"."*/)
		{
			dotCt++;
			// ����������
			if (dotCt > 1) return false;
			continue;
		}
		// ���ַ�Χ
		if (chr < 48 || chr > 57)
			return false;

		bFoundNum = true;
	}
	return bFoundNum;
}

bool CScaleEdit::IsDigitValidate(CString strText)
{
	// �ո���TAB����������
	if ( strText.Find(L" ") != -1 || strText.Find(L"\t") != -1 )
		return false;

	// ��������
	if (!IsDigit(strText))
		return false;

	// С��ǰ��0���
	if ((strText.Left(2) == L"-.")
		|| ((strText.Left(1) == L"0") &&
		(strText.GetLength() > 4 && strText.Mid(1, 1) != L"."))	//0x ���
		|| ((strText.Left(2) == L"-0") &&
		(strText.GetLength() > 2 && strText.Mid(2, 1) != L".")))  //-0x ���
	{
		return false;
	}

	// ��ȡС��λ��
	int dotPos = strText.Find(L".");
	int dotNum = (dotPos != -1) ? strText.GetLength() - dotPos: 0;

	// С��λ�ü��
	if (dotNum > DOT_NUM)
		return false;

	// �����������������󲻳���12λ
	CString strDotLeftText = (dotPos != -1) ? strText.Left(dotPos) : strText;
	strDotLeftText.Trim(L'-');
	if (strDotLeftText.GetLength() > 16)
		return false;

	return true;
}
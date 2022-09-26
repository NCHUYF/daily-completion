#include "StdAfx.h"
#include "ValidEditEx.h"

IMPLEMENT_DYNAMIC(CValidEditEx, CValidEdit)

BEGIN_MESSAGE_MAP(CValidEditEx, CValidEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

CValidEditEx::CValidEditEx()
{
}

CValidEditEx::~CValidEditEx()
{
}

void CValidEditEx::OnKillFocus(CWnd* pNewWnd)
{
	// ���Ϸ���
	if (false == Validate())
		return;

	CEdit::OnKillFocus(pNewWnd);
}

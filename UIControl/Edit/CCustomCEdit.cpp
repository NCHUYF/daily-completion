#include "StdAfx.h"
#include "CCustomCEdit.h"

namespace ControlUI
{
	IMPLEMENT_DYNAMIC(CCustomCEdit, CValidEdit)

	BEGIN_MESSAGE_MAP(CCustomCEdit, CValidEdit)
		ON_WM_NCPAINT()
		ON_WM_PAINT()
	END_MESSAGE_MAP()

	CCustomCEdit::CCustomCEdit() : CValidEdit()
	{
		_bStatus = false;
	}

	CCustomCEdit::~CCustomCEdit()
	{

	}

	void CCustomCEdit::SetStatus(bool bStatus)
	{
		_bStatus = bStatus;
	}

	void CCustomCEdit::OnNcPaint()
	{
		CValidEdit::OnNcPaint();
		// ���ƾ��α߿�
		CRect rcBorder;
		GetWindowRect(rcBorder);
		ScreenToClient(rcBorder);

		// ����ƫ������ (top left Ϊ�����������)
		if (rcBorder.top < 0)
		{
			rcBorder.top = 0;
		}

		if (rcBorder.left < 0)
		{
			rcBorder.left = 0;
		}
		rcBorder.bottom += 1;
		rcBorder.right += 1;

		CBrush	borderBrush;
		if (_bStatus)
		{
			borderBrush.CreateSolidBrush(RGB(255, 0, 0));
			CWindowDC dc(this);
			dc.FrameRect(rcBorder, &borderBrush);
		}
		else
		{
			borderBrush.CreateSolidBrush(RGB(192, 192, 192));
			CWindowDC dc(this);
			dc.FrameRect(rcBorder, &borderBrush);
		}
	}

	void CCustomCEdit::OnPaint()
	{
		CValidEdit::OnNcPaint();
		// ���ƾ��α߿�
		CRect rcBorder;
		GetWindowRect(rcBorder);
		ScreenToClient(rcBorder);

		// ����ƫ������ (top left Ϊ�����������)
		if (rcBorder.top < 0)
		{
			rcBorder.top = 0;
		}

		if (rcBorder.left < 0)
		{
			rcBorder.left = 0;
		}
		rcBorder.bottom += 1;
		rcBorder.right += 1;

		CBrush	borderBrush;
		if (_bStatus)
		{
			borderBrush.CreateSolidBrush(RGB(255, 0, 0));
			CWindowDC dc(this);
			dc.FrameRect(rcBorder, &borderBrush);
		}
		else
		{
			borderBrush.CreateSolidBrush(RGB(192, 192, 192));
			CWindowDC dc(this);
			dc.FrameRect(rcBorder, &borderBrush);
		}
	}
}
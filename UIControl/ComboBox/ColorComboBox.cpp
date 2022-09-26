#include "stdafx.h"
#include "ColorComboBox.h"

namespace ControlUI
{
	IMPLEMENT_DYNAMIC(CColorComboBox, CComboBox)
		CColorComboBox::CColorComboBox()
	{

	}

	CColorComboBox::~CColorComboBox()
	{

	}

	BEGIN_MESSAGE_MAP(CColorComboBox, CComboBox)
	END_MESSAGE_MAP()

	int CColorComboBox::AddItem(LPCTSTR lpszText, COLORREF clrValue)
	{
		int nIndex = AddString(lpszText);
		SetItemData(nIndex, clrValue);
		return nIndex;
	}

	CString CColorComboBox::GetCurText()
	{
		int nIndex = GetCurSel();

		CString strColor;
		GetLBText(nIndex, strColor);

		return strColor;
	}

	COLORREF CColorComboBox::GetCurColor()
	{
		int nIndex = GetCurSel();
		if (nIndex != -1)
		{
			return GetItemData(nIndex);
		}
		else
		{
			return -1;
		}
	}

	void CColorComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);

		//��ȡ��Ŀ����
		CRect itemRC(lpDrawItemStruct->rcItem);
		//������ʾ��ɫ������
		CRect clrRC = itemRC;
		//�����ı�����
		CRect textRC = itemRC;
		//��ȡϵͳ�ı���ɫ
		COLORREF clrText = GetSysColor(COLOR_WINDOWTEXT);
		//ѡ��ʱ���ı���ɫ
		COLORREF clrSelected = GetSysColor(COLOR_HIGHLIGHT);
		//��ȡ���ڱ�����ɫ
		COLORREF clrNormal = GetSysColor(COLOR_WINDOW);
		//��ȡ��ǰ��Ŀ����
		int nIndex = lpDrawItemStruct->itemID;
		//�ж���Ŀ״̬
		int nState = lpDrawItemStruct->itemState;
		if (nState & ODS_SELECTED)	//����ѡ��״̬
		{
			dc.SetTextColor((0x00FFFFFF & ~(clrText)));		//�ı���ɫȡ��
			dc.SetBkColor(clrSelected);						//�����ı�������ɫ
			dc.FillSolidRect(&clrRC, clrSelected);			//�����Ŀ����Ϊ����Ч��
		}
		else
		{
			dc.SetTextColor(clrText);						//�����������ı���ɫ
			dc.SetBkColor(clrNormal);						//�����������ı�������ɫ
			dc.FillSolidRect(&clrRC, clrNormal);
		}
		if (nState & ODS_FOCUS)								//�����Ŀ��ȡ���㣬���ƽ�������
		{
			dc.DrawFocusRect(&itemRC);
		}

		//�����ı�����
		textRC.left = itemRC.Height();

		//������ɫ��ʾ����
		clrRC.DeflateRect(2, 2);
		clrRC.right = itemRC.Height() - 2;


		//������ɫ�ı����������ɫ����
		if (nIndex != -1)	//��Ŀ��Ϊ��
		{
			//��ȡ��Ŀ��ɫ
			COLORREF clrItem = GetItemData(nIndex);
			dc.SetBkMode(TRANSPARENT);
			//��ȡ�ı�
			CString szText;
			GetLBText(nIndex, szText);
			//����ı�
			dc.DrawText(szText, textRC, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			dc.FillSolidRect(&clrRC, clrItem);
			//�����ɫ
			dc.FrameRect(&clrRC, &CBrush(RGB(0, 0, 0)));
		}
		dc.Detach();
	}

	int CColorComboBox::GetColorItemDataIndex(const COLORREF & color)
	{
		int nItemCnt = GetCount();
		for (int i = 0; i < nItemCnt; ++i)
		{
			if (color == GetItemData(i))
				return i;
		}

		return -1;
	}
}
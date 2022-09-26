#include "StdAfx.h"
#include "EditXPver.h"

namespace ControlUI
{
	IMPLEMENT_DYNAMIC(CEditXpVer, CEdit)
	BEGIN_MESSAGE_MAP(CEditXpVer, CEdit)
		//WM_CTLCOLOR����Ϣ����
		ON_WM_CTLCOLOR_REFLECT()
		ON_WM_KILLFOCUS()
		ON_WM_SETFOCUS()
	END_MESSAGE_MAP()

	void CEditXpVer::SetBannerText(const CString& str)
	{
		if (GetStyle() & ES_PASSWORD)
		{
			//���༭��Ϊ��������ȡ�����ַ���ȥ����������ģʽ
			_chPass = GetPasswordChar();
			SetPasswordChar(0);
		}
		//��ȡ��ʾ���ֲ���Ĭ��������Ϊ��ʾ����
		_strBannerText = str;
		CEdit::SetWindowText(_strBannerText);
	}

	HBRUSH CEditXpVer::CtlColor(CDC* pDC, UINT nCtlColor)
	{
		//ˢ��ǰ�����ı���ɫ
		pDC->SetTextColor(m_crText);

		//���ػ�ˢ,�������������ؼ�����
		return GetSysColorBrush(COLOR_WINDOW);
	}

	void CEditXpVer::OnKillFocus(CWnd* pNewWnd)
	{
		CEdit::OnKillFocus(pNewWnd);
		WhenKillFocus();
	}

	void CEditXpVer::OnSetFocus(CWnd* pOldWnd)
	{
		CEdit::OnSetFocus(pOldWnd);
		WhenOnFocus();
	}

	CString CEditXpVer::GetBannerText()
	{
		return _strBannerText;
	}

	CEditXpVer::CEditXpVer()
	{
		//��ʼ����ʾ������ɫ�Լ���ʾ��������
		m_crText = GetSysColor(COLOR_GRAYTEXT);
		_strBannerText = L"";
		_chPass = 0;
	}

	CEditXpVer::~CEditXpVer()
	{

	}

	void CEditXpVer::SetWindowText(LPCTSTR lpszString)
	{
		CEdit::SetWindowText(lpszString);
		bool bFocused = (::GetFocus() == GetSafeHwnd());
		bool bStrEmpty = (_tcslen(lpszString) == 0);
		if (!bStrEmpty)
		{
			m_crText = GetSysColor(COLOR_WINDOWTEXT);
			Invalidate(TRUE);
		}
		else
		{
			bFocused ? WhenOnFocus() : WhenKillFocus();
		}

	}

	void CEditXpVer::GetInputText(CString& strTemp)
	{
		GetWindowText(strTemp);
		if (strTemp == _strBannerText)
			strTemp = L"";
	}

	void CEditXpVer::WhenKillFocus()
	{
		CString strTemp;
		GetWindowText(strTemp);
		if (strTemp.IsEmpty())
		{
			//���༭������Ϊ������ʾ��ʾ���ֲ�ȥ�������
			SetPasswordChar(0);
			CEdit::SetWindowText(_strBannerText);
			m_crText = GetSysColor(COLOR_GRAYTEXT);
			Invalidate(TRUE);
		}
	}

	void CEditXpVer::WhenOnFocus()
	{
		//��ȡ�༭������
		CString strTemp;
		GetWindowText(strTemp);
		if (strTemp == _strBannerText)
		{
			//���༭������Ϊ��ʾ��������ѡ��ʱȥ�����ֲ��޸�������ɫΪĬ��
			SetPasswordChar(_chPass);
			CEdit::SetWindowText(L"");
			m_crText = GetSysColor(COLOR_WINDOWTEXT);
			Invalidate(TRUE);
		}
	}
}
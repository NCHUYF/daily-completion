/*-----------------------------------------------------
* �ļ����ƣ�  BCGPPropEx.H
*  ���������� ��չ�������
* ������ʶ��  ��־��  2020/7/6 8:59
*
* �޸ı�ʶ��
* �޸�������
*
* �޸ı�ʶ��
* �޸�������
-----------------------------------------------------*/

#pragma once

namespace PropEx
{
	class COMMONCONTROLS_API CBCGPPropListPro : public CBCGPPropList
	{
		DECLARE_DYNAMIC(CBCGPPropListPro)
	public:
		CBCGPPropListPro();
		virtual ~CBCGPPropListPro();

		void RemoveAllProperty();
		BOOL IsFocused();
		CString True() { return m_strTrue; };
		CString False() { return m_strFalse; };

		DECLARE_MESSAGE_MAP()
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	private:
		static volatile bool					_bDelete;//��ʶ���ؼ��Ƿ��ѱ��ͷ�
	};

}


////*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           EditValue.H
//    @author         JCC
//    @date           2018/9/5 18:23
//    @brief		  ���Ի�ȡ��һ������ı༭��
//*****************************************************

#pragma once

namespace ControlUI
{
	class CONTROL_UI CEditValue : public CEdit
	{
	public:
		CEditValue();
		~CEditValue();

		CString GetOldValue();


		// ʵ��  
	protected:
		afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags); //������Ϣ  
		DECLARE_MESSAGE_MAP()

	private:
		CString m_strOldValue; // �༭��ǿ�ǰ��һ��ֵ
	};

}
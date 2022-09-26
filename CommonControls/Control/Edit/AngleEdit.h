//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           AngleEdit.H
//    @author         KG
//    @date           2015/3/8 10:12
//    @brief          �Ƕȱ༭��ؼ�(���С㡯��)
//*****************************************************

#pragma once

// �ȣ��֣����л���Ϣ(����)
#define SWITCH_TO_NEXT_PART (WM_USER+140)

/**
*  @class    �Ƕȱ༭��ؼ���
*
*  @brief
*/
class COMMONCONTROLS_API CAngleEdit : public CEdit
{
	DECLARE_DYNAMIC(CAngleEdit)
public:
	CAngleEdit();
	virtual ~CAngleEdit();

protected:
	DECLARE_MESSAGE_MAP()

public:
	/**
	*  @brief    ��ȡ�Ƕȷ����ַ���ֵ
	*
	*  @param    CString & degreeVal ��
	*  @param    CString & minuteVal ��
	*  @param    CString & secondVal ��
	*/
	void GetAngleStrValue(CString& degreeVal,
		CString& minuteVal, CString& secondVal);

	/**
	*  @brief    ��ýǶ��ı�
	*
	*  @return   CString ���������Ƕ��ַ���
	*/
	CString GetAngleText();

	/**
	*  @brief    ��û���ֵ
	*
	*  @return   double ���ػ���ֵ
	*/
	double GetArcValue();

	/**
	*  @brief    ���û���ֵ
	*
	*  @param    double dVal ����ֵ
	*/
	void SetArcValue(double dVal);

	/**
	*  @brief    ��ýǶ�ֵ
	*
	*  @return   double ���ؽǶ�ֵ
	*/
	double GetAngleValue();

	/**
	*  @brief    ���ý���
	*
	*/
	void SetEditFocus();

private:
	/**
	*  @brief    ��ȡ�ָ����ַ�λ��
	*
	*  @param    INT & degreeCharPos ��λ��
	*  @param    INT & minuteCharPos ��λ��
	*  @param    INT & secondCharPos ��λ��
	*  @return   CString ���ظ�ʽ������ı�
	*/
	CString GetSeparatorCharPos(INT &degreeCharPos,
		INT &minuteCharPos, INT &secondCharPos);

	/**
	*  @brief    ����ɾ���ַ��߼�
	*
	*  @return   BOOL �ɹ�����TRUE
	*/
	BOOL ProcessDelChart();

	/**
	*  @brief    ���������ȷ��
	*
	*  @param    TCHAR inChar ��ǰ������ַ�
	*  @return   BOOL ������Ч����TRUE
	*/
	BOOL ValidateInput(TCHAR inChar);

	/**
	*  @brief    ���ݵ�ǰ���λ���Զ�ѡ���������벿��
	*
	*  @param    BOOL isSwitch �Ƿ�ѡ����һ�����벿��
	*/
	void AutoSelectPart(BOOL isSwitch = FALSE);

public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT	OnSwitchToNextPart(WPARAM wParam, LPARAM lParam);
	/**
	*  @brief    ʧȥ�����¼�;
	*
	*/
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};
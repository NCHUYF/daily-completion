//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           AutoWidthComboBox.H
//    @author         wanghongchang
//    @date           2015\9\19 15:06
//    @brief          �Զ����¿��������
//*****************************************************
#pragma once

/**
*  @class    CAutoWidthComboBox
*
*  @brief    �Զ����¿��������
*/
class COMMONCONTROLS_API CAutoWidthComboBox : public CComboBox
{
public:
	/**
	*  @brief    ���������ı����ȸ�����������
	*
	*  @param    CComboBox & combox
	*  @return   void
	*/
	static void ComboxAutoWidth(CComboBox &combox);

	static void ComboxAutoResize(CComboBox &combox);
	/*
	*  @brief    ������Ϣ������
	*
	*  @param    CWnd * pParent
	*/
	void SetMsgParent(CWnd* pParent);

public:

	virtual void MoveWindow(int x, int y, int nWidth, int nHeight,
		BOOL bRepaint = TRUE);

	virtual void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);

public:
	// manipulating listbox items
	/**
	*  @brief    ��������б�
	*
	*  @param    LPCTSTR lpszString �����б��¼����
	*  @param    bool bAutoWidth �Ƿ��Զ�������ȣ�������falseʱ����������Ҫ�Լ�����ComboxAutoWidth�����������
	*  @return   int ����
	*/
	int AddString(LPCTSTR lpszString, bool bAutoWidth = true);
	int DeleteString(UINT nIndex);
	int InsertString(int nIndex, LPCTSTR lpszString);
	void ResetContent();


};
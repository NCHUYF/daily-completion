//*****************************************************
//    
//    @copyright      ���������;
//    @version        v3.0
//    @file           ComboBox.H
//    @author         mahaidong;
//    @date           2015/4/9 14:18
//    @brief          �б���ͨ��Ͽ�ؼ�;
//*****************************************************

#pragma once

#include "EditBase.h"
#include "EditContainer.h"

/**
*  @class    CListComboBox
*
*  @brief    �б���ͨ��Ͽ�ؼ�
*/
class COMMONCONTROLS_API CListComboBox : public CComboBox, public IEditBase
{
	DECLARE_DYNAMIC(CListComboBox)

public:
	CListComboBox();
	virtual ~CListComboBox();

protected:
	DECLARE_MESSAGE_MAP()

public:
	/**
	*  @brief    �����ؼ�;
	*
	*  @param    CWnd * pParent �����ھ��;
	*  @param    CRect & rect ��������;
	*  @param    bool bDropList �Ƿ񲻿ɱ༭;
	*  @param    LPCTSTR sInitText Ĭ����ʾ�ı�;
	*  @return   bool �����ɹ�����true�����򷵻�false;
	*/
	virtual bool Create(CWnd* pParent, CRect& rect, bool bDropList, LPCTSTR sInitText);

	/**
	*  @brief    ���ý����м�ѡ��;
	*
	*/
	void SetSelAndFocus();

	/**
	*  @brief    ������������
	*
	*  @param    const CString& strXmlFile ���������ļ�
	*  @return   bool ���سɹ�����true
	*/
	bool LoadXmlData(const CString& strXmlFile);

	/**
	*  @brief    �����ַ�������
	*
	*  @param    CStringVector & listData �ַ�������
	*/
	void LoadStringVector(CStringVector& listData);

	/**
	*  @brief    ʧȥ����Ĵ���
	*
	*  @param    CWnd * pWnd ���
	*/
	virtual void DoKillFocus(CWnd* pWnd);

	/**
	*  @brief    ȡ���༭
	*
	*/
	void CancelEdit();

private:
	/**
	*  @brief    �Զ�ѡ��Ĭ����
	*
	*/
	void AutoSelectItem();

	/**
	*  @brief    ������Ͽ��б���;
	*
	*/
	void DrawItem(HDC hDC, const CRect& rcItem, int iItem, int iState);

	/**
	*  @brief    ��ȡ������߶�
	*
	*/
	virtual void MeasureItem(LPMEASUREITEMSTRUCT pMItem);

	/**
	*  @brief    ����������
	*
	*/
	virtual void DrawItem(LPDRAWITEMSTRUCT pDIStruct);

public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void ProcessKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
	WNDPROC			_pEditProc;  ///< �༭����Ϣ

protected:
	CString			_strInitText; ///< ��ʼ��ʾֵ
	bool			_bDropList;   ///< �������ģʽ
	bool			_bCandel;	  ///< �Ƿ�ȡ��
	COLORREF		_crNormal;	  ///< ������ɫ
	COLORREF		_crSelected;  ///< ѡ����ɫ
	COLORREF		_crText;      ///< �ı���ɫ
	CEditContainer	_container;   ///< �߿�����
};
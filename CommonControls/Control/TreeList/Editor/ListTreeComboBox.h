//*****************************************************
//    
//    @copyright      ���������;
//    @version        v3.0
//    @file           ComboBox.H
//    @author         mahaidong;
//    @date           2015/4/9 14:18
//    @brief          ������Ͽ�ؼ�;
//*****************************************************

#pragma once

#include "EditBase.h"
#include "EditContainer.h"

/**
*  @class    CListTreeComboBox
*
*  @brief    ������Ͽ�ؼ�
*/
class COMMONCONTROLS_API CListTreeComboBox : public CTreeComboBox, public IEditBase
{
	DECLARE_DYNAMIC(CListTreeComboBox)

public:
	CListTreeComboBox();
	virtual ~CListTreeComboBox();

protected:
	DECLARE_MESSAGE_MAP()

public:
	/**
	*  @brief    �����ؼ�;
	*
	*  @param    CWnd * pParent �����ھ��;
	*  @param    CRect & rect ��������;
	*  @param    LPCTSTR lpszInit Ĭ����ʾ�ı�;
	*  @param    LPCTSTR lpszData Ĭ����ʾ��չ�ı�;
	*  @param    bool bDropList �Ƿ񲻿ɱ༭
	*  @return   bool �����ɹ�����true�����򷵻�false;
	*/
	bool CreateCtrl(CWnd* pParent, CRect& rect, LPCTSTR lpszInit, LPCTSTR lpszData, bool bDropList);

	/**
	*  @brief    �ؼ�����֮���ټ���XML��������
	*
	*  @param    const CString& xmlFile ������Xml�����ļ�����XML�����ַ�����
	*  @param    bool bNoLimitOrSelAll true�Զ���Ӳ��޻�ȫѡ
	*  @return   bool �ɹ�����true
	*/
	bool LoadXmlData(const CString& xmlFile, bool bNoLimitOrSelAll = false);

	/**
	*  @brief    �����ַ�������
	*
	*  @param    CStringVector & listData �ַ�������
	*  @param    bool bNoLimitOrSelAll true�Զ���Ӳ��޻�ȫѡ
	*/
	void LoadStringVector(CStringVector& listData, bool bNoLimitOrSelAll = false);

	/**
	*  @brief    ȡ���༭
	*
	*/
	void CancelEdit();

	/**
	*  @brief    ʧȥ����Ĵ���
	*
	*  @param    CWnd * pWnd ���
	*/
	void DoKillFocus(CWnd* pWnd);

	/**
	*  @brief    ���̰��µ���Ϣ����
	*
	*  @param    UINT nChar
	*  @param    UINT nRepCnt
	*  @param    UINT nFlags
	*  @return   void
	*/
	
	void ProcessKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

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
	afx_msg void OnEditChange();

public:
	WNDPROC			_pEditProc;  ///< �༭����Ϣ

protected:
	bool			_bCandel;	  ///< �Ƿ�ȡ��
	COLORREF		_crNormal;	  ///< ������ɫ
	COLORREF		_crSelected;  ///< ѡ����ɫ
	COLORREF		_crText;      ///< �ı���ɫ
	CString			_strInit;	  ///< Ĭ��ֵ
	CString			_strData;	  ///< Ĭ��ֵ��չ
	CEditContainer	_container;   ///< �߿�����

	bool			_bDropList;   ///< �������ģʽ
	bool			_bIsSelect;
};
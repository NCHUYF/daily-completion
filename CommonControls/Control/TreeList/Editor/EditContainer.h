//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           EditContainer.H
//    @author         jzl
//    @data           2015/7/7 17:08
//    @brief          �༭�ؼ�����
//*****************************************************

#pragma once

/**
*  @class    CEditContainer
*
*  @brief    �༭�ؼ�����
*/
class COMMONCONTROLS_API CEditContainer : public CStatic
{
public:
	CEditContainer();
	virtual ~CEditContainer();

protected:
	DECLARE_MESSAGE_MAP()

public:
	/**
	*  @brief    �����ؼ�;
	*
	*  @param    CRect & rect ��������;
	*  @param    CWnd * pParent �����ھ��;
	*  @return   BOOL �����ɹ�����true�����򷵻�false;
	*/
	BOOL Create(CRect& rect, CWnd* pParent);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	COLORREF _bkColor;	///< ����ɫ
};
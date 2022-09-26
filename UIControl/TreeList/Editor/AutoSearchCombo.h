#pragma once

#include "EditBase.h"
#include "EditContainer.h"

namespace ControlUI
{

	typedef std::vector<std::pair<CString, CString>> DropListSet;

	/**
	*  @class    CAutoSearchCombo
	*
	*  @brief    �б���ͨ��Ͽ�ؼ�
	*/
	class CAutoSearchCombo : public CComboBox, public IEditBase
	{
		DECLARE_DYNAMIC(CAutoSearchCombo)

	public:
		CAutoSearchCombo();

		virtual ~CAutoSearchCombo();

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
		bool Create(CWnd* pParent, CRect& rect, int option, LPCTSTR sInitText);

		bool LoadXmlData(const CString& strXmlFile);

		void LoadStringVector(CStringVector& listData);

		void ProcessKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

		void SetSelAndFocus();

		void DoKillFocus(CWnd* pWnd);

		void CancelEdit();

		WNDPROC			_pEditProc;  ///< �༭����Ϣ

	protected:
		void DrawItem(HDC hDC, const CRect& rcItem, int iItem, int iState);

		int ResetDropContent();

		virtual void MeasureItem(LPMEASUREITEMSTRUCT pMItem);

		virtual void DrawItem(LPDRAWITEMSTRUCT pDIStruct);

		virtual BOOL PreTranslateMessage(MSG* pMsg);

		DECLARE_MESSAGE_MAP()

		afx_msg void OnKillFocus(CWnd* pNewWnd);

		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

		afx_msg void OnEditChange();

		afx_msg void OnDropDown();

		CString			_strInitText;		///< ��ʼ��ʾֵ
		CString			_strData;			///< ��Ͽ����չ����
		bool			_bDropList;			///< �������ģʽ
		bool			_bCandel;			///< �Ƿ�ȡ��
		bool			_autoComplete;		///< �Զ����ƥ��
		COLORREF		_crNormal;			///< ������ɫ
		COLORREF		_crSelected;		///< ѡ����ɫ
		COLORREF		_crText;			///< �ı���ɫ
		CEditContainer	_container;			///< �߿�����
		DropListSet		_loadStringList;	///< �������е������б�
	};
}
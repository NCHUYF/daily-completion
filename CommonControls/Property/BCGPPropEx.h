/*-----------------------------------------------------
* �ļ����ƣ�  BCGPPropEx.H
*  ���������� ��չ����
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
	class COMMONCONTROLS_API CBCGPPropEx : public CBCGPProp
	{
		friend class CBCGPPropListPro;
	public:
		CBCGPPropEx(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

		CBCGPPropEx(const CString& strName, const _variant_t& varValue,
			LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
			LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
			LPCTSTR lpszValidChars = NULL);

		CBCGPPropEx(const CString& strName, UINT nID, const _variant_t& varValue,
			LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
			LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
			LPCTSTR lpszValidChars = NULL);

		virtual ~CBCGPPropEx();

		/**
		*  �������ܣ� ����������
		*
		*  ��������� CDC* pDC
		*  ��������� CRect rect
		*/
		virtual void OnDrawName(CDC* pDC, CRect rect);

		/**
		*  �������ܣ� ��������ֵ
		*
		*  ��������� CDC* pDC
		*  ��������� CRect rect
		*/
		virtual void OnDrawValue(CDC* pDC, CRect rect);

		/**
		*  �������ܣ� �����༭��
		*
		*  ��������� CRect rectEdit
		*  ��������� BOOL& bDefaultFormat
		*/
		virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);

		/**
		*  �������ܣ� ��������������
		*
		*  ��������� const PROPERTYITEM &ite
		*/
		void SetPropertyCfg(const PROPERTYITEM &item);

		/**
		*  �������ܣ� ��ɱ༭
		*
		*  ����ֵ�� BOOL
		*/
		virtual BOOL OnEndEdit();

		/**
		*  �������ܣ� ��������Դ
		*
		*  ��������� IPropertyObjectData *pDataSrc
		*/
		void SetItemData(IPropertyObjectData *pDataSrc);

		/**
		*  �������ܣ� �������ֵ
		*
		*  ��������� UINT uiMsg
		*  ��������� CPoint point
		*/
		virtual BOOL OnClickValue(UINT uiMsg, CPoint point);

		// �жϵ�ǰģ���Ƿ�ɾ��
		bool IsDelete();

	protected:

		/**
		*  �������ܣ� ���Ƴ�����
		*
		*  ��������� CDC* pDC
		*  ��������� CRect rect
		*  ��������� const CString &strText
		*/
		void DrawHyperLink(CDC* pDC, CRect rect, const CString &strText);

		/**
		*  �������ܣ� ��������������ת�����ַ���
		*
		*  ����ֵ��   CString
		*/
		virtual CString FormatProperty();

	protected:
		BOOL						_bHighlighted;	// ����
		PROPERTYITEM				_prop;			// ���������
		CFont						_nameFont;		// ����������
		CFont						_valFont;		// ����ֵ����
		CFont						_underline;		// ����������
		IPropertyObjectData			*_pDataSrc;		// ����Դָ��
		bool								_bDelete = false;
	};
}




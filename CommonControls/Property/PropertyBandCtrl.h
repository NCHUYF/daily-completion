/*-----------------------------------------------------
* �ļ����ƣ�  PropertyBandCtrl.H
*  ���������� �������
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
	struct tagPropertyStyle;
	typedef tagPropertyStyle* HPROPERTYSTYLE;

	struct tagPropertyItem;
	typedef tagPropertyItem* HPROPERTYITEM;

	class IPropertyObjectData;
	class CBCGPPropListPro;
	class CBCGPPropEx;

	class COMMONCONTROLS_API CPropertyBandCtrl : public CBCGPWnd
	{
		typedef std::map<IPropertyObjectData*, CBCGPProp*> ItemPropMap;

		DECLARE_DYNAMIC(CPropertyBandCtrl)

		DECLARE_SINGLE_CLASS(CPropertyBandCtrl);
	public:
		CPropertyBandCtrl();
		virtual ~CPropertyBandCtrl();

		/**
		*  �������ܣ� �����������ؼ����������֮�����SetPropertyData��������ָ�룬������UpdatePropertyPanel��ʾ�������
		*
		*  ��������� CWnd* pParentWnd  ������ָ��
		*  ��������� UINT nID		  ID
		*  ��������� const CRect &rt	  ���ڴ�С
		*  ����ֵ��   BOOL			  �����ɹ�����TRUE����֮
		*/
		BOOL CreatePropertyCtrl(CWnd* pParentWnd, UINT nID, const CRect &rt);

		/**
		*  �������ܣ� ��������������ݣ�ֻ��������ȷ������ָ��֮�����UpdatePropertyPanel������ȷ��ʾ��
		*
		*  ��������� const std::vector<IPropertyObjectData*> &datas ����ָ���������������ʱ�ͷţ�����Ҫ�ֶ��ͷ�
		*/
		void SetPropertyData(const std::vector<IPropertyObjectData*> &datas);

		/**
		*  �������ܣ� ���������ʾ
		*
		*  ��������� bool bUpdate ��Ϊtrue�����»���
		*/
		void UpdatePropertyPanel(bool bUpdate);

		/**
		*  �������ܣ� ������������񣬶����������������Ҫ��ɶԷ��������ã���������ʹ��Ĭ�ϵķ����ʽ
		*
		*  ��������� HPROPERTYSTYLE pStyle ���ⲿ�����ָ�벻�������ͷţ���������ʱ�������ͷ�
		*/
		void SetPropertyStyle(HPROPERTYSTYLE pStyle);

		/**
		*  �������ܣ� ��ȡ���������
		*
		*  ����ֵ�� HPROPERTYSTYLE pStyle
		*/
		HPROPERTYSTYLE GetPropertyStyle();

	protected:
		DECLARE_MESSAGE_MAP()
		afx_msg void OnSize(UINT nType, int cx, int cy);
		virtual void PostNcDestroy();

		/**
		*  �������ܣ� �ͷ��ڴ�
		*/
		void Release();

		/**
		*  �������ܣ� ��ȡ�򴴽�����
		*
		*  ��������� IPropertyObjectData *pItem
		*  ��������� CBCGPProp *pParentGroup
		*  ��������� PROPERTYITEM &item
		*  ����ֵ�� CBCGPProp*
		*/
		CBCGPProp* GetOrCreateBCGPProp(IPropertyObjectData *pItem, CBCGPProp *pParentGroup, PROPERTYITEM &item);

		/**
		*  �������ܣ� �ռ�����
		*
		*  ��������� IPropertyObjectData *pItem
		*  ��������� CBCGPProp *pParentGroup
		*/
		void Collect(IPropertyObjectData *pItem, CBCGPProp *pParentGroup);

		/**
		*  �������ܣ� ��С�ӽڵ�
		*
		*  ��������� IPropertyObjectData *pItem
		*  ��������� const PROPERTYITEM &item
		*/
		bool IsLeaf(IPropertyObjectData *pItem, const PROPERTYITEM &item);

		/**
		*  �������ܣ� ���ⲿ��ȡ�Ĳ������õ�CBCGPProp��
		*
		*  ��������� CBCGPProp *pPropItem
		*  ��������� const PROPERTYITEM &item
		*/
		void SetPropItem(CBCGPProp *pPropItem, const PROPERTYITEM &item);

		/**
		*  �������ܣ� ������С����
		*
		*  ��������� IPropertyObjectData *pItem
		*  ��������� PROPERTYITEM &item
		*/
		CBCGPProp *CreateLeafProp(IPropertyObjectData *pItem, PROPERTYITEM &item);

		/**
		*  �������ܣ� ���������
		*/
		void EnableStyle();

	protected:
		int									_nID;			// ID
		CBCGPPropListPro					*_propList;		// �������ؼ�
		HPROPERTYSTYLE						_pStyle;		// ���
		ItemPropMap							_itemMap;		// Itemָ���Ӧ��������
		std::vector<IPropertyObjectData*>	_datas;			// ������
	};

}

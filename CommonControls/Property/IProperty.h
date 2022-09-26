/*-----------------------------------------------------
* �ļ����ƣ�  IProperty.H
*  ���������� �����������ָ��
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
	namespace Property {

		// �������
		enum COMMONCONTROLS_API EPropertyCategory
		{
			eGroup,		// ��
			eSimple,	// ��һ�Ҷ��
			eDefalut	// Ĭ�϶��巽ʽ�����ӽڵ��Ϊ��
		};

		// ����ֵ�ؼ�����
		enum COMMONCONTROLS_API EPropertyItemType
		{
			eNULL,			// ��ڵ�û������ֵ����Ҫ�ؼ�
			eEdit,			// ��ͨ�༭��
			eDigitEdit,		// ���ֱ༭��
			eScaleEdit,		// �����༭��
			eAngleEdit,		// �Ƕȱ༭��
			eComboBox,		// �����б�
			eHyperlink,		// ������
			eButton,		// ��ť
			eCheckBox		// ��ѡ��
		};
	}
	// ���������
	typedef struct COMMONCONTROLS_API tagPropertyStyle
	{
	public:
		tagPropertyStyle() :bEnableToolbar(FALSE), bEnableSearch(FALSE), bEnableHeader(FALSE),
			bEnableDesc(FALSE), bEnableModify(FALSE), bEnableMenu(FALSE) {}

		BOOL	bEnableToolbar;		// ��ʾ������������ĸ����ť

		BOOL	bEnableSearch;		// ��ʾ������
		CString	strSearchPrompt;	// ��������ʾ����

		BOOL	bEnableHeader;		// ��ʾ��ͷ��Ĭ�ϲ���ʾ
		CString	strLeftName;		// ���������ͷ����
		CString strRightName;		// �Ҳ�������ͷ����

		BOOL	bEnableDesc;		// ������·���ʾ����������
		BOOL    bEnableModify;		// ����ֵ�����޸ļӴ���ʾ��Ĭ�ϲ�����
		BOOL	bEnableMenu;		// ʹ���Ҽ��˵���Ĭ�ϲ�����
	}PROPERTYSTYLE, *HPROPERTYSTYLE;

	typedef struct COMMONCONTROLS_API tagDigitEdit
	{
	public:
		tagDigitEdit() :nDotNum(8), nDigitNum(8), nFlag(eValidEdit | eVeDecimal | eVeNegative | eVeDotNum),
			dMaxVal(DBL_MAX), dMinVal(DBL_MIN) {}

		void Init()
		{
			nDotNum = 8;
			nDigitNum = 8;
			nFlag = eValidEdit | eVeDecimal | eVeNegative | eVeDotNum;
			dMaxVal = DBL_MAX;
			dMinVal = DBL_MIN;
		}

		int					nDotNum;		// �༭������С��λ��
		int					nFlag;			// �༭����,EValidEditControlFlag
		int					nDigitNum;		// ���λ��
		double				dMaxVal;		// ���ֵ
		double				dMinVal;		// ��Сֵ
	}DIGITEDIT, *HDIGITEDIT;

	typedef struct COMMONCONTROLS_API tagPropertyItem
	{
	public:
		tagPropertyItem() :bShow(true), bExpand(TRUE), bReadOnly(FALSE), type(Property::eEdit), cate(Property::eDefalut), bNameFont(FALSE), bValueFont(FALSE),
			valueClr(-1), nameClr(-1), nSel(0), strTrue(L"True"), strFalse(L"False"), nNameAlign(DT_LEFT), nValueAlign(DT_LEFT), bCheckState(TRUE) {}

		void CopyFrom()
		{
			bShow = true;
			bExpand = TRUE;
			bReadOnly = FALSE;
			type = Property::eEdit;
			cate = Property::eDefalut;
			valueClr = -1;
			nameClr = -1;
			bNameFont = FALSE;
			bValueFont = FALSE;
			nSel = 0;
			strTrue = L"True";
			strFalse = L"False";
			digit.Init();
			nNameAlign = DT_LEFT;
			nValueAlign = DT_LEFT;
			bCheckState = TRUE;
		}

		bool						bShow;			// ��ʾ(true)/����(false)
		BOOL						bExpand;		// չ��(TRUE)/����(FALSE)
		BOOL						bReadOnly;		// ֻ��(TRUE)
		BOOL						bNameFont;		// ʹ���Զ������������壬����һ��Ҫ��ȷ�������׳�������
		BOOL						bValueFont;		// ʹ���Զ�������ֵ����
		BOOL						bCheckState;	// checkbox״̬��TRUEΪ��
		LOGFONT						nameFont;		// ���������壬bNameFont����ΪTRUE����������������ͷţ��������ⲿ����
		LOGFONT						valueFont;		// ����ֵ���壬bValueFont����ΪTRUE
		int							nSel;			// ComboBoxĬ��ѡ����
		int							nNameAlign;		// ���������뷽ʽ���֣�DT_LEFT��DT_CENTER��DT_RIGHT
		int							nValueAlign;	// ����ֵ���뷽ʽ
		DIGITEDIT					digit;			// ���ֱ༭�����ã�������С��λ�������ֵ����Сֵ��
		COLORREF					nameClr;		// ��������ɫ
		COLORREF					valueClr;		// ����ֵ��ɫ	
		Property::EPropertyItemType	type;			// ����ֵ�пؼ�����
		Property::EPropertyCategory	cate;			// �����
		CString						strItemName;	// �������ƣ���ڵ�ֻ��name��û��value
		CString						strTrue;		// ֻ��������ֵΪbool����ʱ����Ϊtrueʱ��Ӧ��ʾ���ַ�����Ĭ��Ϊ"True"
		CString						strFalse;		// ֻ��������ֵΪbool����ʱ����Ϊfalseʱ��Ӧ��ʾ���ַ�����Ĭ��Ϊ"False"
		std::vector<CAny>			options;		// combox����
	}PROPERTYITEM, *HPROPERTYITEM;


	class COMMONCONTROLS_API IPropertyObjectData
	{
	public:
		virtual ~IPropertyObjectData() {}

		/**
		*  �������ܣ� ��ȡ����Դ�ӽڵ�����
		*
		*  ����ֵ��   size_t
		*/
		virtual size_t GetPropertyCount() = 0;

		/**
		*  �������ܣ� ��ȡ��Ӧλ���ӽڵ�
		*
		*  ��������� size_t nIndex  �ӽڵ�����
		*  ����ֵ��  IPropertyData*  �����ӽڵ�ָ��
		*/
		virtual IPropertyObjectData* GetPropertyItem(size_t nIndex) = 0;

		/**
		*  �������ܣ� ��ȡ�ӽڵ�������Ϣ��ͨ��HPROPERTYITEMָ�������������������ԣ��磺�Ƿ���ʾ���Ƿ�ɶ������Ƶ�
		*
		*  ��������� HPROPERTYITEM pItem
		*/
		virtual void GetItemConfig(HPROPERTYITEM pItem) = 0;

		/**
		*  �������ܣ� ��ȡ����ֵ
		*
		*  ����ֵ��   CString
		*/
		virtual CAny GetItemValue() = 0;

		/**
		*  �������ܣ� ��������������ֵ
		*
		*  ��������� const CAny &newVal
		*  ��������� const CAny &oldVal
		*/
		virtual void SetItemValue(const CAny &newVal, const CAny &oldVal) = 0;

		/**
		*  �������ܣ� �����ӵ���¼�
		*
		*  ��������� const PROPERTYITEM & item
		*/
		virtual void HyperlinkPressDown(const PROPERTYITEM &item) {};

		/**
		*  �������ܣ� ��ť����¼�
		*
		*  ��������� const PROPERTYITEM & item
		*/
		virtual void ButtonPressDown(const PROPERTYITEM &item) {};

		/**
		*  �������ܣ� ����Ҳ�Item��
		*
		*  ��������� const PROPERTYITEM & item
		*/
		virtual void ClickRValItem(const PROPERTYITEM &item) {}
	};

	class COMMONCONTROLS_API IPropertyObject
	{
	public:
		virtual ~IPropertyObject() {}

		/**
		*  �������ܣ� ��ȡ���ݽڵ�ָ��
		*
		*  ����ֵ�� IPropertyObjectData*
		*/
		virtual std::vector<IPropertyObjectData*> GetPropertyDataList() = 0;

		/**
		*  �������ܣ� ��ȡ�����������ݽڵ�ָ��
		*
		*  ����ֵ�� std::vector<IPropertyObjectData*>
		*/
		virtual std::vector<IPropertyObjectData*> GetProjectPropertyDataList() = 0;
	};

}


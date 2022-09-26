//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           DynEnum.H
//    @author         fanHong
//    @date           2017/11/3 15:32
//    @brief          ��̬ö��
//
//*****************************************************

#pragma once

namespace CommBase
{
	/**
	*  @class    ö����Ϣ�ṹ
	*
	*  @brief
	*/
	typedef struct tag_EnumTextInfo
	{
		int Value;			///< ö��ֵ
		CString Text;		///< ö���ַ���
		CString Show;		///< ö����ʾ�ַ���
	}EnumTextInfo;

	/*
	* ö����Ϣ�ṹ���鶨��
	*/
	typedef std::vector<EnumTextInfo> EnumTextInfoArray;
	typedef EnumTextInfoArray::iterator EnumTextInfoArrayIter;

	/*
	* ö����ϢMap�ṹ����<ö������ö����Ϣ�ṹ����>
	*/
	typedef std::map<CString, EnumTextInfoArray> EnumTextInfoMap;
	typedef EnumTextInfoMap::iterator EnumTextInfoMapIter;

	/**
	*  @class    ��̬ö����
	*
	*  @brief
	*/
	class COMMBASE_API CDynEnum
	{
	public:
		CDynEnum();
		~CDynEnum();

	public:
		/**
		*  @brief    ö��ֵ(ת)ö���ַ���
		*
		*  @param    const CString & strEnumName ö����
		*  @param    int nEnumValue ö��ֵ
		*  @return   CString ����ö�ٶ�Ӧ���ַ���
		*/
		static CString Enum2Text(const CString& strEnumName, int nEnumValue);

		/**
		*  @brief    ö��ֵ(ת)ö����ʾ�ַ���
		*
		*  @param    const CString & strEnumName ö����
		*  @param    int nEnumValue ö��ֵ
		*  @return   CString ����ö�ٶ�Ӧ����ʾ�ַ���
		*/
		static CString Enum2Show(const CString& strEnumName, int nEnumValue);

		/**
		*  @brief    ö���ַ���(ת)ö��ֵ
		*
		*  @param    const CString & strEnumName ö����
		*  @param    const CString & strEnumText ö���ַ���
		*  @return   int ����ö��ֵ
		*/
		static int Text2Enum(const CString& strEnumName, const CString& strEnumText);

		/**
		*  @brief    ö����ʾ�ַ���(ת)ö��ֵ
		*
		*  @param    const CString & strEnumName ö����
		*  @param    const CString & strEnumShow ö���ַ���
		*  @return   int ����ö��ֵ
		*/
		static int Show2Enum(const CString& strEnumName, const CString& strEnumShow);

		/**
		*  @brief    ö����ʾ�ַ���(ת)ö���ַ���
		*
		*  @param    const CString & strEnumName ö����
		*  @param    const CString & strEnumShow ö���ַ���
		*  @return   CString ����ö���ַ���
		*/
		static CString Show2Text(const CString& strEnumName, const CString& strEnumShow);

		/**
		*  @brief   ö���ַ���(ת)ö����ʾ�ַ���
		*
		*  @param    const CString & strEnumName ö����
		*  @param    const CString & strEnumText ö���ַ���
		*  @return   CString ����ö����ʾ�ַ���
		*/
		static CString Text2Show(const CString& strEnumName, const CString& strEnumText);

		/**
		*  @brief    ��ȡö����Ϣ����(�����е�˳����ö�ٶ��岻ͬ)
		*
		*  @param    const CString & strEnumName ö����
		*  @return   EnumTextInfos ö����Ϣ����
		*/
		static EnumTextInfoArray GetEnumInfoArray(const CString& strEnumName);

		/**
		*  @brief    ����ö����Ϣ�����ļ�
		*
		*  @param    const CString & strXmlFile ��̬ö�������ļ�
		*  @return   bool �ɹ�����true
		*/
		static bool LoadEnumConfig(const CString& strXmlFile);

		/**
		*  @brief    ��ȡ������Ϣ
		*
		*  @return   CString ���س�����Ϣ
		*/
		static CString GetLastError();
	};

#ifndef DISABLE_DYNAMIC_ENUM

	/*
	* ����ö��ת����
	*/
#define DECLARE_ENUM_CONVERSION(EnumName) \
	/*
	* ö��������ֵת��
	*/ \
		static  __inline int EnumName##ToInt(EnumName e) { return int(e); } \
	static  __inline EnumName IntTo##EnumName(int e) { return EnumName((int)e); } \
	/*
	* ö��ֵ(ת)ö���ַ���
	*/ \
		static __inline CString EnumName##2Text(EnumName nEnumValue) \
	{\
		return CDynEnum::Enum2Text(L###EnumName, int(nEnumValue)); \
	}\
	/*
	* ö��ֵ(ת)ö����ʾ�ַ���
	*/ \
		static  __inline CString EnumName##2Show(EnumName nEnumValue) \
	{\
		return CDynEnum::Enum2Show(L###EnumName, int(nEnumValue)); \
	}\
	/*
	* ö���ַ���(ת)ö��ֵ
	*/ \
		static  __inline EnumName Text2##EnumName(const CString& strEnumText) \
	{\
		return EnumName(CDynEnum::Text2Enum(L###EnumName, strEnumText)); \
	}\
	/*
	* ö����ʾ�ַ���(ת)ö��ֵ
	*/ \
		static  __inline EnumName Show2##EnumName(const CString& strEnumShow) \
	{\
		return EnumName(CDynEnum::Show2Enum(L###EnumName, strEnumShow)); \
	}\
	/*
	* ö���ַ���(ת)ö����ʾ�ַ���
	*/ \
		static  __inline CString EnumName##Text2Show(const CString& strEnumText) \
	{\
		return CDynEnum::Text2Show(L###EnumName,strEnumText); \
	}\
	/*
	* ö����ʾ�ַ���(ת)ö���ַ���
	*/ \
		static  __inline CString EnumName##Show2Text(const CString& strEnumShow) \
	{\
		return CDynEnum::Show2Text(L###EnumName, strEnumShow); \
	}\
	/*
	* ��ȡö����Ϣ����
	*/ \
		static  __inline EnumTextInfoArray Get##EnumName##InfoArray() \
	{\
		return CDynEnum::GetEnumInfoArray(L###EnumName); \
	}
#else

#define DECLARE_ENUM_CONVERSION(EnumName)

#endif
}
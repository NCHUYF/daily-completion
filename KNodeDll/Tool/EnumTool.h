//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           EnumTool.H
//    @author         fanHong
//    @date           2017/11/3 14:20
//    @brief          ö��-�ı�ת���ӿ�
//
//*****************************************************

#pragma once

namespace CommBase
{
	//-------------------------------------------------------------------
	// ʵ��ö��ֵ���ַ�����ת��
	//-------------------------------------------------------------------


	/****************************************************************************************
	*								** ʹ������ **
	*
	* 1��������ö��ֵ��
	*
	*	enum FileCreateTypeEnum
	*	{
	*		fctStdProject = 1,
	*		fctUserProject,
	*		fctGroupwareLib,
	*	};
	*
	*	DECLARE_ENUMTYPENAME_CONVERSION (FileCreateTypeEnum);
	*
	* 2����ʵ��ö�����ַ�����ʹ�ã�
	*
	*	BEGIN_ENUMTYPENAME_CONVERSION (FileCreateTypeEnum)
	*	{
	*		{ fctStdProject, _T("��׼����") },		{ fctUserProject, _T("����ģ��") },
	*		{ fctGroupwareLib, _T("��·�����") },	{ (FileCreateTypeEnum) NULL, NULL }
	*	}
	*	END_ENUMTYPENAME_CONVERSION (FileCreateTypeEnum);
	*
	* 3����ʹ��ת��������
	*
	*	// ö��ֵת�ַ���
	*	ZJString EnumText = FileCreateTypeEnumToText (fctStdProject);
	*
	*	// �ַ���תö��ֵ
	*	FileCreateTypeEnum EnumValue = TextToFileCreateTypeEnum (_T("��׼����"));
	*
	*	// ȡ��ö��ֵ����
	*	CEnumTextDefines EnumNameList;
	*	GetFileCreateTypeEnumDefines (EnumNameList);
	*
	****************************************************************************************/


	// ����ö��ֵ���ַ�����ת����������
	//   ע:������ַ���ת����ö��ʧ��,�򷵻�0,���򷵻ؾ����ö��ֵ
	//		�����ö��ת�����ַ���ʧ��,�򷵻�NULL,���򷵻ؾ��������
	//
	// ����: ö������ ProjectTypeEnum������������������
	//
	//		1. LPCTSTR ProjectTypeEnumToText (ProjectTypeEnum val);
	//		2. ProjectTypeEnum TextToProjectTypeEnum (LPCTSTR txt);
	//		3. int GetProjectTypeEnumDefines (CEnumTextDefines& arr);

	struct ENUM_YPET_EXT
	{
		int value;
		LPCTSTR text;
		int data;

		bool operator()(CString &strValue)
		{
			return strValue.Compare(text) == 0;
		}
	};
	typedef std::vector<ENUM_YPET_EXT> CEnumTypeTextArray;

	#define DECL_DYN_ENUM(ENUMNAME) \
	LPCTSTR ENUMNAME##ToText (ENUMNAME val);\
	ENUMNAME TextTo##ENUMNAME (LPCTSTR txt,int def=0);\
	size_t Get##ENUMNAME##Defines (CEnumTypeTextArray& arr);



	/** ���嶨��ö��ֵֵ���ַ�����ת������ */
	#define BEGIN_DYN_ENUM(ENUMNAME) \
	ENUM_YPET_EXT ENUMNAME##TextList[] =

	#define END_DYN_ENUM(ENUMNAME) \
	;\
	LPCTSTR ENUMNAME##ToText (ENUMNAME val)\
	{\
		for (int i = 0; ENUMNAME##TextList[i].text != NULL && i < 1000; i ++)\
		{\
			if (ENUMNAME##TextList[i].value == val)\
				return ENUMNAME##TextList[i].text;\
		}\
		return _T("");\
	}\
	ENUMNAME TextTo##ENUMNAME (LPCTSTR txt,int def)\
	{\
		if (txt == NULL || txt[0] == 0) return (ENUMNAME) def;\
		int i = 0;\
		for (i = 0; ENUMNAME##TextList[i].text != NULL && i < 1000; i ++)\
		{\
			if (!_tcscmp (ENUMNAME##TextList[i].text, txt))\
				return (ENUMNAME) ENUMNAME##TextList[i].value;\
		}\
		return (ENUMNAME) ENUMNAME##TextList[i].value;\
	}\
	size_t Get##ENUMNAME##Defines (CEnumTypeTextArray& arr)\
	{\
		arr.clear ();\
		for (int i = 0; ENUMNAME##TextList[i].text != NULL && i < 1000; i ++)\
		{\
			arr.push_back (ENUMNAME##TextList[i]);\
		}\
		return arr.size ();\
	}
}
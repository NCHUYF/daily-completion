//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�EnumConvert.h
// ����������ö��ת��
// ������ʶ��������	2018/08/30
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////
#pragma once
#include"vector"
struct ENUMDATA { int value; LPCTSTR text; int data; };
typedef std::vector<ENUMDATA> EnumTextDefines;

#define BEGIN_ENUM_CONVERSION(ENUMNAME) \
	static LPCTSTR ENUMNAME##2Text (ENUMNAME val);\
	static ENUMNAME Text2##ENUMNAME (LPCTSTR txt,int def=0);\
	static int Get##ENUMNAME##List (EnumTextDefines& arr);\
	static ENUMDATA ENUMNAME##TextList[] =

#define END_ENUM_CONVERSION(ENUMNAME) \
	;\
	LPCTSTR ENUMNAME##2Text (ENUMNAME val)\
		{\
		for (int i = 0; ENUMNAME##TextList[i].text != NULL && i < 1000; i ++)\
		{\
		if (ENUMNAME##TextList[i].value == val)\
		return ENUMNAME##TextList[i].text;\
		}\
		return NULL;\
		}\
		ENUMNAME Text2##ENUMNAME (LPCTSTR txt,int def)\
		{\
		if (txt == NULL) return (ENUMNAME) def;\
		int i = 0;\
		for (i = 0; ENUMNAME##TextList[i].text != NULL && i < 1000; i ++)\
		{\
		if (!_tcscmp (ENUMNAME##TextList[i].text, txt))\
		return (ENUMNAME) ENUMNAME##TextList[i].value;\
		}\
		return (ENUMNAME) ENUMNAME##TextList[i].value;\
		}\
		int Get##ENUMNAME##List (EnumTextDefines& arr)\
		{\
		arr.clear();\
		for (int i = 0; ENUMNAME##TextList[i].text != NULL && i < 1000; i ++)\
		{\
		arr.push_back (ENUMNAME##TextList[i]);\
		}\
		return arr.size();\
		}

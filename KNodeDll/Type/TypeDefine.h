//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           TypeDefine.H
//    @author         fanHong
//    @date           2017/11/2 16:58
//    @brief          �������Ͷ���
//
//*****************************************************

#include "Guid.h"

namespace CommBase
{
	// �ַ�������
	typedef std::vector<CString> StringArray;
	typedef StringArray::iterator StringArrayIter;
	
	// �ַ��������ֵ�
	typedef std::map<CString, CString>	StringMap;
	typedef StringMap::iterator			StringMapIter;
	typedef StringMap::const_iterator	StringMapCIter;

	// ���������С
	#define ARRAY_SIZE(x) sizeof((x))/sizeof((x)[0])

	// ��ȫɾ������
	#define SAFE_DELETE(x) if(NULL != (x)){delete (x); (x) = NULL;}

	// ��ȫɾ���������
	#define SAFE_DELETE_ARRAY(x) if(NULL != (x)){delete [] (x); (x) = NULL;}

	// �����Ƿ����0
	#define TZERO(x) (!((x)!=0))
	#define TZERO2(x) (((x) < 0.01) && ((x) > -0.01))
	#define TZERO3(x) (((x) < 0.001) && ((x) > -0.001))
	#define TZERO4(x) (((x) < 0.0001) && ((x) > -0.0001))
	#define TZERO6(x) (((x) < 0.000001) && ((x) > -0.000001))
	#define TZERO8(x) (((x) < 0.00000001) && ((x) > -0.00000001))
	#define TZERO12(x) (((x) < 0.000000000001) && ((x) > -0.000000000001))

	// С������ж�
	#define FLOAT_EQUAL2(x, y) TZERO2((x)-(y))
	#define FLOAT_EQUAL3(x, y) TZERO3((x)-(y))
	#define FLOAT_EQUAL4(x, y) TZERO4((x)-(y))
	#define FLOAT_EQUAL6(x, y) TZERO6((x)-(y))
	#define FLOAT_EQUAL8(x, y) TZERO8((x)-(y))
	#define FLOAT_EQUAL12(x, y) TZERO12((x)-(y))

		// �����������ٶ�
	#define GRAVITATION 9.80665

		// �ȷָ����
	#define DEGREE_CHAR _T('��')

		// �ַָ����
	#define MINUTE_CHAR _T('��')

		// ��ָ����
	#define SECOND_CHAR _T('��')

		//�����ָ�����
	#define SCALE_CHAR _T(':')

	#ifndef AdInt32
	#define AdInt32 long
	#endif

	// �������Ʒָ���ţ��������Ƹ�ʽ������=��������=����Ӣ������=�������ơ�
	#define PROP_SPLITE_CHAR		L"��"
}
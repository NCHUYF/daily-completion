#include "StdAfx.h"
#include "..\include\DataConvert.h"

using namespace BwProj::toolkit;

#ifndef _CVTBUFSIZE
	#define _CVTBUFSIZE (309+40)
#endif

wchar_t* DataConvert::UTF8ToUnicode(const char* str)
{
	int    textlen = 0;
	wchar_t * result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t *)malloc((textlen + 1)*sizeof(wchar_t));
	memset(result, 0, (textlen + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
	return    result;
}

// �������Ƚ�
bool DataConvert::FloatEqual (double var1, double var2, int dot)
{
	if (dot == -1)
	{
		return (fabs (var1 - var2) <= 0.000001);
	}
	else
	{
		//TCHAR fmtbuf1[_CVTBUFSIZE], fmtbuf2[_CVTBUFSIZE];
		//Float2Text (var1, fmtbuf1, dot, false);
		//Float2Text (var2, fmtbuf2, dot, false);

		//return !_tcscmp (fmtbuf1, fmtbuf2);
		ATLASSERT (dot < 10);

		//long nMultiple = 1;
		//while (dot > 0)
		//{
		//	nMultiple *= 10;

		//	dot--;
		//}

		//return (fabs(var1 - var2) * nMultiple < 1);

		ULONG DotPow = (ULONG) pow ((float) 10, dot + 1);
		LONGLONG u1 = (LONGLONG) (var1 * DotPow);
		LONGLONG u2 = (LONGLONG) (var2 * DotPow);

		u1 += 5; u1 /= 10;
		u2 += 5; u2 /= 10;

		return u1 == u2;
	}
}

// ��������������
double DataConvert::FloatRound (double num, int dot)
{
	if (dot < 0) return num;

	long dSign = 1;
	if (num < 0) dSign = -1;	
	long cs = (long) pow ((double) 10, dot);
	LONGLONG ullVal = (LONGLONG) (fabs (num) * cs + 0.5);

	return ((double)(ullVal * dSign)) / cs;
}

/** 
* __int64 ת�����ַ���
* @param [in] val		Ҫ��ʽ������ֵ
* @param [in] buff		�������
* @return	����__int64��ʽ������ַ���
*/
LPCTSTR DataConvert::I642Text (__int64 val, TCHAR* buff)
{
	// ʵ��64λ����ת��
	errno_t err = _i64tot_s(val, buff, _CVTBUFSIZE, 10);
	if (err != 0)
		return _T("");

	//_sntprintf_s (buff, _T("%d"), val);
	return buff;
}

/** 
* __int64 ת�����ַ���
* @param [in] val		Ҫ��ʽ������ֵ
* @return	����__int64��ʽ������ַ���
*/
CString DataConvert::I642Text (__int64 val)
{
	TCHAR buff [_CVTBUFSIZE];
	return I642Text (val, buff);
}

/** 
* bool ת�����ַ���
* @param [in] val		Ҫ��ʽ������ֵ
* @return	����bool��ʽ������ַ���
*/
LPCTSTR DataConvert::Bool2Text (BOOL val)
{
	return val ? _T("True") : _T("False");
}

/** 
* �ַ��� ת����bool
* @param [in] val		Ҫ��ʽ������ֵ
* @return	�����ַ�����ʽ�����bool
*/
bool DataConvert::Text2Bool (LPCTSTR val)
{
	CString str(val);
	str.MakeUpper();
	return str == _T("TRUE") || str == _T("T");
}

// �Ƚ������ַ����Ƿ���ȣ������ִ�Сд
bool DataConvert::StringEqual (LPCTSTR str1, LPCTSTR str2)
{
	if (str1 == str2)
		return true;
	if (str1 == NULL || str2 == NULL)
		return false;

	//TCHAR ch1[2], ch2[2];
	while (*str1 && *str2)
	{
		// ȫ��ת����Сд��'a' > 'A'��
		TCHAR c1 = (*str1 >= _T('A') && *str1 <= _T('Z')) ? (*str1 + _T('a')-_T('A')) : * str1;
		TCHAR c2 = (*str2 >= _T('A') && *str2 <= _T('Z')) ? (*str2 + _T('a')-_T('A')) : * str2;

		if (c1 != c2)
			return false;

		str1 ++; str2 ++;
	}

	return (*str1 == NULL && *str2 == NULL);
}

// ��������������
//	num		= Ҫ��ʽ������ֵ
//	dot		= С��λ����Ϊ -1 ��ʾ�ǲ���������
//	buffer	= �������
//	FullZero= ���С��λ�������Ƿ��� 0 ���
LPCTSTR DataConvert::Float2Text(double num, TCHAR* buffer, int dot, bool FullZero)
{
	ATLASSERT(dot >= -1 && buffer != NULL);

	TCHAR fmt[_CVTBUFSIZE];

	if (dot >= 0)
	{
		_sntprintf_s(fmt, _CVTBUFSIZE,  _T("%%0.%df"), dot);
		_sntprintf_s(buffer, _CVTBUFSIZE, 1, fmt, FloatRound(num, dot));
	}
	else
	{
		_sntprintf_s(buffer, _CVTBUFSIZE, 1, _T("%f"), num);
	}

	if (FullZero == false || dot <= 0)
	{
		// ����С����λ��
		int dotNum = -1;
		for (int i = 0; i < (int)_tcslen(buffer); i++)
		if (buffer[i] == _T('.'))
		{
			dotNum = i;
			break;
		}

		// ɾ��С�������� 0
		if (dotNum >= 0)
		{
			for (int i = (int)_tcslen(buffer) - 1; i >= dotNum; i--)
			if (buffer[i] == _T('0'))
				buffer[i] = NULL;
			else
				break;

			if (buffer[_tcslen(buffer) - 1] == _T('.'))
				buffer[_tcslen(buffer) - 1] = NULL;
		}
	}

	return buffer;
}

CString DataConvert::Float2Text(double num, int dot, bool FullZero)
{
	TCHAR fmtbuf[_CVTBUFSIZE];
	return Float2Text(num, fmtbuf, dot, FullZero);
}

/**
* long ת�����ַ���
* @param [in] val		Ҫ��ʽ������ֵ
* @param [in] buff		�������
* @return	����long��ʽ������ַ���
*/
LPCTSTR DataConvert::Long2Text(long val, TCHAR* buff)
{
	_sntprintf_s(buff, _CVTBUFSIZE, 1, _T("%d"), val);
	return buff;
}

/**
* long ת�����ַ���
* @param [in] val		Ҫ��ʽ������ֵ
* @return	����long��ʽ������ַ���
*/
CString DataConvert::Long2Text(long val)
{
	TCHAR buff[_CVTBUFSIZE];
	return Long2Text(val, buff);
}
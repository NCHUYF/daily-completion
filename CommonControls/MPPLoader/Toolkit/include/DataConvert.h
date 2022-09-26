
#pragma once
#include <math.h>

// begin namespace
namespace BwProj{ namespace toolkit{

/** @addtogroup DataConvert
* @{
*/

//! ����ת����
class COMMONTOOLS_API DataConvert
{
public:
	static wchar_t* UTF8ToUnicode(const char* str);

	/** 
	* �Ƚ������������Ƿ����
	* @param [in] var1	������1
	* @param [in] var2	������2
	* @param [in] dot	С��λ����Ĭ��Ϊ-1����ʾ���������루�����0.000001����Ϊ��ȣ�
	* @return	���������������Ƿ����
	* - true ��ȣ�false �����
	*/
	static bool FloatEqual (double var1, double var2, int dot = -1);

	/** 
	* ��������������
	* @param [in] num		Ҫ��ʽ������ֵ
	* @param [in] dot		С��λ����Ϊ -1 ��ʾ�ǲ���������
	* @return	���ظ�ʽ�������ֵ
	*/
	static double FloatRound (double num, int dot);

	/** 
	* __int64 ת�����ַ���
	* -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 
	* @param [in] val		Ҫ��ʽ������ֵ
	* @param [in] buff		�������
	* @return ����__int64��ʽ������ַ���
	*/
	static LPCTSTR I642Text (__int64 val, TCHAR* buff);

	/** 
	* __int64 ת�����ַ���
	* -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 
	* @param [in] val		Ҫ��ʽ������ֵ
	* @return	����__int64��ʽ������ַ���
	*/
	static CString I642Text (__int64 val);

	/** 
	* bool ת�����ַ���
	* @param [in] val		Ҫ��ʽ������ֵ
	* @return	����bool��ʽ������ַ���
	*/
	static LPCTSTR Bool2Text (BOOL val);

	/** 
	* �ַ��� ת����bool
	* valתΪ��д����£�val�ǡ�TRUE����T������true�����򷵻�false
	* @param [in] val		Ҫ��ʽ������ֵ
	* @return	�����ַ�����ʽ�����bool
	*/
	static bool Text2Bool (LPCTSTR val);

	/**
	* �Ƚ������ַ����Ƿ���� (�����ִ�Сд)
	* @param [in] str1		�ַ���1
	* @param [in] str2		�ַ���2
	* @return	�����ַ����Ƿ����
	* - true ��ȣ� false �����
	*/
	static bool StringEqual (LPCTSTR str1, LPCTSTR str2);

	/**
	* ����������������ַ���
	* @param [in] num		Ҫ��ʽ������ֵ
	* @param [in] dot		С��λ����Ϊ -1 ��ʾ�ǲ��������루ʵ������C++���ԭ��ֻ���6λС����
	* @param [in] buffer	�������
	* @param [in] FullZero	���С��λ�������Ƿ��� 0 ���
	* @return	���ظ�������ʽ������ַ���
	*/
	static LPCTSTR Float2Text(double num, TCHAR* buffer, int dot = -1, bool FullZero = false);

	/**
	* ����������������ַ���
	* @param [in] num		Ҫ��ʽ������ֵ
	* @param [in] dot		С��λ����Ϊ -1 ��ʾ�ǲ���������
	* @param [in] FullZero	���С��λ�������Ƿ��� 0 ���
	* @return	���ظ�������ʽ������ַ���
	*/
	static CString Float2Text(double num, int dot = -1, bool FullZero = false);

	/**
	* long ת�����ַ���
	* long��Χ��-2,147,483,648 �� 2,147,483,647
	* @param [in] val		Ҫ��ʽ������ֵ
	* @param [in] buff		�������
	* @return	����long��ʽ������ַ���
	*/
	static LPCTSTR Long2Text(long val, TCHAR* buff);

	/**
	* long ת�����ַ���
	* long��Χ��-2,147,483,648 �� 2,147,483,647
	* @param [in] val		Ҫ��ʽ������ֵ
	* @return	����long��ʽ������ַ���
	*/
	static CString Long2Text(long val);
};

/** * @} */
// end namespace
}}
/** @} */
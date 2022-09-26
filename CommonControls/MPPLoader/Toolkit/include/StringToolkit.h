#pragma once
#include <shellapi.h>

// begin namespace
namespace BwProj{ namespace toolkit{


/** @addtogroup CadreLibToolkit
* @{
*/

//! �ַ���ϵͳ
class COMMONTOOLS_API CStringToolkit
{
public:
	/**
	* ȥ���������ߵĿ�����س���
	* @param [in] sString	�ַ���
	* @return	����ȥ���������ߵĿ��кͻس�������ַ���
	*/
	static CString Trim (CString sString);

	/**
	* ͳ���ַ������ж��ٸ��� sParChr �ָ�ĵ���
	* @param [in] sString	�ַ���
	* @param [in] sParChr	�ָ��ַ�
	* @return	�����ַ������ж��ٸ��� sParChr �ָ�ĵ��ʵĸ���
	*/
	static int CountWord (CString sString, TCHAR sParChr = _T(' '));

	/**
	*	��ȡ�ַ�����ָ���ĵ���
	* @param [in] sString	�ַ���
	* @param [in] WordIdx	��ʼλ��
	* @param [in] sParChr	�ָ��ַ���Ĭ��Ϊ�գ�
	* @return ���ض�ȡ���ַ���
	*/
	static CString ReadWord (CString sString, int WordIdx, TCHAR sParChr = _T(' '));

	/**
	* ����ָ���ĵ���
	* @param [in] SourStr	Դ�ַ���
	* @param [in] Word		����
	* @param [in] RigorFind	�ϸ�ƥ�䣨Ĭ��Ϊtrue��
	* - true �������룬 false ��ɴ�д��ĸ���ϸ����
	* @param [in] StartPos	��ʼλ�ã�Ĭ��Ϊ1��
	* @param [in] sParChr	�ָ��ַ���Ĭ��Ϊ�գ�
	* @return ����ָ�����ʵ�λ��
	*/
	static int FindWord (CString SourStr, CString Word, bool RigorFind = true,
						int StartPos = 1, TCHAR sParChr = _T(' '));

	/**
	* �����ָ��λ�ÿ�ʼ���������ַ�
	* @param [in] str	Դ�ַ���
	* @param [in] chr	�������ַ�
	* @param [in] pos	������ʼλ�ã�Ĭ��Ϊ0������ʾ�����ʼ��
	* @return ����ָ�����ʵ�λ�ã�pos<0 ʱ����-1��
	*/
	static int FindLastChar (CString str, TCHAR chr, int pos = 0);

	/**
	* ɾ���������ַ������ݵ� 0
	* @param [in] NumStr	�������ַ���
	* @param [in] keepDot	���Ϊ���������һ��.0����12.00����12.0
	* @return ����ɾ������0���ַ���
	* - ����12.34000 ����Ϊ 12.34��12.00 ����Ϊ 12
	*/
	static CString TrimNumberString (CString NumStr, bool keepDot = false);

	/**
	* ������ת�� CString
	* 
	* long��Χ��-2,147,483,648 �� 2,147,483,647 
	* @param [in] value	������
	* @return ����ת���ɵ��ַ���
	*/
	static CString IntToStr (long value);

	/**
	* �ַ���ת���ɳ�����
	*
	* long��Χ��-2,147,483,648 �� 2,147,483,647 
	* @param [in] str	�ַ���
	* @return ����ת���ɵĳ�����
	*/
	static long StrToInt (CString str);

	/**
	* �ַ���ת���ɸ�����
	* @param [in] str	�ַ���
	* @return ����ת���ɵĸ�����
	*/
	static double StrToDouble (CString str);

	/**
	* ��ȡ�ַ�������ƴ��������ĸ
	* @param [in] HanZiText	�ַ���
	* @return ���ػ�ȡ�ĺ���ƴ������ĸ
	*/
	static CString GetPingYinFirstLetter (LPCTSTR HanZiText);

	/**
	* �Ƚ������汾�Ŵ�С
	* @param [in] version1	�汾��1
	* @param [in] version2	�汾��2
	* @return ���ر�ʾ�汾�Ŵ�С������
	* - 1 �汾��1 > �汾��2�� 0 �汾��1 = �汾��2�� -1 �汾��1 < �汾��2
	*/
	static int CompareVersion (CString version1, CString version2);

	/**
	* �ж��Ƿ�Ϊ����(���ı���������)
	* @param [in] strText
	* @return
	*/
	static bool IsNumber(CString strText);
};

/** * @} */
}}

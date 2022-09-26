//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           Md5Tool.H
//    @author         fanHong
//    @date           2017/11/2 17:17
//    @brief          MD5��װ
//
//*****************************************************

#pragma once

namespace CommBase
{
	/**
	*  @class    MD5��װ��
	*
	*  @brief
	*/
	class COMMBASE_API CMd5Tool
	{
	public:
		/**
		*  @brief    ��ȡ�ļ���Md5��;
		*
		*  @param    const CString & strFile �����ļ�;
		*  @return   CString �ļ���MD5��;
		*/
		static CString GetFileMd5(const CString& strFile);

		/**
		*  @brief    ���ַ���תΪMD5
		*
		*  @param    const CString & strText
		*  @return   CString
		*/
		static CString StringToMd5(const CString& strText);
	};
}
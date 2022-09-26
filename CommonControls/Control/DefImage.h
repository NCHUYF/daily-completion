//*****************************************************
//    
//    @copyright      �����ά���
//    @version        v1.0
//    @file           DefImage.H
//    @author         KG
//    @date           2018/4/20 13:50
//*****************************************************

#pragma once

/**
*  @class    Ĭ��ͼƬ��Դ��
*
*  @brief
*/
class COMMONCONTROLS_API CDefImage
{
public:
	/**
	*  @brief    ��ȡ���Ŀ¼
	*
	*  @return   HICON
	*/
	static HICON LoadSysIcon();

	/**
	*  @brief    ��ȡResource\ImageĿ¼��ͼ��
	*
	*  @return   HICON ����ͼ��(�����ͷ�)
	*/
	static HICON LoadIcon(const CString& strFile);

	/**
	*  @brief    ��ȡResource\ImageĿ¼��λͼ
	*
	*  @return   HBITMAP ����λͼ(�����ͷ�)
	*/
	static HBITMAP LoadBitmap(const CString& strFile);
};

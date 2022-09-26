//****************************************************************
//
//   @copyright     ���������
//   @version       v1.0
//   @file          ��Ļ��ͼ����
//   @author        HBQing
//   @date          2018/12/31 14:39
//*****************************************************************/

#pragma once

extern "C" _declspec(dllimport) int StartScreenshot(LPCTSTR szSaveFileName);

class COMMONCONTROLS_API CScreenShot
{
	CScreenShot();

public:
	/**
	*  @brief    ��ͼ����
	*
	*  @param    LPCTSTR szSaveFileName ���ֽ�ͼ�ļ����ƣ�֧�ֵı����ʽ:BMP/TIFF/GIF/JPEG/PNG��
	*  @return   bool
	*/
	static bool DoScreenShot(LPCTSTR szSaveFileName);

};
//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           IEditBase.H
//    @author         jzl
//    @data           2015/7/7 17:08
//    @brief          �༭�ؼ�����
//*****************************************************

#pragma once

/**
*  @class    IEditBase
*
*  @brief    �༭�ؼ�����
*/
class IEditBase
{
public:
	virtual ~IEditBase() {}

	/**
	*  @brief    ȡ���༭
	*
	*/
	virtual void CancelEdit() = 0;
};
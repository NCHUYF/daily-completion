//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           ResOverride.H
//    @author         JZL
//    @date           2018/5/15 09:32
//    @brief          DLL��Դ�л�
//
//*****************************************************

#pragma once

namespace CommBase
{
	/*
	* �Զ��л���Դ����ǰDLL��
	*/
	class COMMBASE_API CResourceOverride
	{
	public:
		CResourceOverride();
		~CResourceOverride();
	protected:
		HMODULE _oldResModule;
	};

	#define RESOURCE_OVERRIDE CResourceOverride resOverride;
}
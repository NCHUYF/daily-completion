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

#include "stdafx.h"

using namespace CommBase;

	CResourceOverride::CResourceOverride()
	{
		_oldResModule = GetModuleHandle(NULL);
		AfxSetResourceHandle(gInstance);
	}

	CResourceOverride::~CResourceOverride()
	{
		AfxSetResourceHandle(_oldResModule);
	}

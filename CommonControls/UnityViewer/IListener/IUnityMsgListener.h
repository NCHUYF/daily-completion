//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           IUnityMsgListener.h
//    @author         yf
//    @data           2021/08/16  
//    @brief          unity��Ϣ�����ӿ�
//
//*****************************************************


#pragma once

class COMMONCONTROLS_API IUnityMsgListener
{
public:
	IUnityMsgListener();
	virtual ~IUnityMsgListener();
public:
	/**
	*  @brief   ����unity��������Ϣ
	*
	*  @param    wParam 
	*  @param    wParam 
	*  @return   void
	*/
	virtual void OnReceiveMessage(const std::string szsMsg) = 0;
};


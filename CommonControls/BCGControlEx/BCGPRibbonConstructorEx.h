/*******************************************************************
* �ļ����ƣ�BCGPRibbonConstructorEx.h
* ����������������
* �ļ������������Զ���ؼ�
* ����汾��
* ����ʱ�䣺2018-4-16
* Copyright (C) ������΢�¼������޹�˾ All rights reserved
*******************************************************************/
#pragma once

#include "BCGPRibbonConstructor.h"
#include "BCGPRibbonMainPanelEx.h"

class CBCGPRibbonBar;
class CBCGPRibbonStatusBar;

class CBCGPRibbonConstructorEx : public CBCGPRibbonConstructor
{
public:
	CBCGPRibbonConstructorEx(const CBCGPRibbonInfo& info);

	virtual ~CBCGPRibbonConstructorEx() {};

public:
	/**
	* �����ؼ�
	* @param [in] info �ؼ���Ϣ
	* @return ���ؿؼ�ʵ��
	*/
	virtual CBCGPBaseRibbonElement* CreateElement(const CBCGPRibbonInfo::XElement& info) const;

	/**
	* �������˵�
	* @param [in] info �ؼ���Ϣ
	* @return
	*/
	virtual void ConstructCategoryMain(CBCGPRibbonBar& bar, const CBCGPRibbonInfo::XCategoryMain& info) const;

	/**
	* �����˵���ť
	* @param [in] bar 
	* @return
	*/
	virtual CBCGPRibbonMainButton* CreateMainButton(CBCGPRibbonBar& bar) const;

	/**
	* �����˵���ť
	* @param [in] info bar
	* @param [in] info �ؼ���Ϣ
	* @return
	*/
	virtual CBCGPRibbonMainPanelEx* CreateCategoryMainEx(CBCGPRibbonBar& bar, const CBCGPRibbonInfo::XCategoryMain& info) const;

	/**
	* �ж��Ƿ����Զ���ؼ�
	* @param [in] strID			 �ؼ�ID��
	* @param [in] strEleType	 �ؼ����
	* @return ���Զ���ؼ�����TRUE,���򷵻�FALSE
	*/
	BOOL IsCustomElement(const CString& strID, 
						 CString& strEleType) const;

};


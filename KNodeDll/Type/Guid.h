//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           Guid.H
//    @author         fanHong
//    @date           2017/11/2 15:57
//    @brief          GUID��װ
//
//*****************************************************

#pragma once

namespace CommBase
{
	/**
	*  @class    GUID����Hashֵ
	*
	*  @brief
	*/
	struct HashGuid
	{
		/**
		*  @brief    Hashֵ����
		*
		*/
		size_t operator()(const GUID& guid) const;
	};

	
	/**
	*  @class    GUID��װ��
	*
	*  @brief
	*/
	class COMMBASE_API CGuid
	{
	public:
		CGuid();
		CGuid(const GUID& guid);
		CGuid(LPCWSTR strId);

	public:
		/**
		*  @brief    ������ǰ��GUID
		*
		*/
		void ChangeNew();

		/**
		*  @brief    GUIDתString
		*
		*  @param    bool bStand �Ƿ��ַ���֮��ʹ��"-"���ӣ�Ĭ�ϲ�ʹ��
		*  @return   CString ����GUID�ַ���
		*/
		CString ToString(bool bStand = false) const;

		/**
		*  @brief    ���GUID����(IsEmpty����TRUE)
		*
		*  @return   const CGuid&
		*/
		CGuid& Clear();

		/**
		*  @brief    �ж�GUID�Ƿ�Ϊ��
		*
		*  @return   bool Ϊ�շ���true
		*/
		bool IsEmpty() const;

		/**
		*  @brief    ת����CString
		*
		*/
		operator CString() const;

	public:
		/**
		*  @brief    ת����GUID
		*
		*/
		operator GUID() const;

		/**
		*  @brief    ����Map�жϴ�С
		*
		*  @param    const CGuid & guid CGuidֵ
		*  @return   bool ��ǰֵС�ڲ���ֵ����true
		*/
		bool operator < (const CGuid& guid) const;

		/**
		*  @brief    GUID��ֵ
		*
		*  @param    const GUID & guid CGuidֵ
		*  @return   CGuid& ��������
		*/
		CGuid& operator = (const CGuid& guid);

		/**
		*  @brief    ��������ж�
		*
		*  @param    const CGuid & guid
		*  @return   bool ��ȷ���true
		*/
		bool operator == (const CGuid& guid) const;

		/**
		*  @brief    ��������ж�
		*
		*  @param    const CGuid & guid
		*  @return   bool ����ȷ���true
		*/
		bool operator != (const CGuid& guid) const;

	private:
		GUID	_guid;	///<GUID
	};
}
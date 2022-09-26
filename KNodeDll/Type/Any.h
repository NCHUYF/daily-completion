//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           Any.H
//    @author         fanHong
//    @date           2017/11/2 16:01
//    @brief          �ɱ���������
//
//*****************************************************

#pragma once

#include "Guid.h"

namespace CommBase
{
	/*
	* ������������
	*/
	typedef enum
	{
		ANY_EMPTY = 0,		///< ������(û�и�ֵ)
		ANY_BOOL = 1,		///< bool
		ANY_INT = 2,		///< int
		ANY_DOUBLE = 5,		///< double
		ANY_STRING = 6,		///< WCHAR*
		ANY_POINT = 7,		///< CGePoint3d
		ANY_GUID = 8,		///< GUID
		ANY_STREAM = 9,		///< BYTE*
		ANY_PTARRAY = 10,	///< osg::Vec3d Array
		ANY_INT64 = 11,		///< int64
		ANY_MATRIX = 12		///< Matrix
	}EAnyType;

	/**
	*  @class    �ɱ�����������
	*
	*  @brief
	*/
	class COMMBASE_API CAny
	{
	public:
		CAny();
		~CAny();

		/**
		*  @brief    �ж��Ƿ�Ϊ��
		*
		*  @return   bool û�н��и�ֵ��Ϊfalse
		*/
		bool IsEmpty() const;

		/**
		*  @brief    ��ȡ��������
		*
		*  @return   EAnyType ���ض�Ӧ��������
		*/
		EAnyType GetType() const;

		/**
		*  @brief    ��������������(�ض�����ʹ��,������߸�ֵ����)
		*
		*  @param   const CAny& other(�˶�����ú����ݻ����)
		*/
		void Attach(const CAny& other) const;

	public:
		/**
		*  @brief    ��ȡ�ַ���ֵ(�ڲ�����ת��)
		*
		*  @param    int nDotNum С����λ��
		*  @return   CString �����ַ���ֵ
		*/
		CString GetStringValue(int nDotNum = 2) const;

		/**
		*  @brief    ���ַ���ֵת��ָ������ֵ
		*
		*  @param    LPWSTR lpValue �ַ���ֵ����ֵ
		*  @param    EAnyType vType ת������������
		*/
		void SetStringValue(LPCWSTR lpValue, EAnyType vType);

		/**
		*  @brief    �ж�����CAny�Ƿ����
		*
		*  @param    const CAny& value
		*/
		bool operator == (const CAny& value) const;

		/**
		*  @brief    �ж�����CAny�Ƿ����
		*
		*  @param    const CAny& value
		*/
		bool operator != (const CAny& value) const;

	public:
		/**
		*  @brief    �������캯��
		*
		*  @param    const CAny & value
		*/
		CAny(const CAny& value);
		CAny& operator = (const CAny& value);

		/**
		*  @brief    boolֵ����
		*
		*  @param    const bool & value
		*  @return
		*/
		CAny(const bool& value);
		CAny& operator = (const bool& value);
		operator bool() const;

		/**
		*  @brief    intֵ����
		*
		*  @param    const int & value
		*/
		CAny(const int& value);
		CAny& operator = (const int& value);
		operator int() const;

		/**
		*  @brief    int64ֵ����
		*
		*  @param    const INT64 & value
		*/
		CAny(const INT64& value);
		CAny& operator = (const INT64& value);
		operator INT64() const;

		/**
		*  @brief    size_tֵ����
		*
		*  @param    const size_t & value
		*/
		CAny(const size_t& value);
		CAny& operator = (const size_t& value);
		operator size_t() const;

		/**
		*  @brief    longֵ����
		*
		*  @param    const long & value
		*/
		CAny(const long& value);
		CAny& operator = (const long& value);
		operator long() const;

		/**
		*  @brief    DWORDֵ����
		*
		*  @param    const DWORD & value
		*/
		CAny(const DWORD& value);
		CAny& operator = (const DWORD& value);
		operator DWORD() const;


		/**
		*  @brief    doubleֵ����
		*
		*  @param    const double & value
		*/
		CAny(const double& value);
		CAny& operator = (const double& value);
		operator double() const;

		/**
		*  @brief    �ַ���ֵ����
		*			 BuildString���������׵��벻Ҫʹ��
		*
		*  @param    const LPCTSTR & value
		*/
		CAny(const LPCWSTR& value);
		CAny& operator = (const LPCWSTR& value);
		operator LPCWSTR() const;
		LPWSTR BuildString(UINT nLen);

		/**
		*  @brief    �ַ���ֵ����
		*
		*  @param    const CString & value
		*/
		CAny(const CString& value);
		CAny& operator = (const CString& value);
		operator CString() const;

		/**
		*  @brief    GUID����
		*
		*  @param    const GUID & value
		*/
		CAny(const GUID& value);
		CAny& operator = (const GUID& value);
		operator GUID() const;

		/**
		*  @brief    CGuid����
		*
		*  @param    const CGuid & value
		*/
		CAny(const CGuid& value);
		CAny& operator = (const CGuid& value);
		operator CGuid() const;

		/**
		*  @brief    �ֽ�������(ʹ����ע��)
		*			 ����/����ʱ�����BYTE*����п�����
		*			 ��ȡʱBYTE*&Ϊָ��CAny�ڲ��ڴ棬����Ҫ�Լ��ͷţ�����Ҫע��CAny�������ڡ�
		*			 ����BYTE*&�ڴ�����ͷ�
		*
		*  @param    const BYTE * value
		*  @param    int len ���ݳ���
		*/
		CAny(const BYTE* value, int len);
		void SetStreamValue(const BYTE* value, int len);
		int GetStreamValue(BYTE*& value) const;
		BYTE* BuildStreamValue(int len);

		/**
		*  @brief    ��һ�������CVariantData����תΪ�ڴ���(ʹ����ע������)
		*
		*  @param    const void * value
		*/
		CAny(const void* value);
		void SetVoidStreamValue(const void* value);
		int GetVoidStreamValue(void*&) const;

	protected:
		/**
		*  @brief    �����ڴ�
		*
		*/
		void ClearTypeMemory();

	private:
		union vdValue
		{
			bool			valBool;	///< bool
			int				valInt;		///< int/BOOL/size_t
			double			valDouble;	///< double
			INT64			valInt64;	///< int64
			DWORD			valDword;	///< DWORD
			WCHAR			*valString;	///< WCHAR*
			GUID			*valGuid;	///< GUID
			BYTE			*valStream;	///< BYTE*
		}_vdValue;						///< Dataֵ
		char _vdType;					///< Data����
	};
}
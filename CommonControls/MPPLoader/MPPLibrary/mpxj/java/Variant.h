#pragma once

#include "Object.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// ������������
//

class COMMONCONTROLS_API Variant : public Object2
{
public:
	Variant();
	Variant(bool value);
	Variant(int value);
	Variant(double value);
	Variant(LPCTSTR value);
	Variant(LPCGUID value);
	Variant(const Variant& value);
	virtual ~Variant();

	Variant& operator = (bool value);
	Variant& operator = (int value);
	Variant& operator = (double value);
	Variant& operator = (LPCTSTR value);
	Variant& operator = (LPCGUID value);
	Variant& operator = (const Variant& value);

	VARTYPE type();

	operator double();
	operator int();
	operator bool();
	operator CString();
	operator LPCGUID();

	double doubleValue();
	LPCGUID guidValue();
	int intValue();
	bool boolValue();
	CString stringValue();

	CComVariant& getComVariant();

	virtual CString toString();

private:
	VARTYPE _type;
	CComVariant _value;
	LPGUID _guid;
	//CString* _toString;
};

typedef std::shared_ptr<Variant> VariantPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
// �������Ͷ���
//
typedef Variant Number;
typedef Variant Integer;
typedef Variant Double;
typedef Variant Boolean;
typedef Number BigInteger;
typedef Number BigDecimal;

typedef std::shared_ptr<Number> NumberPtr;
typedef std::shared_ptr<BigInteger> BigIntegerPtr;
typedef std::shared_ptr<BigDecimal> BigDecimalPtr;
typedef std::shared_ptr<Integer> IntegerPtr;
typedef std::shared_ptr<Double> DoublePtr;
typedef std::shared_ptr<Boolean> BooleanPtr;

// �ַ���ָ�룬��û���ַ����ɷ��ؿմ���������NULL
class StringPtr : public std::shared_ptr<CString>
{
public:
	operator CString();	// û��ֵʱ���ؿմ�
	operator LPCTSTR();	// û��ֵʱ����NULL

	void reset(LPCTSTR value);
};
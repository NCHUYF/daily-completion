#pragma once

// ��̬����ת����ʽ
//std::shared_ptr<base> sp0(new derived);
//std::shared_ptr<derived> sp1 = std::dynamic_pointer_cast<derived>(sp0);

///////////////////////////////////////////////////////////////////////////////////////////////////
// java �������
//

#include <memory>
class COMMONCONTROLS_API Object2
{
public:
	virtual ~Object2() {}

	virtual CString toString();

	virtual bool equals(Object2* arg0);
};
typedef std::shared_ptr<Object2> ObjectPtr;

class ObjectPtrArray : public Object2
{
public:
	ObjectPtrArray(int size);
	~ObjectPtrArray();
	ObjectPtr& operator[](int index);
	//const Object*& operator[](int index) const;
	ObjectPtr& get(size_t index);
	size_t length();
	void reset();
	void clear();

private:
	CAtlArray<ObjectPtr> _array;
	int _length;
};

typedef std::shared_ptr<ObjectPtrArray> ObjectArrayPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����Ƚϻ���
//
class Comparable
{
public:
	virtual int compareTo(Object2* arg0) = 0;
};

template<class T>
class ComparableT : public Comparable
{
public:
	virtual int compareTo(Object2* arg0)
	{
		return compareTo(dynamic_cast<T*>(arg0));
	}

	virtual int compareTo(T* arg0) = 0;
};
#pragma once

// ��̬��Դ��װ
class ClearProxy
{
public:
	virtual ~ClearProxy() {}
	virtual void Clear() = 0;
};

// ��̬��Դע���
class StaticResource2Clear
{
	StaticResource2Clear() {}
public:
	virtual ~StaticResource2Clear();

	static StaticResource2Clear* GetInstance();

	void Register(ClearProxy* sw);

	void ClearAll();

private:
	CAtlArray<ClearProxy*> _wrapperArray;

	static std::auto_ptr<StaticResource2Clear> _instance;
};

// �ͷŹ���ָ��
template <class T>
class SharedPtrClear : public ClearProxy
{
public:
	SharedPtrClear(std::shared_ptr<T>* sharedObject)
	{
		_sharedObject = sharedObject;
	}

	void Clear()
	{
		_sharedObject->reset();
	}

private:
	std::shared_ptr<T>* _sharedObject;
};

// �ͷŹ���ָ��
template <class T>
class AutoPtrClear : public ClearProxy
{
public:
	AutoPtrClear(std::auto_ptr<T>* autoObject)
	{
		_autoObject = autoObject;
	}

	void Clear()
	{
		_autoObject->reset();
	}

private:
	std::auto_ptr<T>* _autoObject;
};
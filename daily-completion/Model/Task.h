#pragma once

struct Task
{
	CString strName;
	bool bComplete;
};

struct CTaskModel : public BaseModel
{
public:
	YFramework::BindableProperty<CString> SearchKey; // �����ؼ���
	YFramework::BindableProperty<int> k; // �����ؼ���
protected:
	virtual void Init(){}
};

class UpdateGridEvent
{

};
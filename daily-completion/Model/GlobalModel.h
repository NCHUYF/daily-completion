#pragma once
struct CGlobalModel : public BaseModel
{
public:
	YFramework::BindableProperty<CString> SearchKey; // �����ؼ���
protected:
	virtual void Init() {}
};

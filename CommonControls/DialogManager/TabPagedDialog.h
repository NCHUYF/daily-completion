// ͨ��Tab���Ի���ʵ��
// _______________________________________________________________
//|	tabҳ | tabҳ |												  |
//|_______________________________________________________________|
//|																  |
//|																  |
//|																  |
//|					��ҳ������ITabPageContext					  |
//|																  |															
//|																  |	
//|																  |
//|_______________________________________________________________|
#pragma once
#include <memory>

class ITabPageContext : public IObject
{
public:
	ITabPageContext() {};
	virtual ~ITabPageContext() {};

	virtual void Leave() {};
	virtual void Enter() {};
	virtual void PutParam(LPCTSTR key, IObject *pObject) = 0;
	virtual HWND GetWndHandle(HWND parent) { return NULL; }
	virtual LPCTSTR GetTabName() { return L""; }
};

class ITabPageContextWithCfgName : public ITabPageContext
{
public:
	void SetCaptionName(LPCTSTR strName) { _strCaptionName = strName; }
	virtual LPCTSTR GetTabName() { return _strCaptionName; }
	virtual void PutParam(LPCTSTR key, IObject *pObject)
	{
		_mapKeyParam[key] = pObject;
	}
	IObject* GetParam(LPCTSTR key)
	{
		auto finder = _mapKeyParam.find(key);
		return finder == _mapKeyParam.end() ? NULL : finder->second;
	}
protected:
	CString _strCaptionName;
	std::map<CString, IObject*> _mapKeyParam;	// �������
};

typedef std::vector<ITabPageContext*> TabPageContextArray;

class ITabPageContextFactory
{
public:
	ITabPageContextFactory() {}
	virtual ~ITabPageContextFactory() {}
	virtual ITabPageContext* CreateObject() { return NULL; }
};

// ҳ��Ի���
class COMMONCONTROLS_API CTabPagedDialog
{
public:
	CTabPagedDialog();
	~CTabPagedDialog();
	
public:
	// ͨ�������ļ������Ի���
	static CTabPagedDialog* CreateDialogByXmlCfg(HWND hWnd, LPCTSTR szXmlCfg);
	static void RegistPageFactory(LPCTSTR szPageClassName, ITabPageContextFactory *pFactory);
	
	int DoModal();
	HWND ShowWnd();
	void PutParam(LPCTSTR key, IObject *pObject);

protected:
	static ITabPageContext* CreatePageByKey(LPCTSTR szPageClassName);

protected:
	CDialog				*m_pImpl;			// ��ҳ��
	TabPageContextArray m_arrSubPages;		// ��ҳ��
	static std::map<CString, ITabPageContextFactory*> s_mapFactory;
};

typedef std::shared_ptr<CTabPagedDialog> CTabPagedDialogPtr;

#define REGIST_PAGE_CONTEXT(key,className)\
class className##factory : public ITabPageContextFactory\
{\
public:\
	className##factory()\
	{\
		CTabPagedDialog::RegistPageFactory(key, this);\
	}\
	virtual ITabPageContext* CreateObject() { return new className(); }\
} s_##className##factoryInst;
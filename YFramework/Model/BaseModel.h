#pragma once
#include <memory>

namespace YFramework
{
	class IModel
	{
		friend class BaseApp;
	public:
		virtual ~IModel(){}
	protected:
		virtual void Init() = 0;
		virtual BaseApp * GetApp() = 0;
		virtual void SetApp(BaseApp *app) = 0;
	};

	class BaseModel : public IModel
	{
	public:
		virtual ~BaseModel() {}
	protected:
		virtual BaseApp * GetApp()
		{
			return _app;
		}
		virtual void SetApp(BaseApp *app)
		{
			_app = app;
		}
	private:
		BaseApp *_app;
	};
}

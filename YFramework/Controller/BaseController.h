#pragma once

namespace YFramework
{
	class IController : public IGetModel, public IGetSystem, public ISendCommand, public IRegisterEvent
	{
	public:
		virtual ~IController(){}
	private:
		virtual BaseApp * GetApp() = 0;
	};
}

#pragma once

namespace YFramework
{
	class BaseApp 
	{
	public:
		BaseApp()
		{
			_bInit = false;
		}
		virtual ~BaseApp(){}

		// 初始化App（需要在程序入口点调用）
		void Init()
		{
			if(_bInit) return;

			// 子类初始化
			OnInit();

			// 提供外部配置化接口
			OnRegisterConfig.Invoke(this);

			// 初始化所有model
			for (int i = 0; i < _modelList.size(); i++)
			{
				_modelList[i]->Init();
			}

			// 初始化所有system
			for (int i = 0; i < _systemList.size(); i++)
			{
				_systemList[i]->Init();
			}

			_bInit = true;
		}

		template<typename TUtility>
		void RegisterUtility(shared_ptr<TUtility> utility);

		template<typename TModel>
		void RegisterModel(shared_ptr<TModel> model);

		template<typename TSystem>
		void RegisterSystem(shared_ptr<TSystem> system);

		template <typename TUtility>
		shared_ptr<TUtility> GetUtility();

		template <typename TModel>
		shared_ptr<TModel> GetModel();

		template <typename TSystem>
		shared_ptr<TSystem> GetSystem();
	protected:
		// 子类实现
		virtual void OnInit() = 0;
	public:
		Delegate<void(BaseApp *)> OnRegisterConfig;
	private:
		std::vector<std::shared_ptr<IModel>> _modelList;
		std::vector<std::shared_ptr<ISystem>> _systemList;
		IocContainer _ioc;
		bool _bInit;
	};

	template<typename TUtility>
	inline void BaseApp::RegisterUtility(shared_ptr<TUtility> utility)
	{
		static_assert(std::is_base_of<IUtility, TUtility>::value, "类型必须继承自IUtility");
		_ioc.RegisterInstance<TUtility>(utility);
	}

	template<typename TModel>
	inline void BaseApp::RegisterModel(shared_ptr<TModel> model)
	{
		static_assert(std::is_base_of<IModel, TModel>::value, "类型必须继承自IModel");
		_ioc.RegisterInstance<TModel>(model);
		shared_ptr<IModel> mdl = model;
		mdl->SetApp(this);
		if (_bInit)
			mdl->Init();
		else
			_modelList.push_back(mdl);
	}

	template<typename TSystem>
	inline void BaseApp::RegisterSystem(shared_ptr<TSystem> system)
	{
		static_assert(std::is_base_of<ISystem, TSystem>::value, "类型必须继承自ISystem");
		_ioc.RegisterInstance<TSystem>(system);
		shared_ptr<ISystem> sys = system;
		sys->SetApp(this);
		if (_bInit)
			sys->Init();
		else
			_systemList.push_back(sys);
	}

	template <typename TModel>
	shared_ptr<TModel> BaseApp::GetModel()
	{
		static_assert(std::is_base_of<IModel, TModel>::value, "类型必须继承自IModel");
		return _ioc.Get<TModel>();
	}

	template<typename TSystem>
	shared_ptr<TSystem> BaseApp::GetSystem()
	{
		static_assert(std::is_base_of<ISystem, TSystem>::value, "类型必须继承自ISystem");
		return _ioc.Get<TSystem>();
	}

	template <typename TUtility>
	shared_ptr<TUtility> BaseApp::GetUtility()
	{
		static_assert(std::is_base_of<IUtility, TUtility>::value, "类型必须继承自IUtility");
		return _ioc.Get<TUtility>();
	}
}
// ----------------------注意-------------------------
// 继承该类需要添加单例基类为友元类
// 	friend BaseSingleton<类名>;
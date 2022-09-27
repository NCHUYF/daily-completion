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

		// ��ʼ��App����Ҫ�ڳ�����ڵ���ã�
		void Init()
		{
			if(_bInit) return;

			// �����ʼ��
			OnInit();

			// �ṩ�ⲿ���û��ӿ�
			OnRegisterConfig.Invoke(this);

			// ��ʼ������model
			for (int i = 0; i < _modelList.size(); i++)
			{
				_modelList[i]->Init();
			}

			// ��ʼ������system
			for (int i = 0; i < _systemList.size(); i++)
			{
				_systemList[i]->Init();
			}

			_bInit = true;
		}

		template<typename TCommand>
		void SendCommand();
		
		template<typename TCommand>
		void SendCommand(shared_ptr<TCommand> command);

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
		// ����ʵ��
		virtual void OnInit() = 0;
	public:
		Delegate<void(BaseApp *)> OnRegisterConfig;
	private:
		std::vector<std::shared_ptr<IModel>> _modelList;
		std::vector<std::shared_ptr<ISystem>> _systemList;
		IocContainer _ioc;
		bool _bInit;
	};

	template<typename TCommand>
	inline void BaseApp::SendCommand()
	{
		static_assert(std::is_base_of<ICommand, TCommand>::value, "���ͱ���̳���ICommand");
		shared_ptr<ICommand> cmd = std::make_shared<TCommand>();
		cmd->SetApp(this);
		cmd->Init();
		cmd->Execute();
	}

	template<typename TCommand>
	inline void BaseApp::SendCommand(shared_ptr<TCommand> command)
	{
		static_assert(std::is_base_of<ICommand, TCommand>::value, "���ͱ���̳���ICommand");
		shared_ptr<ICommand> cmd = command;
		cmd->SetApp(this);
		cmd->Init();
		cmd->Execute();
	}

	template<typename TUtility>
	inline void BaseApp::RegisterUtility(shared_ptr<TUtility> utility)
	{
		static_assert(std::is_base_of<IUtility, TUtility>::value, "���ͱ���̳���IUtility");
		_ioc.RegisterInstance<TUtility>(utility);
	}

	template<typename TModel>
	inline void BaseApp::RegisterModel(shared_ptr<TModel> model)
	{
		static_assert(std::is_base_of<IModel, TModel>::value, "���ͱ���̳���IModel");
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
		static_assert(std::is_base_of<ISystem, TSystem>::value, "���ͱ���̳���ISystem");
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
		static_assert(std::is_base_of<IModel, TModel>::value, "���ͱ���̳���IModel");
		return _ioc.Get<TModel>();
	}

	template<typename TSystem>
	shared_ptr<TSystem> BaseApp::GetSystem()
	{
		static_assert(std::is_base_of<ISystem, TSystem>::value, "���ͱ���̳���ISystem");
		return _ioc.Get<TSystem>();
	}

	template <typename TUtility>
	shared_ptr<TUtility> BaseApp::GetUtility()
	{
		static_assert(std::is_base_of<IUtility, TUtility>::value, "���ͱ���̳���IUtility");
		return _ioc.Get<TUtility>();
	}
}
// ----------------------ע��-------------------------
// �̳и�����Ҫ��ӵ�������Ϊ��Ԫ��
// 	friend BaseSingleton<����>;
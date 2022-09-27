#pragma once

namespace YFramework
{
	class BaseApp 
	{
	public:
		BaseApp() {
			_bInit = false;
		}
		virtual ~BaseApp(){}
		virtual void Init() = 0;

		template <typename TIOC>
		shared_ptr<TIOC> Get();

		template<typename TModel>
		void RegisterModel(shared_ptr<TModel> model);

		template<typename TUtility>
		void RegisterUtility(shared_ptr<TUtility> utility);

		template <typename TUtility>
		shared_ptr<TUtility> GetUtility();
	public:
		std::vector<std::shared_ptr<IModel>> _modelList;
	private:
		IocContainer _ioc;
		bool _bInit;
	};

	template <typename TIOC>
	shared_ptr<TIOC> BaseApp::Get()
	{
		return _ioc.Get<TIOC>();
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
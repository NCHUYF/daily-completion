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

		// ��ʼ��App
		void Init()
		{
			if(_bInit) return;

			// �����ʼ��
			OnInit();

			// ��ʼ������model
			for (int i = 0; i < _modelList.size(); i++)
			{
				_modelList[i]->Init();
			}

			//// ��ʼ������system
			//for (int i = 0; i < _systemList.Count; i++)
			//{
			//	_systemList[i].Init();
			//}

			_bInit = true;
		}

		template<typename TModel>
		void RegisterModel(shared_ptr<TModel> model);

		template<typename TUtility>
		void RegisterUtility(shared_ptr<TUtility> utility);

		template <typename TModel>
		shared_ptr<TModel> GetModel();

		template <typename TUtility>
		shared_ptr<TUtility> GetUtility();
	protected:
		// ����ʵ��
		virtual void OnInit() = 0;
	public:
		std::vector<std::shared_ptr<IModel>> _modelList;
	private:
		IocContainer _ioc;
		bool _bInit;
	};

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

	template <typename TModel>
	shared_ptr<TModel> BaseApp::GetModel()
	{
		static_assert(std::is_base_of<IModel, TModel>::value, "���ͱ���̳���IModel");
		return _ioc.Get<TModel>();
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
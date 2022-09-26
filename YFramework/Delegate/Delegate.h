#pragma once
#include <mutex>
#include <list>
#include <vector>
#include <memory>

namespace YFramework
{
	template<typename>
	class Delegate;

	template <typename TReturnType, typename... TArgs>
	struct Invoker
	{
		using ReturnType = std::vector<TReturnType>;

	public:
		static ReturnType Invoke(Delegate<TReturnType(TArgs...)> &delegate, TArgs... params)
		{
			std::lock_guard<std::mutex> lock(delegate.mMutex);
			ReturnType returnValues;

			for (const auto &functionPtr : delegate.mFunctionList)
			{
				returnValues.push_back((*functionPtr)(params...));
			}

			return returnValues;
		}
	};

	template <typename... TArgs>
	struct Invoker<void, TArgs...>
	{
		using ReturnType = void;

	public:
		static void Invoke(Delegate<void(TArgs...)> &delegate, TArgs... params)
		{
			std::lock_guard<std::mutex> lock(delegate.mMutex);

			for (const auto &functionPtr : delegate.mFunctionList)
			{
				(*functionPtr)(params...);
			}
		}
	};

	template<typename TReturnType, typename... TArgs>
	class Delegate<TReturnType(TArgs...)>
	{
		using Invoker = Invoker<TReturnType, TArgs...>;
		using functionType = std::function<TReturnType(TArgs...)>;

		friend Invoker;

	public:
		Delegate() {}
		~Delegate() {}

		Delegate(const Delegate&) = delete;
		const Delegate& operator =(const Delegate&) = delete;

		Delegate& Connect(const functionType &function)
		{
			std::lock_guard<std::mutex> lock(this->mMutex);

			this->mFunctionList.push_back(std::make_shared<functionType>(function));

			return *this;
		}

		Delegate& Remove(const functionType &function)
		{
			std::lock_guard<std::mutex> lock(this->mMutex);

			this->mFunctionList.remove_if([&](std::shared_ptr<functionType> &functionPtr)
			{
				return Hash(function) == Hash(*functionPtr);
			});

			return *this;
		}

		inline typename Invoker::ReturnType Invoke(TArgs... args)
		{
			return Invoker::Invoke(*this, args...);
		}

		Delegate& Clear()
		{
			std::lock_guard<std::mutex> lock(this->mMutex);

			this->mFunctionList.clear();

			return *this;
		}

		inline Delegate& operator +=(const functionType &function)
		{
			return Connect(function);
		}

		inline Delegate& operator -=(const functionType &function)
		{
			return Remove(function);
		}

		inline typename Invoker::ReturnType operator ()(TArgs... args)
		{
			return Invoker::Invoke(*this, args...);
		}

	private:
		std::mutex mMutex;
		std::list<std::shared_ptr<functionType>> mFunctionList;

		inline constexpr size_t Hash(const functionType &function) const
		{
			return function.target_type().hash_code();
		}
	};

	class YFRAMEWORK_API SB
	{
	public:
		void Log();
	};
}
//----------------ʹ�÷���---------------------------------------------------------
//void sum2(int a) {
//	CString str;
//	str.Format(L"%d", a);
//	MessageBox(::GetActiveWindow(), L"sum2() : " + str, L"", MB_OK);
//}
//Delegate<void(int)> d2;
//class Test
//{
//public:
//	Test()
//	{
//		d2 += [](int a) {};
//		//d2 += std::bind(&Test::sum, *this, std::placeholders::_1);
//		d2 += sum2;
//		d2.Invoke(5);
//	}
//
//	void sum(int a) {
//		CString str;
//		str.Format(L"%d", a);
//		MessageBox(::GetActiveWindow(), L"sum() : " + str, L"", MB_OK);
//	}
//};

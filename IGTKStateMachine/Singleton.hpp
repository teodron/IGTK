#pragma once
namespace IGTK
{
	template <class TInstance>
	class Singleton
	{
	private:
		Singleton(const Singleton& iOther) = delete;
		Singleton& operator=(const Singleton& iOther) = delete;
		Singleton() = default;
	public:
		static TInstance& GetInstance()
		{
			static TInstance instance;
			return instance;
		}
	};
}
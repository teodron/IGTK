#pragma once
#include <iostream>
namespace IGTK
{
	
	template <typename T>
	void DoCall(typename std::remove_reference<T>::type& arg)
	{
		std::cout << " Call by lvalue reference \n";
	}
	
	template <typename T>
	void DoCall(typename std::remove_reference<T>::type&& arg)
	{
		std::cout << " Call by rvalue reference \n";
	}

	template <typename T>
	void CallWrapper(T&& universalReference)
	{
		DoCall<T>(std::forward<T>(universalReference));
	}
}
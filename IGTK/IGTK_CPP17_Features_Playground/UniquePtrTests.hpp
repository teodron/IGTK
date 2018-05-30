#pragma once
#include <iostream>
#include <memory>
#include "RuleOf5Resource.h"

namespace IGTK
{
	namespace SmartPointerTests
	{

		void TestUniquePtr()
		{
			std::unique_ptr<RuleOf5Resource> p1 = std::make_unique<RuleOf5Resource>();
			if (p1 != nullptr)
			{
				std::cout << "p1 is valid \n";
			}
			// code block
			{
				std::unique_ptr<RuleOf5Resource> p2 = std::move(p1);
			}
			if (p1 == nullptr)
			{
				std::cout << "p1 is no longer valid \n";
			}
		}
	}
}
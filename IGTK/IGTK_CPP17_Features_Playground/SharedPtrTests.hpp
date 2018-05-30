#pragma once
#include <iostream>
#include <memory>
#include "RuleOf5Resource.h"
#include "Macros.h"

namespace IGTK
{
	namespace SmartPointerTests
	{
		void Share(std::shared_ptr<RuleOf5Resource> resource)
		{
			PRINT_FUNC();
		}

		void TestSharedPtr()
		{
			PRINT_FUNC();
			auto resource = std::make_shared<RuleOf5Resource>();
			{
				std::cout << " Sharing a heap resource in a code block will not destory the object upon exiting \n";
				decltype(resource) r1 = resource;
			}
			if (resource != nullptr)
			{
				Share(resource);
				std::cout << "forcing a return should destroy the resource now";
				return;
			}
		}
	}
}
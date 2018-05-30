#pragma once
#include "Macros.h"
#include <iostream>

namespace IGTK
{
	class RuleOf5Resource
	{
	public:
		RuleOf5Resource()
		{
			PRINT_FUNC();
		}

		~RuleOf5Resource()
		{
			PRINT_FUNC();
		}

		RuleOf5Resource(const RuleOf5Resource& other)
		{
			PRINT_FUNC();
		}

		RuleOf5Resource(RuleOf5Resource&& other)
		{
			PRINT_FUNC();
		}

		RuleOf5Resource& operator=(const RuleOf5Resource& other)
		{
			PRINT_FUNC();
		}
		RuleOf5Resource& operator=( RuleOf5Resource&& other)
		{
			PRINT_FUNC();
		}
	};
}


#pragma once
#include <memory>
#include <iostream>
#include "RuleOf5Resource.h"
#include "Macros.h"
namespace IGTK
{
	namespace SmartPointerTests
	{
		void TestWeakPtrFromSmartPtr()
		{
			PRINT_FUNC();
			std::weak_ptr<RuleOf5Resource> weakPtr;

			{
				std::shared_ptr<RuleOf5Resource> temp = std::make_shared<RuleOf5Resource>();
				weakPtr = temp;
				std::cout << " ref count inside block" << weakPtr.use_count() << std::endl;
				
				if (auto sharedPtr = weakPtr.lock())
				{
					std::cout << " ref count inside if" << weakPtr.use_count() << std::endl;
				}
			}
			std::cout << " ref count outside block" << weakPtr.use_count() << std::endl;
		}

		struct A;
		struct B;
		struct A
		{
			std::shared_ptr<B> b;
		};
		struct B
		{
			std::shared_ptr<A> a;
		};
		
		struct BB;
		struct AA
		{
			std::shared_ptr<BB> bb;
		};
		struct BB
		{
			std::weak_ptr<AA> aa;
		};

		void TestCircularReference()
		{
			std::weak_ptr<A> leakyA;
			std::weak_ptr<B> leakyB;
			{
				auto a = std::make_shared<A>();
				auto b = std::make_shared<B>();
				a->b = b;
				b->a = a;
				leakyA = a;
				leakyB = b;
			}
			std::cout << "using shared_ptr in circular references can cause leaks. reference count " << leakyA.use_count() << " " << leakyB.use_count() << std::endl;
			std::weak_ptr<AA> safeAA;
			std::weak_ptr<BB> safeBB;
			{
				auto aa = std::make_shared<AA>();
				auto bb = std::make_shared<BB>();
				aa->bb = bb;
				bb->aa = aa;
				safeAA = aa;
				safeBB = bb;
			}
			std::cout << "using weak_ptr in circular references breaks cyclic counts. reference count " << safeAA.use_count() << " " << safeBB.use_count() << std::endl;

		}
	}
}
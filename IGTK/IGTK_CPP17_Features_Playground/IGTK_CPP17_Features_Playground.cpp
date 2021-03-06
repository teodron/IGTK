// IGTK_CPP17_Features_Playground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MoveSemantics.h"
#include "PerfectForwarding.hpp"
#include "UniquePtrTests.hpp"
#include "SharedPtrTests.hpp"
#include "WeakPtrTests.hpp"

namespace IGTK
{	
	namespace MoveValueTests
	{
		void CallByRValue(IGTK::MoveSemantics&& m)
		{
			PRINT_FUNC();
			MoveSemantics temp = std::forward<IGTK::MoveSemantics>(m);
			int v = temp;
			std::cout << " value = " << v << std::endl;
		}

		void TestMoveSemantics()
		{
			std::cout << " m1 \n";
			IGTK::MoveSemantics m1(1);
			std::cout << " m1 value = " << static_cast<int>(m1) << std::endl;
			std::cout << " m2 \n";
			IGTK::MoveSemantics m2(m1);
			std::cout << " m2 value = " << static_cast<int>(m2) << std::endl;
			CallByRValue(std::move(m2));
			std::cout << " Moved m2 \n";
			std::cout << " now m2's resource is no longer fully valid \n";
			std::cout << " m2 value = " << static_cast<int>(m2) << std::endl;
			std::cout << " Move Construct m3 \n";
			std::cout << " construct m3 from m1 \n";
			IGTK::MoveSemantics m3 = std::move(m1);
			std::cout << " m1 value = " << static_cast<int>(m1) << std::endl;
			std::cout << " m3 value = " << static_cast<int>(m3) << std::endl;
			std::cout << " move assign m3 to m1 \n";
			m1 = std::move(m3);
			std::cout << " m1 value = " << static_cast<int>(m1) << std::endl;
			std::cout << " m3 value = " << static_cast<int>(m3) << std::endl;
		}
	}

	namespace PerfectForwardingTests
	{
		void TestPerfectForwarding()
		{
			IGTK::MoveSemantics m = 10;
			IGTK::CallWrapper(m);
			IGTK::CallWrapper(IGTK::MoveSemantics(15));
		}
	}
}

int main()
{
	//IGTK::MoveValueTests::TestMoveSemantics();
	//IGTK::PerfectForwardingTests::TestPerfectForwarding();
	//IGTK::SmartPointerTests::TestUniquePtr();
	//IGTK::SmartPointerTests::TestSharedPtr();
	IGTK::SmartPointerTests::TestWeakPtrFromSmartPtr();
	IGTK::SmartPointerTests::TestCircularReference();
    return 0;
}


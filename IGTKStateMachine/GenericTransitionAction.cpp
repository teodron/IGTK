#include "stdafx.h"
#include "GenericTransitionAction.h"

// test action delegate
void TestActionDelegate()
{
	struct MockStruct
	{
		bool Do(const EventArgsPtr& iEventArgs)
		{
			return true;
		}
	};
	MockStruct mock;
	ActionDelegate<MockStruct> ad(&mock, &MockStruct::Do);
	ad(nullptr);
}

void TestLambda()
{
	auto lambda = [](const EventArgsPtr& iEventArgs)->bool {return true;};
	
	GenericTransitionAction<decltype(lambda)> gt(lambda);
	gt(nullptr);
}

bool MockFunction(const EventArgsPtr& iEventArgs)
{
	return true;
}

void TestFunction()
{
	ActionFunctor af(&MockFunction);
	GenericTransitionAction<ActionFunctor> gt = af;
	gt(nullptr);
}
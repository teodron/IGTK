#pragma once
#include "ForwardDeclarations.hpp"

class IEventArgs;

class ITransitionAction
{
public:
	ITransitionAction();
	virtual ~ITransitionAction();

	virtual bool operator()(const EventArgsPtr& iEventArgs) = 0;
};


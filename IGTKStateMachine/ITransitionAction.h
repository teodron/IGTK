#pragma once
#include <memory>
class IEventArgs;
using EventArgsPtr = std::shared_ptr<IEventArgs>;

class ITransitionAction
{
public:
	ITransitionAction();
	virtual ~ITransitionAction();

	virtual bool operator()(const EventArgsPtr& iEventArgs) = 0;
};


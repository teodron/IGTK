#pragma once
#include <memory>
class ITransitionAction;
class IEventArgs;
using TransitionActionPtr = std::shared_ptr<ITransitionAction>;
using EventArgsPtr = std::shared_ptr<IEventArgs>;

class Transition
{
public:
	using TransitionPtr = std::shared_ptr<Transition>;

	Transition(size_t iEventId, size_t iFromStateId, size_t iToStateId);
	
	void SetPreTransitionAction(const TransitionActionPtr& iAction) 
	{
		m_preTransitionAction = iAction;
	}

	void SetPostTransitionAction(const TransitionActionPtr& iAction)
	{
		m_preTransitionAction = iAction;
	}

	size_t operator()(const IEventArgs& preTransitionArgs, const IEventArgs& postTransitionArgs);

	~Transition();

private:
	TransitionActionPtr m_preTransitionAction;
	TransitionActionPtr m_postTransitionAction;
};


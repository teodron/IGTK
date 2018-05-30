#pragma once
#include <memory>
#include "ForwardDeclarations.hpp"

class Transition
{
public:

	Transition(size_t iEventId, size_t iFromStateId, size_t iToStateId) :
		m_triggerEventId(iEventId),
		m_fromStateId(iFromStateId),
		m_toStateId(iToStateId)
	{
	}
	
	void SetPreTransitionAction(const TransitionActionPtr& iAction) 
	{
		m_preTransitionAction = iAction;
	}

	void SetPostTransitionAction(const TransitionActionPtr& iAction)
	{
		m_postTransitionAction = iAction;
	}

	size_t operator()(const EventArgsPtr& preTransitionArgs, const EventArgsPtr& postTransitionArgs);

	bool CanTransitionWithEvent(size_t iEventId) const
	{
		return m_triggerEventId == iEventId;
	}

	~Transition();

private:
	size_t				m_triggerEventId;
	size_t				m_fromStateId;
	size_t				m_toStateId;
	TransitionActionPtr m_preTransitionAction	= nullptr;
	TransitionActionPtr m_postTransitionAction  = nullptr;
};


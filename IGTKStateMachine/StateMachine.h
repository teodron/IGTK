#pragma once
#include "State.h"

class StateMachine
{
public:
	StateMachine(const std::initializer_list<const std::string>& iStateNames);
	~StateMachine();

	void CreateTransition(size_t iTriggerEvent, size_t iFromState, size_t iToState, const TransitionActionPtr& iPre, const TransitionActionPtr& iPost);

	bool OnEvent(size_t iEventId, const EventArgsPtr& iPreEventArgs, const EventArgsPtr& iPostEventArgs);


	bool AcceptsEvent(size_t iEventId)
	{
		return (m_registeredEventsFlag & (1 << iEventId)) != 0;
	}

	static void NotifyEvent(size_t iEventId, const EventArgsPtr& iPreEventArgs, const EventArgsPtr& iPostEventArgs);

private:

	void SubscribeToEvent(size_t iEventId)
	{
		m_registeredEventsFlag |= 1 << iEventId;
	}
	void UnsubscribeFromEvent(size_t iEventId)
	{
		m_registeredEventsFlag &= ~(1 << iEventId);
	}

	std::vector<size_t>					m_stateIds;
	size_t								m_activeStateId			= 0;
	size_t								m_registeredEventsFlag	= 0;

	static std::vector<StateMachine*>	ms_runningStateMachines;
};


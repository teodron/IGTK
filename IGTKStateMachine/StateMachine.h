#pragma once
#include "State.h"

class StateMachine
{
public:
	StateMachine(const std::initializer_list<const std::string>& iStateNames);
	~StateMachine();

	void CreateTransition(size_t iTriggerEvent, size_t iFromState, size_t iToState, const TransitionActionPtr& iPre, const TransitionActionPtr& iPost);

	bool OnEvent(size_t iEventId, const EventArgsPtr& iPreEventArgs, const EventArgsPtr& iPostEventArgs);
private:
	std::vector<size_t>	m_stateIds;
	size_t				m_activeStateId;
};


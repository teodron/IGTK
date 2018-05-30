#include "stdafx.h"
#include "State.h"
#include <algorithm>
#include "Transition.h"
#include "Logger.h"

size_t State::ms_count = 0;
std::vector<StatePtr> State::ms_states;

State::State(const std::string& iName):
	m_name(iName),
	m_id(ms_count++)
{
}


StatePtr State::Factory::GetById(size_t iId)
{
	if (iId >= State::ms_count)
	{
		return nullptr;
	}
	return State::ms_states[iId];
}

StatePtr State::Factory::GetByName(const std::string& iName)
{
	auto it = std::find_if(ms_states.cbegin(), ms_states.cend(), [&iName](const StatePtr& state) { return state->m_name == iName;});
	if (it == ms_states.cend())
	{
		return nullptr;
	}
	else
	{
		return *it;
	}
}

size_t State::Factory::RegisterState(const std::string& iName)
{
	auto newState = StatePtr(new State(iName));
	ms_states.push_back(newState);
	return newState->m_id;
}


size_t State::AttemptTransition(size_t iEventId, const EventArgsPtr& iPreEventArgs, const EventArgsPtr& iPostEventArgs)
{
	auto transitionIt = std::find_if(m_outgoingTransition.begin(), m_outgoingTransition.end(), 
		[iEventId](const TransitionPtr& iTransitionPtr)
	{
		return iTransitionPtr->CanTransitionWithEvent(iEventId);
	});

	if (transitionIt == m_outgoingTransition.end())
	{
		IGTKLOG("Cannot execute transition from state " + m_name);
		return m_id;
	}
	return (**transitionIt)(iPreEventArgs, iPostEventArgs);
}


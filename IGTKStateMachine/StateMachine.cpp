#include "stdafx.h"
#include "StateMachine.h"
#include "Transition.h"
#include "Logger.h"
#include "State.h"
#include <algorithm>

std::vector<StateMachine*> StateMachine::ms_runningStateMachines;

StateMachine::StateMachine(const std::initializer_list<const std::string>& iStateNames) :
	m_stateIds(iStateNames.size())
{
	size_t stateIndex = 0;
	for (const auto& stateName : iStateNames)
	{
		m_stateIds[stateIndex++] = State::Factory::RegisterState(stateName);
	}
	m_activeStateId = m_stateIds[0];

	ms_runningStateMachines.push_back(this);
}


StateMachine::~StateMachine()
{
	ms_runningStateMachines.erase(std::remove(ms_runningStateMachines.begin(), ms_runningStateMachines.end(), this), ms_runningStateMachines.end());
}

void StateMachine::CreateTransition(size_t iTriggerEvent, size_t iFromState, size_t iToState, const TransitionActionPtr& iPre, const TransitionActionPtr& iPost)
{
	StatePtr fromState = State::Factory::GetById(iFromState);
	StatePtr toState = State::Factory::GetById(iToState);
	IGTKLOG("Creating transition: " + fromState->GetName() + " -> " + toState->GetName());
	TransitionPtr transition = std::make_shared<Transition>(iTriggerEvent, iFromState, iToState);
	transition->SetPreTransitionAction(iPre);
	transition->SetPostTransitionAction(iPost);
	fromState->AddTransition(transition);
	SubscribeToEvent(iTriggerEvent);
}


bool StateMachine::OnEvent(size_t iEventId, const EventArgsPtr& iPreEventArgs, const EventArgsPtr& iPostEventArgs)
{
	StatePtr currState = State::Factory::GetById(m_activeStateId);
	if (currState == nullptr)
		return false;
	m_activeStateId = currState->AttemptTransition(iEventId, iPreEventArgs, iPostEventArgs);
	return true;
}

void StateMachine::NotifyEvent(size_t iEventId, const EventArgsPtr& iPreEventArgs, const EventArgsPtr& iPostEventArgs)
{
	for (const auto stateMachine : ms_runningStateMachines)
	{
		if (stateMachine->AcceptsEvent(iEventId))
		{
			bool eventHandledSuccessfully = stateMachine->OnEvent(iEventId, iPreEventArgs, iPostEventArgs);
			if (eventHandledSuccessfully)
			{
				IGTKLOG("Transition successful.\n");
			}
			else
			{
				IGTKLOG("Transition failed.\n");
			}
		}
	}
}
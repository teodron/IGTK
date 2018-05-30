#include "stdafx.h"
#include "StateMachine.h"
#include "Transition.h"
#include "Logger.h"
#include "State.h"

StateMachine::StateMachine(const std::initializer_list<const std::string>& iStateNames) :
	m_stateIds(iStateNames.size())
{
	size_t stateIndex = 0;
	for (const auto& stateName : iStateNames)
	{
		m_stateIds[stateIndex++] = State::Factory::RegisterState(stateName);
	}
	m_activeStateId = m_stateIds[0];
}


StateMachine::~StateMachine()
{
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
}


bool StateMachine::OnEvent(size_t iEventId, const EventArgsPtr& iPreEventArgs, const EventArgsPtr& iPostEventArgs)
{
	StatePtr currState = State::Factory::GetById(m_activeStateId);
	if (currState == nullptr)
		return false;
	m_activeStateId = currState->AttemptTransition(iEventId, iPreEventArgs, iPostEventArgs);
	return true;
}
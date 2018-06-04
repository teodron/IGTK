#pragma once
#include <string>
#include <memory>
#include <vector>
#include <string>

#include "ForwardDeclarations.hpp"


class State
{
public:	
	struct Factory
	{
		friend class StateMachine;
		static StatePtr GetById(size_t iId);
		static StatePtr GetByName(const std::string& iName);
		static size_t RegisterState(const std::string& iName);
	};

	const std::string& GetName() const
	{
		return m_name;
	}

	size_t GetId() const
	{
		return m_id;
	}

	void AddTransition(const TransitionPtr& iOutgoingTransition)
	{
		m_outgoingTransitions.push_back(iOutgoingTransition);
	}

	size_t AttemptTransition(size_t iEventId, const EventArgsPtr& iPreEventArgs, const EventArgsPtr& iPostEventArgs);

private:
	
	State() = delete;
	explicit State(const std::string& iName);

private:
	size_t									m_id;
	std::string								m_name;
	std::vector<TransitionPtr>				m_outgoingTransitions;
	static size_t							ms_count;
	static std::vector<StatePtr>			ms_states;
};


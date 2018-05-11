#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Transition.h"


class State
{
public:
	using StatePtr = std::shared_ptr<State>;
	
	static StatePtr GetById(size_t iId);
	static StatePtr GetByName(const std::string& iName);
	static size_t RegisterState(const std::string& iName);

private:
	State() = delete;
	State(const std::string& iName);
	

private:
	size_t									m_id;
	std::string								m_name;
	std::vector<Transition::TransitionPtr>	m_outgoingTransition;
	static size_t							ms_count;
	static std::vector<StatePtr>			ms_states;
};


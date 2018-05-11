#include "stdafx.h"
#include "State.h"

size_t State::ms_count = 0;

State::State(const std::string& iName):
	m_name(iName),
	m_id(m_count++)
{

}


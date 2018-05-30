#include "stdafx.h"
#include "Transition.h"
#include "ITransitionAction.h"

Transition::~Transition()
{
}

size_t Transition::operator()(const EventArgsPtr& preTransitionArgs, const EventArgsPtr& postTransitionArgs)
{
	size_t currentStateId = m_fromStateId;
	if (m_preTransitionAction != nullptr)
	{
		if ((*m_preTransitionAction)(preTransitionArgs))
		{
			currentStateId = m_toStateId;
		}
		else
		{
			return currentStateId;
		}
	}
	if (m_postTransitionAction != nullptr)
	{
		(*m_postTransitionAction)(postTransitionArgs);
	}
	return m_toStateId;
}
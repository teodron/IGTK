#pragma once
#include "IEventArgs.h"
#include <string>
class StringEventArgs :
	public IEventArgs
{
public:
	StringEventArgs(const std::string& iPayload) :
		m_payload(iPayload)
	{
	}

	~StringEventArgs();

	operator std::string()
	{
		return m_payload;
	}

private:
	std::string m_payload;
};


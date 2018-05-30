#include "stdafx.h"
#include "Logger.h"
#include "Singleton.hpp"

using LoggerSingleton = IGTK::Singleton<Logger>;

Logger::Logger()
{
	m_logStream.open("log.txt");
}


Logger::~Logger()
{
	if (m_logStream.is_open())
	{
		m_logStream.close();
	}
}

void Logger::Write(const char* iFunctionName, const std::string& iOutput)
{
	Logger& instance = LoggerSingleton::GetInstance();
	instance.m_logStream << iFunctionName << " : " << iOutput << std::endl;
}
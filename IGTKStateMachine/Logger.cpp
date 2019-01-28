#include "stdafx.h"
#include "Logger.h"
#include "Singleton.hpp"
#include <chrono>
#include <ctime>

using LoggerSingleton = IGTK::Singleton<Logger>;

Logger::Logger()
{
	auto currentTime = std::chrono::system_clock::now();
	std::time_t nowTime = std::chrono::system_clock::to_time_t(currentTime);
	char dateTime[1024];
	sprintf_s( dateTime, 1024, "%llu", nowTime);
	m_logStream.open("Log_" + std::string(dateTime) + ".txt");
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
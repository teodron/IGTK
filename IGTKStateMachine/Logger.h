#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class Logger
{
public:
	Logger();
	~Logger();

	static void Write(const char* iFunctionName, const std::string& iOutput);
private:
	std::ofstream m_logStream;
};

#define IGTKLOG(OUTPUT) Logger::Write(__FUNCSIG__, OUTPUT)

#pragma once

#include <chrono>
#include <string>

class timeProfiler{
	public:
		timeProfiler(const std::string &blockName);
		~timeProfiler();
	
	private:
		std::string codeBlock;
		std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockEndTime;
		std::chrono::microseconds  codeBlockExecutionTime;
	
};

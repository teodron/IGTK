#pragma once

#include <chrono>

class time_profiler{
	public:
		time_profiler(std::string blockName);
		~time_profiler();
	
	private:
		std::string codeBlock;
		std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockEndTime;
		std::chrono::microseconds  codeBlockExecutionTime;
	
};


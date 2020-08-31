#pragma once

#include<iostream>
#include <chrono>


class time_profiler{
	public:
		time_profiler() = default;
		time_profiler(std::string blockName);
		~time_profiler();

		//const std::chrono::time_point<std::chrono::high_resolution_clock> copyofcodeBlockStartTime;
		//const std::chrono::time_point<std::chrono::high_resolution_clock> copyofcodeBlockEndTime;
        //const std::chrono::microseconds copyofcodeBlockExecutionTime;
		int elapsedTime;

	private:
		std::string codeBlock;
		std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockEndTime;
		std::chrono::microseconds  codeBlockExecutionTime;
	
};


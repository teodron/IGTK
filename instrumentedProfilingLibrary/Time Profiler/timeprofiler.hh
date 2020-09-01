#pragma once

#include<iostream>
#include <chrono>


class time_profiler{
	public:
		time_profiler() = default;
		time_profiler(std::string blockName);
		~time_profiler();
	         
		void constructorProcesses();
		void destructorProcesses();

		//time stamp in microseconds.
		uint64_t StartTimeStamp_us;
		uint64_t EndTimeStamp_us;
		uint64_t BlockExecutionTime_us;
	
		int elapsedTime;

	private:
		std::string codeBlock;
		std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockEndTime;
		std::chrono::microseconds  codeBlockExecutionTime;
	
};


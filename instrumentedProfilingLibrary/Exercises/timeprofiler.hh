#ifndef TIMEPROFILER_HH_
#define TIMEPROFILER_HH_

#include<iostream>
#include <chrono>

class time_profiler{
	public:
		time_profiler(std::string blockName);

		~time_profiler();

	private:
		std::string codeBlock;
		std ::chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime;

};

#endif /* TIMEPROFILER_HH_ */

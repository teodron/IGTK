#pragma once

#include <string>
#include <chrono>
#include <fstream>
#include "timeprofiler.hh"


class ProfileDataManager {
public:
	ProfileDataManager();
	~ProfileDataManager();

	time_profiler setTimeprofilerInsatance(std::string name) const;
	void getTimeprofilerdata(time_profiler tp);
	void managerMain(std::string name);

private:
	std::ofstream myfile;
	time_profiler tp;
};


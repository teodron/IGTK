#pragma once

#include <string>
#include <chrono>
#include <fstream>

class profileDataManager {
	
public:
    static profileDataManager* getInstance();
    profileDataManager(profileDataManager& other) = delete;
    void operator=(const profileDataManager&) = delete;
    
    void displayTimerData();
    void storeTimerData();
    void getTimerData(const std::string& name, std::chrono::microseconds timetaken, std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime,
        std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockEndTime);

    std::ofstream myfile;

private:
    std::string codeBlockname;
    uint64_t startTimeStamp;
    uint64_t endTimeStamp;
    uint64_t executionTime;

    static profileDataManager* profiledatamanager;
    profileDataManager();
    //~profileDataManager();
	
};

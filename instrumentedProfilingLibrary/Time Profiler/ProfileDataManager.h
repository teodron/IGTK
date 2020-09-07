#pragma once

#include <string>
#include <chrono>
#include <fstream>

class ProfileDataManager {
	
public:
    static ProfileDataManager* GetInstance(const std::string& name);
    ProfileDataManager(ProfileDataManager& other) = delete;
    void operator=(const ProfileDataManager&) = delete;
    
    void displayTimerData();
    void storeTimerData();
    void getTimerData(const std::string& name, std::chrono::microseconds timetaken, std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime,
        std::chrono::time_point<std::chrono::high_resolution_clock> codeBlockEndTime);

private:
    std::string codeBlockname;
    uint64_t StartTimeStamp_us;
    uint64_t EndTimeStamp_us;
    uint64_t ExecutionTime;

    std::ofstream myfile;

    static ProfileDataManager* profiledatamanager;
    ProfileDataManager(const std::string name);
    ~ProfileDataManager();
	
};


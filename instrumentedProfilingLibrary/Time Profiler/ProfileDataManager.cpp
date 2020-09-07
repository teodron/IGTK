#include "ProfileDataManager.h"
#include <iostream>

using namespace std;

ProfileDataManager* ProfileDataManager::profiledatamanager = nullptr;

ProfileDataManager::ProfileDataManager(const string name){
	
	myfile.open("time.txt");
	
	if (myfile.is_open()) {
	    cout << "myfile is open \n" << endl;
	}

}


ProfileDataManager:: ~ProfileDataManager() {
	
	myfile.close();

}


ProfileDataManager* ProfileDataManager::GetInstance(const string& value) {

	if (profiledatamanager == nullptr) {
		profiledatamanager = new ProfileDataManager(value);
	}
	
	return profiledatamanager;

}


void ProfileDataManager::storeTimerData() {

    cout << "\nWriting data into my file.\n";
    if (myfile.is_open()) {
        myfile << "\nWriting data into my file.\n";
        myfile << "Code block name: "<< codeBlockname << endl;
        myfile << "Start time stamp: " << StartTimeStamp_us << endl;
        myfile << "End time stamp: " << EndTimeStamp_us << endl;
        myfile << "Execution time taken: " << ExecutionTime << endl;
    }
	
}


void ProfileDataManager::getTimerData(const string& name, chrono::microseconds timetaken, chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime,
    chrono::time_point<std::chrono::high_resolution_clock> codeBlockEndTime) {

    codeBlockname = name;
    StartTimeStamp_us = chrono::duration_cast<chrono::microseconds>(codeBlockStartTime.time_since_epoch()).count();
    EndTimeStamp_us = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime.time_since_epoch()).count();
    ExecutionTime = timetaken.count();

}


void ProfileDataManager::displayTimerData() {

    cout << "\nInformation display from ProfileDataManager:" << endl;
    cout << "Code block name:  "<< codeBlockname << endl;
    cout << "Start time stamp: "<< StartTimeStamp_us << endl;
    cout << "End time stamp:   "<< EndTimeStamp_us << endl;
    cout << "Execution time taken: "<< ExecutionTime << endl;

}


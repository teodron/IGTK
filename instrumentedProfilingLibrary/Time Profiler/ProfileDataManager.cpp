#include "ProfileDataManager.h"
#include <iostream>

using namespace std;

profileDataManager *profileDataManager::profiledatamanager = nullptr;

profileDataManager::profileDataManager(){
	
}

/*
profileDataManager:: ~profileDataManager() {
	
}
*/

profileDataManager* profileDataManager::getInstance() {

	if (profiledatamanager == nullptr) {
		profiledatamanager = new profileDataManager();
	}
	
	return profiledatamanager;
}


void profileDataManager::storeTimerData() {

    if (myfile.is_open()) {

        myfile << "Code block name: "<< codeBlockname << endl;
        myfile << "Start time stamp : " << startTimeStamp << endl;
        myfile << "End time stamp: " << endTimeStamp << endl;
        myfile << "Execution time taken [us]: " << executionTime << endl;
        myfile << endl;
    }
}


void profileDataManager::getTimerData(const string& name, chrono::microseconds timetaken, chrono::time_point<std::chrono::high_resolution_clock> codeBlockStartTime,
    chrono::time_point<std::chrono::high_resolution_clock> codeBlockEndTime) {

    codeBlockname = name;
    startTimeStamp = chrono::duration_cast<chrono::microseconds>(codeBlockStartTime.time_since_epoch()).count();
    endTimeStamp = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime.time_since_epoch()).count();
    executionTime = timetaken.count();
}


void profileDataManager::displayTimerData() {

    cout << "\nInformation display from Profile Data Manager:" << endl;
    cout << "Code block name:  "<< codeBlockname << endl;
    cout << "Start time stamp: "<< startTimeStamp << endl;
    cout << "End time stamp:   "<< endTimeStamp << endl;
    cout << "Execution time taken [us]: "<< executionTime << endl;

}


#include "ProfileDataManager.h"
#include <iostream>

using namespace std;

ProfileDataManager::ProfileDataManager(){
	cout << "profile manager constructor called" << endl;
	myfile.open("time.txt");
	if (myfile.is_open()) {
		cout << "myfile is open" << endl;
	}

}


ProfileDataManager:: ~ProfileDataManager() {
	cout << "profile manager destructor called"<<endl;
	myfile.close();

}


time_profiler ProfileDataManager::setTimeprofilerInsatance(string name) const{

	time_profiler tp(name);

	return tp;
}


void ProfileDataManager::getTimeprofilerdata(time_profiler a) {

	if (myfile.is_open()){
		myfile << "This is a line test.\n";
		//test for writing info from time profiler constuctor to file
		myfile << 10000 <<endl;
		myfile << a.elapsedTime <<endl; 
		myfile << a.StartTimeStamp_us << endl;

		//test for writing info from time profiler destructor to file
		myfile << a.EndTimeStamp_us<< endl;
		myfile << a.BlockExecutionTime_us << endl;
	}

}


void ProfileDataManager::managerMain(std::string name) {
	auto timeProfilerInstance = setTimeprofilerInsatance(name);
	getTimeprofilerdata(timeProfilerInstance);
}

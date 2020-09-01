#include"timeprofiler.hh"
#include "ProfileDataManager.h"


using namespace std;

time_profiler::time_profiler(string blockName):codeBlock(move(blockName)), codeBlockStartTime(chrono::high_resolution_clock::now()){
	cout << "time profiler constructor called" << endl;
	elapsedTime = 90000;
	
	constructorProcesses();
}

time_profiler::~time_profiler(){
	codeBlockEndTime = chrono::high_resolution_clock::now();
	codeBlockExecutionTime = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime - codeBlockStartTime);
	cout << codeBlock << " execution time elapsed: " << codeBlockExecutionTime.count() << " microseconds" << endl;
	cout << "time profiler destructor called\n" << endl;
	
	destructorProcesses();
}

void time_profiler::constructorProcesses() {
	StartTimeStamp_us = chrono::duration_cast<chrono::microseconds>(codeBlockStartTime.time_since_epoch()).count();
	auto StartTimeStamp_ns = chrono::duration_cast<chrono::nanoseconds>(codeBlockStartTime.time_since_epoch()).count();
	cout << StartTimeStamp_us << endl;
	cout << StartTimeStamp_ns << endl;

}

void time_profiler::destructorProcesses() {
	EndTimeStamp_us = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime.time_since_epoch()).count();
	auto EndTimeStamp_ns = chrono::duration_cast<chrono::nanoseconds>(codeBlockEndTime.time_since_epoch()).count();

	BlockExecutionTime_us = codeBlockExecutionTime.count();
	auto BlockExecutionTime_ns = chrono::duration_cast<chrono::nanoseconds>(codeBlockExecutionTime).count();

	//cout << codeBlock << " execution time elapsed from epochs: " << EndTimeStamp_us - StartTimeStamp_us << " microseconds" << endl
}

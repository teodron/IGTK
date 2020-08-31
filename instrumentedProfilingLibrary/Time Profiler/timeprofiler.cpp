#include"timeprofiler.hh"
#include "ProfileDataManager.h"


using namespace std;

time_profiler::time_profiler(string blockName):codeBlock(move(blockName)), codeBlockStartTime(chrono::high_resolution_clock::now()){
	cout << "time profiler constructor called" << endl;
	elapsedTime = 90000;
	//copyofcodeBlockStartTime = codeBlockStartTime;

}

time_profiler::~time_profiler(){
	codeBlockEndTime = chrono::high_resolution_clock::now();
	codeBlockExecutionTime = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime - codeBlockStartTime);
	cout << codeBlock << " execution time elapsed: " << codeBlockExecutionTime.count() << " microseconds" << endl;
	cout << "time profiler destructor called\n" << endl;
	//copyofcodeBlockEndTime = codeBlockEndTime;
	//copyofcodeBlockExecutionTime = codeBlockExecutionTime;
}


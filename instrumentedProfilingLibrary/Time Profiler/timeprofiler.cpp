#include "timeprofiler.hh"
#include "ProfileDataManager.h"


using namespace std;

time_profiler::time_profiler(string blockName):codeBlock(move(blockName)), codeBlockStartTime(chrono::high_resolution_clock::now()){

}

time_profiler::~time_profiler(){
	codeBlockEndTime = chrono::high_resolution_clock::now();
	codeBlockExecutionTime = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime - codeBlockStartTime);
	
	ProfileDataManager* tp = ProfileDataManager::GetInstance(codeBlock);
	tp->getTimerData(codeBlock, codeBlockExecutionTime, codeBlockStartTime, codeBlockEndTime);
	
}


#include "timeprofiler.hh"
#include "ProfileDataManager.h"


using namespace std;

timeProfiler::timeProfiler(string blockName):codeBlock(move(blockName)), codeBlockStartTime(chrono::high_resolution_clock::now()){

}

timeProfiler::~timeProfiler(){
	codeBlockEndTime = chrono::high_resolution_clock::now();
	codeBlockExecutionTime = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime - codeBlockStartTime);
	
	profileDataManager* tp = profileDataManager::getInstance();
	tp->getTimerData(codeBlock, codeBlockExecutionTime, codeBlockStartTime, codeBlockEndTime);
	
}


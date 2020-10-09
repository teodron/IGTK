#include"timeprofiler.hh"

using namespace std;

time_profiler::time_profiler(string blockName): codeBlock(move(blockName)),codeBlockStartTime(chrono::high_resolution_clock::now()){

}

time_profiler::~time_profiler(){
	auto codeBlockEndTime = chrono::high_resolution_clock::now();
	auto codeBlockExecutionTime = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime - codeBlockStartTime);
	cout<<codeBlock<<" execution time elapsed: "<< codeBlockExecutionTime.count() << " microseconds\n"<<endl;
}



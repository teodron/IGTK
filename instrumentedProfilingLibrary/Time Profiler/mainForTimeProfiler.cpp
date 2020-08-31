#include <iostream>
#include "timeprofiler.hh"
#include "operationFunctions.hh"
#include "ProfileDataManager.h"

using namespace std;

int main() {

	//operations op;
	ProfileDataManager dm;

	{
		//time_profiler time_profiler("sum code block");
		//op.sumOfNumbers(1000);
		dm.managerMain("sum code block");

	}


	return 0;

}

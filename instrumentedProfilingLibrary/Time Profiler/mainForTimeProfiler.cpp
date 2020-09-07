#include <iostream>
#include "timeprofiler.hh"
#include "operationFunctions.hh"
#include "ProfileDataManager.h"

using namespace std;

int main() {

	operations op;
	ProfileDataManager* tp = ProfileDataManager::GetInstance("code block");

	{
		time_profiler time_profiler("sum code block");
		op.sumOfNumbers(1000);
		
	}
         
	tp->displayTimerData();
	tp->storeTimerData();
	
	{
		time_profiler time_profiler("square root code block");
		op.sqrtOfNumbersSum(10000);

	}

	tp->displayTimerData();
	tp->storeTimerData();

	return 0;

}

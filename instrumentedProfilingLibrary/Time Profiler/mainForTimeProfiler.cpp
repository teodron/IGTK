#include <iostream>
#include "timeprofiler.hh"
#include "operationFunctions.hh"
#include "ProfileDataManager.h"

using namespace std;

int main() {

	operations op;
  
	profileDataManager* tp = profileDataManager::getInstance();
	tp->myfile.open("codeBlockTimeProfileData.txt");

	{
		timeProfiler timeProfiler("sum code block");
		op.sumOfNumbers(1000);
		
	}
         
	tp->displayTimerData();
	tp->storeTimerData();
	
	{
		timeProfiler timeProfiler("square root code block");
		op.sqrtOfNumbersSum(10000);

	}

	tp->displayTimerData();
	tp->storeTimerData();

	tp->myfile.close();
  
	return 0;

}

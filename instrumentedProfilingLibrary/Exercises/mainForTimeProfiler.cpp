#include <iostream>
#include "timeprofiler.hh"
#include "operationFunctions.hh"

using namespace std;

int main(){

	int num = 0;

	operations op;

	while(true){
		cout<<"Enter Maximum Value: "<<endl;
		cin>>num;

		{
			time_profiler profiler("sum code block");
			op.sumOfNumbers(num);
		}
		{
			time_profiler profiler("sum of square roots code block");
			op.sqrtOfNumbersSum(num);

		}
	}

	return 0;

}

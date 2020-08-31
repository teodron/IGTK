#include"operationFunctions.hh"

using namespace std;

void operations::sumOfNumbers(int num){
	long double sum = 0;

	for(int i= 0; i<=num; i++){
	  sum += i;
	}

   cout<<"Sum of "<<num<< " consecutive numbers is: "<<sum<<endl;
}


void operations::sqrtOfNumbersSum(int num) {
  long double sqrtSum = 0;

  for(int i = 0; i<= num ; i++) {
    sqrtSum += sqrt(i);
  }

  cout<<"\nSum of square root of "<<num<< " consecutive integers is: "<<sqrtSum<<endl;
}

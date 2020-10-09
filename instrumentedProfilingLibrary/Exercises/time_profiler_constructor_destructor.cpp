#include<iostream>
#include<chrono>
#include<cmath>


using namespace std;

class time_profiler{
	public:
		time_profiler(string blockName): codeBlock(move(blockName)),codeBlockStartTime(chrono::high_resolution_clock::now()){

		}

		~time_profiler(){
			auto codeBlockEndTime = chrono::high_resolution_clock::now();
			auto codeBlockExecutionTime = chrono::duration_cast<chrono::microseconds>(codeBlockEndTime - codeBlockStartTime);
			cout<<codeBlock<<" execution time elapsed: "<< codeBlockExecutionTime.count() << " microseconds\n"<<endl;
		}

	private:
		string codeBlock;
		chrono::time_point<chrono::high_resolution_clock> codeBlockStartTime;

};

void sumOfNumbers(int num){
	long double sum = 0;

	for(int i= 0; i<=num; i++){
	  sum += i;
	}

   cout<<"Sum of "<<num<< " consecutive numbers is: "<<sum<<endl;
}

void sqrtOfNumbersSum(int num) {
  long double sqrtSum = 0;

  for(int i = 0; i<= num ; i++) {
    sqrtSum += sqrt(i);
  }

  cout<<"Sum of square root of "<<num<< " consecutive integers is: "<<sqrtSum<<endl;
}


int main(){

	int num = 0;

	while(true){
		cout<<"Enter Maximum Value: "<<endl;
		cin>>num;

		{
			time_profiler profiler("sum code block");
			sumOfNumbers(num);
		}
		{
			time_profiler profiler("sum of square roots code block");
			sqrtOfNumbersSum(num);

		}
	}

	return 0;
}


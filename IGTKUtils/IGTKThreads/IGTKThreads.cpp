// IGTKThreads.cpp : Defines the entry point for the application.
//

#include "IGTKThreads.h"
#include "Task.h"
using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
    igtk::TaskManager taskManager;
    int w = 0;
    taskManager.execute([&w]() {w++;});
    taskManager.execute([&w]() {w++;});
    taskManager.execute([&w]() {w++;});
    std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}

// IGTKThreads.cpp : Defines the entry point for the application.
//

#include "IGTKThreads.h"
#include "Task.h"
#include <array>

using namespace std;

std::array<int, 3> v;
int main()
{
	cout << "Hello CMake." << endl;
    v = { 0,0,0 };
    igtk::TaskManager taskManager;
    taskManager.setOnNotifyCallback([]() {
        std::cout << v[0] << " " << v[1] << " " << v[2] << "\n";
    });

    for (size_t i = 0; i < 20; ++i)
    {
        taskManager.execute([]() {v[0]++; std::this_thread::sleep_for(std::chrono::milliseconds(150));});
        taskManager.execute([]() {v[1]++; std::this_thread::sleep_for(std::chrono::milliseconds(150));});
        taskManager.execute([]() {v[2]++; std::this_thread::sleep_for(std::chrono::milliseconds(150));});
        std::this_thread::sleep_for(std::chrono::microseconds(150));
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    taskManager.setRunning(false);
	return 0;
}

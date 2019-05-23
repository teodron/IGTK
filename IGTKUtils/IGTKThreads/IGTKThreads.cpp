// IGTKThreads.cpp : Defines the entry point for the application.
//

#include "IGTKThreads.h"
#include "Task.h"
#include "EcoSystem.h"
#include <array>

using namespace std;

using CallbackT = std::function<void()>;
using UniqueLock = std::unique_lock<std::mutex>;
using LockGuard = std::lock_guard<std::mutex>;

class WorkerPool;
class Worker
{
public:
    Worker(WorkerPool& workerPool);

    void start();

    void stop();

    void notify();
    bool isBusy();
    
    void setWorkload(const CallbackT& callback);
private:
    void operator()();

    WorkerPool& workerPool_;
    bool busy_{ false };
    bool running_{ false };
    std::mutex mutex_;
    std::condition_variable conditionVariable_;
    std::unique_ptr<std::thread> thread_;
    CallbackT callback_;
};

class WorkerPool
{
public:
    void execute(const CallbackT& workload);

    void setOnNotifyCallback(const CallbackT& onNotifyCallback);
    void start();
    void stop();
    void notify();
protected:
    void loop();
private:
    std::vector<std::unique_ptr<Worker>> workers_;
    bool running_{ false };
    std::mutex loopMutex_;
    std::unique_ptr<std::thread> loopThread_;
    std::condition_variable loopCV_;
    std::atomic<int> notifiedCounter_{ 0 };
    CallbackT onNotifyCallback_;
};

    Worker::Worker(WorkerPool& workerPool) : workerPool_{ workerPool }
    {
    }

    void Worker::start()
    {
        running_ = true;
        thread_.reset(new std::thread{ [this]() {(*this)();} });
    }

    void Worker::stop()
    {
        running_ = false;
        thread_->join();
    }

    void Worker::notify()
    {
        LockGuard lockGuard{ mutex_ };
        conditionVariable_.notify_one();
    }

    bool Worker::isBusy()
    {
        LockGuard lockGuard{ mutex_ };
        return busy_;
    }

    void Worker::setWorkload(const CallbackT& callback)
    {
        LockGuard lockGuard{ mutex_ };
        callback_ = callback;
    }

    void Worker::operator()()
    {
        while (running_)
        {
            UniqueLock uniqueLock{ mutex_ };
            conditionVariable_.wait(uniqueLock);
            busy_ = true;
            callback_();
            busy_ = false;
            workerPool_.notify();
        }
    }


    void WorkerPool::execute(const CallbackT& workload)
    {
        Worker* worker = nullptr;
        for (auto& w : workers_)
        {
            if (w->isBusy() == false)
            {
                worker = w.get();
                break;
            }
        }
        if (worker == nullptr)
        {
            workers_.emplace_back(new Worker{ *this });
            worker = workers_.back().get();
        }
        worker->setWorkload(workload);
        worker->notify();
    }

    void WorkerPool::setOnNotifyCallback(const CallbackT& onNotifyCallback)
    {
        // not mutex protected
        onNotifyCallback_ = onNotifyCallback;
    }
    void WorkerPool::start()
    {
        LockGuard lockGuard{ loopMutex_ };
        running_ = true;
        notifiedCounter_++;
        loopThread_.reset(new std::thread{ [this]() {this->loop();} });
        loopCV_.notify_all();
    }
    void WorkerPool::stop()
    {
        {
            LockGuard lockGuard{ loopMutex_ };
            running_ = false;
            notifiedCounter_++;
            loopCV_.notify_all();
        }
        loopThread_->join();
        loopThread_.reset(nullptr);
    }
    
    void WorkerPool::notify()
    {
        LockGuard{ loopMutex_ };
        notifiedCounter_++;
        loopCV_.notify_all();
    }

    void WorkerPool::loop()
    {
        while (running_)
        {
            UniqueLock uniqueLock{ loopMutex_ };
            loopCV_.wait(uniqueLock, [this]() {return notifiedCounter_ > 0;});
            notifiedCounter_--;
            onNotifyCallback_();
        }
    }



std::array<int, 3> v;
int main()
{
    WorkerPool pool;
    pool.setOnNotifyCallback([]() {std::cout << " WP! \n";});
    
    for (size_t i = 0; i < 20; ++i)
    {
       pool.execute([]() {std::cout <<" 0 "<< v[0]++; std::this_thread::sleep_for(std::chrono::milliseconds(150));});
       pool.execute([]() {std::cout << " 1 " << v[1]++; std::this_thread::sleep_for(std::chrono::milliseconds(150));});
       pool.execute([]() {std::cout << " 2 " << v[2]++; std::this_thread::sleep_for(std::chrono::milliseconds(150));});
        std::this_thread::sleep_for(std::chrono::microseconds(150));
    }

    return 0;
	cout << "Hello CMake." << endl;
    igtk::EcoSystem ecoSystem;
    ecoSystem.initialize();
    ecoSystem.start();
    while (ecoSystem.finished() == false)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::this_thread::yield();
    }
    return 0;
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

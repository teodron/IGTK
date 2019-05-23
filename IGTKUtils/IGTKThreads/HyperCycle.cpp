#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace igtk
{
    using CallbackT = std::function<void(void)>;

    class Worker
    {
    protected:
        void work();
    private:
        CallbackT callback_;
        std::mutex mutex_;
        std::condition_variable cv_;
    };

    class WorkerPool
    {
        friend class Worker;
    protected:
        void notify();

        void execute(const CallbackT& callback);
    private:
        std::vector<Worker> workers_;
    };

#pragma region WorkerPool
#pragma endregion

#pragma region Worker
    void Worker::work()
    {
        while (running_)
        {
            UniqueLock uniqueLock{ mutex_ };
            cv.wait(uniqueLock);
            busy_ = true;
            callback_();
            busy_ = false;
            workerPool_.notify();
        }
    }
#pragma endregion

    class Node
    {
    private:
        size_t averageDuration_;
        std::string name_;
    };

   
    class HyperCycleController
    {
    };


}
#pragma once
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>

namespace igtk
{
    class TaskManager;

    class Task
    {
        friend class TaskManager;
      
        friend class std::default_delete<Task>;
        
    public:
        Task() = delete;
        Task(const Task&) = delete;

    protected:
        Task(size_t id, TaskManager& taskManager);
        ~Task();

        void work();
        void setWork(const std::function<void()>& callback);
        void trigger();
        bool isInUse() 
        {
            std::lock_guard<std::mutex> lockGuard{ mutex_ };
            return inUse_;
        }

    private:
        bool triggered_{ false };
        bool running_{ true };
        bool inUse_{ false };
        size_t id_;
        TaskManager& taskManager_;
        std::mutex mutex_;
        std::condition_variable taskConditionVariable_;
        std::unique_ptr<std::thread> worker_;
        std::function<void()> callback_;
        int lastLockedCode_{ -1 };
    };

    class TaskManager
    {
    public:
        class TaskAttorney
        {
        private:
            friend class Task;
            TaskAttorney() = delete;
            ~TaskAttorney() = delete;

            static void notify(TaskManager& taskManager)
            {
                std::lock_guard<std::mutex> lockGuard{ taskManager.taskManagerMutex_ };
                taskManager.notifiedCount_++;
                taskManager.getConditionVariable().notify_all();
            }
        };

        size_t execute(const std::function<void()>& workload);

        void setOnNotifyCallback(const std::function<void()>& callback);
        void setRunning(bool running);

    protected:

        std::condition_variable& getConditionVariable()
        {
            return taskManagerConditionVariable_;
        }

        void loop();

    private:
        bool running_{ false };
        int notifiedCount_{ 0 };
        std::condition_variable taskManagerConditionVariable_;
        std::vector<std::unique_ptr<Task>> tasks_;
        std::unique_ptr<std::function<void()>> onNotifyCallback_;
        std::unique_ptr<std::thread> taskManagerWorkerThread_;
        std::mutex taskManagerMutex_;
        std::mutex executeCriticalSection_;
        std::atomic<int> lockCount_{ 0 };
    };


}
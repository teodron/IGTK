#pragma once
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
                taskManager.notified_ = true;
                taskManager.getConditionVariable().notify_one();
            }
        };

        size_t execute(const std::function<void()>& workload);
        
    protected:

        std::condition_variable& getConditionVariable()
        {
            return taskManagerConditionVariable_;
        }


    private:
        bool notified_{ false };
        std::condition_variable taskManagerConditionVariable_;
        std::vector<std::unique_ptr<Task>> tasks_;
    };


}
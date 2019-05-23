// HyperCycle.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace hyper
{
    using WorkloadT = std::function<void(void)>;
    using LockGuarT = std::lock_guard<std::mutex>;
    using UniqueLockT = std::unique_lock<std::mutex>;

    class Worker
    {
    public:
        Worker();
        ~Worker();
        void run(const WorkloadT& workload);
        void start();
        void stop();
        bool isBusy();
    protected:
        void loop();
    private:
        std::mutex mutex_;
        std::condition_variable cv_;
        std::unique_ptr<std::thread> thread_;
        WorkloadT workload_;
        bool running_{ false };
        bool workPending_{ false };
    };

    class WorkerManager
    {
    public:
        void execute(const WorkloadT& workload);
        void syncCall(const WorkloadT& callback);
        ~WorkerManager();
    protected:

    private:
        std::vector<std::unique_ptr<Worker>> workers_;
        std::mutex m_;
    };

    class Controller;

    class Node
    {
        friend class Controller;
    public:
        Node(const std::string& name, size_t period);

        void work();
        void registerOutput(Node* output);
        size_t getTick() 
        {
            LockGuarT g(m_); return tick_;
        }
        bool getIsBusy()
        {
            LockGuarT g(m_); return working_;
        }
        void setIsBusy(bool value)
        {
            working_ = value;
        }
    private:
        std::vector<Node*> outputs_;
        std::vector<Node*> inputs_;
        size_t period_{ 0 };
        size_t tick_{ 0 };
        std::string name_;
        std::mutex m_;
        bool working_{ false };
    };

    class Controller
    {
    public:
        void registerNode(Node* node);
        void cycle();
        void wakeUp();
    private:
        std::vector<Node*> nodes_;
        bool running_;
        WorkerManager wm_;
        size_t hyperCycle{ 0 };
        std::condition_variable cv_;
        std::mutex m_;
        bool awake_{ false };
    };

    
}
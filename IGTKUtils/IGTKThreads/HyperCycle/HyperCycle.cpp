// HyperCycle.cpp : Defines the entry point for the application.
//

#include "HyperCycle.h"
#include <string>
namespace hyper
{
    Worker::Worker()
    {
        start();
    }

    Worker::~Worker()
    {
        thread_->join();
    }

    void Worker::start()
    {
        running_ = true;
        thread_.reset(new std::thread([this] {loop();}));
    }

    void Worker::stop()
    {
        LockGuarT lockGuard(mutex_);
        running_ = false;
        workload_ = [] {};
        workPending_ = true;
        cv_.notify_one();
    }
    void Worker::loop()
    {
        while (running_)
        {
            UniqueLockT uniqueLock(mutex_);
            cv_.wait(uniqueLock, [this]() {return workPending_;});
            workload_();
            workPending_ = false;
        }
    }

    void Worker::run(const WorkloadT& workload)
    {
        LockGuarT lockGuard(mutex_);
        workload_ = workload;
        workPending_ = true;
        cv_.notify_one();
    }

    bool Worker::isBusy()
    {
        return workPending_ == true;
    }

    void WorkerManager::execute(const WorkloadT& workload)
    {
        size_t tid = 0;
        bool workerAvailable = false;
        for (size_t widx = 0; widx < workers_.size(); ++widx)
        {
            if (workers_[widx]->isBusy() == false)
            {
                tid = widx;
                workerAvailable = true;
            }
        }

        if (workerAvailable)
        {
            workers_[tid]->run(workload);
        }
        else
        {
            workers_.emplace_back(new Worker());
            workers_.back()->run(workload);
        }
    }

    WorkerManager::~WorkerManager()
    {
        for (auto& w : workers_)
        {
            w->stop();
        }
    }

    void WorkerManager::syncCall(const WorkloadT& callback)
    {
        LockGuarT lockGuard{ m_ };
        callback();
    }

    Node::Node(const std::string& name, size_t period) :
        name_{ name }, period_{ period }
    {
    }

    void Node::registerOutput(Node* node)
    {
        outputs_.push_back(node);
        node->inputs_.push_back(this);
    }

    void Node::work()
    {
        size_t currentTick = 0;
        {
            LockGuarT g(m_);
            currentTick = tick_;
        }
        if (currentTick % period_ == 0)
        {
            std::cout << name_.c_str() << " " << currentTick << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(period_ * 10));
        }
        {
            LockGuarT g(m_);
            tick_++;
            working_ = false;
        }
        
    }

    void Controller::registerNode(Node* node)
    {
        nodes_.push_back(node);
    }

    void Controller::wakeUp()
    {
        LockGuarT g(m_);
        awake_ = true;
        cv_.notify_one();
    }

    void Controller::cycle()
    {
        while (running_)
        {
            for (auto node : nodes_)
            {
                if (node->getIsBusy() || node->getTick() != hyperCycle)
                {
                    continue;
                }

                bool triggerNode = true;
                for (auto input : node->inputs_)
                {
                    if (input->getTick() != hyperCycle + 1 || input->getIsBusy())
                    {
                        triggerNode = false;
                        break;
                    }
                }
                if (triggerNode)
                {
                    node->setIsBusy(true);
                    this->wm_.execute([node, this]() {node->work(); this->wakeUp();});
                }
            }

            UniqueLockT ul(m_);
            cv_.wait(ul, [this]() {return this->awake_;});
            awake_ = false;
            bool allDone = true;
            for (auto node : nodes_)
            {
                if (node->getTick() != hyperCycle + 1)
                {
                    allDone = false;
                    break;
                }
            }
            if (allDone)
            {
                hyperCycle++;
            }
            if (hyperCycle == 10)
            {
                running_ = false;
            }
        }
    }
}

using namespace std;

int main()
{
#if 0
    int i = 0;
    auto inc = [&i]() {++i; cout << i << endl;};
    hyper::WorkerManager wm;
    auto lambda = [&] {cout << "Hello CMake." << endl; wm.syncCall(inc); };
    wm.execute(lambda);
    wm.execute(lambda);
#endif

    hyper::Node ego("ego", 1);
    hyper::Node loc("loc", 5);
    hyper::Node inpred("inpred", 5);
    hyper::Node perc("perc", 5);
    ego.registerOutput(&perc);
    ego.registerOutput(&inpred);
    loc.registerOutput(&inpred);
    loc.registerOutput(&perc);
    perc.registerOutput(&inpred);
    hyper::Controller c;
    c.registerNode(&ego);c.registerNode(&loc);c.registerNode(&perc);c.registerNode(&inpred);
    c.cycle();
	return 0;
}

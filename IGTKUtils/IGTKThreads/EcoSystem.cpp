#include "EcoSystem.h"
#include "Task.h"
#include <iostream>

namespace igtk {

    std::mutex printMutex;
    void threadSafePrint(const char* text)
    {
        std::lock_guard<decltype(printMutex)> lock{ printMutex };
        std::cout << text << " ";
    }

    void Node::step()
    {
        if ((cycle_ + 1) % period_ == 0)
        {
            threadSafePrint(name_.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * period_));
        }
        cycle_++;
    }

    EcoSystem::EcoSystem()
    {
//        taskManager_.setOnNotifyCallback([this]() {this->step();});
    }

    void EcoSystem::start()
    {
        if (started_) return;
        started_ = true;
        taskManager_.setOnNotifyCallback([this]() {this->step();});
        taskManager_.setRunning(true);
    }

    void EcoSystem::stop()
    {
        if (!started_) return;
        started_ = false;
        taskManager_.setRunning(false);
    }

    void EcoSystem::initialize()
    {
        enum
        {
            ODO, GPS, CAM, LAS, PERC, LOC, PRED, PLAN, CTRL, COUNT
        };
        std::vector<std::string> componentNames(COUNT);
        componentNames[ODO] = "ODO";
        componentNames[GPS] = "GPS";
        componentNames[CAM] = "CAM";
        componentNames[LAS] = "LAS";
        componentNames[PERC] = "PERC";
        componentNames[LOC] = "LOC";
        componentNames[PRED] = "PRED";
        componentNames[PLAN] = "PLAN";
        componentNames[CTRL] = "CTRL";
        nodes_.resize(COUNT);
        for (size_t i = 0; i < COUNT; ++i)
        {
            nodes_[i].name_ = componentNames[i];
            nodes_[i].id_ = i;
            nodes_[i].cycle_ = 0;
        }

        nodes_[ODO].period_ = 1;
        nodes_[GPS].period_ = 6;
        nodes_[CAM].period_ = 2;
        nodes_[LAS].period_ = 3;
        nodes_[PERC].period_ = 4;
        nodes_[LOC].period_ = 6;
        nodes_[PRED].period_ = 4;
        nodes_[PLAN].period_ = 10;
        nodes_[CTRL].period_ = 2;

        nodes_[PERC].inputNodes_ = { ODO, LAS, CAM };
        nodes_[PRED].inputNodes_ = { ODO, LOC, PERC };
        nodes_[LOC].inputNodes_ = { ODO, GPS, PERC };
        nodes_[PLAN].inputNodes_ = { ODO, LOC, PRED };
        nodes_[CTRL].inputNodes_ = { PLAN }; //end of hypercycle will be here

        constexpr size_t MAX_HYPERCYCLES = 30;
        maxHypercycles_ = MAX_HYPERCYCLES;
    }

    void EcoSystem::step()
    {
        // increment hypercycle count if all  nodes have finished their execution
        bool incrementHypercycle = true;
        for (const auto& node : nodes_)
        {
            if (node.cycle_ != hypercycle_)
            {
                incrementHypercycle = false;
                break;
            }
        }
        if (incrementHypercycle == true)
        {
            if (hypercycle_ == maxHypercycles_)
            {
                stop();
                return;
            }
            threadSafePrint("\n HC: ");
            hypercycle_++;
        }
        // step nodes that are free to cycle
        for (auto& node : nodes_)
        {
            bool canStepNode = true;
            for (size_t inputNodeId : node.inputNodes_)
            {
                if (nodes_[inputNodeId].cycle_ != hypercycle_)
                {
                    canStepNode = false;
                }
            }
            if (canStepNode)
            {
                taskManager_.execute([&node]() {node.step();});
            }
        }
    }
}
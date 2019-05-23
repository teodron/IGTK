#pragma once
#include "Task.h"
#include <string>
#include <vector>

namespace igtk
{
    class EcoSystem;

    class Node
    {
    public:
        void step();

    protected:

    public: //should be private
        std::string name_;
        size_t cycle_{ 0 };
        size_t period_;
        size_t id_;
        std::vector<size_t> inputNodes_;
    };

    class EcoSystem
    {
    public:
        EcoSystem();
        void initialize(); //to be used to set the nodes and their dependencies and properties
        void start();
        void stop();
        bool finished() const {
            return maxHypercycles_ == hypercycle_;
        }
    protected:
        void step();
    private:
        bool started_{ false };
        size_t hypercycle_{ 0 };
        size_t maxHypercycles_{ 30 };
        std::vector<Node> nodes_;
        TaskManager taskManager_;
    };

}
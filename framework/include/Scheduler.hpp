#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include "ThreadPool.hpp"
#include "Node.hpp"
#include "Edge.hpp"

namespace srib {

class Scheduler {
public:
    Scheduler(size_t threads = std::thread::hardware_concurrency())
        : pool_(threads) {}

    void schedule(const std::vector<NodePtr>& nodes) {
        for (auto& node : nodes) {
            pool_.enqueue([node] {
                node->process();
            });
        }
    }

private:
    ThreadPool pool_;
};

} // namespace srib

#endif // __SCHEDULER_HPP__

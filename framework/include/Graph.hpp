#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include "common.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "Scheduler.hpp"

namespace srib {

class Graph {
public:
    void addNode(NodePtr node) {
        nodes_.push_back(node);
    }

    void addEdge(NodePtr src, NodePtr dst) {
        auto edge = std::make_shared<Edge>(src, dst);
        edge->buffer = std::make_shared<Buffer>(1024);
        src->setOutput(edge->buffer);
        dst->setInput(edge->buffer);
        edges_.push_back(edge);
    }

    void run() {
        Scheduler scheduler;
        scheduler.schedule(nodes_);
    }

private:
    std::vector<NodePtr> nodes_;
    std::vector<EdgePtr> edges_;
};

} // namespace srib

#endif //__GRAPH_HPP__

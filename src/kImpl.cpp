#include "Node.hpp"
#include <chrono>
#include <thread>
#include <iostream>

namespace srib {

class BlurNode : public Node {
public:
    BlurNode() : Node("BlurNode", ComputeUnit::CPU) {}
    void process() override {
        std::cout << name() << " running on CPU\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

class ClassifyNode : public Node {
public:
    ClassifyNode() : Node("ClassifyNode", ComputeUnit::GPU) {}
    void process() override {
        std::cout << name() << " running on GPU\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

class EdgeNode : public Node {
public:
    EdgeNode() : Node("EdgeNode", ComputeUnit::NPU) {}
    void process() override {
        std::cout << name() << " running on NPU\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

// Factory functions for test usage
NodePtr makeBlurNode() { return std::make_shared<BlurNode>(); }
NodePtr makeClassifyNode() { return std::make_shared<ClassifyNode>(); }
NodePtr makeEdgeNode() { return std::make_shared<EdgeNode>(); }

} // namespace srib




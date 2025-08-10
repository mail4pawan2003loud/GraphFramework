#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "Buffer.hpp"

namespace srib {

enum class ComputeUnit { CPU, GPU, NPU };

class Node {
public:
    Node(std::string name, ComputeUnit cu) : name_(std::move(name)), cu_(cu) {}
    virtual ~Node() = default;

    const std::string& name() const { return name_; }
    ComputeUnit computeUnit() const { return cu_; }

    virtual void process() = 0;

    void setInput(BufferPtr buf) { input_ = buf; }
    void setOutput(BufferPtr buf) { output_ = buf; }
    BufferPtr input() const { return input_; }
    BufferPtr output() const { return output_; }

private:
    std::string name_;
    ComputeUnit cu_;
    BufferPtr input_;
    BufferPtr output_;
};

using NodePtr = std::shared_ptr<Node>;

} // namespace srib


#endif //__NODE_HPP__


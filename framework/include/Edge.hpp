#ifndef __EDGE_H__
#define __EDGE_H__

#include "Buffer.hpp"

namespace srib {

class Node; // forward declaration

class Edge {
public:
    Edge(std::shared_ptr<Node> src, std::shared_ptr<Node> dst)
        : src_(src), dst_(dst) {}

    std::shared_ptr<Node> src() const { return src_; }
    std::shared_ptr<Node> dst() const { return dst_; }

    BufferPtr buffer;

private:
    std::shared_ptr<Node> src_;
    std::shared_ptr<Node> dst_;
};

using EdgePtr = std::shared_ptr<Edge>;

} // namespace srib



#endif // __EDGE_H__


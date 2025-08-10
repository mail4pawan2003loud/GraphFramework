#include "Graph.hpp"

// Declare factory functions from kImpl.cpp
namespace srib {
    NodePtr makeBlurNode();
    NodePtr makeClassifyNode();
    NodePtr makeEdgeNode();
}

int main() {
    using namespace srib;

    Graph g;

    auto blur = makeBlurNode();
    auto classify = makeClassifyNode();
    auto edge = makeEdgeNode();

    g.addNode(blur);
    g.addNode(classify);
    g.addNode(edge);

    g.addEdge(blur, classify);
    g.addEdge(classify, edge);

    g.run();

    return 0;
}


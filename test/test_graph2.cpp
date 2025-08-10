// test/test_graph.cpp
#include <iostream>
#include <thread>
#include <vector>

#include "Graph.hpp"

//
// Forward declarations for factory functions implemented in src/kImpl.cpp
//
namespace srib {
    NodePtr makeBlurNode();
    NodePtr makeEdgeNode();
    NodePtr makeClassifyNode();

    // ThreadPool is in namespace srib
    class ThreadPool;
}

int main() {
    using namespace srib;

    std::cout << "=== Single-graph runs ===\n";

    {
        Graph g;
        // create nodes (implemented in src/kImpl.cpp)
        auto n_blur = makeBlurNode();
        auto n_edge = makeEdgeNode();
        auto n_clf  = makeClassifyNode();

        // add nodes to graph
        g.addNode(n_blur);
        g.addNode(n_edge);
        g.addNode(n_clf);

        // connect nodes (Graph::addEdge creates a buffer and wires input/output)
        g.addEdge(n_blur, n_edge);
        g.addEdge(n_edge, n_clf);

        std::cout << "Run 1\n";
        g.run();

        std::cout << "Run 2 (re-run same graph)\n";
        g.run();
    }

    std::cout << "\n=== Parallel graphs (ThreadPool) ===\n";

    // Build and run multiple graphs in parallel to stress test thread safety.
    // The ThreadPool here is the lightweight one from the framework; we create
    // std::threads to run multiple graphs concurrently (each Graph uses its own Scheduler/ThreadPool).
    std::vector<std::thread> workers;
    const int num_graphs = 3;

    for (int i = 0; i < num_graphs; ++i) {
        workers.emplace_back([i]() {
            using namespace srib;
            Graph g;
            auto n_blur = makeBlurNode();
            auto n_edge = makeEdgeNode();
            auto n_clf  = makeClassifyNode();

            g.addNode(n_blur);
            g.addNode(n_edge);
            g.addNode(n_clf);

            g.addEdge(n_blur, n_edge);
            g.addEdge(n_edge, n_clf);

            std::cout << "[Worker " << i << "] starting graph\n";
            g.run();
            std::cout << "[Worker " << i << "] finished graph\n";
        });
    }

    // join threads
    for (auto &t : workers) if (t.joinable()) t.join();

    std::cout << "All done.\n";
    return 0;
}


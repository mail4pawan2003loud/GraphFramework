# srib — Header-Only Graph Execution Framework

## Overview
`srib` is a **header-only C++ framework** for building **static, graph-based pipelines** for computer vision and AI workloads.  

It supports:
- **Static graph creation** — Define computation nodes and edges at compile time.
- **Parallel execution** — Run independent nodes on multiple threads.
- **Heterogeneous scheduling** — Assign nodes to CPU, GPU, NPU, etc.
- **Multi-camera & multi-frame processing** — Process video streams in real time.

Inspired by **OpenVX-style pipelines**, but lightweight and embeddable.

---

## 📂 Project Structure
```
project_root/
│
├── framework/include/srib/
│   ├── Buffer.hpp
│   ├── Edge.hpp
│   ├── Graph.hpp
│   ├── Node.hpp
│   ├── Scheduler.hpp
│   ├── ThreadPool.hpp
│   ├── common.hpp
│
├── src/
│   └── kImpl.cpp    # Custom node implementations
│
├── test/
│   └── test_graph.cpp
│
├── docs/
│   ├── multi_cam_timeline.png
│   └── tutorial.md
│
└── CMakeLists.txt
```

---

## 🧩 Core Concepts

### **Node**
A computation unit that processes inputs and produces outputs.
```cpp
class BlurNode : public srib::Node {
public:
    void execute() override {
        auto buf = getInput(0);
        // perform blur
        setOutput(0, buf);
    }
};
```

### **Edge**
Connects node outputs to node inputs.
```cpp
graph.addEdge(nodeA, 0, nodeB, 0);
```

### **Buffer**
Holds data passed between nodes.
```cpp
auto buf = std::make_shared<srib::Buffer>(width * height * channels);
buf->fillRandom();
```

### **Scheduler**
Manages execution order & compute unit assignments.
```cpp
graph.assignComputeUnit(blur, srib::ComputeUnit::GPU);
```

---

## 🚀 Getting Started

### **1. Include headers**
```cpp
#include "srib/Graph.hpp"
#include "srib/Node.hpp"
#include "srib/Buffer.hpp"
#include "srib/Scheduler.hpp"
```

### **2. Implement nodes** (`src/kImpl.cpp`)
```cpp
#include "srib/Node.hpp"
#include <iostream>

class CaptureNode : public srib::Node {
public:
    void execute() override {
        auto buf = std::make_shared<srib::Buffer>(640 * 480 * 3);
        buf->fillRandom();
        setOutput(0, buf);
        std::cout << "Captured frame\n";
    }
};

class DisplayNode : public srib::Node {
public:
    void execute() override {
        auto buf = getInput(0);
        std::cout << "Displaying frame of size " << buf->size() << "\n";
    }
};
```

### **3. Build the graph** (`test/test_graph.cpp`)
```cpp
#include "srib/Graph.hpp"
#include "srib/Scheduler.hpp"
#include "srib/Buffer.hpp"
#include "kImpl.cpp" // For example only

int main() {
    srib::Graph graph;

    auto cap  = graph.addNode<CaptureNode>();
    auto blur = graph.addNode<BlurNode>();
    auto disp = graph.addNode<DisplayNode>();

    graph.addEdge(cap, 0, blur, 0);
    graph.addEdge(blur, 0, disp, 0);

    graph.assignComputeUnit(blur, srib::ComputeUnit::GPU);
    graph.assignComputeUnit(disp, srib::ComputeUnit::CPU);

    graph.execute();
}
```

---

## ⚙️ Building

`CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.10)
project(srib_graph)

set(CMAKE_CXX_STANDARD 17)
include_directories(framework/include)

add_executable(test_graph
    test/test_graph.cpp
    src/kImpl.cpp
)
```

Build & run:
```bash
mkdir build && cd build
cmake ..
make
./test_graph
```

---

## 🎥 Multi-Camera Parallel Pipeline

You can process **multiple camera feeds** in parallel by creating separate capture → processing → display subgraphs.

```cpp
int numCams = 2;
for (int cam = 0; cam < numCams; ++cam) {
    auto cap  = graph.addNode<CaptureNode>();
    auto blur = graph.addNode<BlurNode>();
    auto disp = graph.addNode<DisplayNode>();

    graph.addEdge(cap, 0, blur, 0);
    graph.addEdge(blur, 0, disp, 0);

    graph.assignComputeUnit(blur, srib::ComputeUnit::GPU);
}
```

---

## ⏱ Execution Timeline Example

Below is a **Gantt chart** showing two camera pipelines scheduled on CPU & GPU.

![Multi-camera pipeline timing diagram](docs/multi_cam_timeline.png)

---

## 📌 Features Summary
- Lightweight, header-only design  
- Static graph definition  
- Parallel execution across threads  
- Assign nodes to CPU, GPU, or NPU  
- Real-time multi-camera support  

---

## 📜 License
M

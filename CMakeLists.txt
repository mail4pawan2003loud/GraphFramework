cmake_minimum_required(VERSION 3.10)
project(GraphFrameworkExample LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include framework headers
include_directories(${PROJECT_SOURCE_DIR}/framework/include)

# Source files
set(SRC_FILES
    src/kImpl.cpp
)

# Test executable
add_executable(test_graph
    test/test_graph.cpp
    ${SRC_FILES}
)

# Link libraries (pthread for threading)
if(UNIX)
    target_link_libraries(test_graph pthread)
endif()

# Test executable
add_executable(test_graph2
    test/test_graph2.cpp
    ${SRC_FILES}
)

# Link libraries (pthread for threading)
if(UNIX)
    target_link_libraries(test_graph2 pthread)
endif()


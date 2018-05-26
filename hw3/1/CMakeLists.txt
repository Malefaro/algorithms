cmake_minimum_required(VERSION 3.8)
project(1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ListGraph.cpp ListGraph.hpp MatrixGraph.cpp MatrixGraph.hpp SetGraph.cpp SetGraph.hpp ArcGraph.cpp ArcGraph.hpp)
add_executable(1 ${SOURCE_FILES})
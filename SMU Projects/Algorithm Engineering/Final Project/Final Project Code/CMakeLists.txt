cmake_minimum_required(VERSION 3.23)
project(PA2)

set(CMAKE_CXX_STANDARD 14)

add_executable(PA2 main.cpp AdjacencyList.h AdjacencyList.cpp LinkedList.h CreateGraphs.cpp CreateGraphs.h VertexNode.cpp VertexNode.h ColorSolver.cpp ColorSolver.h Vector.h)

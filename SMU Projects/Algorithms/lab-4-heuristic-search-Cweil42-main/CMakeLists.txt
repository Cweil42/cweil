cmake_minimum_required(VERSION 3.17)
project(lab-4-heuristic-search)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab-4-heuristic-search ./Code/main.cpp Code/fileReader.h Code/fileReader.cpp Code/HamiltonianCircuit.h Code/HamiltonianCircuit.cpp Code/HamiltonianAlgorithms.h Code/HamiltonianAlgorithms.cpp Code/Path.h Code/Path.cpp Code/output.h Code/output.cpp)
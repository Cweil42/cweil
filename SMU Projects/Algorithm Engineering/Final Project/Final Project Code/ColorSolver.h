//
// Created by Colin Weil on 12/5/22.
//

#ifndef MAIN_CPP_COLORSOLVER_H
#define MAIN_CPP_COLORSOLVER_H
#include "AdjacencyList.h"
#include "Vector.h"
#include "CreateGraphs.h"

class ColorSolver {
public:
    ColorSolver();
    int colorGraph(int* order, AdjacencyList graph, string filename, bool output, bool slvo);
    int* slvoSolver(AdjacencyList& graph);             // Smallest last vertex
    int* smallOriginalSolver(AdjacencyList graph);    // small original degree
    int* uniformRandomSolver(AdjacencyList graph);    // uniform random

    void OrderSolverTimings();
    void ColorTimings();

    void PrintExampleSLVO();

//    void REVslvoSolver(AdjacencyList& graph);             // reverse slvo
//    void REVsmallOriginalSolver(AdjacencyList& graph);    // reverse small original degree
//    void inOrderSolver(AdjacencyList& graph);             // In number of node order
};


#endif //MAIN_CPP_COLORSOLVER_H

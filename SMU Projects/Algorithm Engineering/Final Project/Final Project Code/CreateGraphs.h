//
// Created by Colin Weil on 11/28/22.
//

#ifndef MAIN_CPP_CREATEGRAPHS_H
#define MAIN_CPP_CREATEGRAPHS_H
#include "AdjacencyList.h"
#include <iostream>

class CreateGraphs {
public:
    AdjacencyList CreateGraph(int V, int E, string G, string DIST);

    AdjacencyList createComplete(int V);
    AdjacencyList createCycle(int V);

    AdjacencyList createRandomUniform(int V, int E);
    AdjacencyList createRandomTiered(int V, int E);

    AdjacencyList createRandomYours(int V, int E);

    AdjacencyList readFromFile(string filepath);

    int calculateNumberOfLinearDist(int);

    void CycleAndCompleteGraphTimings();
    void RandomGraphCreationTimings();

    void OutputGraphConflicts();
};


#endif //MAIN_CPP_CREATEGRAPHS_H

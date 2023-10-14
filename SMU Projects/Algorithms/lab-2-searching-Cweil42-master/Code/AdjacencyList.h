//
// Created by Colin Weil on 10/4/20.
//

#ifndef LAB_2_SEARCHING_ADJACENCYLIST_H
#define LAB_2_SEARCHING_ADJACENCYLIST_H

#include "Node.h"
#include <vector>
#include <stack>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Vertex.h"
using namespace std;

class AdjacencyList{
public:
    AdjacencyList();
    void loadData(string filepath, int size, vector<vector<double>> distances);
    void printList();
    void add(int, int, double, double);
    void clear();
    Vertex* getVertex(int num);
private:
    list<Vertex> adjList;
};

#endif //LAB_2_SEARCHING_ADJACENCYLIST_H

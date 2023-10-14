//
// Created by Colin Weil on 10/15/22.
//

#ifndef PA2_ADJACENCYLIST_H
#define PA2_ADJACENCYLIST_H
#include <algorithm>
#include <iostream>
#include "VertexNode.h"
using namespace std;

class AdjacencyList{
private:
    int edges;
    int V;
public:
    VertexNode* adjList;
    AdjacencyList();
    AdjacencyList(int V);
    AdjacencyList(const AdjacencyList &list);
    AdjacencyList &operator=(const AdjacencyList &l);
    void addEdge(int src, int dest);
    void addSingleEdge(int src, int dest);
    ~AdjacencyList();
    void display();
    void displayMinusOne();
    void OutputFile(string filename);
    int getNumEdges();
    int getNumVertices();
};

#endif //PA2_ADJACENCYLIST_H

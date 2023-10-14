//
// Created by Colin Weil on 10/4/20.
//

#ifndef LAB_2_SEARCHING_ADJACENCYMATRIX_H
#define LAB_2_SEARCHING_ADJACENCYMATRIX_H

#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class AdjacencyMatrix{
public:
    AdjacencyMatrix();
    void addNode(int, int, Node&);
    Node* getNode(int, int);
    void loadData(string filepath, int size, vector<vector<double>> distances);
    void printMatrix();
    vector<Node>* getRow(int row);
    int getSize();
    void clear();
private:
    vector<vector<Node>> matrix;
};

#endif //LAB_2_SEARCHING_ADJACENCYMATRIX_H

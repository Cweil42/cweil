//
// Created by Colin Weil on 9/8/20.
//

#ifndef LAB_1_SORTING_SORT_H
#define LAB_1_SORTING_SORT_H
#include <iostream>
#include <fstream>
#include "Algorithm.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include <list>
#include <chrono>
#include <queue>
using namespace std;

class Search: public Algorithm{
public:
    Search(int start, int end);
    void Load(string) override;
    void Execute() override;
    void Display() override;
    void Stats() override;
    void Select(int) override;
    void Save(string) override;
    void Configure() override;
private:
    bool randomSearch;
    bool runList;
    bool runMatrix;
    vector<void (Search:: *)(int,int)> algo;
    void (Search:: *currentAlgo)(int,int) ;
    AdjacencyMatrix matrix;
    AdjacencyList adjList;
    int dataSize;
    int start;
    int end;

    string algoName;
    chrono::duration<double> listTime;
    double listCost = 0;
    int listNumNodes = 0;
    int listExplored = 0;
    vector<Node*>  listAnswer;

    chrono::duration<double> matrixTime;
    double matrixCost = 0;
    int matrixNumNodes = 0;
    int matrixExplored = 0;
    vector<Node*>  matrixAnswer;

    void DFSIterative(int, int);
    void DFSRecursive(int, int);
    void BFSIterative(int, int);
    void BFSRecursive(int, int);
    void Dijkstra(int, int);
    void AStar(int, int);

    vector<Node*> DFSIterativeList(int, int);
    vector<Node*>DFSIterativeMatrix(int, int);
    Node* DFSRecursiveList(int end, vector<bool>& visited, stack<Node*>&);
    Node* DFSRecursiveMatrix(int end, vector<bool>& visited, stack<Node*>&);
    vector<Node*> BFSIterativeList(int, int);
    vector<Node*> BFSIterativeMatrix(int, int);
    Node* BFSRecursiveList(int end, vector<bool>& visited, queue<Node*>&);
    Node* BFSRecursiveMatrix(int end, vector<bool>& visited, queue<Node*>&);
    vector<Node*> DijkstraList(int, int);
    vector<Node*> DijkstraMatrix(int, int);
    vector<Node*> AStarList(int, int);
    vector<Node*> AStarMatrix(int, int);

    vector<Node*> getAnswer(Node* parent, int& numNodes, double& weight);

    struct LessThanByWeight{
        bool operator()(Node*& lhs, Node*& rhs) const{
            return lhs->getRank() < rhs->getRank();
        }
    };

    struct LessThanByRank{
        bool operator()(Node*& lhs, Node*& rhs) const{
            return lhs->getRank() < rhs->getRank();
        }
    };
};

#endif //LAB_1_SORTING_SORT_H

//
// Created by Colin Weil on 10/15/22.
//
#include "AdjacencyList.h"
#include <vector>
#include <fstream>
using namespace std;

AdjacencyList::AdjacencyList(){
    V = 2000000;
    edges = 0;
    adjList = new VertexNode[V];
    for(int i = 0; i < V; i++) {
        VertexNode temp;
        adjList[i] = temp;
    }
}

AdjacencyList::AdjacencyList(int size){
    V = size;
    edges = 0;
    adjList = new VertexNode[V];
    for(int i = 0; i < V; i++) {
        VertexNode temp;
        adjList[i] = temp;
    }
}

AdjacencyList::AdjacencyList(const AdjacencyList &list){
    V = list.V;
    edges = 0;
    adjList = new VertexNode[V];
    for(int i = 0; i < V; i++) {
        adjList[i] = list.adjList[i];
    }
}
AdjacencyList& AdjacencyList::operator=(const AdjacencyList &list){
    V = list.V;
    edges = 0;
    adjList = new VertexNode[V];
    for(int i = 0; i < V; i++) {
        adjList[i] = list.adjList[i];
    }
    return *this;
}

void AdjacencyList::addEdge(int src, int dest){
    adjList[src].addNode(dest);
    adjList[dest].addNode(src);
    edges += 2;
}

void AdjacencyList::addSingleEdge(int src, int dest){
    adjList[src].addNode(dest);
    edges++;
}

AdjacencyList::~AdjacencyList(){
    delete[] adjList;
}

void AdjacencyList::display(){
    for(int i = 0; i < V; i++){
        cout << i+1;
        adjList[i].connections.printListPlusOne();
        cout << endl;
    }
}

void AdjacencyList::displayMinusOne(){
    for(int i = 0; i < V; i++){
        cout << i;
        adjList[i].connections.printList();
        cout << endl;
    }
}

void AdjacencyList::OutputFile(string filename){
    int outputSize = 1 + V + edges;
    int out[outputSize];
    out[0] = V;

    int index = 1 + V;
    for(int i = 0; i < V; i++) {
        out[i+1] = index;
        adjList[i].connections.ToOutputPlusOne(out, index);
    }

    ofstream outfile(filename);
    for(int i = 0; i < outputSize; i++)
        outfile << out[i] << endl;
    outfile.close();
}

int AdjacencyList::getNumEdges(){
    return edges;
}
int AdjacencyList::getNumVertices(){
    return V;
}
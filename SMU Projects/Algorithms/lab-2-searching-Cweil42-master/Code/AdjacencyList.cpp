//
// Created by Colin Weil on 10/4/20.
//

#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(){}

void AdjacencyList::loadData(string filepath, int size, vector<vector<double>> distances){
    for(int i = 0; i < size; i++){
        Vertex cur(i+1);
        adjList.push_back(cur);
    }
    string line;
    ifstream w(filepath + "/weights.txt");
    while(getline(w, line, ',')){
        int from = stoi(line);
        getline(w, line, ',');
        int to = stoi(line);
        getline(w, line);
        double weight = stod(line);
        add(from, to, weight, distances[from-1][to-1]);
    }
    w.close();
}

void AdjacencyList::printList(){
    for (list<Vertex>::iterator it = adjList.begin(); it != adjList.end(); ++it){
        it->print();
    }
}

void AdjacencyList::add(int from, int to, double weight, double distance){
    for (list<Vertex>::iterator it = adjList.begin(); it != adjList.end(); ++it){
        if(it->getStart()->getId() == from){
            Node cur;
            cur.setWeight(weight);
            cur.setId(to);
            cur.setDistance(distance);
            it->addNode(cur);
            return;
        }
    }
}

Vertex* AdjacencyList::getVertex(int num){
    for (list<Vertex>::iterator it = adjList.begin(); it != adjList.end(); ++it){
        if(it->getStart()->getId()  == num){
            return &*it;
        }
    }
}

void AdjacencyList::clear(){
    adjList.clear();
}
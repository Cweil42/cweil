//
// Created by Colin Weil on 10/4/20.
//

#include "Vertex.h"
#include <iostream>
using namespace std;

Vertex::Vertex(int id){
    Node cur;
    cur.setId(id);
    start = cur;
}

void Vertex::addNode(Node& node){
    list.push_back(node);
}

list<Node>* Vertex::getList(){
    return &list;
}

Node* Vertex::getStart(){
    return &start;
}

void Vertex::print(){
    cout << start.getId();
    for (std::list<Node>::iterator it = list.begin(); it != list.end(); ++it){
        cout << " -> " << it->getId();
    }
    cout << endl;
}

//
// Created by Colin Weil on 10/4/20.
//

#ifndef LAB_2_SEARCHING_VERTEX_H
#define LAB_2_SEARCHING_VERTEX_H
#include "Node.h"
#include <list>
using namespace std;

class Vertex{
public:
    Vertex(int);
    void addNode(Node&);
    list<Node>* getList();
    Node* getStart();
    void print();
private:
    Node start;
    list<Node> list;
};
#endif //LAB_2_SEARCHING_VERTEX_H

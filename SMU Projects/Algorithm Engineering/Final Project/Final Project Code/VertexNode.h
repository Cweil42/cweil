//
// Created by Colin Weil on 12/5/22.
//

#ifndef MAIN_CPP_VERTEXNODE_H
#define MAIN_CPP_VERTEXNODE_H
#include "LinkedList.h"


class VertexNode {
public:
    VertexNode();
    void addNode(int dest);
    LinkedList<int> connections;
    ListNode<int>* orderPointer;
    bool deleted;
    int size;
    int curConnections;
    int color;
};


#endif //MAIN_CPP_VERTEXNODE_H

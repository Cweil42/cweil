//
// Created by Colin Weil on 12/5/22.
//

#include "VertexNode.h"

VertexNode::VertexNode(){
    deleted = false;
    size = 0;
    orderPointer = nullptr;
    curConnections = 0;
    color = -1;
}
void VertexNode::addNode(int dest){
    connections.push_back(dest);
    size++;
    curConnections++;
}

//
// Created by Colin Weil on 10/4/20.
//

#include "Node.h"

Node::Node(){
    weight = 0;
    id = -1;
    parent = nullptr;
    distance = 0;
}

bool Node::operator<(const Node& n) {
    return rank < n.rank;
}

double Node::getWeight(){
    return weight;
}

int Node::getId(){
    return id;
}

void Node::setWeight(double w){
    weight = w;
}

void Node::setId(int id){
    this->id = id;
}

void Node::setParent(Node* id){
    parent = id;
}

Node* Node::getParent(){
    return parent;
}

double Node::getDistance(){
    return distance;
}

double Node::setDistance(double c){
    distance  = c;
}

double Node::getRank(){
    return rank;
}
void Node::setRank(double r){
    rank = r;
}

//
// Created by Colin Weil on 10/4/20.
//

#ifndef LAB_2_SEARCHING_NODE_H
#define LAB_2_SEARCHING_NODE_H

class Node{
public:
    Node();
    double getWeight();
    int getId();
    void setWeight(double);
    void setId(int id);
    void setParent(Node* id);
    Node* getParent();
    double getDistance();
    double setDistance(double c);
    double getRank();
    void setRank(double r);
    bool operator<(const Node& n);
private:
    Node* parent;
    double weight;
    double distance;
    int id;
    double rank;
};
#endif //LAB_2_SEARCHING_NODE_H

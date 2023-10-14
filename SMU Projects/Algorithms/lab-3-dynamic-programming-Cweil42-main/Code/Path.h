//
// Created by Colin Weil on 10/27/20.
//

#ifndef LAB_3_DYNAMIC_PROGRAMMING_PATH_H
#define LAB_3_DYNAMIC_PROGRAMMING_PATH_H
#include <vector>
#include <iostream>
using namespace std;

class Path{
private:
    vector<int> path;
    double length;
public:
    Path();
    double getLength();
    void addToLength(double l);
    vector<int>* getPath();
    bool operator <(const Path& p) const;
    void addToPath(int id);
    int getMostRecentNode();
    void printPath();
    int getNodeInPath(int index);
    bool notInPath(int id);
};

#endif //LAB_3_DYNAMIC_PROGRAMMING_PATH_H

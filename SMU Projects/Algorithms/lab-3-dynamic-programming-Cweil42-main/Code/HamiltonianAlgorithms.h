//
// Created by Colin Weil on 10/22/20.
//

#ifndef LAB_3_DYNAMIC_PROGRAMMING_HAMILTONIANALGORITHMS_H
#define LAB_3_DYNAMIC_PROGRAMMING_HAMILTONIANALGORITHMS_H
#include <vector>
#include <iostream>
#include "Path.h"
#include <map>
#include <list>
using namespace std;

class HamiltonianAlgorithms{
public:
    static Path bruteForce(vector<vector<double>>* positions);
    static Path dynamicProgramming(vector<vector<double>>* positions);
private:
    static Path bruteRecursive(vector<vector<double>>& positions, Path p, vector<int> nodesLeft);
    static Path solveDynamic(vector<vector<double>>& memo);
    static bool notIn(int id, int subset);
    static vector<int> combinations(int r, int n);
    static void combinations(int set, int at, int r, int n, vector<int>& subsets);
};

#endif //LAB_3_DYNAMIC_PROGRAMMING_HAMILTONIANALGORITHMS_H

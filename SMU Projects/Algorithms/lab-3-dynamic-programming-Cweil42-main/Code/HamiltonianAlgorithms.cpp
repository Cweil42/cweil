//
// Created by Colin Weil on 10/22/20.
//
#include "HamiltonianAlgorithms.h"
#include <algorithm>
#include <limits>
#include <math.h>

Path HamiltonianAlgorithms::bruteForce(vector<vector<double>>* positions){
    Path p;
    vector<int> nodesLeft;
    for(int i = 1; i < positions->size(); i++)
        nodesLeft.push_back(i+1);

    p = bruteRecursive(*positions, p, nodesLeft);
    return p;
}

Path HamiltonianAlgorithms::bruteRecursive(vector<vector<double>>& positions, Path rootPath, vector<int> nodesLeft){
    if(nodesLeft.empty()){
        if(rootPath.getPath()->size() != positions.size()){
            rootPath.addToLength(numeric_limits<double>::max());
            return rootPath;
        }
        rootPath.addToLength(positions[rootPath.getMostRecentNode()-1][0]);
        rootPath.addToPath(1);
        return rootPath;
    }
    Path loopBest;
    loopBest.addToLength(numeric_limits<double>::max());
    int size = nodesLeft.size();
    for(int i = 0; i < size; i++){
        Path curPath = rootPath;
        curPath.addToLength(positions[curPath.getMostRecentNode()-1][nodesLeft[i]-1]);
        curPath.addToPath(nodesLeft[i]);
        int deletedNode = nodesLeft[i];
        nodesLeft.erase(nodesLeft.begin()+i);

        curPath = bruteRecursive(positions, curPath, nodesLeft);
        nodesLeft.insert(nodesLeft.begin()+i, deletedNode);

        if(loopBest.getLength() > curPath.getLength()){
            loopBest = curPath;
        }
    }

    return loopBest;
}

// Algo from https://github.com/williamfiset/Algorithms/blob/master/src/main/java/com/williamfiset/algorithms/graphtheory/TspDynamicProgrammingIterative.java
Path HamiltonianAlgorithms::dynamicProgramming(vector<vector<double>>* positions){
    Path p = solveDynamic(*positions);
    return p;
}

Path HamiltonianAlgorithms::solveDynamic(vector<vector<double>>& positions){
    int size = positions.size();
    int start = 0;

    // Setup of Memo Vector
    vector<vector<double>> memo;
    vector<double> col(pow(2,size), 0);
    for(int i = 0; i < size; i++){
        memo.push_back(col);
    }
    for (int i = 1; i < positions.size(); i++) {
        memo[i][(1 << start) | (1 << i)] = positions[start][i];
    }

//    double** memo = new double*[size];
//    int col = pow(2, size);
//    for (int i = 0; i < size; i++) {
//        memo[i] = new double[col];
//        for (int k = 0; k < col; k++) {
//            memo[i][k] = INFINITY;
//        }
//    }

    // Fills memoization table
    for(int i = 3; i <= size; i++){
        vector<int> subset = combinations(i, size);
        for(int j = 0; j < subset.size(); j++){
            int subsetNum = subset[j];
            if(notIn(start, subsetNum)) continue;
            for(int next = 0; next < size; next++){
                if(next == start || notIn(next, subsetNum)) continue;
                int subsetWithoutNext = subsetNum ^ (1 << next);
                double minDist = INFINITY;
                for(int end = 0; end < size; end++){
                    if (end == start || end == next || notIn(end, subsetNum)) continue;
                    double newDistance = memo[end][subsetWithoutNext] + positions[end][next];
                    if (newDistance < minDist) {
                        minDist = newDistance;
                    }
                }
                memo[next][j] = minDist;
            }
        }
    }

    // Find path and minimize cost
    int END_STATE = (1 << size) - 1;
//    double minTourCost = INFINITY;
//    for (int i = 1; i < size; i++) {
//        double tourCost = memo[i][END_STATE] + positions[i][start];
//        if (tourCost < minTourCost)
//            minTourCost = tourCost;
//    }

    int lastIndex = 0;
    int state = (1 << size) - 1;
    Path p;
    // Make path from memo table
    for (int i = 1; i < size; i++) {
        int index = -1;
        for (int j = 0; j < size; j++) {
            if (j == start || notIn(j, state)) continue;
            if (index == -1) index = j;
            double prevDist = memo[index][state] + positions[index][lastIndex];
            double newDist = memo[j][state] + positions[j][lastIndex];
            if (newDist < prevDist) {
                index = j;
            }
        }
        p.addToLength(positions[p.getMostRecentNode()-1][index]);
        p.addToPath(index+1);
        state = state ^ (1 << index);
        lastIndex = index;
    }
    p.addToLength(positions[p.getMostRecentNode()-1][0]);
    p.addToPath(start+1);

    return p;
}

bool HamiltonianAlgorithms::notIn(int id, int subset){
    return ((1 << id) & subset) == 0;
}

vector<int> HamiltonianAlgorithms::combinations(int r, int n){
    vector<int> subsets;
    combinations(0,0, r, n, subsets);
    return subsets;
}

void HamiltonianAlgorithms::combinations(int set, int at, int r, int n, vector<int>& subsets){
    int elementsLeft = n - at;
    if(elementsLeft < r) return;

    if(r == 0){
        subsets.push_back(set);
    }
    else{
        for(int i = at; i < n; i++){
            set ^= (1 << i);
            combinations(set, i+1, r-1, n ,subsets);
            set = set& ~(1 << i);
        }
    }
}

//
// Created by Colin Weil on 9/8/20.
//

#ifndef LAB_1_SORTING_SORT_H
#define LAB_1_SORTING_SORT_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Algorithm.h"
#include "SortFunctions.h"
#include <chrono>
using namespace std;

class Sort: public Algorithm{
public:
    Sort();
    void Load(string) override;
    void Execute() override;
    void Display() override;
    void Stats() override;
    void Select(int) override;
    void Save(string) override;
    void Configure() override;
private:
    vector<void(*)(vector<int>&)> algo;
    void (*currentAlgo)(vector<int>&);
    vector<int> vect;
    string algoName;
    chrono::duration<double> time;
};

#endif //LAB_1_SORTING_SORT_H

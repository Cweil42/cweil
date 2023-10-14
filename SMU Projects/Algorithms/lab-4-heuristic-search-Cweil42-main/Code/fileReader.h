//
// Created by Colin Weil on 10/22/20.
//
#include <iostream>
#include <vector>
using namespace std;

#ifndef LAB_3_DYNAMIC_PROGRAMMING_READFILE_H
#define LAB_3_DYNAMIC_PROGRAMMING_READFILE_H

class fileReader{
public:
    fileReader();
    void readPositions(string filepath);
    double getIndex(int row, int col);
    int columnSize();
    int rowSize();
    void printData();
    vector<vector<double>>* getData();
private:
    vector<vector<double>> data;
};

#endif //LAB_3_DYNAMIC_PROGRAMMING_READFILE_H

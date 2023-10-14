#include <climits>
//
// Created by Colin Weil on 10/27/20.
//

#ifndef LAB_3_DYNAMIC_PROGRAMMING_OUTPUT_H
#define LAB_3_DYNAMIC_PROGRAMMING_OUTPUT_H
#include "Path.h"
#include <fstream>
#include <iostream>
using namespace std;

class output{
public:
    output();
    void chooseFilePath(string filepath);
    void printPath(Path& p);
    void printToFile(string s);
    void closeFile();
private:
    ofstream outfile;
};

#endif //LAB_3_DYNAMIC_PROGRAMMING_OUTPUT_H

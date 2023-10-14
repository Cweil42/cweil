//
// Created by Colin Weil on 9/7/20.
//
#include <iostream>
#include <fstream>
using namespace std;

#ifndef LAB_1_SORTING_ALGORITHM_H
#define LAB_1_SORTING_ALGORITHM_H

class Algorithm{
public:
    virtual void Load(string)=0;
    virtual void Execute()=0;
    virtual void Display()=0;
    virtual void Stats()=0;
    virtual void Select(int)=0;
    virtual void Save(string)=0;
    virtual void Configure()=0;
};

#endif //LAB_1_SORTING_ALGORITHM_H

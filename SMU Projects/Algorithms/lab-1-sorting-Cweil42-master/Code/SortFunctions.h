//
// Created by Colin Weil on 9/7/20.
//

#ifndef LAB_1_SORTING_SORTFUNCTIONS_H
#define LAB_1_SORTING_SORTFUNCTIONS_H
#include <vector>
using namespace std;

class SortFunctions{
public:
    void static mergeSort(vector<int>& vect);
    void static bubbleSort(vector<int>& vect);
    void static insertionSort(vector<int>& vect);
    void static printArray(vector<int>& vect);
private:
    void static merge(vector<int>& vect, int l, int m, int r);
    void static mergeSort(vector<int>& vect, int l, int r);
    void static swap(int *one, int *two);
};

#endif //LAB_1_SORTING_SORTFUNCTIONS_H

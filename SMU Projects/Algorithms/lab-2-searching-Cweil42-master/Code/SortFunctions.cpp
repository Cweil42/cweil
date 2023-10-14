//
// Created by Colin Weil on 9/7/20.
//
#include "SortFunctions.h"
#include <iostream>
using namespace std;

// Private merge function
void SortFunctions::merge(vector<int>& vect, int left, int mid, int right){
    int i;
    int j;
    int k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Creates sub arrays and copies numbers
    int Left[n1], Right[n2];
    for (i = 0; i < n1; i++)
        Left[i] = vect[left + i];
    for (j = 0; j < n2; j++)
        Right[j] = vect[mid + 1 + j];

    // Merge arrays back together
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2){
        if (Left[i] <= Right[j]){
            vect[k] = Left[i];
            i++;
        }
        else{
            vect[k] = Right[j];
            j++;
        }
        k++;
    }

    // Copy the left over numbers into the end of the combined array
    while (i < n1){
        vect[k] = Left[i];
        i++;
        k++;
    }
    while (j < n2){
        vect[k] = Right[j];
        j++;
        k++;
    }
}

// Private merge sort of sub-arrays
void SortFunctions::mergeSort(vector<int>& vect, int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        mergeSort(vect, left, mid);
        mergeSort(vect, mid + 1, right);
        merge(vect, left, mid, right);
    }
}

// Public use of merge sort with input of an array of ints
void SortFunctions::mergeSort(vector<int>& vect){
    mergeSort(vect, 0, vect.size()-1);
}

// Swaps elements
void SortFunctions::swap(int *one, int *two){
    int temp = *one;
    *one = *two;
    *two = temp;
}

// Private bubble sort
void SortFunctions::bubbleSort(vector<int>& vect){
    if(vect.size() == 0)
        return;
    for (int i = 0; i < vect.size()-1; i++) {
        for (int j = 0; j < vect.size()-i-1; j++) {
            if (vect[j] > vect[j+1])
                swap(&vect[j], &vect[j+1]);
        }
    }
}

// Public insertion sort
void SortFunctions::insertionSort(vector<int>& vect){
    for (int i = 1; i < vect.size(); i++){
        int key = vect[i];
        int j = i - 1;
        while (j >= 0 && vect[j] > key){
            vect[j + 1] = vect[j];
            j = j - 1;
        }
        vect[j + 1] = key;
    }
}

// Prints array to cout
void SortFunctions::printArray(vector<int>& vect){
    for(int i = 0; i < vect.size(); i++)
        cout << vect[i] << endl;
}

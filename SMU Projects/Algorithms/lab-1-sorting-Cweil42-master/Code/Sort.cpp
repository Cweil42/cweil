//
// Created by Colin Weil on 9/8/20.
//
#include "Sort.h"
int MERGE = 0;
int BUBBLE = 1;
int INSERTION = 2;

Sort::Sort():Algorithm(){
    algo.push_back(&SortFunctions::mergeSort);
    algo.push_back(&SortFunctions::bubbleSort);
    algo.push_back(&SortFunctions::insertionSort);
}

void Sort::Load(string file){
    vect.clear();
    string line;
    file = "../Data/" + file;
    ifstream in(file);
    while(getline(in, line)){
        vect.push_back(stoi(line));
    }
    in.close();
}

void Sort::Execute(){
    auto start = std::chrono::steady_clock::now();
    currentAlgo(vect);
    auto end = std::chrono::steady_clock::now();
    time = end-start;
}

void Sort::Display(){
    SortFunctions::printArray(vect);
}

void Sort::Stats(){
    cout << "Algorithm: " << algoName << endl;
    cout << "Time it took to sort " << vect.size() << " numbers: " << time.count() << " seconds." << endl;
}

void Sort::Select(int index) {
    currentAlgo = algo[index];
    switch(index){
        case 0:
            algoName = "Merge";
            break;
        case 1:
            algoName = "Bubble";
            break;
        case 2:
            algoName = "Insertion";
            break;
    }
}

void Sort::Save(string filepath) {
    ofstream out(filepath);
    for(int i = 0; i < vect.size(); i++){
        out << vect[i] << endl;
    }
    out.close();
}

void Sort::Configure() {
    cout << "Not setup yet" << endl;
}

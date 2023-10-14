//
// Created by Colin Weil on 10/22/20.
//

#ifndef LAB_3_DYNAMIC_PROGRAMMING_HAMILTONIANCIRCUIT_H
#define LAB_3_DYNAMIC_PROGRAMMING_HAMILTONIANCIRCUIT_H
#include "Algorithm.h"
#include "fileReader.h"
#include "Algorithm.h"
#include <vector>
#include <chrono>
#include "Path.h"
#include "output.h"
using namespace std;

class HamiltonianCircuit: public Algorithm{
public:
    HamiltonianCircuit();
    void Load(string) override;
    void Execute() override;
    void Display() override;
    void Stats() override;
    void Select(int) override;
    void Save(string) override;
    void Configure() override;
private:
    vector<Path(*)(vector<vector<double>>*)> algo;
    Path (*currentAlgo)(vector<vector<double>>*);
    fileReader positions;
    output out;

    Path bestPath;
    string algoName;
    chrono::duration<double> time;
};

#endif //LAB_3_DYNAMIC_PROGRAMMING_HAMILTONIANCIRCUIT_H

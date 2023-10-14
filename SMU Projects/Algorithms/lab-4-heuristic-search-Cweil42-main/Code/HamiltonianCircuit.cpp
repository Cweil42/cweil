//
// Created by Colin Weil on 9/8/20.
//
#include "HamiltonianCircuit.h"
#include "HamiltonianAlgorithms.h"
int BRUTE_FORCE = 0;
int DYNAMIC_PROGRAMMING = 1;

HamiltonianCircuit::HamiltonianCircuit():Algorithm(){
    algo.push_back(&HamiltonianAlgorithms::bruteForce);
    algo.push_back(&HamiltonianAlgorithms::dynamicProgramming);
    algo.push_back(&HamiltonianAlgorithms::simulatedAnnealing);
    algo.push_back(&HamiltonianAlgorithms::geneticAlgorithm);
}

void HamiltonianCircuit::Load(string file){
    positions.readPositions(file);
}

void HamiltonianCircuit::Execute(){
    auto start = std::chrono::steady_clock::now();
    bestPath = currentAlgo(positions.getData());
    auto end = std::chrono::steady_clock::now();
    time = end-start;
}

void HamiltonianCircuit::Display(){
    bestPath.printPath();
}

void HamiltonianCircuit::Stats(){
    cout << "Algorithm: " << algoName << endl;
    cout << "Time: " << time.count() << " seconds" << endl;
    cout << "Best Path: ";
    bestPath.printPath();
    cout << "Length of path: " << bestPath.getLength() << endl << endl;

//    ofstream temp("../Report/tempTimes.txt", ios::app);
//    temp << time.count() << endl;
//    temp.close();
}

void HamiltonianCircuit::Select(int index) {
    currentAlgo = algo[index];
    switch(index){
        case 0:
            algoName = "Brute Force";
            break;
        case 1:
            algoName = "Dynamic Programming";
            break;
        case 2:
            algoName = "Simulated Annealing";
            break;
        case 3:
            algoName = "Genetic Algorithm";
            break;
    }
}

void HamiltonianCircuit::Save(string filepath) {
    out.chooseFilePath(filepath);
    string stats = to_string(positions.rowSize()) + ',' + to_string(time.count()) + ',' + algoName + ',';
    out.printToFile(stats);
    out.closeFile();
}

void HamiltonianCircuit::Configure() {
    cout << "Not setup yet" << endl;
}

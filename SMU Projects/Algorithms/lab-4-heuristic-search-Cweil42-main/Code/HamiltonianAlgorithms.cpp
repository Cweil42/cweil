//
// Created by Colin Weil on 10/22/20.
//
#include "HamiltonianAlgorithms.h"
#include <algorithm>
#include <limits>
#include <math.h>
#include "output.h"
#include <chrono>
#include <fstream>
#include <iostream>

// output file names
string OUTPUT_GA = "DataGA.csv";
string OUTPUT_SA = "DataSA.csv";

// SIMULATED ANNEALING VARIABLES
double TEMP = 10000;
double COOLING_CONSTANT = .000001;
// 0 for random and 1 for rand+-1
int INDEX_PICKER = 0;

// MUTATION VARIABLES
double MUTATION_RATE = .10;
int SELECTION = 0;
int MUTATION = 0;
int CROSSOVER = 0;
// Selection Changes
int ROULETTE = 0;
int RANDOM = 1;
// Mutation Changes
int ADJMUT = 0;
int RANMUT = 1;
// Crossover Changes
int SLICECROSS = 0;
int ALTERCROSS = 1;

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
//    vector<vector<double>> memo;
//    vector<double> col(pow(2,size), 0);
//    for(int i = 0; i < size; i++){
//        memo.push_back(col);
//    }
    double** memo = new double*[size];
    int col = pow(2, size);
    for (int i = 0; i < size; i++) {
        memo[i] = new double[col];
        for (int k = 0; k < col; k++) {
            memo[i][k] = 0;
        }
    }
    for (int i = 1; i < positions.size(); i++) {
        memo[i][(1 << start) | (1 << i)] = positions[start][i];
    }

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


Path HamiltonianAlgorithms::geneticAlgorithm(vector<vector<double>>* pos){
    Path p;
    vector<Path> population;
    // Create Population
    vector<int> examplePath;
    for(int i = 0; i < pos->size(); i++){
        examplePath.push_back(i);
    }
    for(int i = 0; i < pos->size(); i++){
        vector<int> curPath = createRanPath(pos->size(), examplePath);
        Path c;
        for(int i = 0; i < curPath.size(); i++){
            c.addToLength((*pos)[c.getMostRecentNode()-1][curPath[i]]);
            c.addToPath(curPath[i]);
        }
        population.push_back(c);
    }

    Path best;
    best.addToLength(INFINITY);
    string output;
    vector<double> fitness;

//    int i = 1;
//    while(i < 10000){
//        calculateFitness(*pos, population, fitness);
//        nextGeneration(*pos, population, fitness, best);
//        i++;
//        output += to_string(i) + ',' + to_string(best.getLength()) + '\n';
//        fitness.clear();
//    }

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    chrono::duration<double> time = end-start;
    double t = time.count();
    int i = 0;
    while(t < 600){
        calculateFitness(*pos, population, fitness);
        nextGeneration(*pos, population, fitness, best);
        i++;
        output += to_string(i) + ',' + to_string(best.getLength()) + '\n';
        fitness.clear();
        end = std::chrono::steady_clock::now();
        chrono::duration<double> time = end-start;
        t = time.count();
    }


    ofstream out("../Report/" + OUTPUT_GA, ios::trunc);
    output::printToFile(out, output);
    out.close();

    return best;
}

void HamiltonianAlgorithms::calculateFitness(vector<vector<double>>& positions, vector<Path>& population, vector<double>& fitness){
    int best = INFINITY;
    Path bestPath;
    for(int i = 0; i < population.size(); i++){
        double curDistance = population[i].getLength();
        if(curDistance < best){
            best = curDistance;
            bestPath = population[i];
        }
        fitness.push_back(1/ curDistance);
    }

    // Normalize all the fitnesses
    double high = 0;
    // Add all
    for (int i = 0; i < fitness.size(); i++) {
        if(fitness[i]>high)
            high = fitness[i];
    }
    // Normalize values
    for (int i = 0; i < fitness.size(); i++) {
        fitness[i] = fitness[i] / high;
    }
}

void HamiltonianAlgorithms::nextGeneration(vector<vector<double>>& positions, vector<Path>& population, vector<double>& fitness, Path& best){
    vector<Path> newPop;
    for(int i = 0; i < population.size(); i++){
        vector<int> parent1 = selection(population, fitness);
        vector<int> parent2 = selection(population, fitness);
        vector<int> child = crossOver(positions, parent1, parent2);
        mutate(positions, child);
        Path cur;
        cur.setPathAndLength(positions, child);
        if(cur.getLength() < best.getLength()){
            best = cur;
        }
        newPop.push_back(cur);
    }
    population = newPop;
}

vector<int> HamiltonianAlgorithms::selection(vector<Path>& population, vector<double>& fitness){
    vector<int> cur;
    if(SELECTION == 0){
        cur = roule(population, fitness);
    }
    else if(SELECTION == 1){
        cur = randomSelect(population, fitness);
    }
    return cur;
}

vector<int> HamiltonianAlgorithms::roule(vector<Path>& population, vector<double>& fitness){
    double index = double((rand() % fitness.size()));
    while(fitness[index] < .99){
        index++;
        if(index == fitness.size())
            index = 0;
    }
    return *population[index].getPath();
}

vector<int> HamiltonianAlgorithms::randomSelect(vector<Path>& population, vector<double>& fitness){
    double index = double((rand() % population.size()));
    return *population[index].getPath();
}

vector<int> HamiltonianAlgorithms::crossOver(vector<vector<double>>& positions, vector<int> a, vector<int> b){
    // Makes new path with a section of vector a
    int left = rand() % (positions.size()-1)+1;
    int right =  (rand() % (positions.size()-left)) + left;
    vector<int> newPath;
    newPath.push_back(1);
    // Take section from a then fill in b
    if(CROSSOVER == SLICECROSS){
        for(int i = left; i <= right; i++)
            newPath.push_back(a[i]);
        // Adds remaining city id's from vector b in order
        for (int i = 1; i < b.size()-1; i++) {
            int id = b[i];
            if (find(newPath.begin(), newPath.end(), id) == newPath.end()) {
                newPath.push_back(id);
            }
        }
    }
    // Alternate a and b
    else if(CROSSOVER == ALTERCROSS){
        int fI = 0;
        int sI = 0;
        for(int i = 1; i < a.size()-1; i++){
            if(i%2 == 1){
                while(find(newPath.begin(), newPath.end(), a[fI]) != newPath.end()) {
                    fI++;
                }
                newPath.push_back(a[fI]);
            }
            else{
                while (find(newPath.begin(), newPath.end(), b[sI]) != newPath.end()) {
                    sI++;
                }
                newPath.push_back(b[sI]);
            }
        }
    }
    newPath.push_back(1);

    return newPath;
}

void HamiltonianAlgorithms::mutate(vector<vector<double>>& positions, vector<int>& order){
    for(int i = 1; i < order.size()-1; i++){
        if((rand()/(double)RAND_MAX) < MUTATION_RATE){
            int left;
            int right;
            // Swap Adjacent
            if(MUTATION == ADJMUT){
                left = (rand() % (positions.size()-1)) + 1;
                right = left+1;
                if(right >= positions.size()){
                    right = left - 1;
                }
            }
            // Swap Random
            else if(MUTATION == RANMUT){
                left = rand() % (positions.size()-1) + 1;
                right = rand() % (positions.size()-1) + 1;
            }
            // Swaps two cities (muatation)
            swap(order, left, right);
        }
    }
}

void HamiltonianAlgorithms::swap(vector<int>& vect,int left,int right){
    int temp = vect[left];
    vect[left] = vect[right];
    vect[right] = temp;
}


vector<int> HamiltonianAlgorithms::createRanPath(int size, vector<int> list){
    vector<int> path;
    int curSize = size-1;
    for(int i = 0; i < size-1; i++){
        int index = (rand() % curSize) + 1;
        path.push_back(list[index]+1);
        list.erase(list.begin()+index);
        curSize--;
    }
    path.push_back(1);
    return path;
}


Path HamiltonianAlgorithms::simulatedAnnealing(vector<vector<double>>* pos){
    string output = "";
    vector<int> examplePath;
    for(int i = 0; i < pos->size(); i++){
        examplePath.push_back(i);
    }

    examplePath = createRanPath(pos->size(), examplePath);
    examplePath.insert(examplePath.begin(), 1);
    Path best;
    best.setPathAndLength(*pos, examplePath);

    double curDist = 0;
    double temp = TEMP;
    int left = 0;
    int right = 0;
    Path cur;
    int counter = 1;
    while (temp > 1) {
        cur = best;

        if(INDEX_PICKER == 0){
            left = (rand() % (pos->size() - 1)) + 1;
            right = (rand() % (pos->size() - 1)) + 1;
        }
        else if(INDEX_PICKER == 1) {
            left = (rand() % (pos->size() - 1)) + 1;
            right = left + 1;
            if (right >= pos->size()) {
                right = left - 1;
            }
        }
        cur.swap(left, right);
        curDist = cur.calculatePath(*pos);

        if(best.getLength() > curDist)
           best = cur;

        temp *= 1-COOLING_CONSTANT;

        output += to_string(counter) + ',' + to_string(best.getLength()) + '\n';
        counter++;
    }
    ofstream out("../Report/" + OUTPUT_SA, ios::trunc);
    output::printToFile(out, output);
    out.close();
    return best;
}



//
// Created by Colin Weil on 11/28/22.
//

#include "CreateGraphs.h"
#include <chrono>
#include <fstream>
#include <random>
using namespace std;

AdjacencyList CreateGraphs::CreateGraph(int V, int E, string G, string DIST){
    if(G == "COMPLETE"){
        return createComplete(V);
    }
    else if(G == "CYCLE"){
        return createCycle(V);
    }
    else{
        if(DIST == "UNIFORM"){
            return createRandomUniform(V,E);
        }
        else if(DIST == "TIERED"){
            return createRandomTiered(V,E);
        }
        else{
            return createRandomYours(V,E);
        }
    }
}

AdjacencyList CreateGraphs::createRandomUniform(int V, int E){
    AdjacencyList graph(V);
    for(int i = 0; i < E; i++){
        int x = rand() % V;
        int y = rand() % V;
        while(graph.adjList[x].connections.getSize() == V-1){
            x = rand() % V;
        }
        while(x == y || graph.adjList[x].connections.existsInList(y)){
            y = rand() % V;
        }
        graph.addEdge(x,y);
    }
    return graph;
}

int getTiered(int V){
    int x = rand() % (2 * (V/10 * 9));
    if(x < V/10 * 9) x = x % V/10;
    else x = (x - V/10 * 8);
    return x;
}
AdjacencyList CreateGraphs::createRandomTiered(int V, int E){
    AdjacencyList graph(V);
    for(int i = 0; i < E; i++){
        int x = getTiered(V);
        int y = getTiered(V);
        while(graph.adjList[x].connections.getSize() == V-1){
            x = getTiered(V);
        }
        while(x == y || graph.adjList[x].connections.existsInList(y)){
            y = getTiered(V);
        }
        graph.addEdge(x,y);
    }
    return graph;
}

int CreateGraphs::calculateNumberOfLinearDist(int v){
    int V = v-1;
    int count = ((V * (V+1))/2);
    int x = rand() % count;
    for(int j = V; j > 0; j--){
        count = count - j;
        if(count < x) return j-1;
    }
    return V;
}

AdjacencyList CreateGraphs::createRandomYours(int V, int E){
    AdjacencyList graph(V);
    for(int i = 0; i < E; i++){
        int x = calculateNumberOfLinearDist(V);
        int y = calculateNumberOfLinearDist(V);
        while(graph.adjList[x].connections.getSize() == V-1){
            x = calculateNumberOfLinearDist(V);
        }
        while(x == y || graph.adjList[x].connections.existsInList(y)){
            y = calculateNumberOfLinearDist(V);
        }
        graph.addEdge(x,y);
    }
    return graph;
}

AdjacencyList CreateGraphs::createComplete(int V){
    AdjacencyList graph(V);
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(i != j)
                graph.addSingleEdge(i, j);
        }
    }
    return graph;
}

AdjacencyList CreateGraphs::createCycle(int V){
    AdjacencyList graph(V);
    for(int i = 1; i < V; i++){
        graph.addEdge(i, i-1);
    }
    graph.addEdge(0, V-1);
    return graph;
}

void CreateGraphs::CycleAndCompleteGraphTimings(){
    ofstream output("../Timings/CycleAndCompleteGraphTimings.csv");
    output << "V" << "," << "Complete" << "," << "Cycle" << endl;

    for(int i = 1000; i <= 10000; i+=1000)
    {
        auto beginTime = chrono::high_resolution_clock::now();
        createComplete(i);
        auto endTime = chrono::high_resolution_clock::now();
        auto completeRunTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        createCycle(i);
        endTime = chrono::high_resolution_clock::now();
        auto cycleRunTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        output << i << "," << completeRunTime.count() << "," << cycleRunTime.count() << endl;
    }
    output.close();
}

void CreateGraphs::RandomGraphCreationTimings(){
    ofstream output("../Timings/RandomGraphCreationTimings.csv");
    output << "V" << "," << "E" << "," << "Uniform" << "," << "Tiered" << "," << "Linear" << endl;

    int E = 500;
    for(int i = 1000; i <= 10000; i+=1000)
    {
        auto beginTime = chrono::high_resolution_clock::now();
        createRandomUniform(i, E);
        auto endTime = chrono::high_resolution_clock::now();
        auto uniformRunTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        createRandomTiered(i, E);
        endTime = chrono::high_resolution_clock::now();
        auto tieredRunTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        createRandomYours(i, E);
        endTime = chrono::high_resolution_clock::now();
        auto linearRunTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        output << i << "," << E << "," << uniformRunTime.count() << ","
            << tieredRunTime.count() << "," << linearRunTime.count() << endl;
    }

    int V = 500;
    for(int i = 1000; i <= 10000; i+=1000)
    {
        auto beginTime = chrono::high_resolution_clock::now();
        createRandomUniform(V, i);
        auto endTime = chrono::high_resolution_clock::now();
        auto uniformRunTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        createRandomTiered(V, i);
        endTime = chrono::high_resolution_clock::now();
        auto tieredRunTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        createRandomYours(V, i);
        endTime = chrono::high_resolution_clock::now();
        auto linearRunTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        output << V << "," << i << "," << uniformRunTime.count() << ","
               << tieredRunTime.count() << "," << linearRunTime.count() << endl;
    }
    output.close();
}

AdjacencyList CreateGraphs::readFromFile(string filepath){
    ifstream file(filepath);

    int size;
    file >> size;
    int lineNumbers[size];
    for(int i = 0; i < size; i++){
        file >> lineNumbers[i];
    }

    AdjacencyList graph(size);
    for(int i = 0; i < size-1; i++){
        for(int j = lineNumbers[i]; j < lineNumbers[i+1]; j++){
            int dest;
            file >> dest;
            graph.addSingleEdge(i, dest-1);
        }
    }
    int dest;
    while(file >> dest)
        graph.addSingleEdge(size-1, dest-1);

    return graph;
}

void outputGraphConflict(AdjacencyList graph, string filename){
    ofstream output("../GraphConflicts/" + filename);
    output << "Vertex" << "," << "# of Conflicts" << endl;
    for(int i = 0; i < graph.getNumVertices(); i++){
        output << i+1 << "," << graph.adjList[i].size << endl;
    }
    output.close();
}

void CreateGraphs::OutputGraphConflicts(){
    int V = 50; int E = 100;
    AdjacencyList cycle = CreateGraph(V, E, "CYCLE", "NONE");
    AdjacencyList complete = CreateGraph(V, E, "COMPLETE", "NONE");
    AdjacencyList uniform = CreateGraph(V, E, "RANDOM", "UNIFORM");
    AdjacencyList tier = CreateGraph(V, E, "RANDOM", "TIERED");
    AdjacencyList linear = CreateGraph(V, E, "RANDOM", "LINEAR");
    outputGraphConflict(cycle, "cycle.csv");
    outputGraphConflict(complete, "complete.csv");
    outputGraphConflict(uniform, "uniform.csv");
    outputGraphConflict(tier, "tier.csv");
    outputGraphConflict(linear, "linear.csv");
}


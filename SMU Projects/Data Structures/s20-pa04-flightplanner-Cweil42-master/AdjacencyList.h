//
// Created by Colin Weil on 3/30/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_ADJACENCYLIST_H
#define S20_PA04_FLIGHTPLANNER_ADJACENCYLIST_H

#include "sourceCity.h"
#include "DSvector.h"
#include <fstream>
#include "DSstack.h"

class AdjacencyList{
private:
    LinkedList<sourceCity> flightMap;
    ListNode<sourceCity>* findStartCity(DSString);
    void addCity(char*, char* city, int cost, int time);
    sourceCity stackToSourceCity(DSstack<flightData>& stack, char* city);

public:
    AdjacencyList();
    void fillMap(ifstream& data);
    void printMap(ostream& out);
    DSvector<sourceCity> findPaths(char* start, char* dest);
};

#endif //S20_PA04_FLIGHTPLANNER_ADJACENCYLIST_H

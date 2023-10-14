//
// Created by Colin Weil on 3/30/20.
//

#include "AdjacencyList.h"

// Default constructor
AdjacencyList::AdjacencyList(){}

// Fills Adjacency List with flight map
void AdjacencyList::fillMap(ifstream &data){
    // Gets number from file
    char* line = new char [100];
    data.getline(line, 100, '\n');
    int num = atoi(line);

    // Add flight data into the AdjacencyList
    for(int i = 0; i < num; i++){
        char* city1 = new char [100];
        data.getline(city1, 100, '|');

        char* city2 = new char [100];
        data.getline(city2, 100, '|');

        data.getline(line, 100, '|');
        int cost = atoi(line);

        data.getline(line, 100, '\n');
        int time = atoi(line);

        addCity(city1, city2, cost, time);
        addCity(city2, city1, cost, time);

        delete[] city1;
        delete[] city2;
    }
    delete[] line;
}

// Adds city to Adjacency List
void AdjacencyList::addCity(char* fromCity, char* toCity, int cost, int time){
    ListNode<sourceCity>* mapLocation = findStartCity(fromCity);
    flightData cur(toCity, cost, time);
    if(mapLocation == nullptr){
        sourceCity cityNode(fromCity, toCity);
        cityNode.addDestinationToEnd(cur);
        flightMap.insertAtEnd(cityNode);
    }
    else{
        // inserts in function but mapLocation doesn't save
        mapLocation->getData().addDestinationToEnd(cur);
    }
}

// Returns pointer to listNode of source city in Link List
ListNode<sourceCity>* AdjacencyList::findStartCity(DSString city){
    ListNode<sourceCity>* cur = flightMap.getHead();
    while(cur != nullptr){
        if(cur->getData().getCity() == city){
            return cur;
        }
        cur = flightMap.getNext(cur);
    }
    return nullptr;
}

// Prints map
void AdjacencyList::printMap(ostream& out){
    ListNode<sourceCity>* cur = flightMap.getHead();
    while(cur != nullptr){
        cur->getData().print(out);
        out << endl;
        cur = flightMap.getNext(cur);
    }
}

// Finds all paths of a start and end city
DSvector<sourceCity> AdjacencyList::findPaths(char *start, char *dest) {
    DSvector<sourceCity> pathList;
    DSstack<flightData> paths;
    DSstack<sourceCity*> lists;

    if(findStartCity(start) == nullptr){
        sourceCity city(start, dest);
        pathList.push_back(city);
        return pathList;
    }
    sourceCity* curList = &findStartCity(start)->getData();
    lists.push(curList);

    // Push source to stack
    flightData beginning(start,0,0);
    paths.push(beginning);

    while(!paths.isEmpty()){
        if(paths.peek().getDest() == dest){
            //Store path
            sourceCity city = stackToSourceCity(paths, start);
            city.setDest(dest);
            pathList.push_back(city);
            // Pop
            paths.pop();
            lists.pop();
            curList = lists.peek();
        }
        else{
            if(curList->getDestinations()->getIter() == nullptr){
                //Pop stack.top
                paths.pop();
                lists.pop();
                // Reset iter
                curList->getDestinations()->iterReset();
                // Makes linked list looking at the one that is the top of the stack
                if(!lists.isEmpty())
                    curList = lists.peek();
            }
            else{
                if(paths.search(curList->getDestinations()->getIter()->getData()) == true){ //might need to make a == operator
                    // Move iter
                    curList->getDestinations()->iterNext();
                }
                else{
                    // Push connection
                    paths.push(curList->getDestinations()->getIter()->getData());
                    sourceCity* pastList = curList;
                    curList = &findStartCity(curList->getDestinations()->getIter()->getData().getDest())->getData();
                    lists.push(curList);

                    // Move iter
                    pastList->getDestinations()->iterNext();
                }
            }
        }
    }
    if(pathList.getSize()==0){
        sourceCity city(start, dest);
        pathList.push_back(city);
    }
    return pathList;
}

// Makes a stack of cities into a source City object
sourceCity AdjacencyList::stackToSourceCity(DSstack<flightData>& stack, char* start){
    DSstack<flightData> temp = stack;
    sourceCity city;
    city.setCity(start);
    while(!temp.isEmpty()){
        flightData tempFlight = temp.peek();
        city.addDestinationToFront(tempFlight);
        temp.pop();
    }
    city.removeFirstFlight();
    return city;
}



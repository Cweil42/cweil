//
// Created by Colin Weil on 4/1/20.
//

#include "requestedFlights.h"

// Default constructor
requestedFlights::requestedFlights(){}

// Copy constructor
requestedFlights::requestedFlights(const requestedFlights& rF){
    flights = rF.flights;
}

// Overloaded = operator
requestedFlights& requestedFlights::operator=(const requestedFlights& rF){
    flights = rF.flights;
    return *this;
}

// Adds best three flights of each request to private vector
void requestedFlights::requestFlights(ifstream& data, AdjacencyList& map){
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

        data.getline(line, 100, '\n');
        char type = line[0];

        DSvector<sourceCity> paths = map.findPaths(city1, city2);
        findBestPaths(paths, type);
        setTypes(type);

        delete[] city1;
        delete[] city2;
    }
    delete[] line;
}

// Takes best three paths and adds them to private vector
void requestedFlights::findBestPaths(DSvector<sourceCity>& paths, char type){
    DSvector<sourceCity> best;
    sortPaths(paths, type);
    if(paths.getSize() < 3){
        for(int i = 0; i < paths.getSize(); i++) {
            best.push_back(paths[i]);
        }
    }
    else{
        for(int i = 0; i < 3; i++) {
            best.push_back(paths[i]);
        }
    }
    flights.push_back(best);
}

// Takes vector of flights and sorts them by type
void requestedFlights::sortPaths(DSvector<sourceCity> &paths, char type){
    if(type == 'T'){
        int left = 0;
        int right = paths.getSize()-1;
        for (int i = left+1; i <= right; i++)
        {
            sourceCity key = paths[i];
            int j = i-1;
            while (j >= left && paths[j].getTime() > key.getTime())
            {
                paths[j+1] = paths[j];
                j = j-1;
            }
            paths[j+1] = key;
        }
    }
    else{
        int left = 0;
        int right = paths.getSize()-1;
        for (int i = left+1; i <= right; i++)
        {
            sourceCity key = paths[i];
            int j = i-1;
            while (j >= left && paths[j].getCost() > key.getCost())
            {
                paths[j+1] = paths[j];
                j = j-1;
            }
            paths[j+1] = key;
        }
    }
}

// Prints out all requested flights
void requestedFlights::printRequested(ostream& out){
    for(int i = 0; i < flights.getSize(); i++){
        out << "Flight " << (i+1) << ": " << flights[i][0].getCity() << ", ";
        out << flights[i][0].getDest();
        out << " (" << flights[i][0].getType() << ")" << endl;
        if(flights[i][0].getDestinations()->getSize() == 0){
            out << "No possible paths" << endl << endl;
        }
        else {
            for (int a = 0; a < flights[i].getSize(); a++) {
                out << "Path " << a + 1 << ": ";
                flights[i][a].print(out);
                out << ". Time: " << flights[i][a].getTime();
                out << " Cost: " << flights[i][a].getCost() << ".00" << endl;
            }
            out << endl;
        }
    }
}

// Sets source city to the type of flight request
void requestedFlights::setTypes(char t){
    DSString type;
    if(t == 'T')
        type = "Time";
    else
        type = "Cost";

    int i = flights.getSize()-1;
    for(int a = 0; a < flights[i].getSize(); a++){
        flights[i][a].setType(type);
    }
}
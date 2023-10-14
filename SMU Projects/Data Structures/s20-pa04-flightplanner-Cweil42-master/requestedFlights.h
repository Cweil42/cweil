//
// Created by Colin Weil on 4/1/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_REQUESTEDFLIGHTS_H
#define S20_PA04_FLIGHTPLANNER_REQUESTEDFLIGHTS_H

#include "AdjacencyList.h"
using namespace std;

class requestedFlights{
private:
    DSvector< DSvector<sourceCity>> flights;
    void findBestPaths(DSvector<sourceCity>& paths, char type);
    void sortPaths(DSvector<sourceCity>& paths, char type);
    void setTypes(char type);
public:
    requestedFlights();
    requestedFlights(const requestedFlights& flights);
    requestedFlights& operator=(const requestedFlights& vector);
    void requestFlights(ifstream& data, AdjacencyList& map);
    void printRequested(ostream& out);
};

#endif //S20_PA04_FLIGHTPLANNER_REQUESTEDFLIGHTS_H


//
// Created by Colin Weil on 3/31/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_SOURCECITY_H
#define S20_PA04_FLIGHTPLANNER_SOURCECITY_H

#include "LinkedList.h"
#include "flightData.h"

class sourceCity{
private:
    LinkedList<flightData> destinations;
    DSString city;
    DSString dest;
    int time;
    int cost;
    DSString type;
public:
    sourceCity();
    sourceCity(char* name);
    sourceCity(char* start, char* dest);
    sourceCity(const sourceCity &s);
    int getCost();
    int getTime();
    DSString getDest();
    void setDest(DSString d);
    void setCity(DSString c);
    sourceCity& operator=(const sourceCity& s);
    void addDestinationToEnd(flightData&);
    void addDestinationToFront(flightData&);
    LinkedList<flightData>* getDestinations();
    DSString getCity();
    void print(ostream& out);
    bool operator==(const sourceCity&) const;
    void removeFirstFlight();
    DSString getType();
    void setType(DSString&);
};

#endif //S20_PA04_FLIGHTPLANNER_SOURCECITY_H

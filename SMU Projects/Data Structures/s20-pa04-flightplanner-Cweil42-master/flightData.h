//
// Created by Colin Weil on 3/30/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_FLIGHTDATA_H
#define S20_PA04_FLIGHTPLANNER_FLIGHTDATA_H

#include "DSString.h"

class flightData{
private:
    int time;
    int cost;
    DSString dest;
public:
    flightData();
    flightData(char*, int, int);
    flightData(const flightData &d);
    int getTime();
    int getCost();
    DSString getDest();
    void setTime(int t);
    void setCost(int c);
    void setDest(DSString d);
    friend ostream& operator << (ostream &out, const flightData &d);
    flightData& operator=(const flightData& d);
    bool operator==(const flightData& d);
};
#endif //S20_PA04_FLIGHTPLANNER_FLIGHTDATA_H

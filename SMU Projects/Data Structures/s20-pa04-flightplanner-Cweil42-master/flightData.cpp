//
// Created by Colin Weil on 3/31/20.
//

#include "flightData.h"

// DefaultConstructor
flightData::flightData(){
    cost = 0;
    time = 0;
}

// Constructor with parameters of ints and char*
flightData::flightData(char* d, int c = 0, int t = 0){
    cost = c;
    time = t;
    dest = d;
}

// Copy constructor
flightData::flightData(const flightData &d){
    cost = d.cost;
    time = d.time;
    dest = d.dest;
}

// Getters and setters for private variables
int flightData::getTime() { return time; }
int flightData::getCost() { return cost; }
DSString flightData::getDest() { return dest; }
void flightData::setTime(int t) { time = t; }
void flightData::setCost(int c) { cost = c; }
void flightData::setDest(DSString d) { dest = d; }

// Prints data of flight Data
ostream& operator << (ostream &out, const flightData &d){
    out << d.dest;
    return out;
}

// Overloaded = operator
flightData& flightData::operator=(const flightData& d){
    cost = d.cost;
    time = d.time;
    dest = d.dest;
    return *this;
}

// Overloaded == operator
bool flightData::operator==(const flightData& d){
    return dest==d.dest;
}


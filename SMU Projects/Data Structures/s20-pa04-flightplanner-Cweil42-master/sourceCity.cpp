//
// Created by Colin Weil on 3/31/20.
//

#include "sourceCity.h"

// Default constructor
sourceCity::sourceCity(){
    cost = 0;
    time = 0;
}

// Constructor with char* parameter
sourceCity::sourceCity(char* name){
    city = name;
    cost = 0;
    time = 0;
}

// Constructor with two char* parameter
sourceCity::sourceCity(char* start, char* end){
    city = start;
    dest = end;
    cost = 0;
    time = 0;
}

// Getters for private variables
int sourceCity::getCost(){ return cost; }
int sourceCity::getTime(){ return time; }
DSString sourceCity::getCity(){ return city; }
DSString sourceCity::getDest(){ return dest; }
void sourceCity::setDest(DSString d){ dest = d; }

// Adds flight data to linked list of destinations
void sourceCity::addDestinationToEnd(flightData& d){
    destinations.insertAtEnd(d);
    time += d.getTime();
    cost += d.getCost();
}

// Adds a flight data to beginning of linked list
void sourceCity::addDestinationToFront(flightData& d){
    destinations.insertAtFront(d);
    time += d.getTime();
    cost += d.getCost();
}

// Returns linked list of destinations
LinkedList<flightData>* sourceCity::getDestinations(){
    return &destinations;
}

// Prints out source city and destinations
void sourceCity::print(ostream& out){
    out << city;
    destinations.print(out);
}

// Copy constructor
sourceCity::sourceCity(const sourceCity &s){
    destinations = s.destinations;
    city = s.city;
    time = s.time;
    cost = s.cost;
    dest = s.dest;
}

// Overloaded = operator
sourceCity& sourceCity::operator=(const sourceCity& s){
    destinations = s.destinations;
    city = s.city;
    time = s.time;
    cost = s.cost;
    dest = s.dest;
    return *this;
}

// Setter for city name
void sourceCity::setCity(DSString c){
    city = c;
}

// Overaloaded == operator
bool sourceCity::operator==(const sourceCity& c) const{
    return city == c.city;
}

// Removes first flight from destinations
void sourceCity::removeFirstFlight() {
    destinations.removeHead();
}

// Get and set for type of flight flight search
DSString sourceCity::getType(){ return type; }
void sourceCity::setType(DSString& s){ type = s; }

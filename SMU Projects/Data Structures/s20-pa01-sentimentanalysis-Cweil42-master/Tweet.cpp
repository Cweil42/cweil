//
// Created by Colin Weil on 2/6/20.
//
#include "Tweet.h"

Tweet::Tweet(){
    id = nullptr;
    positivity = 0;
}

Tweet::Tweet(char* id,int pos){
    this->id = id;
    positivity = pos;
}

// getters and setters for private variables
void Tweet::setID(char* num){id = num;}
char* Tweet::getID(){ return id;}
void Tweet::setPositivity(int pos) { positivity = pos; }
int Tweet::getPositivity(){ return positivity; }

ostream& operator<<(ostream &out, const Tweet &t){
    out << t.id;
    return out;
}

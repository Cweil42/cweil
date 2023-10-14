//
// Created by Colin Weil on 4/29/20.
//
#include "fileRank.h"

// Default Constructor
fileRank::fileRank(){
    queryCount = 0;
    totalWords = 0;
}

// Constructor with string parameter
fileRank::fileRank(string w){
    file = w;
    queryCount = 0;
    totalWords = 0;
}

// Getters and setters for private variables
void fileRank::setFile(string w){ file = w; }
string fileRank::getFile(){ return file; }
void fileRank::addCount(){ queryCount++; }
int fileRank::getCount(){ return queryCount; }
void fileRank::addTotal(){ totalWords++; }
int fileRank::getTotal(){ return totalWords; }

// Gets percentage of word that was in the file
double fileRank::getRatio() { return (double)queryCount/totalWords; }

// Overloaded comparison operators
bool fileRank::operator==(const fileRank& w) const{
    return ((double)queryCount/totalWords) == ((double)w.queryCount/w.totalWords);
}
bool fileRank::operator<(const fileRank& w) const{
    return ((double)queryCount/totalWords) < ((double)w.queryCount/w.totalWords);
}
bool fileRank::operator>(const fileRank& w) const{
    return ((double)queryCount/totalWords) > ((double)w.queryCount/w.totalWords);
}

//
// Created by Colin Weil on 2/1/20.
//
#include "Word.h"

// Default Constructor
Word::Word(){
    word = nullptr;
    positivity = 0;
}

// Constructor with DSString and int parameters
Word::Word(DSString* w, int t){
    word = w;
    positivity = t;
}

Word::~Word(){
}

// Get and Set methods for private variables
DSString& Word::getWord(){ return *word; }
void Word::setWord(DSString* w){ word = w; }
int Word::getPositivity(){ return positivity; }
void Word::setPositivity(int p){ positivity = p; }


//Adds or subtracts number of positivity to word
void Word::addPositivity(int pos){
   positivity += pos;
}

// Override Insertion Operator
ostream& operator<<(ostream &out, const Word &w){
    out << *w.word;
    return out;
}

//  Returns if word private variable is equal to DSString parameter
bool Word::isEqual(DSString* s){
    return (*s == *word);
}

// Set word values equal to another
Word Word::operator=(const Word w){
    word = new DSString(*w.word);
    positivity = w.positivity;
    return *this;
}

//
// Created by Colin Weil on 4/16/20.
//
#include "wordIndexes.h"
using namespace std;

// Default constructor
wordIndexes::wordIndexes(){ count = 0; }

// Constructor with word parameter
wordIndexes::wordIndexes(string w){ word = w; count = 1; }

// Constructor with word and file string parameters
wordIndexes::wordIndexes(string w, string file){
    word = w;
    count = 1;
    index.insert(file);
}

// Gete and set for word
void wordIndexes::setWord(string w){ word = w; }
string wordIndexes::getWord(){ return word; }

// Adds file name to file tree that contain word
void wordIndexes::addIndex(string i){ index.insert(i); }

// Get count and add to count
int wordIndexes::getCount(){ return count; }
void wordIndexes::addCount(){ count++; }
void wordIndexes::setCount(int n){ count = n; }


// Return AVLTree of indexes
AVLTree<string>* wordIndexes::getIndexes(){ return &index;}

// Overloaded ==,<,> operators that compares words
bool wordIndexes::operator==(const wordIndexes& w){
    return word==w.word;
}
bool wordIndexes::operator<(const wordIndexes& w){
    return word<w.word;
}
bool wordIndexes::operator>(const wordIndexes& w){
    return word>w.word;
}

// << operator
ostream& operator << (ostream &out, wordIndexes& w){
    out << w.getWord() << "," << w.getCount();
    w.printIndexes(out);
    out << endl;
    return out;
}

// Compares the count of wordIndexes
bool wordIndexes::compare(const wordIndexes& one, const wordIndexes& two){
    return one.count < two.count;
}

// Prints AVLTree of index strings
void wordIndexes::printIndexes(ostream& out){
    index.toTextFile(out);
}

// Copy constructor
wordIndexes::wordIndexes(const wordIndexes& w){
    word = w.word;
    count = w.count;
    index = w.index;
}

// Overloaded = operator
wordIndexes& wordIndexes::operator=(const wordIndexes& w){
    word = w.word;
    count = w.count;
    index = w.index;
    return *this;
}
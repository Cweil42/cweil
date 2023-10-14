//
// Created by Colin Weil on 4/16/20.
//

#ifndef SEARCHENGINE_WORDINDEXES_H
#define SEARCHENGINE_WORDINDEXES_H
#include <string>
#include "AVLTree.h"
#include "iostream"
using namespace std;

class wordIndexes{
private:
    string word;
    AVLTree<string> index;
    int count;
public:
    wordIndexes();
    wordIndexes(string w);
    wordIndexes(string w, string file);
    void setWord(string w);
    string getWord();
    void addIndex(string i);
    int getCount();
    void addCount();
    void setCount(int n);
    AVLTree<string>* getIndexes();
    bool operator==(const wordIndexes& w);
    bool operator<(const wordIndexes& w);
    bool operator>(const wordIndexes& w);
    friend ostream& operator << (ostream &out, wordIndexes &w);
    bool compare(const wordIndexes& one, const wordIndexes& two);
    void printIndexes(ostream& out);
    wordIndexes(const wordIndexes& w);
    wordIndexes& operator=(const wordIndexes& w);
};
#endif //SEARCHENGINE_WORDINDEXES_H

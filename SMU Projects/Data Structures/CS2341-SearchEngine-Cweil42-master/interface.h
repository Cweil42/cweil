//
// Created by Colin Weil on 4/22/20.
//

#ifndef SEARCHENGINE_INTERFACE_H
#define SEARCHENGINE_INTERFACE_H
#include "Processor.h"
#include <iostream>

class interface{
private:
    Processor processor;
    string pathToFiles;
public:
    interface(string path);
    void clearIndex();
    void parseIndex();
    bool boolQuery();
    int numArticles();
    int avgWordPerArticle();
    int numWords();
    int numAuthors();
    void printFreqWords();
    void openPersistenceFile(ifstream& in);
    void createPersistenceFile(ostream& out);
    bool print300WordsOfArticle(int n);
    void printAllWords();
    bool hasParsed();
    int getQuerySize();
};

#endif //SEARCHENGINE_INTERFACE_H

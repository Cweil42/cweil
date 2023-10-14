//
// Created by Colin Weil on 4/22/20.
//

#ifndef SEARCHENGINE_PROCESSOR_H
#define SEARCHENGINE_PROCESSOR_H
#include "Parser.h"

class Processor{
private:
    void relevancyRank(string words);
    vector<string> query;
    Parser index;

    void boolAND(vector<string>* word);
    void boolOR(vector<string>* word);
    void boolNOT(vector<string>* word);
    void printArticleInfo(string name);
public:
    Processor();
    void parseIndex(string index);
    void clearIndex();
    Parser* getIndex();
    void boolQuery(char* arg);
    bool printQuery();
    string getQueryIndex(int n);
    bool hasParsed();
    int getQuerySize();
    int getNumAuthors();
};
#endif //SEARCHENGINE_PROCESSOR_H

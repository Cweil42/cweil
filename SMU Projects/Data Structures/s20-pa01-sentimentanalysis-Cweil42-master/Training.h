//
// Created by Colin Weil on 2/1/20.
//

#ifndef S20_PA01_SENTIMENTANALYSIS_TRAINING_H
#define S20_PA01_SENTIMENTANALYSIS_TRAINING_H

#include "Word.h"
#include <vector>
#include <fstream>
#include <sstream>

class Training{
private:
    vector<Word> database;
    vector<DSString> stopWords;
public:
    Training();
    ~Training();
    void fillDatabase(ifstream& data, ifstream& target);
    void print();
    int search(DSString*);
    vector<Word> getDatabase();
    bool stopWordChecker(DSString*);
    void fillStopWord(ifstream& data);
};
#endif //S20_PA01_SENTIMENTANALYSIS_TRAINING_H

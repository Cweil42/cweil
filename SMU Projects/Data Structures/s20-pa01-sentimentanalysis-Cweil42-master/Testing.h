//
// Created by Colin Weil on 2/6/20.
//

#ifndef S20_PA01_SENTIMENTANALYSIS_TESTING_H
#define S20_PA01_SENTIMENTANALYSIS_TESTING_H

#include "Training.h"
#include "Tweet.h"
#include <vector>
#include <fstream>
#include <sstream>

class Testing{
private:
    vector<Tweet> incorrect;
    float percent;
public:
    Testing();
    ~Testing();
    void checkFile(ifstream& data, ifstream& target, Training& database);
    void print();
    void printOut(ofstream& file);
};

#endif //S20_PA01_SENTIMENTANALYSIS_TESTING_H

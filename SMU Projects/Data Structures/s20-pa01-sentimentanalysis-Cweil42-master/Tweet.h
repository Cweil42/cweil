//
// Created by Colin Weil on 2/6/20.
//
#ifndef S20_PA01_SENTIMENTANALYSIS_TWEET_H
#define S20_PA01_SENTIMENTANALYSIS_TWEET_H

#include "Word.h"

class  Tweet{
private:
    char* id;
    int positivity;
public:
    Tweet();
    Tweet(char*,int);
    void setID(char*);
    char* getID();
    void setPositivity(int);
    int getPositivity();
    friend ostream& operator<<(ostream &out, const Tweet &w);
};
#endif //S20_PA01_SENTIMENTANALYSIS_TWEET_H

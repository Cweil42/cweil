//
// Created by Colin Weil on 2/1/20.
//

#ifndef S20_PA01_SENTIMENTANALYSIS_WORD_H
#define S20_PA01_SENTIMENTANALYSIS_WORD_H

#include "DSString.h"

class Word{
private:
    DSString* word;
    int positivity;
public:
    Word();
    Word(DSString*, int);
    ~Word();
    bool isEqual(DSString*);
    DSString& getWord();
    int getType();
    void setWord(DSString*);
    void setPositivity(int);
    int getPositivity();
    void addPositivity(int pos);
    Word operator=(const Word w);
    friend ostream& operator<<(ostream &out, const Word &w);
};



#endif //S20_PA01_SENTIMENTANALYSIS_WORD_H

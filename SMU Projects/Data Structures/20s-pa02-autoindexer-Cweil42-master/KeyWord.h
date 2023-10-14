//
// Created by Colin Weil on 2/17/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_KEYWORD_H
#define INC_20S_PA02_AUTOINDEXER_KEYWORD_H

#include "DSString.h"
#include "DSvector.h"

class KeyWord{
private:
    DSString word;
    DSvector<int> pages;
public:
    KeyWord();
    KeyWord(DSString);
    DSString getWord();
    void setWord(DSString);
    void addPage(int);
    void printKeyWord();
    bool operator>(const KeyWord& s) const;
    void printToOutfile(ostream& out);
};

#endif //INC_20S_PA02_AUTOINDEXER_KEYWORD_H

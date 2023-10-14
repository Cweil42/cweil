//
// Created by Colin Weil on 2/17/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_INDEXER_H
#define INC_20S_PA02_AUTOINDEXER_INDEXER_H

#include "KeyWord.h"

class Indexer{
private:
    DSvector<KeyWord> keywords;
    int getPageNum();
public:
    Indexer();
    void fillKeywords(ifstream& file);
    void findWords(ifstream& file);
    void printIndex();
    void printToOutfile(ostream& out);
    bool checkWordInPage(DSString& page, const DSString& w);
};

#endif //INC_20S_PA02_AUTOINDEXER_INDEXER_H

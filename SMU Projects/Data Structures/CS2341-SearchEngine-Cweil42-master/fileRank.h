//
// Created by Colin Weil on 4/29/20.
//

#ifndef SEARCHENGINE_FILERANK_H
#define SEARCHENGINE_FILERANK_H
#include <iostream>
using namespace std;

class fileRank{
private:
    string file;
    int queryCount;
    int totalWords;
public:
    fileRank();
    fileRank(string w);
    void setFile(string w);
    string getFile();
    void addCount();
    int getCount();
    void addTotal();
    int getTotal();
    double getRatio();
    bool operator==(const fileRank& w) const;
    bool operator<(const fileRank& w) const;
    bool operator>(const fileRank& w) const;
};

#endif //SEARCHENGINE_FILERANK_H

//
// Created by Colin Weil on 1/29/20.
//

#ifndef UNTITLED_DSSTRING_H
#define UNTITLED_DSSTRING_H

#include <iostream>
#include <cstring>
using namespace std;

class DSString{
private:
    char* data;
    int length;
public:
    DSString();
    DSString(char*);
    ~DSString();
    char* getData();
    int getLength();
    DSString& operator=(const DSString&);
    DSString& operator=(const char*);
    bool operator==(const DSString&) const;
    bool operator==(const char*) const;
    bool operator!=(const DSString&) const;
    bool operator>(const DSString& s) const;
    bool operator<(const DSString& s) const;
    char operator[](int);
    DSString operator+(const DSString& rhs);
    DSString& operator+=(const DSString & rhs);
    friend ostream& operator<<(ostream &out, const DSString &s);
    DSString substring(int, int);
    char* c_str();
    void setDataCSV(char*, int);
    DSString(const DSString &string);
};


#endif //UNTITLED_DSSTRING_H

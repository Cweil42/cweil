//
// Created by Colin Weil on 1/29/20.
//
#include <cstring>
#include <iostream>
#include "DSString.h"

// Default Constructor
DSString::DSString(){
    data = nullptr;
    length = 0;
}

// Constructor with char* parameter
DSString::DSString(const char* word){
    length = strlen(word);
    data = new char[length+1];
    strcpy(data, word);
}

// Destructor
DSString::~DSString(){
    if(data != nullptr)
        delete[] data;
}

// Returns Data of DSString
char* DSString::getData(){
    return data;
}

// Returns Length of DSString
int DSString::getLength() const {
    return length;
}

// Sets DSString to have same value as another
DSString& DSString::operator=(const DSString& s){
    if(data != nullptr)
        delete[] data;
    length = s.length;
    data = new char[length+1];
    strcpy(data, s.data);
    return *this;
}

// Sets data to a char* and update the length
DSString& DSString::operator=(const char* s){
    if(data != nullptr) {
        delete[] data;
    }
    length = strlen(s);
    data = new char[length+1];
    strcpy(data, s);
    return *this;
}

// Test if two DSString are equal
bool DSString::operator==(const char* s) const{
    if(strcmp(data, s) == 0)
        return true;
    else
        return false;
}

// Test if two DSString are equal
bool DSString::operator==(const DSString& s) const{
    if(strcmp(data, s.data) == 0)
        return true;
    else
        return false;
}


// Test if greater than
bool DSString::operator>(const DSString& s) const{
    if(strcmp(data, s.data) > 0)
        return true;
    else
        return false;
}

// Test if less than
bool DSString::operator<(const DSString& s) const{
    if(strcmp(data, s.data) < 0)
        return true;
    else
        return false;
}

// Test if two DSString are not equal
bool DSString::operator!=(const DSString& s) const{
    if(strcmp(data, s.data) == 0)
        return false;
    else
        return true;
}

char DSString::operator[](int index){
   return *(data+index);
}

// Combines two DSStrings together
DSString DSString::operator+(const DSString& rhs){
    char* temp = new char[strlen(data) +strlen(rhs.data)+1];
    int i = 0;
    strcpy(temp,data);
    strcat(temp, rhs.data);
    DSString temp2(temp);
    delete[] temp;
    return temp2;
}

// Adds a DSString onto the end of an already existing DSString
DSString& DSString::operator+=(const DSString& rhs){
    length += rhs.length;
    DSString temp = *this;
    if(data != nullptr) {
        delete[] data;
    }
    strcat(temp.data, rhs.data);
    data = temp.data;
    return *this;
}

// Prints data of DSString
ostream& operator << (ostream &out, const DSString &s){
    if(s.data[0] == ' '){
        out << s.data+1;
    }
    else{
        out << s.data;
    }
    return out;
}

DSString DSString::substring(int start, int end){
    char* temp = new char[abs(end-start)+2];
    for(int i = start; i < end+start; i++){
        temp[i-start] = data[i];
    }
    temp[end] = '\0';
    DSString sub(temp);
    delete[] temp;
    return sub;
}

char* DSString::c_str(){
    return data;
}

DSString::DSString(const DSString &string) {
    length = string.length;
    data = new char[length+1];
    strcpy(data, string.data);
}

int DSString::search(const DSString& s){
    if(substring(0, s.getLength())==s){
        return 0;
    }
    for(int i = 1; i < length-s.length+1; i++){
        if(substring(i, s.getLength())==s){
            return i;
        }
    }
    return -1;
}

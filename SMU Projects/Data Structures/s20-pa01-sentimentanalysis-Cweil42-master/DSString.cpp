//
// Created by Colin Weil on 1/29/20.
//
#include <cstring>
#include <iostream>
#include "DSString.h"

// Default Constructor
DSString::DSString(){
    data = new char;
    length = 0;
}

// Constructor with char* parameter
DSString::DSString(char* word){
    length = strlen(word);
    data = new char[length+1];
    strcpy(data, word);
    length = strlen(data);
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
int DSString::getLength() {
    return length;
}

// Sets DSString to have same value as another
DSString& DSString::operator=(const DSString& s){
    if(data != nullptr)
        delete[] data;
    length = strlen(s.data);
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
    data = new char[length];
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
    if(strcmp(data, s.data) == 0)
        return false;
    else
        return true;
}

// Test if less than
bool DSString::operator<(const DSString& s) const{
    if(strcmp(data, s.data) == 0)
        return false;
    else
        return true;
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
    length = strlen(data) + strlen(rhs.data)+1;
    char* temp = data;
    data = new char[length+1];
    for(int i = 0; i < strlen(temp); i++){
        data[i] = temp[i];
    }
    strcat(data, rhs.data);
    delete[] temp;
    return *this;
}

// Prints data of DSString
ostream& operator << (ostream &out, const DSString &s){
    out << s.data;
    return out;
}

DSString DSString::substring(int start, int end){
    char* temp = new char[end-start+1];
    for(int i = start; i <= end; i++){
        temp[i-start] = data[i];
        cout << temp[i-start] << " " << data[i] << endl;
    }
    temp[end] = '\0';
    cout << temp << endl;
    DSString sub(temp);
    delete[] temp;
    return sub;
}

char* DSString::c_str(){
    return data;
}

// Returns DSString of a column in CSV line
void DSString::setDataCSV(char* line, int col){
    if(data != nullptr) {
        delete[] data;
        data = new char;
    }
    int index = 0;
    for(int i = 0; i < col-1; i++) {
        int a = index;
        if(line[a] == '\0'){
            return;
        }
        while (line[a] != ',') {
            index++;
            a++;
        }
        index++;
    }
    int i = 0;
    while (line[index] != ',' && line[index] != '\n') {
        data[i] = line[index];
        i++;
        index++;
    }
    data[i] = '\0';
}

DSString::DSString(const DSString &string) {
    length = string.length;
    data = new char;
    strcpy(data, string.data);
}


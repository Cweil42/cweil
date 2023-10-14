//
// Created by Colin Weil on 2/1/20.
//
#include "Training.h"
#include <cctype>

// Default Constructor
Training::Training(){}

Training::~Training(){}

//Takes data from csv file and makes directory of words and if they are positive or negative affiliation
void Training::fillDatabase(ifstream& data, ifstream& target){
    int num;
    data.ignore(350, '\n');
    target.ignore(50, '\n');

    //while(!data.eof()) {
    for(int i = 0; i <  50000;   i++) {
        char *line = new char[700];
        char *positivity = new char[1];
        target.ignore(10, ',');
        target.getline(positivity, 5, ',');
        int num = positivity[0] - 48;
        if (num == 0) {
            num = -1;
        } else {
            num = 1;
        }
        target.ignore(11, '\n');

        data.ignore(6, ',');
        data.ignore(11, ',');
        data.ignore(16, ',');
        data.getline(line, 700, '\n');

        // Removing non ASCII characters from https://www.codespeedy.com/deletion-of-any-non-ascii-characters-present-in-cpp/
        char* modifiedline = new char[strlen(line)+1];
        int a=-1;
        int b=-1;
        while(line[++a]!='\0'){
            if(!(line[a]>=0 && line[a]<=127))continue;
            else modifiedline[++b]=line[a];
        }
        modifiedline[++b]='\0';

        stringstream iss;
        iss << modifiedline;
        char *cur = new char[700];

        while (iss >> cur) {
            // To lowercase function
            for(int i = 0; i < strlen(cur); i++){
                cur[i] = tolower(cur[i]);
            }
            DSString* curWord = new DSString(cur);
            // Returns  true if not a stop word
            if(stopWordChecker(curWord)){
                if(stopWordChecker(curWord)){
                    if(curWord->getLength() < 10 ){
                        int index = search(curWord);
                        if (index == -1) {
                            Word word(curWord, num);
                            database.push_back(word);
                        } else {
                            database[index].addPositivity(num);
                        }
                    }
                }
            }
        }
        delete[] line;
        delete[] positivity;
        delete[] cur;
        delete[] modifiedline;
    }
}

// Prints vector of words
void Training::print(){
    for(int i = 0; i < database.size()-1; i++){
        cout << database[i] << ' ' << database[i].getPositivity() << endl;
    }
}

// Searches for word and returns index
int Training::search(DSString* s){
    int index = -1;
    for(int i = 0; i < database.size(); i++){
        if(database[i].getWord() == *s){
            index = i;
            return index;
        }
    }
    return index;
}

// Returns the vector of words
vector<Word> Training::getDatabase(){
    return database;
}

// Returns if word is a stop word
bool Training::stopWordChecker(DSString* w) {
    for (int i = 0; i < stopWords.size(); i++) {
        if (stopWords[i] == *w) {
            return false;
        }
    }
    return true;
}

// Fills stop word vector
void Training::fillStopWord(ifstream& stop){
    char* line = new char[200];
    while(stop >> line){
        DSString word(line);
        stopWords.push_back(word);
    }
    delete[] line;
}

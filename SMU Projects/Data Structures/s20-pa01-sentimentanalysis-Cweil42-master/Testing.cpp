//
// Created by Colin Weil on 2/6/20.
//
#include "Testing.h"
#include <iomanip>

Testing::Testing(){
    percent = 0;
}

Testing::~Testing(){}

void Testing::checkFile(ifstream& data, ifstream& target, Training& database){
    data.ignore(5, '\n');
    target.ignore(300, '\n');
    int numTweets = 0;
    double numWrong = 0;
    //while(!data.eof()) {
    for(int i = 0; i < 10000; i++) {
        Tweet tweet;
        numTweets++;
        char* line = new char[300];
        data.getline(line, 6, ',');
        data.getline(line, 11, ',');
        data.getline(line, 20, ',');
        data.getline(line, 300, '\n');
        stringstream iss;
        iss << line;
        char* cur = new char[300];
        DSString* curWord;
        int sentencePositivity = 0;
        while(iss >> cur){
            curWord = new DSString(cur);
            int index = database.search(curWord);
            if(index != -1) {
                int wordPos = database.getDatabase()[index].getPositivity();
                if(wordPos>-1){
                    sentencePositivity++;
                }else if (wordPos< 0){
                    sentencePositivity--;
                }
            }
        }
        if(sentencePositivity>0){
            tweet.setPositivity(0);
        }
        else{
            tweet.setPositivity(4);
        }
        char* idNum = new char [12];
        char* positivity = new char[1];
        target.ignore(5, ',');
        target.getline(positivity, 5, ',');
        target.getline(idNum, 15, '\n');
        tweet.setID(idNum);
        if (positivity[0] - 48 != tweet.getPositivity()) {
            incorrect.push_back(tweet);
            numWrong++;
        }
    }
    percent = (numTweets-numWrong)/numTweets;
}

void Testing::print(){
    cout << percent << endl;
    for(int i = 0; i < incorrect.size(); i++){
        cout << incorrect[i].getID() << endl;
    }
}

void Testing::printOut(ofstream& file){
    file << setprecision(3) << percent << endl;
    for(int i = 0; i < incorrect.size(); i++){
        file << incorrect[i].getID() << endl;
    }
}
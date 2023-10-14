//
// Created by Colin Weil on 2/17/20.
//

#include "KeyWord.h"

// KeyWord Default Constructor
KeyWord::KeyWord(){}

// KeyWord Constructor with DSString parameter
KeyWord::KeyWord(DSString w){
    word = w;
}

// Word Getter and Setter
DSString KeyWord::getWord(){ return word; }
void KeyWord::setWord(DSString w){ word = w; }

// Add page number to vector of page numbers
void KeyWord::addPage(int p){
    pages.push_back(p);
}

// Print word and list of page numbers
void KeyWord::printKeyWord(){
    cout << word <<  ": ";
    if(pages.getSize()>0){
        cout << pages[0];
        for(int i = 1; i < pages.getSize(); i++){
            cout << ", " << pages[i];
        }
    }
    cout << endl;
}

// Print word and list of page numbers to outfile
void KeyWord::printToOutfile(ostream& out){
    int newLineChecker = 0;
    out << word << ": ";
    newLineChecker += word.getLength() + 2;
    if(pages.getSize()>0){
        out << pages[0];
        for(int i = 1; i <pages.getSize(); i++){
            newLineChecker += to_string(pages[i]).length() + 2;
            if (newLineChecker>79)
            {
                cout << "," << endl;
                out << "    " << pages[i];
                newLineChecker = 5;
            }else
                out << ", " << pages[i];
        }
    }
    out << endl;
}

// Test if a word is greater than another
bool KeyWord::operator>(const KeyWord& s) const{
    if(word > s.word) {
        return true;
    }
    else{
        return false;
    }
}
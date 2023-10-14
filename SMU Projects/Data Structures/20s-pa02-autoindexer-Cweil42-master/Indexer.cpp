//
// Created by Colin Weil on 2/17/20.
//

#include "Indexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Indexer Constructor
Indexer::Indexer(){}

// Fills vector with KeyWords read in from file
void Indexer::fillKeywords(ifstream& file){
    char* line = new char[100];
    while(file.getline(line,100, '\n')){
        // To lowercase function
        char* modifiedline = new char[strlen(line)+1];
        int a=-1;
        int b=-1;
        while(line[++a]!='\0'){
            if(((line[a]>=48 && line[a]<=57) || (line[a]>=65 && line[a]<=90) || (line[a]>=97 && line[a]<=122) || line[a]==32) && line[a] != '\n')
                modifiedline[++b]= tolower(line[a]);
        }
        modifiedline[++b]='\0';
        DSString cur(modifiedline);
        KeyWord key(cur);
        keywords.push_back(key);
    }
    delete[] line;
    keywords.sort();
}

// Finds KeyWords in file then adds page number where Keyword appears
void Indexer::findWords(ifstream &file){
    char* line = new char[100];
    char* space = new char[2];
    space[0] = ' ';
    space[1] = '\0';

    //Get Initial Page Number
    int pageNum;
    file.getline(line,100, '\n');
    while(line[0] != '<'){
        file.getline(line,100, '\n');
    }
    char* page = new char[5];
    int i = 1;
    while(line[i] != '>'){
        page[i-1] = line[i];
        i++;
    }
    page[i] = '\n';
    pageNum = atoi(page);
    delete[] page;

    // Get first line after page number in file
    file.getline(line,100, '\n');
    char* modifiedline = new char[strlen(line)+1];
    int a=-1;
    int b=-1;
    while(line[++a]!='\0'){
        if(((line[a]>=48 && line[a]<=57) || (line[a]>=65 && line[a]<=90) || (line[a]>=97 && line[a]<=122) || line[a]==32) && line[a] != '\n')
            modifiedline[++b]= tolower(line[a]);
    }
    modifiedline[++b]='\0';
    DSString pageText(modifiedline);
    delete[] modifiedline;

    while(file.getline(line,100, '\n')){
        // Check to see change of page
        if(line[0] == '<'){
            for(int i = 0; i < keywords.getSize(); i++){
                if(checkWordInPage(pageText, keywords[i].getWord())){
                    keywords[i].addPage(pageNum);
                }
            }

            // Get new Page Num
            char* page = new char[5];
            int i = 1;
            while(line[i] != '>'){
                page[i-1] = line[i];
                i++;
            }
            page[i] = '\n';
            pageNum = atoi(page);
            delete[] page;

            file.getline(line,100, '\n');
            char* modifiedline = new char[strlen(line)+1];
            int a=-1;
            int b=-1;
            while(line[++a]!='\0'){
                if((line[a]>=48 && line[a]<=57) || (line[a]>=65 && line[a]<=90) || (line[a]>=97 && line[a]<=122) || line[a]==32)
                    modifiedline[++b]= tolower(line[a]);
            }
            modifiedline[++b]='\0';
            pageText = modifiedline;
            delete[] modifiedline;
        }
        else{
            // lower case and get rid of punctuation
            char* modifiedline = new char[strlen(line)+1];
            int a=-1;
            int b=-1;
            while(line[++a]!='\0'){
                if(((line[a]>=48 && line[a]<=57) || (line[a]>=65 && line[a]<=90) || (line[a]>=97 && line[a]<=122) || line[a]==32) && line[a] != '\n')
                    modifiedline[++b]= tolower(line[a]);
            }
            modifiedline[++b]='\0';

            DSString temp(modifiedline);
            delete[] modifiedline;
            pageText = pageText + space;
            pageText = pageText + temp;
        }
    }
    delete[] line;
    delete[] space;
}

// Prints Index
void Indexer::printIndex(){
    char cur = ' ';
    for(int i = 0; i < keywords.getSize(); i++){
        if(toupper(keywords[i].getWord()[0]) != cur){
            cur = toupper(keywords[i].getWord()[0]);
            cout << "[" << cur << "]" << endl;
        }
        keywords[i].printKeyWord();
    }
}

// Prints Index to Outfile
void Indexer::printToOutfile(ostream& out){
    char cur = ' ';
    for(int i = 0; i < keywords.getSize(); i++){
        if(toupper(keywords[i].getWord()[0]) != cur){
            cur = toupper(keywords[i].getWord()[0]);
            out << "[" << cur << "]" << endl;
        }
        keywords[i].printToOutfile(out);
    }
}

// Returns true if KeyWord is found in page
bool Indexer::checkWordInPage(DSString& page, const DSString& w) {
    if(page.search(w) != -1){
        return true;
    }
    return false;
}

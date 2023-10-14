//
// Created by Colin Weil on 4/23/20.
//

#include "Processor.h"
#include <algorithm>
#include "fileRank.h"
#include "csv.hpp"

Processor::Processor(){}

// Ranks files based on relevancy rank
void Processor::relevancyRank(string words){
    vector<fileRank> rank;
    for(int i = 0; i < query.size(); i++){
        string pathToFile = "cs2341_data/" + query[i];
        ifstream in(pathToFile);
        nlohmann::json j;
        in >> j;
        in.close();

        fileRank cur(query[i]);
        // Gets the text and adds each word to indexer
        for(int i = 0; i < j["body_text"].size(); i++) {
            string s = j["body_text"][i]["text"].get<string>();
            char *text = new char[s.size() + 1];
            strcpy(text, s.c_str());

            char* split;
            split = strtok(text, " ,()");
            while (split != nullptr){
                string word = split;
                cur.addTotal();

                // Stem words
                Porter2Stemmer::trim(word);
                Porter2Stemmer::stem(word);

                size_t found = words.find(word);
                if (found!=std::string::npos){
                    cur.addCount();
                }

                split = strtok(nullptr, " ,()");
            }
            delete text;
        }
        rank.push_back(cur);
    }
    sort(rank.begin(), rank.end());
    query.clear();
    for(int i = rank.size()-1; i >= 0; i--){
        query.push_back(rank[i].getFile());
        if(i==rank.size()-15)
            return;
    }
}

// Fills query from an boolean arguement
void Processor::boolQuery(char* arg){
    char* split;
    string word;
    split = strtok(arg, " \n");
    string relRank;
    if(split == nullptr){
        return;
    }

    // Get initial boolean values
    if(strcmp(split, "AND") == 0){
        split = strtok(nullptr, " ");
        word = split;
        // Stem words
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        relRank = word;
        index.searchWord(word, query);
        split = strtok(nullptr, " ");
        while(split != nullptr && strcmp(split, "NOT") != 0 && strcmp(split, "AUTHOR") != 0) {
            vector<string> cur;
            word = split;
            // Stem words
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            relRank += " " + word;
            index.searchWord(word, cur);
            boolAND(&cur);
            split = strtok(nullptr, " ");
        }
    }
    else if(strcmp(split, "OR") == 0){
        split = strtok(nullptr, " ");
        word = split;
        // Stem words
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        relRank = word;
        index.searchWord(word, query);
        split = strtok(nullptr, " ");
        while(split != nullptr && strcmp(split, "NOT") != 0 && strcmp(split, "AUTHOR") != 0) {
            vector<string> cur;
            word = split;
            // Stem words
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            relRank += " " + word;
            index.searchWord(word, cur);
            boolOR(&cur);
            split = strtok(nullptr, " ");
        }
    }
    else{
        word = split;
        // Stem words
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        relRank = word;
        index.searchWord(word, query);
    }

    // Find values of NOT or AUTHOR
    split = strtok(nullptr, " ");
    if(split != nullptr && strcmp(split, "NOT") == 0){
        split = strtok(nullptr, " ");
        while(split != nullptr && strcmp(split, "NOT") != 0 && strcmp(split, "AUTHOR") != 0) {
            word = split;
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            vector<string> cur;
            index.searchWord(word, cur);
            boolNOT(&cur);
            split = strtok(nullptr, " ");
        }
    }
    if(split != nullptr && strcmp(split, "AUTHOR") == 0){
        split = strtok(nullptr, " ");
        while(split != nullptr) {
            vector<string> cur;
            hashNode<string, vector<string>>* node = index.searchAuthor(split);
            if(node != nullptr){
                cur = node->getData();
            }
            boolAND(&cur);
            split = strtok(nullptr, " ");
        }
    }
    relevancyRank(relRank);
}

// AND boolean for query and vector
void Processor::boolAND(vector<string>* word){
    for(int i = 0; i < query.size(); i++){
        vector<string>::iterator it = find(word->begin(), word->end(), query[i]);
        if (it == word->end()){
            query.erase(query.begin()+i);
            i--;
        }
    }
}

// OR boolean for query and vector
void Processor::boolOR(vector<string>* word){
    for(int i = 0; i < word->size(); i++){
        vector<string>::iterator it = find(query.begin(), query.end(), word->at(i));
        if (it == query.end()){
            query.push_back(word->at(i));
        }
    }
}

// NOT boolean for query and vector
void Processor::boolNOT(vector<string>* word){
    for(int i = 0; i < query.size(); i++){
        vector<string>::iterator it = find(query.begin(), query.end(), word->at(i));
        if (it != query.end()){
            query.erase(it);
        }
    }
}

// Parses index
void Processor::parseIndex(string loc){
    index.parseDirectory(loc);
}

// Clears index
void Processor::clearIndex(){ index.clear(); }

// Returns location of Parser object
Parser* Processor::getIndex(){ return &index; }

// Prints query of files
bool Processor::printQuery(){
    if(query.size()==0){
        cout << "No articles contain these parameters." << endl;
        return false;
    }
    else{
        cout << "Top Articles that contain these parameters: " << endl;
        for(int i = 0; i < query.size(); i++){
            cout << i+1 << ". ";
            printArticleInfo(query[i]);
            cout << endl;
        }
    }
    return true;
}

// Prints the title, author, publication, and date published of article
void Processor::printArticleInfo(string name){
    string path = "cs2341_data/metadata-cs2341.csv";
    ifstream meta(path);
    for(int i = 0; i < 5; i++){
        name.pop_back();
    }
    csv::CSVReader reader(path);
    csv::CSVRow row;
    for (auto& row: reader) {
        if(row["sha"].get<string>() ==  name) {
            cout << row["title"].get<string>() << endl;
            cout << "        Authors: " << row["authors"].get<string>() << endl;
            cout << "        Publish Date: " << row["publish_time"].get<string>() << endl;
            cout << "        Publication: " << row["journal"].get<string>() << endl;
            return;
        }
    }
}

// Returns value in query
string Processor::getQueryIndex(int n){
    return query[n-1];
}

// Sees if files have been parsed
bool Processor::hasParsed(){
    return index.hasParsed();
}

// Get query size
int Processor::getQuerySize(){
    return query.size();
}

// Gets number of authors
int Processor::getNumAuthors(){
    return index.getNumAuthors();
}

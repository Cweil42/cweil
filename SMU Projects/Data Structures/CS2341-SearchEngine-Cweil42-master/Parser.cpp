//
// Created by Colin Weil on 4/16/20.
//
#include "Parser.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
#include <ctime>

// Default constructor
Parser::Parser(){
    fillStopWords();
    numFiles = 0;
    numWords = 0;
}

// Parses through a file directory and populates tree
void Parser::parseDirectory(string path){
    const filesystem::path pathToShow{ path };
    for (const auto& entry : filesystem::directory_iterator(pathToShow)) {
        if(entry.path().extension() == ".json") {
            // Creates json object with text from file
            numFiles++;
            string fileName = entry.path().filename().string();
            ifstream in(path + "/" + fileName);
            nlohmann::json j;
            in >> j;
            in.close();

            // Gets the text and adds each word to indexer
            for(int i = 0; i < j["body_text"].size(); i++){
                string s = j["body_text"][i]["text"].get<string>();
                char* text = new char[s.size()+1];
                strcpy(text, s.c_str());
                addText(text, fileName);
                delete text;
            }

            // Gets the text and adds each word to author hashmap
            for(int i = 0; i < j["metadata"]["authors"].size(); i++){
                string s = j["metadata"]["authors"][i]["last"].get<string>();
                if(s == ""){
                    s = j["metadata"]["authors"][i]["first"].get<string>();
                }
                vector<string> vec;
                vec.push_back(fileName);
                hashNode<string, vector<string>>* cur = authors.insert(s, vec);
                if(cur != nullptr){
                    cur->getData().push_back(fileName);
                }
            }
        }
//        if(numFiles == 1000){
//            findTopWords();
//            return;
//        }
    }
    cout << "All Words Parsed." << endl;
    findTopWords();
    cout << "Tops words have been found." << endl;
}

void Parser::addText(char* text, string& path){
    char* split;
    if(text == "")
        return;
    split = strtok(text, " ,()");
    while (split != nullptr){
        string word = split;
        addWordToIndex(word, path);
        split = strtok(nullptr, " ,()");
    }
}

// Adds word to new Node if new and adds word to index if exists
void Parser::addWordToIndex(string& word, string& file){
    // Stem words
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    while(word[0] == '\'') {
        word.erase(0, 1);
    }
    while(word[word.size()-1] == '\'') {
        word.pop_back();
    }
    // Get rid of stop words and empty strings
    if(isStopWord(word) || word == ""){
        return;
    }

    wordIndexes curWord(word);
    TreeNode<wordIndexes>* node = words.search(curWord);
    if(node != nullptr){
        // Adds to indexes if it is not part of vector already
        AVLTree<string>* indexes = node->getData().getIndexes();
        TreeNode<string>* wordNode = indexes->search(file);
        if(wordNode != nullptr ){
            node->getData().addCount();
        }
        else{
            node->getData().addIndex(file);
            node->getData().addCount();
        }
    }
    else{
        wordIndexes cur(word,file);
        words.insert(cur);
        numWords++;
    }
}

// Returns if word is stop word or not
bool Parser::isStopWord(string& word){
    if(stopWords.search(word) != nullptr){
        return true;
    }
    return false;
}

// Creates AVLtree of stop words
void Parser::fillStopWords(){
    ifstream stop;
    stop.open("StopWords.txt");
    char *line = new char[50];
    while(stop.getline(line, 50, '\n')){
        string l = line;
        stopWords.insert(l);
    }
    delete[] line;
}

// Getters for private variables
int Parser::getNumFiles() { return numFiles; }
int Parser::getNumWords(){ return numWords; }

// Output for searched word
void Parser::printSearchWord(string word){
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    wordIndexes curWord(word);
    TreeNode<wordIndexes>* node = words.search(curWord);
    if(node == nullptr){
        cout << "No articles contain this word" << endl;
        return;
    }
    int size = node->getData().getIndexes()->getSize();
    cout << "Article Count that contain " << word << ": " << size << endl;
    cout << "Article File Names: " << endl;
    node->getData().getIndexes()->inorderTraversal();
}

// Searches for word in index and return a vector of file names that contain it
void Parser::searchWord(string word, vector<string>& files){
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    wordIndexes curWord(word);
    TreeNode<wordIndexes>* node = words.search(curWord);
    if(node == nullptr){
        return;
    }
    files = node->getData().getIndexes()->toVector();
}

// Prints all words in AVLTree
void Parser::printWords(){
    words.inorderTraversal();
}

// Clears parsed index
void Parser::clear(){
    words.clear();
    stopWords.clear();
    topWords.clear();
    authors.clear();
    numFiles = 0;
    numWords = 0;
}

bool compareNumWords(wordIndexes first, wordIndexes second){
    return first.getCount() < second.getCount();
}

// Returns a vector of the top 50 words
void Parser::findTopWords(){
    vector<wordIndexes> vec = words.toVector();
//    sort(wordIndexes.begin(), wordIndexes.end(), compareNumWords);
//    for (int i = wordIndexes.size() - 1; i > 0; i--){
//        topWords.push_back(wordIndexes[i]);
//        if(i == (wordIndexes.size() - 50)){
//                return;
//        }
//    }
    for(int i = 0; i < 50; i++){
        int index = 0;
        int high = 0;
        for(int a = 0; a < vec.size(); a++){
            if(vec[a].getCount() > high){
                index = a;
                high = vec[a].getCount();
            }
        }
        topWords.push_back(vec[index].getWord());
        vec.erase(vec.begin() + index);
    }
}

// Returns a vector of the top 50 words
void Parser::printTopWords(){
    for (int i = 0; i < topWords.size(); i++){
        cout << i+1 << ". " << topWords[i] << endl;
    }
}

// Prints index to a file
void Parser::indexToFile(ostream& out){
    words.toTextFile(out);
    out << ",+," << endl;
    authors.print(out);
    out << ",+," << endl;
    for(int i = 0; i < 50; i++){
        out << topWords[i] << endl;
    }
    out << numFiles << endl;
}

// Creates index from file
void Parser::readPersistence(ifstream& in) {
    char *line = new char[100];
    in.getline(line, 100, ',');
    in.getline(line, 100, ',');
    while(strcmp(line, "+") != 0){
        wordIndexes cur(line);
        in.getline(line, 100, ',');
        cur.setCount(atoi(line));
        in.getline(line, 100, ',');
        while(line[strlen(line)-1] != '\n'){
            cur.addIndex(line);
            in.getline(line, 100, ',');
        }
        string final = line;
        final.pop_back();
        cur.addIndex(final);
        words.insert(cur);
        numWords++;
        in.getline(line, 100, ',');
    }
    in.getline(line, 100, '\n');
    in.getline(line, 100, ',');
    in.getline(line, 100, ',');
    while(strcmp(line, "+") != 0){
        vector<string> vec;
        authors.insert(line, vec);
        hashNode<string, vector<string>>* node = authors.get(line);
        in.getline(line, 100, ',');
        while(line[strlen(line)-1] != '\n'){
            node->getData().push_back(line);
            in.getline(line, 100, ',');
        }
        string final = line;
        final.pop_back();
        node->getData().push_back(final);
        in.getline(line, 100, ',');
    }
    in.getline(line, 100, '\n');
    for(int i = 0; i < 50; i++){
        in.getline(line, 100, '\n');
        topWords.push_back(line);
    }
    in.getline(line, 100, '\n');
    numFiles = atoi(line);
    delete line;
}

// Returns if there is values in the AVLTree
bool Parser::hasParsed(){
    return !words.isEmpty();
}

// Gets number of authors
int Parser::getNumAuthors(){
    return authors.getSize();
}

hashNode<string, vector<string>>* Parser::searchAuthor(char* author){
    return authors.get(author);
}

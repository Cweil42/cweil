//
// Created by Colin Weil on 4/16/20.
//

#ifndef SEARCHENGINE_PARSER_H
#define SEARCHENGINE_PARSER_H
#include "AVLTree.h"
#include <filesystem>
#include <fstream>
#include "wordIndexes.h"
#include <vector>
#include "porter2_stemmer.h"
#include "json.hpp"
#include "hashMap.h"

class Parser{
private:
    int numFiles;
    int numWords;
    AVLTree<wordIndexes> words;
    AVLTree<string> stopWords;
    hashMap<string, vector<string>> authors;
    vector<string> topWords;
    bool isStopWord(string& word);
    void fillStopWords();
    void addText(char* text, string& path);
    void addWordToIndex(string& word, string& file);
    void findTopWords();
public:
    Parser();
    void parseDirectory(string path);
    void printWords();
    int getNumFiles();
    int getNumWords();
    void printSearchWord(string word);
    void searchWord(string word, vector<string>& files);
    void clear();
    void indexToFile(ostream& out);
    void printTopWords();
    void readPersistence(ifstream& in);
    bool hasParsed();
    int getNumAuthors();
    hashNode<string, vector<string>>* searchAuthor(char* author);
};
#endif //SEARCHENGINE_PARSER_H

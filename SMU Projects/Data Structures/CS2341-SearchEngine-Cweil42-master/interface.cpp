//
// Created by Colin Weil on 4/23/20.
//

#include "interface.h"

// Default constructor
interface::interface(string path){ pathToFiles = path; }

// Clears index of parser
void interface::clearIndex(){
    processor.clearIndex();
}

// Parse index
void interface::parseIndex(){
    processor.parseIndex(pathToFiles);
}

// Fills query with boolean query given
bool interface::boolQuery(){
    char* quer = new char[256];
    cin.ignore();
    cout << "Enter search query: " << endl;
    cin.getline(quer, 256);
    processor.boolQuery(quer);
    delete quer;
    return !processor.printQuery();
}

// Prints number of articles
int interface::numArticles(){
    cout << "Total number of articles parsed is " << processor.getIndex()->getNumFiles() << "." << endl;
}

// Prints average number of words per article
int interface::avgWordPerArticle(){
    double wpa = (double)processor.getIndex()->getNumWords()/processor.getIndex()->getNumFiles();
    cout << "The average number of words per article is " << wpa << "." << endl;
}

// Print num of total unique words parsed
int interface::numWords(){
    cout << "Total number of words parsed is " << processor.getIndex()->getNumWords() << "." << endl;
}

// Prints number of unique authors
int interface::numAuthors(){
    cout << "Total number of authors is " << processor.getNumAuthors() << "." << endl;
}

// Prints the 50 most frequent words
void interface::printFreqWords(){
    cout << "50 Most Frequent Words: " << endl;
    processor.getIndex()->printTopWords();
}

// Prints first 300 words of an article
bool interface::print300WordsOfArticle(int n){
    namespace fs = std::filesystem;
    const fs::path pathToShow{ pathToFiles };
    string path = pathToFiles + "/" + processor.getQueryIndex(n);
    // Creates json object with text from file
    ifstream in(path);
    if(!in.is_open()){
        cout << "File does not exist, try again." << endl;
        return false;
    }
    nlohmann::json j;
    in >> j;
    in.close();

    int wordCount = 0;
    for (int i = 0; i < j["body_text"].size() - 1; i++) {
        string s = j["body_text"][i]["text"].get<string>();
        char* text = new char[s.size()+1];
        strcpy(text, s.c_str());

        int lineCount = 0;
        char* sub = strtok(text, " ");
        while(lineCount < 120 && sub != nullptr){
            if(wordCount == 300) {
                cout << "..." << endl;
                return true;
            }
            wordCount++;
            lineCount += strlen(sub + 1);
            cout << sub << " ";
            if(lineCount >= 80){
                cout << endl;
                lineCount = 0;
            }
            sub = strtok(nullptr, " ");
        }
        delete text;
    }
    cout << "..." << endl;
    return true;
}

// Prints all words indexed
void interface::printAllWords(){
    processor.getIndex()->printWords();
}

// Opens a persistence file
void interface::openPersistenceFile(ifstream& in){
    processor.getIndex()->readPersistence(in);
}

// Creates a persistence file
void interface::createPersistenceFile(ostream& out){
    processor.getIndex()->indexToFile(out);
}

// Returns if index has been parsed
bool interface::hasParsed(){
    return processor.hasParsed();
}

int interface::getQuerySize(){
    return processor.getQuerySize();
}

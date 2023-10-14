#include <climits>
//
// Created by Colin Weil on 10/27/20.
//
#include "output.h"

output::output(){}

void output::closeFile(){
    outfile.close();
}

void output::chooseFilePath(string filepath){
    outfile.open(filepath, ios_base::app);
}

void output::printPath(Path& p){
    vector<int> path = *p.getPath();
    if(path.size() == 0){
        outfile << "Path is empty" << endl;
        return;
    }
    outfile << path[0];
    for(int i = 1; i < path.size(); i++){
        outfile << "->" << path[i];
    }
    outfile << endl;
}

void output::printToFile(string s) {
    outfile << s << endl;
}

void output::printToFile(ofstream& outfile, string s){
    outfile << s << endl;
}


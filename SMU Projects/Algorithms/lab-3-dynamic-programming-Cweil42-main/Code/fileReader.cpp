//
// Created by Colin Weil on 10/22/20.
//
#include "fileReader.h"
#include "fstream"
#include "math.h"

fileReader::fileReader(){}

void fileReader::readPositions(string filepath){
    string line;
    ifstream g(filepath);
    vector<int> x;
    vector<int> y;
    vector<int> z;
    for(int i = 0; i < 7; i++){
    //while(getline(g,line, ',')){
        getline(g,line, ',');
        getline(g,line, ',');
        x.push_back(stoi(line));
        getline(g,line, ',');
        y.push_back(stoi(line));
        getline(g,line);
        z.push_back(stoi(line));
    }
    for(int i = 0; i < x.size(); i++){
        vector<double> temp;
        for(int j = 0; j < y.size(); j++) {
            //double distance = abs(x[i] - x[j]) + abs(y[i] - y[j]) + abs(z[i] - z[j]);
            double distance = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2) + pow(z[i] - z[j], 2));
            temp.push_back(distance);
        }
        data.push_back(temp);
    }
}

double fileReader::getIndex(int row, int col){
    return data[row][col];
}

int fileReader::columnSize(){
    return data[0].size();
}

int fileReader::rowSize(){
    return data.size();
}

void fileReader::printData(){
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[0].size(); j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<double>>* fileReader::getData(){
    return &data;
}


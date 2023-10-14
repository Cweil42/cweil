//
// Created by Colin Weil on 10/4/20.
//

#include "AdjacencyMatrix.h"
#include <fstream>

AdjacencyMatrix::AdjacencyMatrix(){

}

void AdjacencyMatrix::addNode(int i, int j, Node& node){
    matrix[i][j] = node;
}

Node* AdjacencyMatrix::getNode(int i, int j){
    return &matrix[i][j];
}

void AdjacencyMatrix::loadData(string filepath, int size, vector<vector<double>> distances){
    for(int i = 0; i < size; i++){
        vector<Node> vect;
        for(int j = 0; j < size; j++){
            Node cur;
            cur.setWeight(0);
            cur.setDistance(distances[i][j]);
            if(j==i)
                cur.setId(i+1);
            vect.push_back(cur);
        }
        matrix.push_back(vect);
    }

    string line;
    ifstream w(filepath+"/weights.txt");
    while(getline(w, line, ',')){
        int i = stoi(line);
        getline(w, line, ',');
        int j = stoi(line);
        getline(w, line, '\n');
        double weight = stod(line);
        matrix[i-1][j-1].setWeight(weight);
        matrix[i-1][j-1].setId(j);
    }
    w.close();
}

void AdjacencyMatrix::printMatrix(){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j].getWeight() << ' ';
        }
        cout << endl;
    }
}

void AdjacencyMatrix::clear(){
    matrix.clear();
}

int AdjacencyMatrix::getSize(){
    return matrix.size();
}

vector<Node>* AdjacencyMatrix::getRow(int row){
    return &matrix[row];
}



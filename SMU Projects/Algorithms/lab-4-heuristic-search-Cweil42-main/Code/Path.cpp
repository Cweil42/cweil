//
// Created by Colin Weil on 10/27/20.
//
#include "Path.h"

Path::Path(){
    path.push_back(1);
    length=0;
}

double Path::getLength(){
    return length;
}

void Path::addToLength(double l){
    length+=l;
}

vector<int>* Path::getPath(){
    return &path;
}

bool Path::operator < (const Path& p) const{
    return (length < p.length);
}

void Path::addToPath(int id){
    path.push_back(id);
}

int Path::getMostRecentNode(){
    return path[path.size()-1];
}

int Path::getNodeInPath(int index){
    return path[index];
}


void Path::printPath(){
    cout << path[0];
    for(int i = 1; i < path.size(); i++){
        cout << "->" << path[i];
    }
    cout << endl;
}

bool Path::notInPath(int id){
    for(int i = 0; i < path.size(); i++){
        if(path[i] == id)
            return true;
    }
    return false;
}

void Path::setPathAndLength(vector<vector<double>>& pos, vector<int>& p){
    length = 0;
    path.clear();
    path.push_back(p[0]);
    for(int i = 1; i < p.size(); i++){
        path.push_back(p[i]);
        addToLength(pos[path[i-1]-1][path[i]-1]);
    }
    addToLength(pos[getMostRecentNode()-1][path.size()-1]);
}

void Path::swap(int left,int right){
    int temp = path[left];
    path[left] = path[right];
    path[right] = temp;
}

double Path::calculatePath(vector<vector<double>>& pos){
    length = 0;
    for(int i = 1; i < path.size(); i++){
        addToLength(pos[path[i-1]-1][path[i]-1]);
    }
    addToLength(pos[getMostRecentNode()-1][path.size()-1]);
    return length;
}
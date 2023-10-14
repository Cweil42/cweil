//
// Created by Colin Weil on 9/8/20.
//
#include "Search.h"
#include <math.h>
//int DFSIterative = 0;
//int DFSRecursive = 1;
//int BFSIterative = 2;
//int BFSRecursive = 3;
//int Dijkstra = 4;
//int AStar = 5;

Search::Search(int start, int end):Algorithm(){
    this->start = start;
    this->end = end;
    algo.push_back(&Search::DFSIterative);
    algo.push_back(&Search::DFSRecursive);
    algo.push_back(&Search::BFSIterative);
    algo.push_back(&Search::BFSRecursive);
    algo.push_back(&Search::Dijkstra);
    algo.push_back(&Search::AStar);

    // Manipulation of data
    randomSearch = false;
    runList = true;
    runMatrix = true;
}

void Search::Load(string filepath){
    matrix.clear();
    adjList.clear();
    string line;
    ifstream g(filepath+"/positions.txt");
    vector<int> x;
    vector<int> y;
    vector<int> z;
    while(getline(g,line, ',')){
        getline(g,line, ',');
        x.push_back(stoi(line));
        getline(g,line, ',');
        y.push_back(stoi(line));
        getline(g,line);
        z.push_back(stoi(line));
    }
    dataSize = x.size();
    vector<vector<double>> distances;
    for(int i = 0; i < x.size(); i++){
        vector<double> temp;
        for(int j = 0; j < y.size(); j++) {
            double distance = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2) + pow(z[i] - z[j], 2));
            temp.push_back(distance);
        }
        distances.push_back(temp);
    }
    matrix.loadData(filepath, x.size(), distances);
    adjList.loadData(filepath, x.size(), distances);
}

void Search::Execute(){
    listCost = 0;
    listNumNodes = 0;
    listExplored = 0;
    matrixCost = 0;
    matrixNumNodes = 0;
    matrixExplored = 0;

    if(randomSearch){
        start = (rand() % dataSize) +1 ;
        end = (rand() % dataSize) +1;
    }

    (this->*(currentAlgo))(start,end);
}

void Search::Display(){
    if(listAnswer.size()==0)
        return;
    if(runList) {
        cout << "List: ";
        for (int i = 0; i < listAnswer.size() - 1; i++)
            cout << listAnswer[i]->getId() << "->";
        cout << listAnswer[listAnswer.size() - 1]->getId() << endl;
    }
    if(runMatrix) {
        cout << "Matrix: ";
        for (int i = 0; i < matrixAnswer.size() - 1; i++)
            cout << matrixAnswer[i]->getId() << "->";
        cout << matrixAnswer[matrixAnswer.size() - 1]->getId() << endl;
    }
}

void Search::Stats(){
    cout << "Algorithm: " << algoName << endl;
    if(runList) {
        cout << "   List: " << endl;
        cout << "   Number of Nodes Visited: " << listExplored << endl;
        cout << "   Cost of path: " << listCost << endl;
        cout << "   Number of nodes in path: " << listNumNodes << endl;
        cout << "   Execution time: " << listTime.count() << endl;
    }
    if(runMatrix) {
        cout << "   Matrix: " << endl;
        cout << "   Number of Nodes Visited: " << matrixExplored << endl;
        cout << "   Cost of path: " << matrixCost << endl;
        cout << "   Number of nodes in path: " << matrixNumNodes << endl;
        cout << "   Execution time: " << matrixTime.count() << endl << endl;
    }
}

void Search::Select(int index) {
    currentAlgo = algo[index];
    switch(index){
        case 0:
            algoName = "DFSIterative";
            break;
        case 1:
            algoName = "DFSRecursive";
            break;
        case 2:
            algoName = "BFSIterative";
            break;
        case 3:
            algoName = "BFSRecursive";
            break;
        case 4:
            algoName = "Dijkstra";
            break;
        case 5:
            algoName = "A*";
            break;
    }
}

void Search::Save(string filepath) {
    if(runList) {
        ofstream out(filepath+"AdjacencyData.csv", ios_base::app);
        out << listNumNodes << ',' << listExplored << ',' << listTime.count() << ',' << listCost << "," << endl;
        out.close();
    }
    if(runMatrix) {
        ofstream out(filepath + "MatrixData.csv", ios_base::app);
        out << matrixNumNodes << ',' << matrixExplored << ',' << matrixTime.count() << ',' << matrixCost << "," << endl;
        out.close();
    }
}

void Search::Configure() {
    cout << "Not setup yet" << endl;
}

// Makes a vector by finding list of parents and pushing to vector
vector<Node*> Search::getAnswer(Node* parent, int& numNodes, double& weight){
    vector<Node*> answer;
    if(parent== nullptr){
        return answer;
    }
    while(parent!=nullptr){
        numNodes++;
        weight += parent->getWeight() * parent->getDistance();
        answer.insert(answer.begin(), parent);
        parent = parent->getParent();
    }
    return answer;
}

// All BFS and DFS functions adapated from class pseudocode
void Search::DFSIterative(int start, int end){
    if(runList) {
        // List
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        listAnswer = DFSIterativeList(start, end);
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        listTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
    if(runMatrix) {
        // Matrix
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        matrixAnswer = DFSIterativeMatrix(start, end);
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        matrixTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
}

vector<Node*> Search::DFSIterativeList(int start, int end){
    stack<Node*> path;
    vector<bool> visited(dataSize, false);
    Vertex* vert = adjList.getVertex(start);
    list<Node>* to = vert->getList();
    Node* cur = vert->getStart();
    listExplored++;
    if(start == end){
        return getAnswer(cur, listNumNodes, listCost);
    }
    path.push(cur);
    visited[vert->getStart()->getId()-1] = true;
    bool found = false;
    while(!path.empty() && !found){
        cur = path.top();
        path.pop();
        to = adjList.getVertex(cur->getId())->getList();
        for (list<Node>::iterator it = to->begin(); it != to->end(); ++it){
            if(!visited[it->getId()-1]){
                listExplored++;
                path.push(&*it);
                path.top()->setParent(cur);
                visited[it->getId()-1] = true;
                if(it->getId()==end){
                    found = true;
                    break;
                }
            }
        }
    }
    return getAnswer(path.top(), listNumNodes, listCost);
}

vector<Node*> Search::DFSIterativeMatrix(int start, int end){
    stack<Node*> path;
    vector<bool> visited(dataSize, false);
    Node* cur = matrix.getNode(start-1,start-1);
    matrixExplored++;
    if(start == end){
        return getAnswer(cur, matrixNumNodes, matrixCost);
    }
    path.push(cur);
    visited[start-1] = true;
    bool found = false;
    while(!path.empty() && !found){
        cur = path.top();
        path.pop();
        for(int i = 0; i < matrix.getSize(); i++){
            Node* next = matrix.getNode(cur->getId()-1, i);
            if(next->getId() != -1){
                if(!visited[i]) {
                    matrixExplored++;
                    next->setParent(cur);
                    path.push(next);
                    visited[i] = true;
                    if (i+1 == end) {
                        found = true;
                        break;
                    }
                }
            }
        }
    }
    return getAnswer(path.top(), matrixNumNodes, matrixCost);
}

void Search::DFSRecursive(int start, int end){
    if(runList) {
        // List
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        vector<bool> visited(dataSize, false);
        stack<Node *> path;
        Node *cur = adjList.getVertex(start)->getStart();
        visited[start - 1] = true;
        listExplored++;
        if(start == end){
            listAnswer = getAnswer(cur, listNumNodes, listCost);
        }
        else {
            path.push(cur);
            listAnswer = getAnswer(DFSRecursiveList(end, visited, path), listNumNodes, listCost);
        }
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        listTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
    if(runMatrix) {
        // Matrix
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        vector<bool> visited(dataSize, false);
        stack<Node *> p;
        Node *cur = matrix.getNode(start - 1, start - 1);
        visited[start - 1] = true;
        matrixExplored++;
        if(start == end){
            matrixAnswer = getAnswer(cur, matrixNumNodes, matrixCost);
        }
        else {
            p.push(cur);
            matrixAnswer = getAnswer(DFSRecursiveMatrix(end, visited, p), matrixNumNodes, matrixCost);
        }
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        matrixTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
}

Node* Search::DFSRecursiveList(int end, vector<bool>& visited, stack<Node*>& s){
    if(!s.empty()) {
        Node* cur = s.top();
        s.pop();
        list<Node> *to = adjList.getVertex(cur->getId())->getList();
        for (list<Node>::iterator it = to->begin(); it != to->end(); ++it) {
            bool visit = visited[it->getId() - 1];
            if (!visited[it->getId() - 1]) {
                listExplored++;
                visited[it->getId() - 1] = true;
                Node* next = &*it;
                next->setParent(cur);
                s.push(next);
                if(it->getId()==end){
                    return next;
                }
            }
        }
        return DFSRecursiveList(end, visited, s);
    }
    return nullptr;
}

Node* Search::DFSRecursiveMatrix(int end, vector<bool>& visited, stack<Node*>& s){
    if(!s.empty()) {
        Node* cur = s.top();
        s.pop();
        for(int i = 0; i < matrix.getSize(); i++){
            Node* next = matrix.getNode(cur->getId()-1, i);
            if(next->getId() != -1){
                if (!visited[next->getId() - 1]) {
                    matrixExplored++;
                    visited[next->getId() - 1] = true;
                    next->setParent(cur);
                    s.push(next);
                    if(next->getId()==end){
                        return next;
                    }
                }
            }
        }
        return DFSRecursiveMatrix(end, visited, s);
    }
    return nullptr;
}


void Search::BFSIterative(int start, int end){
    if(runList) {
        // List
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        listAnswer = BFSIterativeList(start, end);
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        listTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
    if(runMatrix) {
        // Matrix
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        matrixAnswer = BFSIterativeMatrix(start, end);
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        matrixTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
}

vector<Node*> Search::BFSIterativeList(int start, int end){
    queue<Node*> path;
    vector<bool> visited(dataSize, false);
    Vertex* vert = adjList.getVertex(start);
    list<Node>* to = vert->getList();
    Node* cur = vert->getStart();
    listExplored++;
    if(start == end){
        return getAnswer(cur, listNumNodes, listCost);
    }
    path.push(cur);
    visited[vert->getStart()->getId()-1] = true;
    bool found = false;
    while(!path.empty() && !found){
        cur = path.front();
        path.pop();
        to = adjList.getVertex(cur->getId())->getList();
        for (list<Node>::iterator it = to->begin(); it != to->end(); ++it){
            if(!visited[it->getId()-1]){
                Node* next = &*it;
                next->setParent(cur);
                path.push(next);
                visited[it->getId()-1] = true;
                listExplored++;
                if(it->getId()==end){
                    found = true;
                    break;
                }
            }
        }
    }
    return getAnswer(path.back(), listNumNodes, listCost);
}

vector<Node*> Search::BFSIterativeMatrix(int start, int end){
    queue<Node*> path;
    vector<bool> visited(dataSize, false);
    Node* cur = matrix.getNode(start-1,start-1);
    matrixExplored++;
    if(start == end){
        return getAnswer(cur, matrixNumNodes, matrixCost);
    }
    path.push(cur);
    visited[start-1] = true;
    bool found = false;
    while(!path.empty() && !found){
        cur = path.front();
        path.pop();
        for(int i = 0; i < matrix.getSize(); i++){
            Node* next = matrix.getNode(cur->getId()-1, i);
            if(next->getId() != -1){
                if(!visited[i]) {
                    matrixExplored++;
                    next->setParent(cur);
                    path.push(next);
                    visited[i] = true;
                    if (i+1 == end) {
                        found = true;
                        break;
                    }
                }
            }
        }
    }
    return getAnswer(path.back(), matrixNumNodes, matrixCost);
}


void Search::BFSRecursive(int start, int end){
    if(runList) {
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        queue<Node*> path;
        vector<bool> visited(dataSize, false);
        Node* cur = adjList.getVertex(start)->getStart();
        visited[start - 1] = true;
        listExplored++;
        if(start == end){
            listAnswer = getAnswer(cur, listNumNodes, listCost);
        }
        else {
            path.push(cur);
            listAnswer = getAnswer(BFSRecursiveList(end, visited, path), listNumNodes, listCost);
        }
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        listTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
    if(runMatrix) {

        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        queue<Node*> p;
        vector<bool> visited(dataSize, false);
        Node* cur = matrix.getNode(start-1,start-1);
        visited[start - 1] = true;
        matrixExplored++;
        if(start == end){
            matrixAnswer = getAnswer(cur, matrixNumNodes, matrixCost);
        }
        else {
            p.push(cur);
            matrixAnswer = getAnswer(BFSRecursiveMatrix(end, visited, p), matrixNumNodes, matrixCost);
        }
        chrono::high_resolution_clock::time_point  endTime = chrono::high_resolution_clock::now();
        matrixTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
}

Node* Search::BFSRecursiveList(int end, vector<bool>& visited, queue<Node*>& q){
    if(!q.empty()) {
        Node* cur = q.front();
        q.pop();
        if(cur->getId()!= end){
            list<Node> *to = adjList.getVertex(cur->getId())->getList();
            for (list<Node>::iterator it = to->begin(); it != to->end(); ++it) {
                if (!visited[it->getId() - 1]) {
                    listExplored++;
                    Node* next = &*it;
                    visited[it->getId() - 1] = true;
                    next->setParent(cur);
                    q.push(next);
                    if(it->getId()==end){
                        return next;
                    }
                }
            }
            return BFSRecursiveList(end, visited, q);
        }
    }
    return nullptr;
}

Node* Search::BFSRecursiveMatrix(int end, vector<bool>& visited, queue<Node*>& q){
    if(!q.empty()) {
        Node* cur = q.front();
        q.pop();
        for (int i = 0; i < matrix.getSize(); i++) {
            Node *next = matrix.getNode(cur->getId() - 1, i);
            if (next->getId() != -1) {
                if (!visited[next->getId()-1]) {
                    matrixExplored++;
                    visited[next->getId() - 1] = true;
                    next->setParent(cur);
                    q.push(next);
                    if (next->getId() == end) {
                        return next;
                    }
                }
            }
        }
        return BFSRecursiveMatrix(end, visited, q);
    }
    return nullptr;
}


// Reference for Dijkstra and A*
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
void Search::Dijkstra(int start, int end){
    if(runList) {
        // List
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        listAnswer = DijkstraList(start, end);
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        listTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
    if(runMatrix) {
        // Matrix
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        matrixAnswer = DijkstraMatrix(start, end);
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        matrixTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
}

vector<Node*> Search::DijkstraList(int start, int end){
    priority_queue<Node*, vector<Node*>, LessThanByWeight> q;
    vector<double> ranks(dataSize, numeric_limits<double>::infinity());
    Vertex* vert = adjList.getVertex(start);
    list<Node>* to = vert->getList();
    Node* cur = vert->getStart();
    listExplored++;
    if(start == end){
        return getAnswer(cur, listNumNodes, listCost);
    }
    q.push(cur);
    ranks[vert->getStart()->getId()-1] = 0;
    Node b;
    Node* best = &b;
    best->setRank(numeric_limits<double>::infinity());
    while(!q.empty()){
        cur = q.top();
        q.pop();
        if(cur->getId() == end && best->getRank()>cur->getRank()){
            best = cur;
        }
        if(best->getRank()>cur->getRank()) {
            to = adjList.getVertex(cur->getId())->getList();
            for (list<Node>::iterator it = to->begin(); it != to->end(); ++it) {
                double rank = it->getWeight() * it->getDistance();
                if (rank < ranks[it->getId() - 1]) {
                    if (ranks[it->getId() - 1] == numeric_limits<double>::infinity())
                        listExplored++;
                    ranks[it->getId() - 1] = rank;
                    it->setRank(rank);
                    it->setParent(cur);
                    q.push(&*it);
                }
            }
        }
        else{
            return getAnswer(best, listNumNodes, listCost);
        }
    }
    return getAnswer(nullptr, listNumNodes, listCost);
}

vector<Node*> Search::DijkstraMatrix(int start, int end){
    priority_queue<Node*, vector<Node*>, LessThanByWeight> q;
    vector<double> ranks(dataSize, numeric_limits<double>::infinity());

    Node* cur = matrix.getNode(start-1,start-1);
    matrixExplored++;
    if(start == end){
        return getAnswer(cur, matrixNumNodes, matrixCost);
    }
    q.push(cur);
    ranks[start-1] = 0;
    Node b;
    Node* best = &b;
    best->setRank(numeric_limits<double>::infinity());
    while(!q.empty()) {
        cur = q.top();
        q.pop();
        if(cur->getId() == end && best->getRank()>cur->getRank()){
            best = cur;
        }
        if(best->getRank()>cur->getRank()) {
            for (int i = 0; i < matrix.getSize(); i++) {
                Node *next = matrix.getNode(cur->getId() - 1, i);
                if (next->getId() != -1) {
                    double rank = next->getWeight() * next->getDistance();
                    if (rank < ranks[next->getId() - 1]) {
                        if (ranks[next->getId() - 1] == numeric_limits<double>::infinity())
                            matrixExplored++;
                        ranks[next->getId() - 1] = rank;
                        next->setRank(rank);
                        next->setParent(cur);
                        q.push(&*next);
                    }
                }
            }
        }
        else{
            return getAnswer(best, matrixNumNodes, matrixCost);
        }
    }
    return getAnswer(nullptr, matrixNumNodes, matrixCost);
}


void Search::AStar(int start, int end){
    if(runList) {
        // List
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        listAnswer = AStarList(start, end);
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        listTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
    if(runMatrix) {
        // Matrix
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
        matrixAnswer = AStarMatrix(start, end);
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        matrixTime = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);
    }
}

vector<Node*> Search::AStarList(int start, int end){
    priority_queue<Node*, vector<Node*>, LessThanByWeight> q;
    vector<double> ranks(dataSize, numeric_limits<double>::infinity());
    Vertex* vert = adjList.getVertex(start);
    list<Node>* to = vert->getList();
    Node* cur = vert->getStart();
    listExplored++;
    if(start == end){
        return getAnswer(cur, listNumNodes, listCost);
    }
    q.push(cur);
    ranks[vert->getStart()->getId()-1] = 0;
    Node b;
    Node* best = &b;
    best->setRank(numeric_limits<double>::infinity());
    while(!q.empty()){
        cur = q.top();
        q.pop();
        if(cur->getId() == end && best->getRank()>cur->getRank()){
            best = cur;
        }
        if(best->getRank()>=cur->getRank()) {
            to = adjList.getVertex(cur->getId())->getList();
            for (list<Node>::iterator it = to->begin(); it != to->end(); ++it) {
                double rank = it->getWeight() * it->getDistance() + matrix.getNode(start-1, it->getId()-1)->getRank();
                if (rank < ranks[it->getId() - 1]) {
                    if (ranks[it->getId() - 1] == numeric_limits<double>::infinity())
                        listExplored++;
                    ranks[it->getId() - 1] = rank;
                    it->setRank(rank);
                    it->setParent(cur);
                    q.push(&*it);
                }
            }
        }
        else{
            return getAnswer(best, listNumNodes, listCost);
        }
    }
    return getAnswer(nullptr, listNumNodes, listCost);
}

vector<Node*> Search::AStarMatrix(int start, int end){
    priority_queue<Node*, vector<Node*>, LessThanByRank> q;
    vector<double> ranks(dataSize, numeric_limits<double>::infinity());

    Node* cur = matrix.getNode(start-1,start-1);
    matrixExplored++;
    if(start == end){
        return getAnswer(cur, matrixNumNodes, matrixCost);
    }
    q.push(cur);
    ranks[start-1] = 0;
    Node b;
    Node* best = &b;
    best->setRank(numeric_limits<double>::infinity());
    while(!q.empty()) {
        cur = q.top();
        q.pop();
        if(cur->getId() == end && best->getRank()>cur->getRank()){
            best = cur;
        }
        if(best->getRank()>cur->getRank()) {
            for (int i = 0; i < matrix.getSize(); i++) {
                Node *next = matrix.getNode(cur->getId() - 1, i);
                if (next->getId() != -1) {
                    double rank = next->getWeight() * next->getDistance() + matrix.getNode(start-1, next->getId()-1)->getRank();
                    if (rank < ranks[next->getId() - 1]) {
                        if (ranks[next->getId() - 1] == numeric_limits<double>::infinity())
                            matrixExplored++;
                        ranks[next->getId() - 1] = rank;
                        next->setRank(rank);
                        next->setParent(cur);
                        q.push(&*next);
                    }
                }
            }
        }
        else{
            return getAnswer(best, matrixNumNodes, matrixCost);
        }
    }
    return getAnswer(nullptr, matrixNumNodes, matrixCost);
}



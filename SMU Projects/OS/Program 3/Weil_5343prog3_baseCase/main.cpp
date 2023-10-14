#include <pthread.h>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

void *runner(void *threadid);
vector<int> listToArray(vector<int> list);

bool start = false;
bool needMoreTables = true;
int k, m, n; // num tools, num tables, num philosophers

pthread_mutex_t toolMut;
pthread_mutex_t tableMut;
pthread_mutex_t printMut;

vector<int> totalTools;

queue<string> names;
queue<vector<int>> philosopherTools;

vector<string> seatedNames;
vector<vector<int>> seatedToolsNeededList;
vector<vector<int>> seatedToolsNeededMatrix;
vector<vector<int>> seatedToolsAcquired;
vector<bool> seatsActive;

int numFinished = 0;
queue<int> finishedTables;

int main (int argc, char **argv) {
    fstream in(argv[1]); // open file from command line args
    in >> k >> m >> n; // Read in first line of input
    vector<int> emptyVec(k,0);
    int temp;
    for(int i = 0; i < k; i++) { // Read in tool counts
        in >> temp;
        totalTools.push_back(temp);
    }
    for(int i = 0; i < n; i++){ // Read in tools needed by philosopher into 2D vector
        string name;
        in >> name; // read name
        int numToolsNeeded;
        in >> numToolsNeeded; // read num tools needed
        vector<int> curVector;
        for(int j = 0; j < numToolsNeeded; j++){
            in >> temp; // reads num individual tools needed
            curVector.push_back(temp);
        }
        names.push(name);
        philosopherTools.push(curVector);
    }
    // Done reading in file

    pthread_t threads[m]; // Set threads
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_mutex_init(&toolMut, NULL); // Initialize tool request mutex
    pthread_mutex_init(&tableMut, NULL); // Initialize table mutex
    pthread_mutex_init(&printMut, NULL); // Initialize print mutex

    for(int i = 0; i < m; i++ ) {
        seatedNames.push_back(names.front());
        cout << seatedNames[i] << " sits down at table "<< i << "." << endl;
        names.pop();
        seatedToolsNeededList.push_back(philosopherTools.front());
        seatedToolsNeededMatrix.push_back(listToArray(philosopherTools.front()));
        seatedToolsAcquired.push_back(emptyVec);
        philosopherTools.pop();
        seatsActive.push_back(true);
        pthread_create(&threads[i], &attr, runner, (void *)i );
    }

    start = true; // Start the tables
    while(numFinished < n){ // While all players aren't finished
        if(!finishedTables.empty()){
            pthread_mutex_lock(&tableMut);
            int index = finishedTables.front();
            if(!names.empty()){
                seatedNames[index] = names.front();
                names.pop();
                pthread_mutex_lock(&printMut);
                cout << seatedNames[index] << " sits down at table "<< index <<"." << endl;
                pthread_mutex_unlock(&printMut);
                seatedToolsNeededList[index] = philosopherTools.front();
                seatedToolsNeededMatrix[index] = listToArray(philosopherTools.front());
                seatedToolsAcquired[index] = emptyVec;
                philosopherTools.pop();
            }
            else{
                needMoreTables = false;
                pthread_mutex_lock(&printMut);
                cout << "No one is sitting down at table " << index << endl;
                pthread_mutex_unlock(&printMut);
            }
            finishedTables.pop();
            numFinished++;
            seatsActive[index] = true;
            pthread_mutex_unlock(&tableMut);
        }
    }
    // free attribute and wait for the other threads
    for(int i = 0; i < m; i++ ) {
        pthread_join(threads[i], NULL);
//        cout << "THREAD " << i << " quit. "<< endl;
    }
    return 0;
}

bool Request(int tid, int numTools){
    pthread_mutex_lock(&toolMut);
    for(int i = 0; i < k; i++){
        if(seatedToolsNeededMatrix[tid][i] > totalTools[i]){
            for(int i = 0; i < numTools; i++)
                seatedToolsNeededList[tid].push_back(seatedToolsNeededList[tid][i]);
            seatedToolsNeededList[tid].erase(seatedToolsNeededList[tid].begin(), seatedToolsNeededList[tid].begin()+numTools); // Delete tools at front
            pthread_mutex_unlock(&toolMut);
            return false;
        }
    }
    for(int i = 0; i < numTools; i++) {
        int toolNum = seatedToolsNeededList[tid][i];
        seatedToolsNeededMatrix[tid][toolNum]--;
        seatedToolsAcquired[tid][toolNum]++;
        totalTools[toolNum]--;
    }
    seatedToolsNeededList[tid].erase(seatedToolsNeededList[tid].begin(), seatedToolsNeededList[tid].begin()+numTools); // Delete tools at front
    pthread_mutex_unlock(&toolMut);
    return true;
}

void *runner(void *threadid) {
    int tid = (long)threadid;
    while(!start) ;// Wait for start

    while(needMoreTables){ // While all playeres aren't finished
        while(!seatedToolsNeededList[tid].empty()) {
            time_t t = time(0);
            int numTools;
            string listOfToolsLine = seatedNames[tid] + " requests ";
            if (t % 2 == 1 || seatedToolsNeededList[tid].size() == 1) {
                numTools = 1;
                listOfToolsLine += to_string(seatedToolsNeededList[tid][0]);
            }
            else {
                numTools = 2;
                listOfToolsLine += to_string(seatedToolsNeededList[tid][0]) + " " + to_string(seatedToolsNeededList[tid][1]);
            }
            pthread_mutex_lock(&printMut);
            cout << listOfToolsLine << endl;
            pthread_mutex_unlock(&printMut);

            bool granted = Request(tid, numTools);

            pthread_mutex_lock(&printMut);
            if (granted) { // update tools that the philosopher got
                cout << listOfToolsLine << ", granted" << endl;
            } else { // Move the requested items to the end of the list
                cout << listOfToolsLine << ", denied" << endl;
            }
            pthread_mutex_unlock(&printMut);

            struct timespec slptm = {1, (1000000 * (t % 1000))};
            nanosleep(&slptm, NULL); // sleep for 1 sec + (t mod 1000) milliseconds
        } // Until the philosopher obtains all tools
        struct timespec slptm = {2, 0}; // Sleep for 2 seconds
        nanosleep(&slptm, NULL); // sleep for 2 seconds

        pthread_mutex_lock(&toolMut);
        string releasingItems = seatedNames[tid] + " finishes, releasing ";
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < seatedToolsAcquired[tid][i]; j++) {
                releasingItems += to_string(i) + " ";
                totalTools[i]++; // Return tools back to restaurant
            }
        }
        pthread_mutex_unlock(&toolMut); // Clear aquired tools

        pthread_mutex_lock(&printMut);
        cout << releasingItems << endl;
        pthread_mutex_unlock(&printMut);

        // Signal the main process that he is done eating and is leaving
        pthread_mutex_lock(&tableMut);
        seatsActive[tid] = false;
        finishedTables.push(tid);
        pthread_mutex_unlock(&tableMut);

        while(!seatsActive[tid]); // Wait until main process says to continue (someone seated or main says continue)
    }
    pthread_exit(0);
}

vector<int> listToArray(vector<int> list){
    vector<int> arr(k,0);
    for(int i = 0; i < list.size(); i++)
        arr[list[i]]++;
    return arr;
}

#include <iostream>
#include "Search.h"
#include "Sort.h"

int main(int argc, char **argv) {

    Algorithm *search = new Search(stoi(argv[1]), stoi(argv[2]));
    vector<string> filepaths = {"../Data/SampleGraph", "../Data/large50", "../Data/large100"};

    for(int i = 0; i < 6; i++){
        search->Select(i);
        for(int j = 0; j < 3; j++){
            search->Load(filepaths[j]);
            search->Execute();
            search->Stats();
        }
    }


    // Used to get Data
//    string filepath = "../Report/";
//    search->Select(5);
//    for(int i = 0; i < 100; i++){
//        for(int j = 0; j < 3; j++){
//            search->Load(filepaths[j]);
//            search->Execute();
//            search->Save(filepath);
//        }
//   }


    return 0;
}

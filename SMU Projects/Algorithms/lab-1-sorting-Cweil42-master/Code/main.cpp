#include <iostream>
#include "Sort.h"

int main() {
    Algorithm *sort = new Sort;

    string files[16] = {"10_Random", "10_Reverse", "10_20%Unique", "10_30%Random",
                        "1000_Random", "1000_Reverse", "1000_20%Unique", "1000_30%Random",
                        "10000_Random", "10000_Reverse", "10000_20%Unique", "10000_30%Random",
                        "100000_Random", "100000_Reverse", "100000_20%Unique", "100000_30%Random"};

    for(int i = 0; i < 3; i++){
        sort->Select(i);
        for(int j = 0; j < 16; j++){
            string filepath = "../Data/" + files[j] + ".txt";
            sort->Load(filepath);
            sort->Execute();
            sort->Stats();
        }
    }

    return 0;
}

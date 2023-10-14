#include <iostream>
#include "HamiltonianCircuit.h"

int main() {
    Algorithm* ham = new HamiltonianCircuit;
    ham->Load("../Data/Graph/positions.txt");
    for(int i = 0; i < 2; i++){
        ham->Select(i);
        ham->Execute();
        ham->Stats();
    }

    return 0;
}



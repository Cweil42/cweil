#include <iostream>
#include "HamiltonianCircuit.h"

int main() {
    srand( (unsigned)time( NULL ) );

    Algorithm* ham = new HamiltonianCircuit;
    ham->Load("../Data/Graph/positions.txt");
    for(int i = 2; i < 4; i++){
        ham->Select(i);
        ham->Execute();
        ham->Stats();
    }

    return 0;
}



#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include "requestedFlights.h"
using namespace std;

int main(int argc, char **argv) {

    if(argc == 1){
        cout << "running catch" << endl;
        return Catch::Session().run();
    }

    // Read in Flight Data
    ifstream data(argv[1]);
    AdjacencyList flightMap;
    flightMap.fillMap(data);
    data.close();

    // Creates vector of requested flight plans
    ifstream requested(argv[2]);
    requestedFlights requests;
    requests.requestFlights(requested, flightMap);
    requested.close();

    // Prints requested flight plans
    ofstream output(argv[3]);
    requests.printRequested(output);
    output.close();

    return 0;
}

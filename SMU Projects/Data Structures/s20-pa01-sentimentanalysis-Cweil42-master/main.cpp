#include <iostream>
#include "Training.h"
#include "Testing.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;


int main(int argc, char **argv) {

    cout << "HELLO" << endl;
    if(argc == 1){
        cout << "running catch" << endl;
        return Catch::Session().run();
    }

    ifstream fin3(argv[3]);
    ifstream fin4(argv[4]);
    ifstream fin5(argv[5]);
    Training train;
    train.fillStopWord(fin5);
    fin5.close();
    train.fillDatabase(fin3,fin4);
    fin3.close();
    fin4.close();

    ifstream fin1(argv[1]);
    ifstream fin2(argv[2]);
    Testing test;
    test.checkFile(fin1,fin2, train);
    fin1.close();
    fin2.close();

    ofstream fout(argv[6]);
    test.printOut(fout);
    fout.close();


    cout << endl << "---------------------------------" << endl;
    cout << "We made it!" << endl << "---------------------------------" << endl;

    return 0;
}

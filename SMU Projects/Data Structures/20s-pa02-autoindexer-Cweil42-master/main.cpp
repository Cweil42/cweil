#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Indexer.h"

int main(int argc, char **argv) {

    if(argc == 1){
        cout << "running catch" << endl;
        return Catch::Session().run();
    }


    // Create vector of keywords
    Indexer index;
    ifstream keywords(argv[2]);
    index.fillKeywords(keywords);
    keywords.close();

    // Go through book and find keywords and add page numbers to each word
    ifstream text(argv[1]);
    index.findWords(text);
    text.close();

    // Print indexed data to outfile
    ofstream fout(argv[3]);
    index.printToOutfile(cout);
    index.printToOutfile(fout);
    fout.close();

    return 0;
}

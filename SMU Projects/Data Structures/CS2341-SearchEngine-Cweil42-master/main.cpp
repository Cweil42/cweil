#include <iostream>
#include "interface.h"
using namespace std;

int main(int argc, char **argv) {

    cout << "------------------------------" << endl;
    cout << "Welcome to the Search Engine." << endl;
    cout << "------------------------------" << endl;
    interface inter(argv[1]);
    int option;
    int wrong;
    do {
        cout << endl << "--------------------------------------------" << endl;
        cout << "Options:" << endl;
        cout << "1. Parse the entire corpus and fill index." << endl;
        cout << "2. Open a persistence file." << endl;
        cout << "3. Create a persistence file." << endl;
        cout << "4. Clear Index." << endl;
        cout << "5. Search a Boolean Query." << endl;
        cout << "6. Print Statistics of the Search Engine." << endl;
        cout << "-1 Exit Search Engine." << endl;
        cout << "--------------------------------------------" << endl;

        do{
            wrong = 0;
            cin >> option;
            if (cin.fail())
            {
                cout << "Please enter a valid integer." << endl;
                wrong = 1;
                cin.clear();
                cin.ignore(80, '\n');
            }
        }while(wrong == 1);

        if(option == 1){
            if(inter.hasParsed()){
                cout << "Index has already been parsed." << endl;
            }
            else{
                inter.parseIndex();
                cout << "Index has been parsed." << endl;
            }
        }
        else if(option == 2){
            ifstream in(argv[2]);
            inter.openPersistenceFile(in);
            cout << "Persistence file has been opened." << endl;
            in.close();
        }
        else if(option == 3){
            ofstream out(argv[2]);
            inter.createPersistenceFile(out);
            cout << "Persistence file has been created." << endl;
            out.close();
        }
        else if(option == 4){
            inter.clearIndex();
            cout << "Index has been cleared" << endl;
        }
        else if(option == 5) {
            bool isFile = inter.boolQuery();
            while(!isFile){
                int choice;
                int error;
                cout << endl << "Enter a number to print first 300 words of article or enter -1 to continue: " << endl;
                do{error = 0;
                    cin >> choice;
                    if(cin.fail() || (choice < 1 || choice > inter.getQuerySize()) && choice != -1){
                        cout << "Not valid. Enter a different choice." << endl;
                        error = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                    }
                }while(error == 1);
                if (choice == -1) {
                    isFile = true;
                }
                else {
                    isFile = inter.print300WordsOfArticle(choice);
                }
            }
        }
        else if(option == 6){
            inter.numArticles();
            inter.numWords();
            inter.avgWordPerArticle();
            inter.numAuthors();
            inter.printFreqWords();
        }
        else if(option == -1){
            cout << endl << endl;
            cout << "---------------------------------------" << endl;
            cout << "Thank you for using the search engine!" << endl;
            cout << "---------------------------------------" << endl;
        }
        else{
            cout << option << " is not an option. Try again." << endl;
            cin.ignore(100, '\n');
        }
        cout << endl;
    }while(option != -1);

    return 0;
}

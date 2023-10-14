#include <iostream>
#include <fstream>
#include <cstring>
void quickSort(char* arr[], int begin, int end);
int partition(char* arr[], int begin, int end);
void linearSort(char* arr[], int begin, int end);
void swap(char** first, char** second);
int cmpString(char* first, char* second);
using namespace std;

int main(int argc, char **argv){
    // Gets number of words to sort through
    ifstream input(argv[1]);
    char* line = new char [30];
    input.getline(line, 30, '\n');
    int numWords = atoi(line);
    delete[] line;
    numWords = 1000000;

    // Make an array with number of elements in file
    char** sort = new char*[numWords];

    // Adds every word into vector
    for(int i = 0; i < numWords; i++){
        char* cur = new char[30];
        input.getline(cur, 30);
        sort[i] = cur;
    }
    input.close();

    // Sort vector
    quickSort(sort, 0, numWords-1);

    // Prints to outfile
    ofstream output(argv[2]);
    for(int i = 0; i < numWords; i++){
        output << sort[i] << endl;
    }
    output.close();

    return 0;
}

// Adds word into sorted vector
void quickSort(char* arr[], int begin, int end) {
    if(begin < end){
        if(end-begin < 33){
            linearSort(arr, begin, end);
        }
        else{
            int mid = partition(arr, begin, end);
            quickSort(arr, begin, mid-1);
            quickSort(arr, mid+1, end);
        }
    }
}

// Partions between the two indexes
int partition(char* arr[], int begin, int end)
{
    char* pivot = arr[end];
    int index = (begin - 1);
    for (int j = begin; j <= end - 1; j++)
    {
        if (strlen(arr[j]) < strlen(pivot)){
            index++;
            swap(&arr[index], &arr[j]);
        }
        else if (strlen(arr[j]) == strlen(pivot) && (strcmp(arr[j],pivot) < 0)){
            index++;
            swap(&arr[index], &arr[j]);
        }
    }
    swap(&arr[index + 1], &arr[end]);
    return (index + 1);
}

// Sorts through linear sort
void linearSort(char* arr[], int begin, int end){
    for (int i = begin+1; i < end+1; i++){
        char* cur = arr[i];
        int j = i-1;
        while (j >= begin && cmpString(cur, arr[j]) < 0){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = cur;
    }
}

// Swaps DSStrings in vector
void swap(char** first, char** second){
    char* temp = *first;
    *first = *second;
    *second = temp;
}

// Compare char* by Length and then Data
int cmpString(char* first, char* second) {
    if (strlen(first) < strlen(second)) {
        return -1;
    }
    else if (strlen(first) == strlen(second)) {
        if (strcmp(first,second) < 0) {
            return -1;
        }
        else {
            return 1;
        }
    }
    else {
        return 1;
    }
}
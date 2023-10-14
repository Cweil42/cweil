//
// Created by Colin Weil on 2/13/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_DSVECTOR_H
#define INC_20S_PA02_AUTOINDEXER_DSVECTOR_H

using namespace std;

template<class T>
class DSvector{
private:
    T* data;
    int size;
    int cap;
public:
    void resize();
    void push_back(const T& x);
    int getSize();
    DSvector();
    ~DSvector();
    DSvector (const DSvector& vector);
    DSvector& operator=(const DSvector& vector);
    T& operator[](int index);
    void print();
    void printToOutfile(ostream& out);
    void sort();
    void insert(int,T);
};

// Vector Constructor
template<class T>
DSvector<T>::DSvector() {
    data = new T[10];
    size = 0;
    cap = 10;
}

// Vector Destructor
template<class T>
DSvector<T>::~DSvector() {
    if(data != nullptr)
        delete[] data;
}

// Returns size of vector
template<class T>
int DSvector<T>::getSize(){
    return size;
}

// Vector copy constructor
template<class T>
DSvector<T>::DSvector(const DSvector<T>& vector){
    size = vector.size;
    cap = vector.cap;
    data = new T[cap];
    for(int i = 0; i < size; i++){
        data[i] = vector.data[i];
    }
}

// Resizes vector to twice the capacity as before
template<class T>
void DSvector<T>::resize() {
    cap = cap*2;
    T* temp = new T[cap];
    for(int i = 0; i < size; i++){
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
}

// Adds a value to the end of the vector
template<class T>
void DSvector<T>::push_back(const T &x) {
    if(cap == size){
        resize();
    }
    data[size++] = x;
}

// Overided equal operator
template<class T>
DSvector<T>& DSvector<T>::operator=(const DSvector<T> &vector) {
    if(data==nullptr){
        delete[] data;
    }
    data = new T[vector.cap];
    for(int i = 0; i < size; i++){
        data[i] = vector.data[i];
    }
    return *this;
}

// Returns element in [index] of vector
template<class T>
T& DSvector<T>::operator[](int index){
    if(index>=size || index<0){
        throw:: std::out_of_range("not in index of vector");
    }
    return data[index];
}

// Prints all elements of the vector
template<class T>
void DSvector<T>::print(){
    for(int i = 0; i < size; i++){
        cout << data[i] << endl;
    }
};

// Prints all elements to outfile
template<class T>
void DSvector<T>::printToOutfile(ostream& out){
    for(int i = 0; i < size; i++){
        out << data[i] << endl;
    }
}

// Sorts elements in the vector
template<class T>
void DSvector<T>::sort(){
    // code from https://www.geeksforgeeks.org/internal-details-of-stdsort-in-c/
    // Get the left and the right index of the subarray
    // to be sorted
    int left = 0;
    int right = size-1;
    for (int i = left+1; i <= right; i++)
    {
        T key = data[i];
        int j = i-1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= left && data[j] > key)
        {
            data[j+1] = data[j];
            j = j-1;
        }
        data[j+1] = key;
    }
}

// inserts value at certain index
template<class T>
void DSvector<T>::insert(int index, T value){
    if(cap == size){
        resize();
    }
    for(int i = size-1; i >= index; i--){
        data[i+1] = data[i];
    }
    size++;
    data[index] = value;
}

#endif //INC_20S_PA02_AUTOINDEXER_DSVECTOR_H

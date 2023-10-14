//
// Created by Colin Weil on 12/7/22.
//

#ifndef MAIN_CPP_VECTOR_H
#define MAIN_CPP_VECTOR_H
#include <ostream>
#include <iostream>
//#include <random>
using namespace std;

template<class T>
class Vector{
private:
    T* data;
    int size;
    int cap;
public:
    void resize();
    void push_back(const T& x);
    int getSize();
    Vector();
    ~Vector();
    Vector (const Vector& vector);
    Vector& operator=(const Vector& vector);
    T& operator[](int index);
    void remove(int index);
    void createRandom(int size);
    void print();
};

template<class T>
void Vector<T>::createRandom(int s){
    Vector<int> temp;
    for(int i = 0; i < s; i++)
        temp.push_back(i);

    for(int i = 0; i < s; i++){
        int randIndex = rand() % temp.size;
        push_back(temp[randIndex]);
        temp.remove(randIndex);
    }
}

template<class T>
void Vector<T>::print(){
    for(int i = 0; i < size; i ++)
        cout << data[i] << " ";
    cout << endl;
}

// Vector Constructor
template<class T>
Vector<T>::Vector() {
    data = new T[10];
    size = 0;
    cap = 10;
}

// Vector Destructor
template<class T>
Vector<T>::~Vector() {
    if(data != nullptr)
        delete[] data;
}

// Returns size of vector
template<class T>
int Vector<T>::getSize(){
    return size;
}

// Vector copy constructor
template<class T>
Vector<T>::Vector(const Vector<T>& vector){
    size = vector.size;
    cap = vector.cap;
    data = new T[cap];
    for(int i = 0; i < size; i++){
        data[i] = vector.data[i];
    }
}

// Resizes vector to twice the capacity as before
template<class T>
void Vector<T>::resize() {
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
void Vector<T>::push_back(const T &x) {
    if(cap == size){
        resize();
    }
    data[size++] = x;
}

// Overided equal operator
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T> &vector) {
    if(data!=nullptr){
        delete[] data;
    }
    size = vector.size;
    cap = vector.cap;
    data = new T[cap];
    for(int i = 0; i < size; i++){
        data[i] = vector.data[i];
    }
    return *this;
}

// Returns element in [index] of vector
template<class T>
T& Vector<T>::operator[](int index){
    if(index>=size || index<0){
        throw:: std::out_of_range("not in index of vector");
    }
    return data[index];
}

template<typename T>
void Vector<T>::remove(int index) {
    T *tempData = new T[size-1];
    for(int i = 0; i < size; i++) {
        if(i < index)
            tempData[i] = data[i];
        else if(i > index)
            tempData[i-1] = data[i];
    }
    delete[] data;
    data = tempData;
    size--;
}


#endif //MAIN_CPP_VECTOR_H

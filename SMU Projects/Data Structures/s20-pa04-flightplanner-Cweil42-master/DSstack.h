//
// Created by Colin Weil on 3/30/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_DSSTACK_H
#define S20_PA04_FLIGHTPLANNER_DSSTACK_H


#include "LinkedList.h"

template<class T>
class DSstack{
private:
    LinkedList<T> stack;
public:
    void push(T data);
    void pop();
    T peek();
    bool isEmpty();
    void print(ostream& out);
    bool search(T data);
    DSstack<T>();
    DSstack<T>(const DSstack<T> &stack);
    DSstack<T> operator=(const DSstack<T> &stack);
};

template<class T>
void DSstack<T>::push(T data){
    stack.insertAtEnd(data);
}

template<class T>
void DSstack<T>::pop(){
    if(stack.getHead() != nullptr){
        stack.removeTail();
    }
}

template<class T>
T DSstack<T>::peek(){
    return stack.getData(stack.getTail());
}

template<class T>
bool DSstack<T>::isEmpty(){
    if(stack.getSize() == 0)
        return true;
    else
        return false;
}

template<class T>
void DSstack<T>::print(ostream& out){
    stack.print(out);
}

template<class T>
bool DSstack<T>::search(T data){
    return (stack.search(data) != 0);
}

template<class T>
DSstack<T>::DSstack(){}

template<class T>
DSstack<T>::DSstack(const DSstack<T> &s){
    stack = s.stack;
}

template<class T>
DSstack<T> DSstack<T>::operator=(const DSstack<T> &s){
    stack = s.stack;
    return *this;
}

#endif //S20_PA04_FLIGHTPLANNER_DSSTACK_H

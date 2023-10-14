//
// Created by Colin Weil on 3/27/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_LINKEDLIST_H
#define S20_PA04_FLIGHTPLANNER_LINKEDLIST_H

#include "ListNode.h"
#include <iostream>
#include <fstream>
using namespace std;


template<class T>
class LinkedList{
private:
    ListNode<T>* head;
    ListNode<T>* iter;
public:
    LinkedList();
    LinkedList(T data);
    LinkedList(const LinkedList &list);
    void insertAtFront(T data);
    void insertAtEnd(T data);
    void remove(T data);
    void removeHead();
    void removeTail();
    void print(ostream& out);
    ~LinkedList();
    LinkedList& operator=(const LinkedList& l);
    ListNode<T>* getHead(){ return head; }
    ListNode<T>* getNext(ListNode<T>* node){ return node->next; }
    ListNode<T>* getTail();
    int getSize();
    T& getData(ListNode<T>* node);
    ListNode<T>* search(T data);
    ListNode<T>* getIter();
    void iterNext();
    void iterPrev();
    void iterReset();
};

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    iter = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(T data) {
    head = new ListNode<T>(data);
    iter = head;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &list){
    head = nullptr;
    ListNode<T> *cur = list.head;
    while (cur != nullptr) {
        insertAtEnd(cur->data);
        cur = cur->next;
    }
    iter = head;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list){
    head = nullptr;
    ListNode<T> *cur = list.head;
    while (cur != nullptr) {
        insertAtEnd(cur->data);
        cur = cur->next;
    }
    iter = head;
    return *this;
}

template<class T>
void LinkedList<T>::insertAtFront(T data) {
    if(head ==  nullptr) {
        head = new ListNode<T>(data);
        iter = head;
    }
    else{
        ListNode<T>* cur = new ListNode<T>(data);
        head->previous = cur;
        cur->next = head;
        head = cur;
    }
}

template<class T>
void LinkedList<T>::insertAtEnd(T data) {
    if (head == nullptr) {
        head = new ListNode(data);
    } else {
        ListNode<T> *cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = new ListNode<T>(data, nullptr, cur);
    }
}

template<class T>
void LinkedList<T>::remove(T data){
    if(head ==  nullptr)
        return;
    ListNode<T>* cur = head;
    while(cur != nullptr){
        if(cur->data ==  data){
            // data is not at head
            if(cur->previous != nullptr){
                if(cur->next != nullptr) {
                    cur->previous->next = cur->next;
                    cur->next->previous = cur->previous;
                ListNode<T>* temp = cur->previous;
                delete cur;
                cur = temp;
                delete temp;
                }
                else{
                    cur->previous->next = nullptr;
                }
            }
            // data is at head
            else{
                if(cur->next != nullptr) {
                    head = cur->next;
                    delete cur->previous;
                    head->previous = nullptr;
                }
                else{
                    head = nullptr;
                }
                iter = head;
            }
        }
        cur = cur->next;
    }
}

template<class T>
void LinkedList<T>::removeHead(){
    if(head ==  nullptr)
        return;
    ListNode<T>* cur = head;
    if(cur->next != nullptr) {
        head = cur->next;
        delete cur->previous;
        head->previous = nullptr;
    }
    else{
        head = nullptr;
    }
    iter = head;
}

template<class T>
void LinkedList<T>::removeTail(){
    if(head ==  nullptr)
        return;

    ListNode<T>* cur = head;
    while(cur->next != nullptr) {
        cur = cur->next;
    }
    if(cur->previous == nullptr){
        delete head;
        head = nullptr;
    }
    else{
        cur = cur->previous;
        delete cur->next;
        cur->next =  nullptr;
    }
    iter = head;
}

template<class T>
void LinkedList<T>::print(ostream& out) {
    if(head == nullptr){
        out << "empty" << endl;
    }
    ListNode<T>* cur = head;
    while(cur != nullptr){
        out << " -> " << cur->data ;
        cur = cur->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    if (head != nullptr) {
        while (head->next != nullptr) {
            head = head->next;
            delete head->previous;
        }
        delete head;
    }
}

template<class T>
int LinkedList<T>::getSize(){
    if(head == nullptr){
        return 0;
    }
    int size = 0;
    ListNode<T>* cur = head;
    while(cur != nullptr){
        cur = cur->next;
        size++;
    }
    return size;
}

template<class T>
ListNode<T>* LinkedList<T>::getTail(){
    if(head == nullptr){
        return nullptr;
    }
    ListNode<T>* cur = head;
    while(cur->next != nullptr){
        cur = cur->next;
    }
    return cur;
}

template<class T>
T& LinkedList<T>::getData(ListNode<T>* node){
    return node->data;
}

template<class T>
ListNode<T>* LinkedList<T>::search(T data){
    ListNode<T>* cur = head;
    while(cur != nullptr){
        if(cur->data == data){
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

template<class T>
ListNode<T>* LinkedList<T>::getIter(){
    return iter;
}

template<class T>
void LinkedList<T>::iterNext(){
    iter = iter->next;
}

template<class T>
void LinkedList<T>::iterPrev(){
    iter = iter->previous;
}

template<class T>
void LinkedList<T>::iterReset(){
    iter = head;
}

#endif //S20_PA04_FLIGHTPLANNER_LINKEDLIST_H

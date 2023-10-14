//
// Created by Colin Weil on 4/25/20.
//

#ifndef SEARCHENGINE_HASHMAP_H
#define SEARCHENGINE_HASHMAP_H

#include "hashNode.h"
#include <functional>
#include <bitset>
#include <iostream>
#include "cstdlib"
using namespace std;

template<typename K, typename V>
class hashMap{
private:
    int cap;
    int size;
    hashNode<K,V>** elements;
public:
    hashMap();
    ~hashMap();
    hashNode<K, V>* insert(K key, V val);
    hashNode<K, V>* get(K k);
    int getSize();
    void print(ostream& out);
    void clear();
};

template<typename K, typename V>
// Default constructor
hashMap<K, V>::hashMap(){
    cap = 1000;
    size = 0;
    elements = new hashNode<K,V>*[cap];
    for(int i = 0; i < cap; i++){
        elements[i] = nullptr;
    }
}

template<typename K, typename V>
// HashMap destructor
hashMap<K, V>::~hashMap(){
    for (int i = 0; i < cap; ++i) {
        hashNode<K, V>* cur = elements[i];
        while (cur != nullptr) {
            hashNode<K, V>* prev = cur;
            cur = cur->next;
            delete prev;
        }
        elements[i] = nullptr;
    }
    delete[] elements;
}

template<typename K, typename V>
// Clears all of the hashMap
void hashMap<K, V>::clear(){
    for (int i = 0; i < cap; ++i) {
        hashNode<K, V>* cur = elements[i];
        while (cur != nullptr) {
            hashNode<K, V>* prev = cur;
            cur = cur->next;
            delete prev;
        }
        elements[i] = nullptr;
    }
}

template<typename K, typename V>
// Adds a key and value
hashNode<K, V>* hashMap<K, V>::insert(K key, V val){
    hash<string> mystdhash;
    int hash = mystdhash(key);
    int index = abs(hash) / 10000000;
    hashNode<K, V>* prev = nullptr;
    hashNode<K, V>* cur = elements[index];

    // Find next open spot in list
    while (cur != nullptr) {
        if(cur->key == key){
            return cur;
        }
        prev = cur;
        cur = cur->getNext();
    }
    cur = new hashNode<K, V>(key, val);

    // If bucket empty, enter or else insert at end
    if (prev == nullptr) {
        elements[index] = cur;
    }
    else {
        prev->next = cur;
    }
    size++;
    return nullptr;
}

template<typename K, typename V>
// Gets the pointer to a hasnNode that has key K
hashNode<K, V>* hashMap<K, V>::get(K key){
    hash<string> mystdhash;
    int hash = mystdhash(key);
    int index = abs(hash) / 10000000;
    hashNode<K, V>* cur = elements[index];
    while (cur != nullptr) {
        if (cur->key == key) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

template<typename K, typename V>
// Returns the size of the hashMap
int hashMap<K, V>::getSize(){
    return size;
}

template<typename K, typename V>
// Printing hashMap
void hashMap<K, V>::print(ostream& out){
    for (int i = 0; i < cap; ++i) {
        hashNode<K, V>* cur = elements[i];
        while (cur != nullptr) {
            out << "," << cur->key;
            for(int i = 0; i < cur->getData().size(); i++){
                out  << "," << cur->getData()[i];
            }
            out << endl;
            cur = cur->next;
        }
    }
}

#endif //SEARCHENGINE_HASHMAP_H



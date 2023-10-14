//
// Created by Colin Weil on 4/24/20.
//

#ifndef SEARCHENGINE_HASHNODE_H
#define SEARCHENGINE_HASHNODE_H

template<typename K, typename V>
class hashMap;

template<typename K, typename T>
class hashNode{
private:
    K key;
    T data;
    hashNode* next;
public:
    // Constructor
    hashNode(K k, T d, hashNode<K, T>* n = nullptr){
        data = d;
        key = k;
        next = n;
    }

    // Overloaded == operator that returns comparison of keys
    bool operator==(const hashNode& h) const { return key == h.key; }

    // Copy constructor
    hashNode(const hashNode& n){
        key = n.key;
        data = n.data;
        next = n.next;
    }

    // Overloaded = operator
    hashNode& operator=(const hashNode& n){
        key = n.key;
        data = n.data;
        next = n.next;
        return *this;
    }

    // Getters for private variables
    T& getData(){ return data; }
    K& getKey(){ return key; }
    hashNode* getNext(){ return next; }

    // Setters for private variables
    void setData(T d){ data = d; }
    void setKey(K k){ key = k; }
    void setNext(hashNode* n){ next = n; }

    friend class hashMap<K, T>;
};

#endif //SEARCHENGINE_HASHNODE_H

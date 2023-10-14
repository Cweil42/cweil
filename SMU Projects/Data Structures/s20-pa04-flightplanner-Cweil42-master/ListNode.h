//
// Created by Colin Weil on 3/27/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_LISTNODE_H
#define S20_PA04_FLIGHTPLANNER_LISTNODE_H
template<typename T>
class LinkedList;

template<class T>
class ListNode{
private:
    T data;
    ListNode* next;
    ListNode* previous;
public:
    ListNode(T d, ListNode<T>* n = nullptr, ListNode<T>* p = nullptr){
        data = d;
        next = n;
        previous = p;
    }

    bool operator==(const ListNode& n) const { return data == n.data; }
    T& getData(){ return data; }
    ListNode* getNext(){ return next; }
    ListNode* getPrevious(){ return previous; }

    friend class LinkedList<T>;
};

#endif //S20_PA04_FLIGHTPLANNER_LISTNODE_H

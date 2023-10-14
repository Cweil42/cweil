#include <iostream>
#include <fstream>
using namespace std;

template<class T>
class ListNode{
public:
    T data;
    ListNode* next;
    ListNode* previous;

    ListNode(T d, ListNode<T>* n = nullptr, ListNode<T>* p =
    nullptr){
        data = d;
        next = n;
        previous = p;
    }

    bool operator==(const ListNode& n) const { return data ==
                                                      n.data; }
    T& getData(){ return data; }
    ListNode* getNext(){ return next; }
    ListNode* getPrevious(){ return previous; }
};

template<class T>
class LinkedList {
private:
    ListNode<T> *head;
    ListNode<T> *tail;
    int size;
public:
    LinkedList();
    LinkedList(T data);
    LinkedList(const LinkedList &list);
    LinkedList &operator=(const LinkedList &l);

    void ToOutputPlusOne(int* out, int &index);
    void printListPlusOne();
    void printList();
    ~LinkedList();
    int getSize();
    ListNode<T>* push_back(T data);
    bool existsInList(T data);
    ListNode<T>* getTail();
    ListNode<T>* getHead();
    T removeHead();
    ListNode<T>* deleteNode(ListNode<T>* point);
};

template<class T>
ListNode<T>* LinkedList<T>::getTail(){ return tail; }

template<class T>
ListNode<T>* LinkedList<T>::getHead(){ return head; }

template<class T>
T LinkedList<T>::removeHead(){
    if(head == nullptr)
        return -1;
    T data = head->data;

    ListNode<T>* temp = head;
    head = temp->next;
    if(head != nullptr) head->previous = nullptr;

    size--;
    delete temp;
    return data;
}

template<class T>
bool LinkedList<T>::existsInList(T data){
    ListNode<T>* cur = head;
    while(cur != nullptr){
        if(cur->data == data)
            return true;
        cur = cur->next;
    }
    return false;
}

template<class T>
ListNode<T>* LinkedList<T>::push_back(T data) {
    // No data
    if(head == nullptr) {
        head = new ListNode<T>(data);
        tail = head;
    }
    else{
        ListNode<T> *temp = new ListNode<T>(data, nullptr, tail);
        tail->next = temp;
        tail = temp;
    }
    size++;
    return tail;
}

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(T data) {
    head = new ListNode<T>(data);
    size = 1;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &list){
    head = nullptr;
    ListNode<T> *cur = list.head;
    while (cur != nullptr) {
        push_back(cur->data);
        cur = cur->next;
    }
    size = list.size;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list){
    head = nullptr;
    ListNode<T> *cur = list.head;
    while (cur != nullptr) {
        push_back(cur->data);
        cur = cur->next;
    }
    size = list.size;
    return *this;
}

template<class T>
void LinkedList<T>::ToOutputPlusOne(int* out, int &index) {
    ListNode<T>* cur = head;
    while(cur != nullptr){
        out[index] = cur->data+1;
        index++;
        cur = cur->next;
    }
}

template<class T>
void LinkedList<T>::printListPlusOne() {
    if(head == nullptr){
        return;
    }
    ListNode<T>* cur = head;
    while(cur != nullptr){
        cout << " -> " << cur->data + 1;
        cur = cur->next;
    }
}

template<class T>
void LinkedList<T>::printList() {
    if(head == nullptr){
        return;
    }
    ListNode<T>* cur = head;
    while(cur != nullptr){
        cout << " -> " << cur->data;
        cur = cur->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    ListNode<T>* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template<class T>
int LinkedList<T>::getSize(){
    return size;
}

template<class T>
ListNode<T>* LinkedList<T>::deleteNode(ListNode<T>* cur){
    // Not head
    if(cur->previous != nullptr){
        // not head, not tail
        if(cur->next != nullptr) {
            cur->previous->next = cur->next;
            cur->next->previous = cur->previous;
            delete cur;
        }
        // not head, but tail
        else{
            tail = cur->previous;
            tail->next = nullptr;
            delete cur;
        }
    }
    // data is at head
    else{
        // head, not tail
        if(cur->next != nullptr) {
            head = cur->next;
            head->previous = nullptr;
            delete cur;
        }
        // head and tail
        else{
            head = nullptr;
            delete cur;
        }
    }
    size--;
    return head;
}
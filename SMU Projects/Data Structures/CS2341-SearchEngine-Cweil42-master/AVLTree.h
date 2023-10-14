//
// Created by Colin Weil on 4/13/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_AVLTREE_H
#define INC_20S_PA02_AUTOINDEXER_AVLTREE_H

#include "TreeNode.h"
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class AVLTree{
private:
    int size;
    TreeNode<T>* root;
    TreeNode<T>* insert(T& val, TreeNode<T>*& cur);
    void inorderTraversal(TreeNode<T>* cur);
    TreeNode<T>* checkBalance(TreeNode<T>* cur);
    TreeNode<T>* rightRight(TreeNode<T>* cur);
    TreeNode<T>* rightLeft(TreeNode<T>* cur);
    TreeNode<T>* leftRight(TreeNode<T>* cur);
    TreeNode<T>* leftLeft(TreeNode<T>* cur);
    TreeNode<T>* search(T val, TreeNode<T>* cur);
    void clear(TreeNode<T>*& cur);
    void toVector(TreeNode<T>*& cur, vector<T>* vect);
    void toTextFile(TreeNode<T>*& cur, ostream& out);
    void copy(TreeNode<T>*& cur, AVLTree<T>& t);
    void printGivenLevel(TreeNode<T>* cur, int level, ostream& out);
public:
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree<T>& t);
    AVLTree(T val);
    TreeNode<T>* insert(T& val);
    void inorderTraversal();
    int getHeight(TreeNode<T>* node);
    TreeNode<T>* search(T& val);
    int getSize();
    void clear();
    vector<T> toVector();
    void backwardTraversal(TreeNode<T>* cur);
    void toTextFile(ostream& out);
    AVLTree<T>& operator=(const AVLTree<T>& t);
    bool isEmpty();
};

template<typename T>
//Default constructor
AVLTree<T>::AVLTree() {
    root = nullptr;
    size = 0;
}

template<typename T>
// Constructor with value parameter
AVLTree<T>::AVLTree(T val) {
    root = new TreeNode<T>(val);
    size = 0;
}

template<typename T>
// Destructor
AVLTree<T>::~AVLTree() {
    root = nullptr;
    //delete root;
    //clear(root);
}

template<typename T>
// Copy Constructor
AVLTree<T>::AVLTree(const AVLTree<T>& t){
    AVLTree<T> cur;
    TreeNode<T>* copyRoot = t.root;
    copy(copyRoot, cur);
    root = cur.root;
}

template<typename T>
// Copy Method
void AVLTree<T>::copy(TreeNode<T>*& cur, AVLTree<T>& t){
    if(cur != nullptr){
        copy(cur->left, t);
        copy(cur->right, t);
        t.insert(cur->data);
    }
}


template<typename T>
// Clear all elements in tree (public)
void AVLTree<T>::clear(){
    //clear(root);
    root = nullptr;
    size = 0;
}

template<typename T>
// Recursive clear of nodes
void AVLTree<T>::clear(TreeNode<T>*& cur){
    if(cur != nullptr){
        clear(cur->left);
        clear(cur->right);
        delete cur;
    }
}

template<typename T>
// Insert value to tree
TreeNode<T>* AVLTree<T>::insert(T& val) {
    insert(val, root);
    size++;
}

template<typename T>
// Prints values in order (public)
void AVLTree<T>::inorderTraversal() {
    inorderTraversal(root);
}

template<typename T>
// Recursive insert call
TreeNode<T>* AVLTree<T>::insert(T& val, TreeNode<T>*& cur) {
    if(cur == nullptr){
        cur = new TreeNode(val);
        return cur;
    }
    else if(val < cur->data){
        insert(val, cur->left);
        cur = checkBalance(cur);
    }
    else{
        insert(val, cur->right);
        cur = checkBalance(cur);
    }
    return cur;
}

template<typename T>
// Resursive in Order Traversal
void AVLTree<T>::inorderTraversal(TreeNode<T>* cur) {
    if(cur != nullptr){
        inorderTraversal(cur->left);
        cout << cur->data << endl;
        inorderTraversal(cur->right);
    }
}

template<typename T>
// Recursive backward traversal
void AVLTree<T>::backwardTraversal(TreeNode<T>* cur) {
    if(cur != nullptr){
        inorderTraversal(cur->right);
        cout << cur->data << endl;
        inorderTraversal(cur->left);
    }
}

template<typename T>
// Search for a value in the tree (public)
TreeNode<T>* AVLTree<T>::search(T& val) {
    return search(val, root);
}

template<typename T>
// Recursive search for value
TreeNode<T>* AVLTree<T>::search(T val, TreeNode<T>* cur) {
    if(cur == nullptr){
        return nullptr;
    }
    else if(cur->data == val){
        return cur;
    }
    else if(val < cur->data){
        return search(val, cur->left);
    }
    else if(val > cur->data){
        return search(val, cur->right);
    }
}

template<typename T>
// Returns the height of a node
int AVLTree<T>::getHeight(TreeNode<T>* cur){
    int height = 0;
    if(cur != nullptr){
        int left = getHeight(cur->left);
        int right = getHeight(cur->right);
        if(left >= right){
            height = left + 1;
        }
        else{
            height = right + 1;
        }
    }
    return height;
}

template<typename T>
// Checks balance of a node and corrects accordingly
TreeNode<T>* AVLTree<T>::checkBalance(TreeNode<T>* cur){
    int balance = getHeight(cur->left)-getHeight(cur->right);
    if(balance == 2){
        if(getHeight(cur->left->left)-getHeight(cur->left->right) > 0){
            cur = leftLeft(cur);
        }
        else{
            cur = leftRight(cur);
        }
    }
    else if(balance == -2){
        if(getHeight(cur->right->left)-getHeight(cur->right->right) > 0){
            cur = rightLeft(cur);
        }
        else{
            cur = rightRight(cur);
        }
    }
    return cur;
}

template<typename T>
// Right right rotate
TreeNode<T>* AVLTree<T>::rightRight(TreeNode<T>* cur){
    TreeNode<T>* temp = cur->right;
    cur->right = temp->left;
    temp->left = cur;
    if(cur == root){
        root = temp;
    }
    return temp;
}

template<typename T>
// Right left rotate
TreeNode<T>* AVLTree<T>::rightLeft(TreeNode<T>* cur){
    TreeNode<T>* temp = cur->right;
    cur->right = leftLeft(temp);
    return rightRight(cur);
}

template<typename T>
// Left right rotate
TreeNode<T>* AVLTree<T>::leftRight(TreeNode<T>* cur){
    TreeNode<T>* temp = cur->left;
    cur->left = rightRight(temp);
    return leftLeft(cur);
}

template<typename T>
// Left left rotate
TreeNode<T>* AVLTree<T>::leftLeft(TreeNode<T>* cur){
    TreeNode<T>* temp = cur->left;
    cur->left = temp->right;
    temp->right = cur;
    if(cur == root){
        root = temp;
    }
    return temp;
}

template<typename T>
// Gets size of tree
int AVLTree<T>::getSize(){
    return size;
}

template<typename T>
// Turns AVLTree to vector (public)
vector<T> AVLTree<T>::toVector(){
    vector<T> vect;
    toVector(root, &vect);
    return vect;
}

template<typename T>
// AVLtree to vector recursive
void AVLTree<T>::toVector(TreeNode<T>*& cur, vector<T>* vect){
    if(cur != nullptr){
        toVector(cur->left, vect);
        vect->push_back(cur->data);
        toVector(cur->right, vect);
    }
}

template<typename T>
// Prints tree to output file
void AVLTree<T>::toTextFile(ostream& out){
    int height = getHeight(root);
    int i;
    for (i = 1; i <= height; i++){
        printGivenLevel(root, i, out);
    }
}

template<typename T>
// Prints level of tree
void AVLTree<T>::printGivenLevel(TreeNode<T>* cur, int level, ostream& out){
    if (cur != nullptr){
        if(level == 1){
            out << "," << cur->data;
        }
        else if(level > 1){
            printGivenLevel(cur->left, level-1, out);
            printGivenLevel(cur->right, level-1, out);
        }
    }
}

// Overloaded = operator
template<typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& t){
    AVLTree<T> cur;
    TreeNode<T>* copyRoot = t.root;
    copy(copyRoot, cur);
    root = cur.root;
    return *this;
}

// Returns bool if is empty
template<typename T>
bool AVLTree<T>::isEmpty(){
    return root==nullptr;
}

#endif //INC_20S_PA02_AUTOINDEXER_AVLTREE_H

//
// Created by Colin Weil on 4/13/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_TREENODE_H
#define INC_20S_PA02_AUTOINDEXER_TREENODE_H

//
// Created by Colin Weil on 3/27/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_LISTNODE_H
#define S20_PA04_FLIGHTPLANNER_LISTNODE_H
template<typename T>
class AVLTree;

template<class T>
class TreeNode{
private:
    T data;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(T d, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr){
        data = d;
        left = l;
        right = r;
    }

    bool operator==(const TreeNode& n) const { return data == n.data; }
    T& getData(){ return data; }

    TreeNode<T>& operator=(const TreeNode<T>& n){
        data = n.data;
        left = n.left;
        right = n.right;
        return *this;
    }

    ~TreeNode(){
        if(left != nullptr)
            delete left;
        if(right != nullptr)
            delete right;
    }

    friend class AVLTree<T>;
};

#endif //S20_PA04_FLIGHTPLANNER_LISTNODE_H


#endif //INC_20S_PA02_AUTOINDEXER_TREENODE_H

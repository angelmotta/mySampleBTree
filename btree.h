#ifndef MYSAMPLEBTREE_BTREE_H
#define MYSAMPLEBTREE_BTREE_H

#include "node.h"

template <typename T>
class BTree {
private:
    Node<T>* root;
    unsigned int minDegree;    // min Degree

public:
    BTree(unsigned int minDegree) : minDegree(minDegree), root(nullptr) {};

    pair<Node<T>*, int> search(int k) {
        if(!root){
            return make_pair(nullptr, -1);
        }
        return root->searchUtil(k);
    }

    void insert(T keyValue){
        cout << "** Insert value: " << keyValue << "\n";
        if(root == nullptr){
            root = new Node<T>(minDegree, true);
            root->keys[0] = keyValue;
            root->currentKeys = 1;
        }
        else {
            // if root is full
            if(root->currentKeys == 2 * minDegree - 1){
                auto ptrRoot = root;
                auto newRoot = new Node<T>(minDegree, false);
                root = newRoot;
                // New Root node is now parent of the original old Root node
                newRoot->children[0] = ptrRoot;
                // Execute split staying from the New Root node
                newRoot->splitChild(ptrRoot, 0);
                // Select 1 of 2 children of root to have new key
                int idx = 0;
                if(keyValue > root->keys[0]){
                    idx++;
                }
                newRoot->children[idx]->insertNonFullNode(keyValue);
            }
            else {
                root->insertNonFullNode(keyValue);
            }
        }
    }

    bool remove(int k) {
        // TODO
    }

    void traverse(){
        cout << "** Traverse print BTree **\n";
        if(this->root){
            root->traverse();
        }
        cout << "\n";
    }

    void print() {
        if(root) root->recorrerNodes();
        cout << '\n';
    }

    ~BTree(){
        cout << "Pending Call Destructor\n";
//        if(root){
//            root->killSelf();
//        }
    }
};


#endif //MYSAMPLEBTREE_BTREE_H

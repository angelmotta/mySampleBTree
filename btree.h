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
        cout << "** Search key: " << k << " **\n";
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

    void remove(int k) {
        cout << "** Remove: " << k << " **\n";
        if(!root){
            cout << "BTree is empty\n";
            return;
        }
        root->remove(k);
        // After deletion, if root node has 0 keys, check if its first child and make it the new root node.
        // Otherwise set root as Null
        if(root->currentKeys == 0){
            auto ptrRoot = root;
            if(root->isLeaf){
                root = nullptr;
            }
            else {
                root = root->children[0];
            }
            delete ptrRoot;
        }
    }

    // InOrder
    void traverse(){
        cout << "** Traverse print BTree **\n";
        if(this->root){
            root->traverse();
        }
        cout << "\n";
    }

    void print() {
        cout << "** Print Level BTree **\n";
        if(root) root->recorrerNodes();
        cout << '\n';
    }

    void printSearch(pair<Node<T>*, int> result){
        if(result.first){
            cout << result.first->getKey(result.second) << "\n";
        }
        else {
            cout << "Key Not Found\n";
        }
    }

    ~BTree(){
        cout << "Pending Destructor\n";
        if(root){
            root->killSelf();
        }
    }
};


#endif //MYSAMPLEBTREE_BTREE_H

#ifndef MYSAMPLEBTREE_NODE_H
#define MYSAMPLEBTREE_NODE_H

#include <vector>
#include <queue>
#include <iostream>
#include <utility>

using namespace std;

template<typename T>
class BTree;

template <typename T>
class Node {
private:
    unsigned int t; // minimum degree
    unsigned int currentKeys;
    vector<T> keys;
    vector<Node<T>*> children;
    bool isLeaf;

public:
    Node(unsigned int t, bool isLeaf) : t(t), isLeaf(isLeaf) {
        keys.resize(2 * t - 1);
        children.resize(2 * t);
        currentKeys = 0;
    }

    pair<Node<T>*, int> searchUtil(int k){
        int keyIdx=0;
        while(keyIdx < currentKeys && k > keys[keyIdx]){
            keyIdx++;
        }
        if( keyIdx < currentKeys && keys[keyIdx] == k){
            //return this;
            return make_pair(this, keyIdx);
        }
        else if(isLeaf){
            return make_pair(nullptr, -1);
        }
        return children[keyIdx]->searchUtil(k); // Recursive call: go down to the child and search
    }

    // Inorder traverse
    void traverse(){
        int idx;
        for(idx = 0; idx < currentKeys; ++idx){
            if(!isLeaf){    // if It is internal node
                children[idx]->traverse();      // recursive call
            }
            cout << keys[idx] << " ";
        }
        // If it's internal node, print the rightmost position child
        if(!isLeaf){
            children[idx]->traverse();
        }
    }

    // This->node is parent of child Y. This function Split child Y
    void splitChild(Node<T>* nodeY, int idx){
        auto nodeZ = new Node(nodeY->t, nodeY->isLeaf);
        nodeZ->currentKeys = t - 1;
        for(int i = 0; i < t - 1; i++){
            nodeZ->keys[i] = nodeY->keys[i+t];
        }

        if(!nodeY->isLeaf){
            for(int i = 0; i < t; i++){
                nodeZ->children[i] = nodeY->children[i+t];
            }
        }

        nodeY->currentKeys = t - 1;

        // Update child pointers of this->node which is parent of Y
        for(int i = currentKeys; i >= idx + 1; i--){
            this->children[i + 1] = this->children[i];
        }
        this->children[idx + 1] = nodeZ;

        // Update keys indexes of this->node
        for(int i = currentKeys - 1; i >= idx; i--){
            this->keys[i + 1] = this->keys[i];
        }

        // Move up the midterm key of y to this node
        this->keys[idx] = nodeY->keys[t-1];

        this->currentKeys++;
    }

    void insertNonFullNode(T keyValue){
        int keyIdx = currentKeys - 1;   // index of rightmost key in Node
        // If this node is Leaf, execute insertion
        if(this->isLeaf){
            while(keyIdx >= 0 && this->keys[keyIdx] > keyValue){
                this->keys[keyIdx + 1] = this->keys[keyIdx];
                keyIdx--;
            }
            this->keys[keyIdx + 1] = keyValue;
            this->currentKeys++;
        }
        else { // if not, go down (recursion) to the the leaf node
            while(keyIdx >= 0 && this->keys[keyIdx] > keyValue){
                keyIdx--;
            }
            // check if childNode found (keyIdx + 1) is Full
            if(this->children[keyIdx + 1]->currentKeys == 2 * t - 1 ){
                splitChild(children[keyIdx + 1], keyIdx + 1);
                // After split of child, check where go down
                if(keyValue > this->keys[keyIdx + 1]){
                    keyIdx++;
                }
            }
            this->children[keyIdx + 1]->insertNonFullNode(keyValue);
        }
    }

    void killSelf(){
        if(!isLeaf){    // If is internal Node go down
            for(int i=0; i<children.t(); ++i){
                if(children[i]){
                    children[i]->killSelf();
                }
            }
        }
        delete this;    // if I arrived here is a Leaf, so delete it
    }

    T getKey(int keyIdex){
        return this->keys[keyIdex];
    }

    void recorrerNodes() {
        queue<pair<Node<T>*, int>> next;
        next.push(pair<Node<T>*, int>(this, 0));

        while (!next.empty()) {
            auto temp = next.front();
            next.pop();

            temp.first->printIndexes(temp.second);

            for (int i = 0; i < temp.first->children.size(); i++) {
                next.push(pair<Node<T>*, int>(temp.first->children[i], temp.second + 2));
            }

            cout << endl;
        }
    }

    void printIndexes(int level) {
        cout << level << ": ";
        for (int i = 0; i < keys.size(); i++) {
            cout << keys[i] << " ";
        }
    }

    friend class BTree <T>;
};

#endif //MYSAMPLEBTREE_NODE_H

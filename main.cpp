#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    /*
    BTree<int> treecampeon(3);
    treecampeon.insert(10);
    treecampeon.insert(20);
    treecampeon.insert(5);
    treecampeon.insert(6);
    treecampeon.insert(12);
    treecampeon.insert(30);
    treecampeon.insert(7);
    treecampeon.insert(17);
    treecampeon.traverse();
    */
    //old test
    BTree<int> treecampeon(3);
    treecampeon.insert(10);
    treecampeon.insert(20);
    treecampeon.insert(5);
    treecampeon.insert(6);
    treecampeon.insert(12);
    treecampeon.insert(30);
    treecampeon.traverse();
    //treecampeon.print();
    auto result = treecampeon.search(6);
    if(result.first){
        cout << result.first->getKey(result.second) << "\n";
    }
    else {
        cout << "Not Found\n";
    }
    result = treecampeon.search(13);
    if(result.first){
        cout << result.first->getKey(result.second) << "\n";
    }
    else {
        cout << "Not Found\n";
    }
    result = treecampeon.search(30);
    if(result.first){
        cout << result.first->getKey(result.second) << "\n";
    }
    else {
        cout << "Not Found\n";
    }
    //cout << boolalpha << treecampeon.search(13) << '\n';
    // No se está insertando de la manera correcta
    // Hay problemas con el destructor
    return EXIT_SUCCESS;
}
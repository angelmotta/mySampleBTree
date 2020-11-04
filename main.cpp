#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    BTree<int> treecampeon(3);
    treecampeon.insert(1);
    treecampeon.insert(3);
    treecampeon.insert(7);
    treecampeon.insert(10);
    treecampeon.insert(11);
    treecampeon.insert(13);
    treecampeon.insert(14);
    treecampeon.insert(15);
    treecampeon.insert(18);
    treecampeon.insert(16);
    treecampeon.insert(19);
    treecampeon.insert(24);
    treecampeon.insert(25);
    treecampeon.insert(26);
    treecampeon.insert(21);
    treecampeon.insert(4);
    treecampeon.insert(5);
    treecampeon.insert(20);
    treecampeon.insert(22);
    treecampeon.insert(2);
    treecampeon.insert(17);
    treecampeon.insert(12);
//    treecampeon.insert(6);
//    treecampeon.traverse();
    treecampeon.print();
//    treecampeon.remove(6);
//    treecampeon.traverse();
//    treecampeon.print();
    //old test
    /*
    BTree<int> treecampeon(3);
    treecampeon.insert(10);
    treecampeon.insert(20);
    treecampeon.insert(5);
    treecampeon.insert(6);
    treecampeon.insert(12);
    treecampeon.insert(30);
    auto result = treecampeon.search(6);
    treecampeon.printSearch(result);
    result = treecampeon.search(13);
    treecampeon.printSearch(result);
    result = treecampeon.search(30);
    treecampeon.printSearch(result);
    treecampeon.traverse();
    treecampeon.print();
    */
    // Hay problemas con el destructor
    return EXIT_SUCCESS;
}
#include <iostream>
#include <functional>
#include "linked_list.hpp"

void linkedList() {
    LinkedList<int> *list = new LinkedList<int>();
    int elements[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++) {
        std::cout << *list << std::endl;
        list->insertStart(elements[i]);
    }
    std::cout << *list << std::endl;

    delete list;
}

int main() {
    linkedList();
}
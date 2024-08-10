#include "LinkedList.hpp"
#include <iostream>
#include <memory> // Needed for std::unique_ptr

int main() {
    LinkedList<int> list;

    // Create a LinkedList of integer
    list.insertStart(10);
    list.insertEnd(20);
    list.insertEnd(30);
    list.insertStart(5);

    // Display the list
    std::cout << "List after insertion: " << list << std::endl; // Expected: {5, 10, 20, 30}

    // Test peekStart and peekEnd
    std::cout << "First element (peekStart): " << list.peekStart() << std::endl; // Expected: 5
    std::cout << "Last element (peekEnd): " << list.peekEnd() << std::endl; // Expected: 30

    // Test get function
    std::cout << "Element at index 2: " << list.get(2) << std::endl; // Expected: 20

    // Test removal from start and end
    int removedStart = list.removeStart();
    std::cout << "Removed first element: " << removedStart << std::endl; // Expected: 5
    std::cout << "List after removing the first element: " << list << std::endl; // Expected: {10, 20, 30}

    int removedEnd = list.removeEnd();
    std::cout << "Removed last element: " << removedEnd << std::endl; // Expected: 30
    std::cout << "List after removing the last element: " << list << std::endl; // Expected: {10, 20}

    // Test insertion at a specific index
    list.insert(15, 1);
    std::cout << "List after inserting 15 at index 1: " << list << std::endl; // Expected: {10, 15, 20}

    // Test the getArray method
    std::unique_ptr<int[]> array = list.getArray();
    std::cout << "Array representation of the list: {";
    for (std::size_t i = 0; i < list.size; i++) {
        std::cout << array[i];
        if (i < list.size - 1) std::cout << ", ";
    }
    std::cout << "}" << std::endl; // Expected: {10, 15, 20}


    return 0;
}

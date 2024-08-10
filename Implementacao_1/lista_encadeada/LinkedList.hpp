#include <iostream>
#include <stdexcept>
#include <sstream> // Needed for std::ostringstream
#include <memory>

/**
 * @file LinkedList.h
 * @brief Implementation of a singly linked list template class.
 *
 * This LinkedList class template provides a basic implementation of a singly linked list
 * with common operations such as insertion, removal, and element access. The list supports 
 * any data type `T` and dynamically manages memory for the list nodes. 
 *
 * Key Public Methods:
 * - **Accessors**: {peekStart, peekEnd, get}
 * - **Inserters**: {insertStart, insertEnd, insert} 
 * - **Removers**: {removeStart, removeEnd, remove} 
 * - **Utility**: {getString, getArray}
 * 
 * Operator overload: 
 * - Support for standart stream output (std::ostream) operator (<<)
 * 
 * Exception Handling:
 * - std::out_of_range for invalid index access.
 * - Functions that do not throw exceptions marked as noexcept
 *
 * Memory Management:
 * - The destructor (`~LinkedList`) ensures that all dynamically allocated nodes are properly deleted.
 *
 * Usage:
 * ```
 * LinkedList<int> list;
 * list.insertStart(10);
 * list.insertEnd(20);
 * std::cout << list; // Outputs: {10, 20}
 * ```
 *
 * @tparam T The type of elements stored in the linked list.
 */

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T value;
        Node *next;

        Node(T val) : value(val), next(nullptr) {}
    };


public:
    Node *header = new Node(T());
    Node *end = header;
    std::size_t size = 0;

    // Constructor
    LinkedList() noexcept {}

    // Acessor Methods
    T peekStart() { 
        return get(0); 
    } 

    T peekEnd() { 
       return this->end->value;
    }

    T get(std::size_t index) {
        if (index >= size || index < 0) {
            throw std::out_of_range("Index out of bounds");
        }

        Node *node = header->next;
        while (index > 0) {
            node = node->next;
            index--;
        } 
        return node->value;
    }


    // Insertion methods    
    void insertStart(T value)  noexcept { 
        Node *newNode = new Node(value);
        newNode->next = this->header->next;
        this->header->next = newNode;

        if (this->end == this->header) end = newNode;
        this->size++;
    }

    void insertEnd(T value) noexcept { 
        this->end->next = new Node(value); 
        this->end = this->end->next;
        this->size++;
    }
    
    void insert(T value, std::size_t index) {
        if (index > size || index < 0) {
            throw std::out_of_range("Index out of bounds");
        }

        Node *node = this->header;
        while (index > 0) {
            node = node->next;
            index--;
        }

        Node *newNode = new Node(value);
        newNode->next = node->next;
        node->next = newNode;
        if (node == end) newNode = end;
        this->size++;
    }


    // Removal methods
    T removeStart() { 
        return remove(0); 
    }
    
    T removeEnd() { 
        return remove(size-1); 
    }

    T remove(long index) {
        if (index >= size || index < 0) {
            throw std::out_of_range("Index out of bounds");
        }   

        Node *node = this->header;
        while (index > 0) {
            node = node->next;
            index--;
        }

        Node *rm = node->next;
        node->next = rm->next;
        T res = rm->value;
        this->size--;

        if (rm == this->end) 
            this->end = node;

        delete rm;
        return res;
    }

    // Utility methods
    // Response for ostream class (usually used on std::cout or std::ostringstream)
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) noexcept {
        Node *node = list.header->next;
        if (node == nullptr) {
            os << "{}";
            return os;
        }

        os << "{";
        while (node->next != nullptr) {
            os << node->value << ", ";
            node = node->next;
        }

        os << node->value << "}";
        return os;
    }

    std::string getString() noexcept {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }

    std::unique_ptr<T[]> getArray() noexcept {
        std::unique_ptr<T[]> array(new T[this->size]);
        Node *node = this->header;
        for (std::size_t i = 0; i < this->size; i++) {
            node = node->next;
            array[i] = node->value;
        }
        return array;
    }

    // Deconstructor 
    ~LinkedList() noexcept { 
        Node *node = header;
        while (node != nullptr) {
            Node *nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }
};
#include <iostream>

template <typename T>
class LinkedList {

private:
    class Node {
    public:
        T value;
        Node *next;

        // Constructor
        Node(T val) : value(val), next(nullptr) {}
    };

public:
    Node *header = new Node(T());
    std::size_t size = 0;

    // Constructor
    LinkedList() {}


    void insertStart(T value) {
        Node *newNode = new Node(value);
        newNode->next = header->next;
        header->next = newNode;
        this->size++;
    }

    void insertEnd(T value) {
        Node *node = header;
        while (node->next != nullptr) {
            node = node->next;
        }
        node->next = new Node(value);
        this->size++;
    }

    void insert(T value, long index) {
        if (index > size) {
            // No error handling    
            return;
        }

        Node *node = header;
        while (index > 0) {
            node = node->next;
            index--;
        }

        Node *newNode = new Node(value);
        newNode->next = node->next;
        node->next = newNode;
        this->size++;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
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

    
    ~LinkedList() { //deconstructor
        Node *node = header;
        while (node != nullptr) {
            Node *nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }
};
#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
    T* value;
    Node* next;

    //construtores
    Node() {
        value = nullptr;
        next = nullptr;
    }
    Node(T value) {
        this->value = new T(value);
        next = nullptr;
    }
    Node(T vale, Node* next) {
        this->value = new T(value);
        this->next = next;
    }
    Node(T* value) {
        this->value = value;
        next = nullptr;
    }
    Node(T* vale, Node* next) {
        this->value = value;
        this->next = next;
    }

    //destrutores
    ~Node() {
        delete value;
    }
};
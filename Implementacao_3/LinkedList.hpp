#include <iostream>
#include "Node.hpp"

template <typename T>
class LinkedList {
private:
    Node<T>* head;  // Célula cabeça
    Node<T>* tail;  // Aponta para o último nó (ou célula cabeça se lista estiver vazia)
    int length;

public:
    // Construtor padrão
    LinkedList() {
        head = tail = new Node<T>();
        length = 0;
    }

    LinkedList(int lenght) {
        head = tail = new Node<T>();
        for(int i=0; i<lenght; i++){
            push_back(new T());
        }
        this->length = lenght;
    }

    // Construtor de cópia
    LinkedList(const LinkedList<T>& other) : LinkedList() {
        Node<T>* current = other.head->next;  // Pula a célula cabeça
        while (current != nullptr) {
            push_back(*(current->value));
            current = current->next;
        }
    }

    // Destrutor
    ~LinkedList() {
        clear();
        delete head;  // Libera a célula cabeça
    }

    // Retorna o tamanho da lista
    int size() {
        return length;
    }

    // Verifica se a lista está vazia
    bool isEmpty() {
        return length == 0;
    }

    // Limpa a lista
    void clear() {
        while (!isEmpty()) {
            pop_back();
        }
    }

    // Obtém o nó em um índice específico (pula célula cabeça)
    Node<T>* get(int index) {
        if (index < 0 || index >= length) {
            throw out_of_range("Índice fora do alcance.");
        }
        Node<T>* current = head->next; 
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    Node<T>* getBegin() const {
        return head->next;
    }

    Node<T>* getEnd() const {
        return tail;
    }

    // Obtém o valor em um índice específico
    T getValue(int index) {
        Node<T>* node = get(index);
        return *(node->value);
    }

    // Define o valor de um nó em um índice específico
    void set(int index, T newValue) {
        Node<T>* node = get(index);
        *(node->value) = newValue;
    }

    // Insere um valor em um índice específico
    void insert(int index, T newValue) {
        if (index < 0 || index > length) {
            throw out_of_range("Índice fora do alcance.");
        }
        if (index == 0) {
            head->next = new Node<T>(newValue, head->next);  // Insere após a célula cabeça
            if (tail == head) {
                tail = head->next;
            }
        } else {
            Node<T>* prev = get(index - 1);
            prev->next = new Node<T>(newValue, prev->next);
            if (prev->next->next == nullptr) {
                tail = prev->next;
            }
        }
        length++;
    }

    // Remove um nó de um índice específico
    void remove(int index) {
        if (index < 0 || index >= length) {
            throw out_of_range("Índice fora do alcance.");
        }
        Node<T>* nodeToDelete;
        if (index == 0) {
            nodeToDelete = head->next;
            head->next = nodeToDelete->next;
        } else {
            Node<T>* prev = get(index - 1);
            nodeToDelete = prev->next;
            prev->next = nodeToDelete->next;
            if (prev->next == nullptr) {
                tail = prev;
            }
        }
        delete nodeToDelete;
        length--;
    }

    // Adiciona um valor ao final da lista
    void push_back(T newValue) {
        tail->next = new Node<T>(newValue);
        tail = tail->next;
        length++;
    }

    void push_back(T* newValue) {
        tail->next = new Node<T>(*(newValue));
        tail = tail->next;
        length++;
    }

    // Remove o último valor da lista
    void pop_back() {
        if (isEmpty()) {
            throw out_of_range("A lista está vazia.");
        }
        Node<T>* nodeToDelete;
        if (length == 1) {
            nodeToDelete = tail;
            head->next = nullptr;  // Célula cabeça agora não aponta para nada
            tail = head;
        } else {
            Node<T>* prev = get(length - 2);
            nodeToDelete = tail;
            prev->next = nullptr;
            tail = prev;
        }
        delete nodeToDelete;
        length--;
    }

    // Busca por um valor e retorna o índice
    int find(const T& value) const {
        Node<T>* current = head->next;  // Pula a célula cabeça
        int index = 0;
        while (current != nullptr) {
            if (*(current->value) == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;  // Não encontrado
    }

    // Operador para acesso mutável
    T operator[](const int index) {
        return get(index);  // Retorna uma referência ao valor
    }

};
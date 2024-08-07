#include <iostream>

//--------------------------------------------------------------------//
// Classe node - nó da pilha que comporta o valor de tipo T (genérico)//
// assim como o endereço de memória do próximo nó.                    //
//--------------------------------------------------------------------//
template <typename T>
class Node {
    public:
        T value;
        Node<T>* next;
    
        Node(T val){
            value = val;
            next = nullptr;
        }
        Node(T val, Node<T>* nex){
            value = val;
            next = nex;
        }

        void setValue(T value){
            this.value = value;
        }
        void setNext(Node<T>* next){
            this.next = next;
        }


        int getValue(){
            return value;
        }
        int getNext(){
            return next;
        }

};

//--------------------------------------------------------------------//
// Classe stack - A pilha em se, que comporta o endereço de memória do//
// primeiro nó.                                                       //
//---------------------------------//---------------------------------//
// Observações:                                                       //
//   - O destrutor foi construido de modo à garantir que todos        //
//   os nós sejam destruidos juntamente ao objeto atual de stack.     //
//                                                                    //
//   - A função de verificar se um elemento existe exige que o        //
//   operador "==" esteja definido no elemento genérico, sendo        //
//   necessário uma possivel sobrecarga de operador para a devida     //
//   operação do objeto genérico.                                     //
//                                                                    //
//   - Assim como o operador ==, para imprimir na tela o objeto       //
//   genérico, caso ele não imprima o valor esperado talvez seja      //
//   necessário sobrecarga do operador "<<"                           //
//--------------------------------------------------------------------//

template <typename T>
class Stack {
    private:
        Node<T>* first;
    public:
        Stack(){
            first = nullptr;
        }
        ~Stack(){
            while (first != nullptr){
                pop();
            }
        }

        void push(Node<T>* insertedNode){
            insertedNode->next = first;
            first = insertedNode;
        }
        void push(T value){
            first = new Node<int>(value, first);
        }
        T pop(){
            Node<T>* tmp = first;
            T removedValue = tmp->value;
            first = first->next;
            delete tmp;
            return removedValue;
        }

        bool contains(T test){
            bool result = false;
            Node<T>* tmp = first;
            while(tmp != nullptr){
                if(tmp->value == test){
                    tmp = nullptr;
                    result = true;
                } else {
                    tmp = tmp->next;
                }
            }
            return result;
        }

        void print(){
            std::cout << "Stack values representation:\n";
            Node<T>* tmp = first;
            while(tmp != nullptr){
                std::cout << tmp->value << " -> ";
                tmp = tmp->next;
            }
            std::cout << "null\n";
        }
};


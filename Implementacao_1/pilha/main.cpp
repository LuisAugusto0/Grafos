#include "pilha.hpp"
#include <iostream>
#include <string>

int main() {
    // Exemplo de uso com inteiros
    Stack<int> intStack;
    
    // Testes da estrutura
    for(int i=1; i<=10; i++){
        intStack.push(i);
        std::cout << "Push: " << i << std::endl;
    }
    intStack.print(); 
    std::cout << "The stack " << ( intStack.contains(9) ? "contains the number 9.\n" : "don't contains the number 9.\n" );
    std::cout << "Pop: " << intStack.pop() << std::endl;
    std::cout << "Pop: " << intStack.pop() << std::endl;
    intStack.print(); 
    std::cout << "The stack " << ( intStack.contains(9) ? "contains the number 9.\n" : "don't contains the number 9.\n" );
    

    return 0;
}

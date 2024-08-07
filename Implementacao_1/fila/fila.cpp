#include <iostream>
#include <cstdio>

class Celula {
public:
    int elemento;
    Celula *prox;

    Celula(int elemento) {
        this->elemento = elemento;
        this->prox = NULL;
    }

    Celula() {
        this->elemento = -1;
        this->prox = NULL;
    }
};

class Fila {
private:
    Celula *primeiro;
    Celula *ultimo;

public:
    Fila() {
        primeiro = new Celula();
        ultimo = primeiro;
    }

    void inserir(int elemento) {
        ultimo->prox = new Celula(elemento);
        ultimo = ultimo->prox;
    }

    int remover() {
        if (primeiro == ultimo) {
            throw std::runtime_error("Fila vazia!");
        }
        Celula *tmp = primeiro;
        primeiro = primeiro->prox;
        int resp = primeiro->elemento;
        delete tmp;
        return resp;
    }

    void mostrar() {
        printf("[");
        for (Celula *i = primeiro->prox; i != NULL; i = i->prox) {
            printf("%d", i->elemento);
            if (i->prox != NULL) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    bool buscar(int elemento) {
        for (Celula *i = primeiro->prox; i != NULL; i = i->prox) {
            if (i->elemento == elemento) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Fila *fila = new Fila();
    fila->inserir(9);
    fila->inserir(5);
    fila->inserir(4);
    fila->inserir(3);
    fila->mostrar();

    if (fila->buscar(9)) {
        printf("Elemento 9 encontrado na fila.\n");
    } else {
        printf("Elemento 9 não encontrado na fila.\n");
    }

    if (fila->buscar(1)) {
        printf("Elemento 1 encontrado na fila.\n");
    } else {
        printf("Elemento 1 não encontrado na fila.\n");
    }

    if (fila->buscar(8)) {
        printf("Elemento 8 encontrado na fila.\n");
    } else {
        printf("Elemento 8 não encontrado na fila.\n");
    }

    int x1 = fila->remover();
    int x2 = fila->remover();
    printf("Apos as remocoes de %d e %d:\n", x1, x2);
    fila->mostrar();

    delete fila;
    return 0;
}

#include <iostream>
#include <ctype.h>

//Start of Cell Class
class Cell{
    //Public Elements of Cell Class
    public:
    int element;
    Cell *right;
    Cell *left;
    Cell *lower;
    Cell *upper;
    //End Public Elements of Cell Class

    //Constructors Methods
    Cell(int element){
        this->element = element;
        this->lower = NULL;
        this->upper = NULL;
        this->left = NULL;
        this->right = NULL;
    }

    Cell(){
        this->element = -1;
        this->lower = NULL;
        this->upper = NULL;
        this->left = NULL;
        this->right = NULL;
    }
    //End Constructors Methods
};//End of Cell Class

//Start of Matrix Class
class Matrix{
    //Public Elements of Matrix Class
    public:
    Cell *start;
    int columns;
    int lines;
    int quantityOfItens;

    //Matrix Methods
    Cell *Generate(){
        Cell *start = new Cell();
        Cell *aux = start;
        //printf("Lines: %i - Columns: %i\n", this->lines, this->columns);
        for(int i = 0; i < this->lines - 1; i++){
            aux->lower = new Cell();
            aux->lower->upper = aux;
            aux = aux->lower;
        }   
        aux = start;
        
        for(int i = 0; i < this->lines - 1; i++){
            aux->right = new Cell();
            Cell *auy = aux->right;
            auy->left = aux;
            Cell *auz = aux->lower;    
            for(int j = 0; j < this->columns - 1; j++){
                auy->lower = new Cell();
                auy->lower->upper = auy;
                auy = auy->lower;
                auy->left = auz;
                auz->right = auy;
                auz = auz->lower;
            }
            aux = aux->right;
        }
        return start;
    }

    void Insert(int value){
        if(quantityOfItens < (this->columns * this->lines)){
            int i = quantityOfItens;
            Cell *aux = this->start;
            while(i >= this->columns){
                i -= this->columns;
                aux = aux->lower;
            }
            if(i > 0){
                for(int j = 0; j < i; j++){
                    aux = aux->right;
                }
            }
            aux->element = value;
            quantityOfItens++;
        }
    }

    void Show(){
        Cell *aux = this->start;
        for(int i = 0; i < this->lines; i++){
            Cell *auy = aux;
            for(int j = 0; j < this->columns; j++){
                printf("Val[%i][%i]: %i ", i, j, auy->element);
                auy = auy->right;
            }
            printf("\n");
            if(i < this->lines - 1){
                aux = aux->lower;
            }
        }
        
    }

    //Matrix Constructors Methods
    Matrix(int columns, int lines){
        this->columns = columns;
        this->lines = lines;
        this->quantityOfItens = 0;
        this->start = Generate();
    }

    Matrix(){
        this->columns = 0;
        this->lines = 0;
        this->quantityOfItens = 0;
        this->start = Generate();   
    }

};

int main(void){
    Matrix *matrix;
    printf("Teste\n");
    matrix = new Matrix(2, 2);
    printf("Lines: %i - Columns: %i\n\n", matrix->lines, matrix->columns);
    matrix->Show();
    printf("\n");
    matrix->Insert(9);
    matrix->Show();
    printf("\n");
    matrix->Insert(12);
    matrix->Show();
    printf("\n");
    matrix->Insert(15);
    matrix->Show();
    printf("\n");
    matrix->Insert(18);
    matrix->Show();
    printf("\n");
    matrix->Insert(21);
    matrix->Show();
    printf("\n");
        printf("Teste\n");
    matrix = new Matrix(3, 3);
    printf("Lines: %i - Columns: %i\n\n", matrix->lines, matrix->columns);
    matrix->Show();
    printf("\n");
    matrix->Insert(9);
    matrix->Show();
    printf("\n");
    matrix->Insert(12);
    matrix->Show();
    printf("\n");
    matrix->Insert(15);
    matrix->Show();
    printf("\n");
    matrix->Insert(18);
    matrix->Show();
    printf("\n");
    matrix->Insert(21);
    matrix->Show();
    printf("\n");
    return 0;
}
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
        if(this->quantityOfItens < (this->columns * this->lines)){
            int i = this->quantityOfItens;
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


    int Remove(){
        int resp = 0;
        if(this->quantityOfItens > 0){
            int i = this->quantityOfItens;
            //printf("I - 1: %i\n",i);
            Cell *aux = this->start;
            while(i > this->columns){
                i -= this->columns;
                aux = aux->lower;
            }
            //printf("I - 2: %i\n",i);
            if(i > 0){
                for(int j = 0; j < (i - 1); j++){
                    aux = aux->right;
                }
            }
            resp = aux->element;
            aux->element = -1;
            this->quantityOfItens--;
        }
        return resp;
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

    bool Search(int element){
        Cell *aux = this->start;
        bool resp = false;
        for(int i = 0; i < this->lines; i++){
            Cell *auy = aux;
            for(int j = 0; j < this->columns; j++){
                if(auy->element == element){
                    resp = true;
                    i = this->lines;
                    j = this->columns;
                }
                auy = auy->right;
            }
            if(i < this->lines - 1){
                aux = aux->lower;
            }
        }
        return resp;
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
    matrix->Insert(21);(matrix->columns * matrix->lines);
    matrix->Show();
    printf("\n");
    printf("Removing Elements: \n");
    for(int i = 0; i < (matrix->columns * matrix->lines); i++){
        int removed = matrix->Remove();
        printf("Removed Element: %i\n", removed);
    }
    printf("\nMatrix after removing all elements:\n");
    matrix->Show();
    printf("\n");
    
    Matrix *matrix2 = new Matrix(3, 3);
    printf("Lines: %i - Columns: %i\n\n", matrix2->lines, matrix2->columns);
    matrix2->Show();
    printf("\n");
    matrix2->Insert(9);
    matrix2->Show();
    printf("\n");
    matrix2->Insert(12);
    matrix2->Show();
    printf("\n");
    matrix2->Insert(15);
    matrix2->Show();
    printf("\n");
    matrix2->Insert(18);
    matrix2->Show();
    printf("\n");
    matrix2->Insert(21);
    matrix2->Show();
    printf("\nSearching Elements:\n");
    int vector[] = {0, 1, 9, 15, 20, 18, 21, 4, 3, 17};
    for(int i = 0; i < 10; i++){
        printf("Searched Element: %i\n", vector[i]);
        if(matrix2->Search(vector[i])){
            printf("Found\n");
        }
        else{
            printf("Not found\n");
        }
    }
    return 0;
}
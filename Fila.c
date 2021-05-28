#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valor;
    struct nodo* prox;
} NODO;

typedef struct fila {
    NODO* head;
    NODO* tail;
} FILA;

void iniciarFila (FILA* fila) {
    fila->head = NULL;
    fila->tail = NULL;
}

void adicionar(FILA* fila, int valor) {  
    NODO* novo = (NODO*) malloc(sizeof(NODO));
    novo->valor = valor;
    novo->prox = NULL;
    if (fila->head == NULL) 
        fila->head = novo; 
    else 
        fila->tail->prox = novo; 

    fila->tail = novo;
}

void deletar(FILA* fila) {
    if (fila->head != NULL) {
        NODO* apagar = fila->head;
        fila->head = apagar->prox;
        free(apagar);
        if (fila->head == NULL) 
            fila->tail = NULL;
    }
}

void imprimirFila(FILA* fila) {
    NODO* auxiliar = fila->head;
    while (auxiliar != NULL) {
        printf("|_%d_|", auxiliar->valor);
        auxiliar = auxiliar->prox;
    }
    printf("\n");
}

int length(FILA* fila) {
    NODO* auxiliar = fila->head;
    int length = 0;
    while (auxiliar != NULL) {
        length++;
        auxiliar = auxiliar->prox;
    }
    return length;
}

int main() {
    //Comandos de Teste
    FILA minhaFila;
    iniciarFila(&minhaFila);
    adicionar(&minhaFila , 1);
    adicionar(&minhaFila , 2);
    adicionar(&minhaFila , 3);
    adicionar(&minhaFila , 4);
    deletar(&minhaFila);
    imprimirFila(&minhaFila);

    return 0;
}

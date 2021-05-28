#include<stdio.h>
#include<stdlib.h>

#define TAMANHO_MAXIMO 10 //Define uma constante

//NODO tem: Valor, Próximo*

typedef struct nodo {
    int valor;
    struct nodo* prox;
} NODO;

typedef struct {
    NODO* topo;
} PILHA;

void inicializarPilha(PILHA* pilha) {
	pilha->topo = NULL;
}

void pop(PILHA* pilha){
	if(pilha->topo != NULL){
        NODO* apagar;
        apagar = pilha->topo;
        pilha->topo = apagar->prox;
        free(apagar);
	}
}

void push(PILHA* pilha, int valor) {
    NODO* novo = (NODO*) malloc(sizeof(NODO));
    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo; 
}

void limpaPilha(PILHA* pilha) {
    NODO* apagar;
    NODO* posicao = pilha->topo;
    while(posicao != NULL){
        apagar = posicao;
        posicao = posicao->prox;
        free(apagar);
    }
    pilha->topo = NULL;
}

int length(PILHA* pilha) {
    NODO* element = pilha->topo;
    int i = 0;
    while (element != NULL){
        i++;
        element = element->prox;
    }

    return i;
}

void imprimirPilha(PILHA* pilha) {
    NODO* element = pilha->topo;
    while(element != NULL){
        printf("|_%d_|\n", element->valor);
        element = element->prox;
    }    
    printf("\n");
}

int main() {
    PILHA minhaPilha;
    inicializarPilha(&minhaPilha);

    push(&minhaPilha , 2);
    push(&minhaPilha , 4);
    push(&minhaPilha , 6);

    pop(&minhaPilha);
    imprimirPilha(&minhaPilha);

    return 0;
}
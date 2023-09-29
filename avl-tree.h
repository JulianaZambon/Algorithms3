#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
    nodo *raiz;
    int numNodos;
} arvore;

typedef struct nodo {
    int chave;
    nodo *pai;
    nodo *filhoEsq;
    nodo *filhoDir;
} nodo;

arvore *inicializaArvore();

nodo *inicializaNodo(int valor);

void insereNodo(arvore *avl, nodo *novo);

int buscaNodo();

void removeNodo();

void rotacionaArvore();

void imprimeArvore();

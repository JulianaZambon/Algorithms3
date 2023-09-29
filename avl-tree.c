#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

arvore *inicializaArvore() {
    arvore *AVL;
    AVL->raiz = NULL;
    AVL->numNodos = 0;
    return AVL;
}

nodo *inicializaNodo(int valor) {
    nodo *novo;
    novo->chave = valor;
    novo->pai = NULL;
    novo->filhoEsq = NULL;
    novo->filhoDir = NULL;
    return novo;
}

void insereNodo(arvore *avl, nodo *novo) {
    nodo *aux = NULL;

    /*Se a árvore for vazia, sua raiz vai receber o nodo a ser inserido*/
    if (avl->numNodos <= 0) {
        avl->raiz = novo;
        avl->numNodos++;
        return;
    } else
        aux = avl->raiz;

    /*Se a árvore não for vazia, verifica a posição correta para se 
    colocar o nó. Após o nó ser inserido, verifica se a árvore precisa 
    de alteração para cumprir os critérios de uma AVL, se sim, faz as 
    rotações necessárias*/
    while (aux != NULL) {
        if (novo <= aux) {
            if (aux->filhoEsq == NULL) {
                novo->pai = aux;
                aux->filhoEsq = novo;
                avl->numNodos++;
                return;
            }
            aux = aux->filhoEsq;
        } else {
            if (aux->filhoDir == NULL) {
                novo->pai = aux;
                aux->filhoDir = novo;
                avl->numNodos++;
                return;
            }
            aux = aux->filhoDir;
        }
    }
}

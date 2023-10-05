#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

/*Inicializa uma árvore vazia.*/
arvore *inicializaArvore() {
    arvore *AVL = (struct nodo *)malloc(sizeof(struct nodo)) ;
    AVL->raiz = NULL;
    AVL->numNodos = 0;
    return AVL;
}

/*Inicializa um nodo vazio.*/
nodo *inicializaNodo(int valor) {
    nodo *novo = malloc(sizeof(nodo));
    novo->chave = valor;
    novo->altura = 1;
    novo->pai = NULL;
    novo->filhoEsq = NULL;
    novo->filhoDir = NULL;
    return novo;
}

/*Verifica se a árvore está balanceada e chama a função rotacionaArvore
caso seja necessário rotacioná-la para balanço*/
void verificaBalancoArvore(arvore *avl) {

}

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à esquerda para ser balanceada*/  
void rotacionaArvoreEsquerda(arvore *avl) {
  
}

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à direita para ser balanceada*/  
void rotacionaArvoreDireita(arvore *avl) {
  
}

/*Verifica se um nodo está, ou não, presente na árvore. Caso 
esteja, retorna 1, caso não esteja retorna 0*/
int buscaNodo(arvore *avl, int chave) {

}

/*Insere um nodo específico na árvore*/
arvore *insereNodo(arvore *avl, nodo *novo) {

    /*Se a árvore for vazia, sua raiz vai receber o nodo a ser inserido*/
    if (avl->raiz->chave == NULL) {
        avl->raiz = novo;
        avl->numNodos++;
        printf("O nodo de valor %d foi inserido com sucesso!\n", novo->chave);
        return avl;
    }

    /*Se a árvore não for vazia, verifica a posição correta para se 
    colocar o nó. Após o nó ser inserido, verifica se a árvore precisa 
    de alteração para cumprir os critérios de uma AVL, se sim, faz as 
    rotações necessárias*/
    if (novo->chave < avl->raiz->chave)
        avl->raiz->filhoEsq = insereNodo(avl->raiz->filhoEsq, novo);
    
    else if (novo->chave > avl->raiz->chave)
        avl->raiz->filhoDir = insereNodo(avl->raiz->filhoDir, novo);
    
    else
        perror("O nodo que você deseja novo já está na árvore, não foi possível realizar a inserção.\n");
    
    verificaBalancoArvore(avl);
    return avl;
}

/*Verifica se um nodo está, ou não, presente em 
uma árvore. Caso esteja, o remove.*/
arvore *removeNodo(arvore *avl, int chave) {
    
    /*Caso a árvore seja vazia, retorna erro na remoção. Caso tenha um 
    só elemento, remove-o e retorna uma árvore vazia de raiz nula.*/
    if (avl->numNodos <= 0) {
        perror("Árvore vazia, não foi possível realizar a remoção.\n");
        return avl;
    } else if (avl->numNodos == 1) {
        avl->numNodos--;
        avl->raiz = NULL;
        return avl;
    }
    
    /*Caso a árvore tenha mais de um elemento, verifica se o nodo a ser removido 
    faz parte da árvore, é removido e substituído por seu sucessor imediato, 
    caso não esteja, é retornada uma mensagem de erro*/

    if (buscaNodo(avl, chave) != 0) {
        
        if (chave < avl->raiz->chave)
            avl->raiz->filhoEsq = removeNodo(avl->raiz->filhoEsq, chave);
        
        else if (chave > avl->raiz->chave)
            avl->raiz->filhoDir = removeNodo(avl->raiz->filhoDir, chave);
        
        else {
            //Aqui realiza a remoção do nodo em si

            avl->numNodos--;
            printf("O nodo de valor %d foi removido com sucesso!\n", chave);
            verificaBalancoArvore(avl);    
        }
    
    } else {
        perror("O nodo que você deseja remover não está na árvore, não foi possível realizar a remoção.\n");
        return avl;
    }

    return avl;
}

/*Imprime recursivamente a estrutura de uma árvore.*/
void imprimeArvore(arvore *avl) {
    
}

/*Libera a memória alocada para uma árvore.*/
void destroiArvore(arvore *avl) {
    free(avl);
}

#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

/*Inicializa uma árvore vazia.*/
arvore *inicializaArvore() {
    arvore *AVL = (arvore *)malloc(sizeof(arvore));
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

/*Calcula o máximo de dois números*/
int calculaMaximo(int a, int b) {
    if (a > b)
        return a;
    return b;
}

/*Verifica se a árvore está balanceada e chama a função rotacionaArvore
caso seja necessário rotacioná-la para balanço*/
nodo *verificaBalancoArvore(nodo *raiz) {
    if (raiz == NULL)
        return NULL;

    int alturaEsq = (raiz->filhoEsq != NULL) ? raiz->filhoEsq->altura : 0;
    int alturaDir = (raiz->filhoDir != NULL) ? raiz->filhoDir->altura : 0;
    int balanco = alturaEsq - alturaDir;

    if (balanco > 1) {
        if (raiz->chave > raiz->filhoEsq->chave)
            return rotacionaArvoreDireita(raiz);
        
        else {
            raiz->filhoEsq = rotacionaArvoreEsquerda(raiz->filhoEsq);
            return rotacionaArvoreDireita(raiz);
        }
    }

    if (balanco < -1) {
        if (raiz->chave < raiz->filhoDir->chave)
            return rotacionaArvoreEsquerda(raiz);
        
        else {
            raiz->filhoDir = rotacionaArvoreDireita(raiz->filhoDir);
            return rotacionaArvoreEsquerda(raiz);
        }
    }

    //Atualiza a altura do nó após a rotação
    raiz->altura = 1 + calculaMaximo(alturaEsq, alturaDir);

    //Verifica balanço das subárvores recursivamente
    raiz->filhoEsq = verificaBalancoArvore(raiz->filhoEsq);
    raiz->filhoDir = verificaBalancoArvore(raiz->filhoDir);

    return raiz;
}

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à esquerda para ser balanceada*/  
nodo *rotacionaArvoreEsquerda(nodo *aux) {
    if (aux == NULL)
        return NULL;
    
    nodo *nodoEsq = aux->filhoEsq;
    
    //Se nodoEsq for nulo, não há rotação a ser feita
    if (nodoEsq == NULL)
        return aux;


    //Realiza a rotação
    nodo *nodoDir = (nodoEsq->filhoDir != NULL) ? nodoEsq->filhoDir : NULL;    
    nodoEsq->filhoDir = aux;
    aux->filhoEsq = nodoDir;

    //Atualiza as alturas após a rotação
    aux->altura = 1 + calculaMaximo((aux->filhoEsq != NULL) ? aux->filhoEsq->altura : 0, (aux->filhoDir != NULL) ? aux->filhoDir->altura : 0);
    nodoEsq->altura = 1 + calculaMaximo((nodoEsq->filhoEsq != NULL) ? nodoEsq->filhoEsq->altura : 0, (nodoEsq->filhoDir != NULL) ? nodoEsq->filhoDir->altura : 0);

    return nodoEsq;
}

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à direita para ser balanceada*/  
nodo *rotacionaArvoreDireita(nodo *aux) {
    if (aux == NULL) 
        return NULL;
    
    nodo *nodoDir = aux->filhoDir;

    //Se nodoDir for nulo, não há rotação a ser feita
    if (nodoDir == NULL) 
        return aux;

    //Realiza a rotação
    nodo *nodoEsq = (nodoDir->filhoEsq != NULL) ? nodoDir->filhoEsq : NULL;
    nodoDir->filhoEsq = aux;
    aux->filhoDir = nodoEsq;

    //Atualiza as alturas após a rotação
    aux->altura = 1 + calculaMaximo((aux->filhoEsq != NULL) ? aux->filhoEsq->altura : 0, (aux->filhoDir != NULL) ? aux->filhoDir->altura : 0);
    nodoDir->altura = 1 + calculaMaximo((nodoDir->filhoEsq != NULL) ? nodoDir->filhoEsq->altura : 0, (nodoDir->filhoDir != NULL) ? nodoDir->filhoDir->altura : 0);

    return nodoDir;
}

/*Verifica se um nodo está, ou não, presente na árvore. Caso 
esteja, retorna 1, caso não esteja retorna 0*/
int buscaNodo(nodo *raiz, int chave) {
    if (raiz == NULL)
        return 0;
   
    /*Se a árvore não for vazia, verifica se o nó em questão é encontrado*/
    if (raiz->chave == chave)
        return 1;

    if (raiz->chave > chave)
        return buscaNodo(raiz->filhoEsq, chave);

    return buscaNodo(raiz->filhoDir, chave);
}

/*Insere um nodo específico na árvore*/
arvore *insereNodo(arvore *avl, nodo *novo) {

    /*Se a árvore for vazia, sua raiz vai receber o nodo a ser inserido*/
    if (avl->raiz == NULL) {
        avl->raiz = novo;
        avl->numNodos++;
        return avl;
    }

    /*Se a árvore não for vazia, verifica a posição correta para se 
    colocar o nó. Após o nó ser inserido, verifica se a árvore precisa 
    de alteração para cumprir os critérios de uma AVL, se sim, faz as 
    rotações necessárias*/
    nodo *atual = avl->raiz;
    while (atual != NULL) {    
        
        if (novo->chave < atual->chave) {
            if (atual->filhoEsq == NULL) {
                atual->filhoEsq = novo;
                novo->pai = atual;
                avl->numNodos++;
                break;
            
            } else
                atual = atual->filhoEsq;
        
        } else if (novo->chave > atual->chave) {
            if (atual->filhoDir == NULL) {
                atual->filhoDir = novo;
                novo->pai = atual;
                avl->numNodos++;
                break;
            
            } else
                atual = atual->filhoDir; 
        
        } else
            break;
    }

    //Atualiza as alturas dos nodos na árvore
    atual = novo->pai;
    while (atual != NULL) {
        int alturaEsq = (atual->filhoEsq != NULL) ? atual->filhoEsq->altura : 0;
        int alturaDir = (atual->filhoDir != NULL) ? atual->filhoDir->altura : 0;
        atual->altura = 1 + calculaMaximo(alturaEsq, alturaDir);
        atual = atual->pai;
    }
    verificaBalancoArvore(avl->raiz);

    return avl;
}

/*Verifica se um nodo está, ou não, presente em 
uma árvore. Caso esteja, o remove.*/
arvore *removeNodo(arvore *avl, int chave) {
        
        //Se a árvore for vazia, retorna erro
        if (avl->raiz == NULL)
            return avl;
    
        /*Se a árvore não for vazia, verifica 
        se o nó em questão é encontrado*/
        nodo *atual = avl->raiz;
        while (atual != NULL) {
            
            if (chave < atual->chave)
                atual = atual->filhoEsq;
            
            else if (chave > atual->chave)
                atual = atual->filhoDir;
            
            else
                break;
        }
    
        /*Se o nó não for encontrado, retorna erro*/
        if (atual == NULL) {
            free(atual);
            return avl;
        }        

        /*Se o nó for encontrado, verifica se ele é uma folha, se for, 
        o remove e atualiza as alturas dos nodos na árvore*/
        if (atual->filhoEsq == NULL && atual->filhoDir == NULL) {
            if (atual->pai == NULL) {
                avl->raiz = NULL;
                free(atual);
                avl->numNodos--;
                return avl;
            }
    
            if (atual->pai->filhoEsq == atual)
                atual->pai->filhoEsq = NULL;
            
            else
                atual->pai->filhoDir = NULL;
            
            avl->numNodos--;
        
        /*Se o nó não for uma folha, verifica se ele tem apenas um filho, 
        se tiver, o remove e atualiza as alturas dos nodos na árvore*/
        } else if (atual->filhoEsq == NULL || atual->filhoDir == NULL) {
            nodo *filho = (atual->filhoEsq != NULL) ? atual->filhoEsq : atual->filhoDir;
            if (atual->pai == NULL) {
                avl->raiz = filho;
                free(atual);
                avl->numNodos--;
                return avl;
            }
        
            if (atual->pai->filhoEsq == atual)
                atual->pai->filhoEsq = filho;
            
            else
                atual->pai->filhoDir = filho;

            filho->pai = atual->pai;
            avl->numNodos--;
            free(filho);

        /*Se o nó não for uma folha e tiver dois filhos, verifica se o
        sucessor direto do nó é seu filho direito, se for, o remove e
        atualiza as alturas dos nodos na árvore*/
        } else if (atual->filhoEsq != NULL && atual->filhoDir != NULL) {
            nodo *sucessor = atual->filhoDir;
            
            while (sucessor->filhoEsq != NULL)
                sucessor = sucessor->filhoEsq;
            
            if (sucessor->pai == atual) {
                sucessor->pai->filhoDir = sucessor->filhoDir;
                if (sucessor->filhoDir != NULL)
                    sucessor->filhoDir->pai = sucessor->pai;
            
            } else {
                sucessor->pai->filhoEsq = sucessor->filhoDir;
                if (sucessor->filhoDir != NULL)
                    sucessor->filhoDir->pai = sucessor->pai;
            }
            
            atual->chave = sucessor->chave;
            free(sucessor);
            avl->numNodos--;
        }
    
        /*Atualiza as alturas dos nodos na árvore*/
        atual = atual->pai;
        while (atual != NULL) {
            int alturaEsq = (atual->filhoEsq != NULL) ? atual->filhoEsq->altura : 0;
            int alturaDir = (atual->filhoDir != NULL) ? atual->filhoDir->altura : 0;
            atual->altura = 1 + calculaMaximo(alturaEsq, alturaDir);
            atual = atual->pai;
        }
        verificaBalancoArvore(avl->raiz);
        free(atual);
        return avl;
}

/*Imprime recursivamente a estrutura de uma árvore.*/
void imprimeArvore(nodo *avl) {

    if (avl != NULL) {
        printf("(%d,", avl->chave);
        imprimeArvore(avl->filhoEsq);
        printf(",");
        imprimeArvore(avl->filhoDir);
        printf(")");
    
    } else
        printf("()");
}

/*Libera a memória alocada para uma árvore.*/
void destroiArvore(arvore *avl) {
        
    if (avl->raiz != NULL) {
        avl = removeNodo(avl, avl->raiz->chave);
        destroiArvore(avl);
    
    } else
        free(avl);
}

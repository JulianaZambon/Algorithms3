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
    
    /*Se a árvore for vazia, retorna erro*/
    if (raiz == NULL) {
        perror("Árvore vazia, não foi possível encontrar o nodo.\n");
        return 0;
    }
    
    /*Se a árvore não for vazia, verifica se o nó em questão é encontrado*/
    if (chave < raiz->chave)
        return buscaNodo(raiz->filhoEsq, chave);
    
    else if (chave > raiz->chave)
        return buscaNodo(raiz->filhoDir, chave);
    
    return 1;
}

/*Insere um nodo específico na árvore*/
arvore *insereNodo(arvore *avl, nodo *novo) {

    /*Se a árvore for vazia, sua raiz vai receber o nodo a ser inserido*/
    if (avl->raiz == NULL) {
        avl->raiz = novo;
        avl->numNodos++;
        printf("O nodo de valor %d foi inserido com sucesso!\n", novo->chave);
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
                printf("O nodo de valor %d foi inserido com sucesso!\n", novo->chave);
                break;
            
            } else
                atual = atual->filhoEsq;
        
        } else if (novo->chave > atual->chave) {
            if (atual->filhoDir == NULL) {
                atual->filhoDir = novo;
                novo->pai = atual;
                avl->numNodos++;
                printf("O nodo de valor %d foi inserido com sucesso!\n", novo->chave);
                break;
            
            } else
                atual = atual->filhoDir; 
        
        } else {
            printf("O nodo que você deseja novo já está na árvore, não foi possível realizar a inserção.\n");
            break;
        }
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
    
    /*Caso a árvore seja vazia, retorna erro na remoção. Caso tenha um 
    só elemento, remove-o e retorna uma árvore vazia de raiz nula.*/
    if (avl->numNodos <= 0) {
        perror("Árvore vazia, não foi possível realizar a remoção.\n");
        return avl;
    }
    
    nodo *raiz = avl->raiz;
    nodo *pai = NULL;
    int lado = 0; //raiz(0), esquerda(-1), direita(1)

    /*Caso a árvore tenha mais de um elemento, verifica se o nodo a ser removido 
    faz parte da árvore, é removido e substituído por seu sucessor imediato, 
    caso não esteja, é retornada uma mensagem de erro*/
    if (buscaNodo(avl->raiz, chave) != 0) {
        
        //Encontra o nodo a ser removido e seu pai
        while (raiz != NULL && raiz->chave != chave) {
            pai = raiz;

            if (chave < raiz->chave) {
                raiz = raiz->filhoEsq;
                lado = -1;

            } else {
                raiz = raiz->filhoDir;
                lado = 1;
            }
        }
    
    } else {
        perror("O nodo que você deseja remover não está na árvore, não foi possível realizar a remoção.\n");
        return avl;
    }
    
    nodo *substituto = NULL;

    //Caso o nodo a ser removido tenha um ou nenhum filho
    if (raiz->filhoEsq == NULL)
        substituto = raiz->filhoDir;
    
    else if (raiz->filhoDir == NULL)
        substituto = raiz->filhoEsq;
    
    else {
        
        //Caso tenha dois filhos, encontra o sucessor imediato
        nodo *sucessor = raiz->filhoDir;
        pai = raiz;

        while (sucessor->filhoEsq != NULL) {
            pai = sucessor;
            sucessor = sucessor->filhoEsq;
        }

        if (pai != raiz) {
            pai->filhoEsq = sucessor->filhoDir;
            sucessor->filhoDir = raiz->filhoDir;
        }
        
        substituto = sucessor;
    }

    //Caso o nodo a ser removido seja a raiz
    if (lado == 0) 
        avl->raiz = substituto;
    
    else if (lado == -1)
        pai->filhoEsq = substituto;
    
    else
        pai->filhoDir = substituto;
    
    /*Libera a memória do nodo eliminado, atualiza o número de nodos da 
    árvore, a altura dos nodos e verifica o balanceamento da árvore*/
    free(raiz);
    avl->numNodos--;
    if (avl->raiz != NULL) {
        avl->raiz->altura = 1 + calculaMaximo(avl->raiz->filhoEsq->altura, avl->raiz->filhoDir->altura);
        verificaBalancoArvore(avl->raiz);
    }

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
        
    if (avl->numNodos > 0) {
        avl = removeNodo(avl, avl->raiz->chave);
        destroiArvore(avl);
    
    } else
        free(avl);
}

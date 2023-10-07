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
int verificaBalancoArvore(arvore *avl, int chave) {
    
    //Se a árvore é vazia, já está equilibrada
    if (avl->raiz == NULL)
        return 1;

    int balanco = (avl->raiz->filhoEsq->altura) - (avl->raiz->filhoDir->altura);

    //Se a árvore está desbalanceada, realiza rotações
    if (balanco > 1 || balanco < -1) {

        if (balanco > 1 && chave < avl->raiz->filhoEsq->chave)
            avl->raiz = rotacaoDireita(avl, avl->raiz);

        else if (balanco < -1 && chave > avl->raiz->filhoDir->chave)
            avl->raiz = rotacaoEsquerda(avl, avl->raiz);

        else if (balanco > 1 && chave > avl->raiz->filhoEsq->chave) {
            avl->raiz->filhoEsq = rotacaoEsquerda(avl, avl->raiz->filhoEsq);
            avl->raiz = rotacaoDireita(avl, avl->raiz);

        } else if (balanco < -1 && chave < avl->raiz->filhoDir->chave) {
            avl->raiz->filhoDir = rotacaoDireita(avl, avl->raiz->filhoDir);
            avl->raiz = rotacaoEsquerda(avl, avl->raiz);
        }
    }

    //Verifica balanço das sub-árvores recursivamente
    return verificaBalancoArvore(avl, avl->raiz->filhoEsq) && verificaBalancoArvore(avl, avl->raiz->filhoDir);
}

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à esquerda para ser balanceada*/  
nodo *rotacionaArvoreEsquerda(arvore *avl, nodo *aux) {
    nodo *nodoEsq = aux->filhoEsq;
    nodo *nodoDir = nodoEsq->filhoDir;

    //Realiza a rotação
    nodoEsq->filhoDir = aux;
    aux->filhoEsq = nodoDir;

    //Atualiza as alturas após a rotação
    if (aux != NULL)
        aux->altura = 1 + calculaMaximo(aux->filhoEsq, aux->filhoDir);

    if (nodoEsq != NULL)
        nodoEsq->altura = 1 + calculaMaximo(nodoEsq->filhoEsq, nodoEsq->filhoDir);

    return nodoEsq;
}

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à direita para ser balanceada*/  
nodo *rotacionaArvoreDireita(arvore *avl, nodo *aux) {
    nodo *nodoDir = aux->filhoDir;
    nodo *nodoEsq = nodoDir->filhoEsq;

    //Realiza a rotação
    nodoDir->filhoEsq = aux;
    aux->filhoDir = nodoEsq;

    //Atualiza as alturas após a rotação
    if (aux != NULL)
        aux->altura = 1 + calculaMaximo(aux->filhoEsq, aux->filhoDir);
    
    if (nodoDir != NULL)
        nodoDir->altura = 1 + calculaMaximo(nodoDir->filhoEsq, nodoDir->filhoDir);
    
    return nodoDir;
}

/*Verifica se um nodo está, ou não, presente na árvore. Caso 
esteja, retorna 1, caso não esteja retorna 0*/
int buscaNodo(arvore *avl, int chave) {
    
    /*Se a árvore for vazia, retorna erro*/
    if (avl->raiz->chave == NULL) {
        perror("Árvore vazia, não foi possível encontrar o nodo\n");
        return 0;
    }
    
    /*Se a árvore não for vazia, verifica se o nó em questão é encontrado*/
    if (chave < avl->raiz->chave)
        avl->raiz->filhoEsq = buscaNodo(avl->raiz->filhoEsq, chave);
    
    else if (chave > avl->raiz->chave)
        avl->raiz->filhoDir = buscaNodo(avl->raiz->filhoDir, chave);
    
    else
        return 1;

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
    
    //Atualiza a altura da raiz
    if (avl->raiz->altura != NULL)
        avl->raiz->altura = 1 + calculaMaximo(avl->raiz->filhoEsq, avl->raiz->filhoDir);


    verificaBalancoArvore(avl, novo->chave);
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
    nodo *nodoRemovido = NULL;
    int lado = 0; //raiz(0), esquerda(-1), direita(1)

    /*Caso a árvore tenha mais de um elemento, verifica se o nodo a ser removido 
    faz parte da árvore, é removido e substituído por seu sucessor imediato, 
    caso não esteja, é retornada uma mensagem de erro*/
    if (buscaNodo(avl, chave) != 0) {
        
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
        verificaBalancoArvore(avl, chave);
    }

    return avl;
}

/*Imprime recursivamente a estrutura de uma árvore.*/
void imprimeArvore(arvore *avl) {

    if (avl->raiz->chave != NULL) {
        printf("(%d,", avl->raiz->chave);
        imprimeArvore(avl->raiz->filhoEsq);
        printf(",");
        imprimeArvore(avl->raiz->filhoDir);
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
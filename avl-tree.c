#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

/*Inicializa uma árvore vazia.*/
arvore *inicializaArvore()
{
    arvore *AVL = (arvore *)malloc(sizeof(arvore));
    AVL->raiz = NULL;
    AVL->numNodos = 0;
    return AVL;
}

/*Inicializa um nodo vazio.*/
nodo *inicializaNodo(int valor)
{
    nodo *novo = malloc(sizeof(nodo));
    novo->chave = valor;
    novo->altura = 1;
    novo->filhoEsq = NULL;
    novo->filhoDir = NULL;
    novo->pai = NULL;
    return novo;
}

/*Calcula o máximo de dois números*/
int calculaMaximo(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

nodo *rotacionaArvoreDireita(nodo *aux)
{
    nodo *aux2 = aux->filhoEsq;
    aux->filhoEsq = aux2->filhoDir;
    aux2->filhoDir = aux;
    aux->altura = calculaMaximo(alturaNodo(aux->filhoEsq), alturaNodo(aux->filhoDir)) + 1;
    aux2->altura = calculaMaximo(alturaNodo(aux2->filhoEsq), alturaNodo(aux2->filhoDir)) + 1;
    return aux2;
}

nodo *rotacionaArvoreEsquerda(nodo *aux)
{
    nodo *aux2 = aux->filhoDir;
    aux->filhoDir = aux2->filhoEsq;
    aux2->filhoEsq = aux;
    aux->altura = calculaMaximo(alturaNodo(aux->filhoEsq), alturaNodo(aux->filhoDir)) + 1;
    aux2->altura = calculaMaximo(alturaNodo(aux2->filhoEsq), alturaNodo(aux2->filhoDir)) + 1;
    return aux2;
}

nodo *verificaBalancoArvore(nodo *raiz)
{
    int balanco = alturaNodo(raiz->filhoEsq) - alturaNodo(raiz->filhoDir);

    if (balanco > 1)
    {
        if (alturaNodo(raiz->filhoEsq->filhoEsq) >= alturaNodo(raiz->filhoEsq->filhoDir))
            raiz = rotacionaArvoreDireita(raiz);
        else
        {
            raiz->filhoEsq = rotacionaArvoreEsquerda(raiz->filhoEsq);
            raiz = rotacionaArvoreDireita(raiz);
        }
    }
    else if (balanco < -1)
    {
        if (alturaNodo(raiz->filhoDir->filhoDir) >= alturaNodo(raiz->filhoDir->filhoEsq))
            raiz = rotacionaArvoreEsquerda(raiz);
        else
        {
            raiz->filhoDir = rotacionaArvoreDireita(raiz->filhoDir);
            raiz = rotacionaArvoreEsquerda(raiz);
        }
    }

    return raiz;
}

arvore *insereNodo(arvore *avl, nodo *novo)
{
    if (avl->raiz == NULL)
    {
        avl->raiz = novo;
        avl->numNodos++;
        return avl;
    }

    nodo *aux = avl->raiz;
    nodo *pai = NULL;

    while (aux != NULL)
    {
        pai = aux;

        if (novo->chave < aux->chave)
            aux = aux->filhoEsq;
        else
            aux = aux->filhoDir;
    }

    if (novo->chave < pai->chave)
        pai->filhoEsq = novo;
    else
        pai->filhoDir = novo;

    novo->pai = pai;
    avl->numNodos++;

    nodo *aux2 = novo->pai;

    while (aux2 != NULL)
    {
        aux2->altura = calculaMaximo(alturaNodo(aux2->filhoEsq), alturaNodo(aux2->filhoDir)) + 1;
        aux2 = aux2->pai;
    }

    avl->raiz = verificaBalancoArvore(avl->raiz);
    return avl;
}

int alturaNodo(nodo *nodo)
{
    if (nodo == NULL)
        return 0;
    return nodo->altura;
}

arvore *removeNodo(arvore *avl, int chave)
{
    if (avl->raiz == NULL)
        return avl;

    nodo *aux = avl->raiz;
    nodo *pai = NULL;

    while (aux != NULL && aux->chave != chave)
    {
        pai = aux;

        if (chave < aux->chave)
            aux = aux->filhoEsq;
        else
            aux = aux->filhoDir;
    }

    if (aux == NULL)
        return avl;

    if (aux->filhoEsq == NULL || aux->filhoDir == NULL)
    {
        nodo *filho = aux->filhoEsq ? aux->filhoEsq : aux->filhoDir;

        if (filho == NULL)
        {
            if (pai == NULL)
                avl->raiz = NULL;
            else
            {
                if (aux == pai->filhoEsq)
                    pai->filhoEsq = NULL;
                else
                    pai->filhoDir = NULL;
            }
        }
        else
        {
            if (pai == NULL)
                avl->raiz = filho;
            else
            {
                if (aux == pai->filhoEsq)
                    pai->filhoEsq = filho;
                else
                    pai->filhoDir = filho;
            }

            filho->pai = pai;
        }

        free(aux);
        avl->numNodos--;
    }
    else
    {
        nodo *sucessor = aux->filhoDir;

        while (sucessor->filhoEsq != NULL)
            sucessor = sucessor->filhoEsq;

        aux->chave = sucessor->chave;
        avl = removeNodo(avl, sucessor->chave);
    }

    if (avl->raiz == NULL)
        return avl;

    nodo *aux2 = avl->raiz;

    while (aux2 != NULL)
    {
        aux2->altura = calculaMaximo(alturaNodo(aux2->filhoEsq), alturaNodo(aux2->filhoDir)) + 1;
        aux2 = aux2->pai;
    }

    avl->raiz = verificaBalancoArvore(avl->raiz);
    return avl;
}

/*Verifica se um nodo está, ou não, presente na árvore. Caso
esteja, retorna 1, caso não esteja retorna 0*/
int buscaNodo(nodo *raiz, int chave)
{
    if (raiz == NULL)
        return 0;

    /*Se a árvore não for vazia, verifica se o nó em questão é encontrado*/
    if (raiz->chave == chave)
        return 1;

    if (raiz->chave > chave)
        return buscaNodo(raiz->filhoEsq, chave);

    return buscaNodo(raiz->filhoDir, chave);
}

/*Imprime recursivamente a estrutura de uma árvore.*/
void imprimeArvore(nodo *avl)
{

    if (avl != NULL)
    {
        printf("(%d,", avl->chave);
        imprimeArvore(avl->filhoEsq);
        printf(",");
        imprimeArvore(avl->filhoDir);
        printf(")");
    }
    else
        printf("()");
}

void destroiArvore(nodo *avl)
{
    if (avl != NULL)
    {
        destroiArvore(avl->filhoEsq);
        destroiArvore(avl->filhoDir);
        free(avl);
    }
}

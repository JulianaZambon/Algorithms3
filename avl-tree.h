#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
    nodo *raiz;
    int numNodos;
} arvore;

typedef struct nodo {
    int chave;
    int altura;
    nodo *pai;
    nodo *filhoEsq;
    nodo *filhoDir;
} nodo;

/*Inicializa uma árvore vazia.*/
arvore *inicializaArvore();

/*Inicializa um nodo vazio.*/
nodo *inicializaNodo(int valor);

/*Verifica se a árvore está balanceada e chama a função rotacionaArvore
caso seja necessário rotacioná-la para balanço*/
void verificaBalancoArvore(arvore *avl);

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à esquerda para ser balanceada*/  
void rotacionaArvoreEsquerda(arvore *avl);

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à direita para ser balanceada*/  
void rotacionaArvoreDireita(arvore *avl);

/*Verifica se um nodo está, ou não, presente na árvore. Caso 
esteja, retorna 1, caso não esteja retorna 0*/
int buscaNodo(arvore *avl, int chave);

/*Insere um nodo específico na árvore*/
arvore *insereNodo(arvore *avl, nodo *novo);

/*Verifica se um nodo está, ou não, presente em 
uma árvore. Caso esteja, o remove.*/
arvore *removeNodo(arvore *avl, int chave);

/*Imprime recursivamente a estrutura de uma árvore.*/
void imprimeArvore(arvore *avl);

/*Libera a memória alocada para uma árvore.*/
void destroiArvore(arvore *avl);

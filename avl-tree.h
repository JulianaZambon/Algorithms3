#include <stdio.h>
#include <stdlib.h>

typedef struct nodoArvore {
    int chave;
    int altura;
    nodo *pai;
    nodo *filhoEsq;
    nodo *filhoDir;
} nodo;

typedef struct arvore {
    nodo *raiz;
    int numNodos;
} arvore;

/*Inicializa uma árvore vazia.*/
arvore *inicializaArvore();

/*Inicializa um nodo vazio.*/
nodo *inicializaNodo(int valor);

/*Calcula o máximo de dois números*/
int calculaMaximo(int a, int b);

/*Verifica se a árvore está balanceada e chama a função rotacionaArvore
caso seja necessário rotacioná-la para balanço*/
int verificaBalancoArvore(arvore *avl, int chave);

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à esquerda para ser balanceada*/  
nodo *rotacionaArvoreEsquerda(arvore *avl, nodo *aux);

/*É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à direita para ser balanceada*/  
nodo *rotacionaArvoreDireita(arvore *avl, nodo *aux);

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
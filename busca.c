#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

int main() {
    
    //Cria uma árvore AVL vazia
    arvore *avl = inicializaArvore();

    char comando;
    int chave;

    while (scanf(" %c %d", &comando, &chave) == 2) {

        if (comando == 'i') {
            //Insere nó na árvore
            nodo *novo = inicializaNodo(chave);
            avl = insereNodo(avl, novo);

        } else if (comando == 'r') {
            //Remove nó da árvore
            avl = removeNodo(avl, chave);

        } else if (comando == 'b') {
            
            //Se árvore é vazia, indica erro
            if (avl->raiz != NULL) {
            
                //Se nó não está na árvore, indica erro
                if (buscaNodo(avl->raiz, chave) == 0)
                    fprintf(stderr, "Nó não encontrado.\n");

                //Imprime os nós consultados na busca
                nodo *nodoEncontrado = avl->raiz;
                printf("\n");
                printf("%d", nodoEncontrado->chave);

                while (nodoEncontrado != NULL && nodoEncontrado->chave != chave) {
                    if (nodoEncontrado->chave < chave)
                        nodoEncontrado = nodoEncontrado->filhoDir;

                    else if (nodoEncontrado->chave > chave)
                        nodoEncontrado = nodoEncontrado->filhoEsq;

                    if (nodoEncontrado != NULL)
                        printf(",%d", nodoEncontrado->chave);
                }
                printf("\n"); 

            } else
                fprintf(stderr, "Nó não encontrado: Árvore vazia.\n");
        }

        imprimeArvore(avl->raiz);
        printf("\n\n");
    }

    //Libera a memória da árvore
    destroiArvore(avl);
    return 0;
}

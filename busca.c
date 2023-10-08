#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

int main() {
    // Cria uma árvore AVL vazia
    arvore *avl = inicializaArvore();

    char comando; // i, r ou b
    int chave; // valor do nó

    while (scanf(" %c %d", &comando, &chave) == 2) {
        printf("%c %d\n", comando, chave);

        if (comando == 'i') {
            // Insere o nó na árvore
            nodo *novo = inicializaNodo(chave);
            avl = insereNodo(avl, novo);
        } else if (comando == 'r') {
            // Remove o nó da árvore
            avl = removeNodo(avl, chave);
        } else if (comando == 'b') {
            // Verifica se o nó procurado está na árvore
            if (buscaNodo(avl->raiz, chave))
                printf("Nó presente na árvore. Os nós consultados na busca foram:\n");
            else
                printf("Nó não presente na árvore. Os nós consultados na busca foram:\n");

            // Imprime os nós consultados na busca
            nodo *nodoEncontrado = avl->raiz;
            printf("%d", nodoEncontrado->chave);

            while (nodoEncontrado != NULL && nodoEncontrado->chave != chave) {
                printf(",");
                if (nodoEncontrado->chave < chave)
                    nodoEncontrado = nodoEncontrado->filhoDir;
                else if (nodoEncontrado->chave > chave)
                    nodoEncontrado = nodoEncontrado->filhoEsq;

                if (nodoEncontrado != NULL)
                    printf("%d", nodoEncontrado->chave);
            }
            printf("\n\n");
        }

        // Imprime a estrutura da árvore
        printf("\nEstrutura da árvore:\n");
        imprimeArvore(avl->raiz);
        printf("\n");
    }

    // Libera a memória da árvore
    destroiArvore(avl);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

int main()
{
    // Cria uma árvore AVL vazia
    arvore *avl = inicializaArvore();
    char comando; // i, r ou b
    int chave;    // Chave do nó

    // Lê os comandos e chaves
    while (scanf(" %c %d", &comando, &chave) == 2)
    {
        // insere nó na árvore
        if (comando == 'i') {
            nodo *novo = inicializaNodo(chave);
            avl = insereNodo(avl, novo);

            // remove nó da árvore
        } else if (comando == 'r') {
            avl = removeNodo(avl, chave);

            // busca nó na árvore
        } else if (comando == 'b') {
            if (avl->raiz != NULL) {
                nodo *nodoEncontrado = avl->raiz;
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
            }
        }
        imprimeArvore(avl->raiz);
        printf("\n");
    }
    // Libera a memória da árvore
    destroiArvore(avl);
    return 0;
}

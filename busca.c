#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

int main() {
    // Cria uma árvore AVL vazia
    Arvore *arvore = inicializaArvore();

    char comando;
    int chave;

    while (scanf(" %c %d", &comando, &chave) == 2) {
        printf("%c %d\n", comando, chave);

        if (comando == 'i') {
            // Insere o nó na árvore
            Nodo *novo = inicializaNodo(chave);
            arvore = insereNodo(arvore, novo);
        } else if (comando == 'r') {
            // Remove o nó da árvore
            arvore = removeNodo(arvore, chave);
        } else if (comando == 'b') {
            // Realiza a busca na árvore
            Nodo *nodoEncontrado = buscaNodo(arvore, chave);

            // Imprime os nós consultados na busca, se encontrado
            if (nodoEncontrado) {
                Nodo *nodoAtual = arvore;
                while (nodoAtual) {
                    printf("%d", nodoAtual->chave);
                    nodoAtual = nodoAtual->pai;
                    if (nodoAtual) {
                        printf(",");
                    }
                }
                printf("\n");
            }
        }

        // Imprime a estrutura da árvore
        imprimeArvore(arvore);
        printf("\n");
    }

    // Libera a memória da árvore
    destroiArvore(arvore);
    return 0;
}

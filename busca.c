#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

// Função para imprimir a descrição da árvore no formato especificado
void imprimeDescricaoArvore(Arvore *arvore) {
    if (arvore == NULL) {
        printf("()");
        return;
    }

    printf("(%d,", arvore->chave);
    imprimeDescricaoArvore(arvore->esquerda);
    printf(",");
    imprimeDescricaoArvore(arvore->direita);
    printf(")");
}

int main() {
    // Cria uma árvore AVL vazia
    Arvore *arvore = inicializaArvore();

    char comando;
    int chave;

    while (scanf(" %c %d", &comando, &chave) == 2) {
        printf("%c %d\n", comando, chave);

        if (comando == 'i') {
            // Insere o nó na árvore
            arvore = insereNodo(arvore, chave);
        } else if (comando == 'r') {
            // Remove o nó da árvore
            arvore = removeNodo(arvore, chave);
        } else if (comando == 'b') {
            // Realiza a busca na árvore
            Nodo *nodoEncontrado = buscaNodo(arvore, chave);

            if (nodoEncontrado) {
                // Imprime os nós consultados na busca
                Nodo *nodoAtual = arvore;
                while (nodoAtual) {
                    printf("%d", nodoAtual->chave);
                    nodoAtual = nodoAtual->pai;
                    if (nodoAtual) {
                        printf(",");
                    }
                }
                printf("\n");
            } else {
                printf("Nodo não encontrado.\n");
            }
        }

    // Libera a memória da árvore 
    destroiArvore(arvore);
    return 0;
}


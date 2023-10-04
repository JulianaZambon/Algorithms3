# Algoritmos e Estrutura de Dados III

## Trabalho Prático 1: Implementação de Árvore AVL
Este trabalho prático foi desenvolvido para a disciplina CI1057 - Algoritmos e Estruturas de Dados 3 do Departamento de Informática da UFPR. <br>
O objetivo é implementar as rotinas de manipulação de uma árvore AVL. <br>
Equipe: <br>
- Juliana Zambon, GRR20224168 <br>
- Millena Suiani Costa, GRR2022 <br>

### Estruturas de Dados 
A implementação da árvore AVL utilizou as seguintes estruturas definidas na biblioteca avl-tree.h <br>

```c
typedef struct arvore {
    nodo *raiz;
    int numNodos;
} arvore;
```

```c
typedef struct nodo {
    int chave;
    int altura;
    nodo *pai;
    nodo *filhoEsq;
    nodo *filhoDir;
} nodo;
```

### Bibliotecas desenvolvidas no Projeto
A biblioteca desenvolvida para o trabalho foi a avl-tree.h, que define as structs mencionadas anteriormente.

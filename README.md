# Algoritmos e Estrutura de Dados III

## Trabalho Prático 1: Implementação de Árvore AVL
Este trabalho prático foi desenvolvido para a disciplina CI1057 - Algoritmos e Estruturas de Dados 3 do Departamento de Informática da UFPR. <br>
O objetivo é implementar as rotinas de manipulação de uma árvore AVL. <br>
Equipe: <br>
- Juliana Zambon, GRR20224168 <br>
- Millena Suiani Costa, GRR2022 <br>

### Estruturas de Dados 
A implementação da árvore AVL utilizou as seguintes estruturas definidas na biblioteca avl-tree.h <br>

- Struct Árvore AVL: Contém um ponteiro para um nó da árvore, no caso a raiz, e contém a quantia de nodos dela.
  
```c
typedef struct arvore {
    nodo *raiz;
    int numNodos;
} arvore;
```

- Struct Nodos da Árvore: contém três ponteiros para nós, sendo eles o pai, o filho esquerdo e o filho direito. Além de
uma chave de busca e a altura.
  
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
Também estão definidas as seguintes funções:
<br>
- `arvore *inicializaArvore();`<br>
        Inicializa uma árvore vazia.
   
- `nodo *inicializaNodo(int valor);`<br>
        Inicializa um nodo vazio.
  
- `void verificaBalancoArvore(arvore *avl);` <br>
        Verifica se a árvore está balanceada e chama a função rotacionaArvore
caso seja necessário rotacioná-la para balanço.

- `void rotacionaArvoreEsquerda(arvore *avl);`<br>
        É chamada pela função verificaBalancoArvore caso a árvore AVL esteja 
desbalanceada e precise de rotações à esquerda para ser balanceada.

- `void rotacionaArvoreDireita(arvore *avl);`<br>
        É chamada pela função verificaBalancoArvore caso a árvore AVL esteja
desbalanceada e precise de rotações à direita para ser balanceada.

- `int buscaNodo(arvore *avl, int chave);`<br>
        Verifica se um nodo está, ou não, presente na árvore. Caso esteja,
retorna 1, caso não esteja retorna 0.

- `arvore *insereNodo(arvore *avl, nodo *novo);`<br>
        Insere um nodo específico na árvore.

  
  
- `arvore *removeNodo(arvore *avl, int chave);`<br>
        Verifica se um nodo está, ou não, presente em 
uma árvore. Caso esteja, o remove.

- `void imprimeArvore(arvore *avl);` <br>
        Imprime recursivamente a estrutura de uma árvore.

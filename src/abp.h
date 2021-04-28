#include "lista.h"

struct TNodoA{
  char palavra[46];
  struct TNodoA *esq;
  struct TNodoA *dir;
  lista *ocorrencias; // lista onde sera armazenado os id's das linhas onde ocorre a palavra em questao
};
typedef struct TNodoA PtPalavra;

// cria uma árvore vazia
PtPalavra* cria_arvore(void);

// insesre nodo na arvore
PtPalavra* InsereArvore(PtPalavra *a, char *palavra, int* comp);

// consulta ABP por recursão
PtPalavra* consultaABP(PtPalavra *a, char *palavra, int *comp);

int contaNodos(PtPalavra *a);

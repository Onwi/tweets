#include "lista.h"
#include <stdbool.h>

// definicao do tipo palavra (PtPalavra)
// tipo usado na avl
typedef struct s_palavra{
    char palavra[46]; // maior palavra na lingua portuguesa = 46 letras
    int FB; // fator de balanceamento
    struct s_palavra *esq;
    struct s_palavra *dir;
    lista *ocorrencias; // lista onde sera armazenado os id's das linhas onde ocorre a palavra em questao
} PtPalavra;

/******* FUNCOES PARA A AVL *******/

// rotacao simples direita
PtPalavra *rotacao_direita(PtPalavra *p);

// rotacao simples esquerda
PtPalavra *rotacao_esquerda(PtPalavra *p);

// rotacao dupla direita
PtPalavra *rotacao_dupla_direita(PtPalavra *p);

// rotacao dupla esquerda
PtPalavra *rotacao_dupla_esquerda(PtPalavra *p);

// insere um nodo na avl
PtPalavra *InsereAVL(PtPalavra *a, char *s, int *ok, int *rot);

// caso rotacoes a direita
PtPalavra *Caso1(PtPalavra *a, int *ok, int *rot);

// caso rotacoes a esquerda
PtPalavra *Caso2(PtPalavra *a, int *ok, int *rot);

// calcula a altura de um nodoS
int Altura(PtPalavra *a);

// calcula o fator de balanceamento de um avl
int fator_balanceamento(PtPalavra *a);

PtPalavra *cria_arvore(void);

// consulta AVL por recursão
// retorna true se encontrar uma palavra na avl, falso ao contrario
PtPalavra *consultaAVL(PtPalavra *a, char *s, int *comp);
#include <stdbool.h>
// tipo lista
// usada para armazenar os id's das linhas onde ocorre a palavra em questao
typedef struct s_occ{
    int linha;
    struct s_occ *prox;
} lista;

/******* FUNCOES PARA A LISTA *******/

// inicializa uma lista vazia
lista *inicializa();

// exibe todos os elementos da lista
void imprime(lista *ptLista);

// insere um nodo no inicio da lista
lista *insereInicio(lista *ptLista, int linha);

// insere um nodo no final da lista
lista *insereFim(lista *ptLista, int linha);

// consulta se um id ja esta na lista
// retorna true ou false 
bool consultaLista(lista *ptLista, int linha);

// destroi uma lista
lista *destroi(lista *ptLista);
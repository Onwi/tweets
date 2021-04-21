#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

//inicializa uma lista vazia
lista *inicializa(){
    return NULL;
}


// insere um nodo no inicio da lista
lista *insereInicio(lista *ptLista, int linha){
    lista *novo;

    novo = (lista *)malloc(sizeof(lista));
    novo->linha = linha;
    novo->prox = ptLista;
    ptLista = novo;
    
    return novo;
}

// insere um nodo no final da lista
lista *insereFim(lista *ptLista, int linha){
    lista *novo, *ptAux = ptLista;
    
    novo = (lista *)malloc(sizeof(lista));
    novo->linha = linha;
    novo->prox = NULL;

    if(ptAux){
        for(ptAux = ptLista; ptAux->prox; ptAux = ptAux->prox);
        ptAux->prox = novo;
    }else{
        ptLista = novo;
    }
    return ptLista;
}

// consulta se um id ja esta na lista
// retorna true se o id estiver, ou false caso não 
bool consultaLista(lista *ptLista, int linha){
    lista *ptAux;

    if(ptLista == NULL){
        return false; // se a lista estiver vazia retorna false
    }else{
        for(ptAux = ptLista; ptAux != NULL; ptAux = ptAux->prox){
            if(linha == ptAux->linha){ // se for encontrado o id na lista 
                return true;           // retorna true
            }
        }
        return false;  // se chegar ao fim da lista sem ter encontrado o id, retorna false
    }
}

// destroi uma lista
lista *destroi(lista *ptlista){
    lista *ptaux;
    while (ptlista != NULL){
        ptaux = ptlista;
        ptlista = ptlista->prox;
        free(ptaux);
    }
    free(ptlista);
    return NULL;
}
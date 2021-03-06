#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"

PtPalavra* cria_arvore(void){
  return NULL;
}

// retorna a altura de uma ABP
int Altura(PtPalavra *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura(a->esq);
        Alt_Dir = Altura(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}


// nas duas funções que seguem, comp é uma variavel passada por referencia
// para contar o número de comparções realizadas na inserção e consulta a ABP

// insere nodo na arvore
PtPalavra* InsereArvore(PtPalavra *a, char *palavra, int *comp){
  // insere raiz
  if (a == NULL){
    (*comp)++;
    a = (PtPalavra*) malloc(sizeof(PtPalavra));
    strcpy(a->palavra, palavra);
    a->esq = NULL;
    a->dir = NULL;
    a->ocorrencias = inicializa();
  }
  else if (strcmp(palavra, a->palavra) < 0 ){
        (*comp)+=2;
        a->esq = InsereArvore(a->esq, palavra, comp);
  }
       else{
         (*comp)+=2;
          a->dir = InsereArvore(a->dir, palavra, comp);
       }
  return a;
}

// consulta ABP por recursão
PtPalavra* consultaABP(PtPalavra *a, char *palavra, int *comp) {
  if (a==NULL){
        return NULL;
  }
  else{
    if (strcmp(palavra, a->palavra) == 0){ 
        (*comp)++;
        return a;
    }
    else{
      (*comp)+=2;
      if (strcmp(a->palavra, palavra) > 0){
        return consultaABP(a->esq, palavra, comp);
      }
      else return consultaABP(a->dir, palavra, comp);
    }
  }
}

int contaNodos(PtPalavra *a){
    if(a){
      return contaNodos(a->esq) + contaNodos(a->dir) + 1;
    }
    return 0;
}

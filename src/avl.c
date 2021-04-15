#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"

// calcula o fator de balanceamento de uma abp
int fator_balanceamento(PtPalavra *a)
{
 return (Altura(a->esq) - Altura(a->dir));
}

PtPalavra* cria_arvore(void){
  return NULL;
}

PtPalavra* InsereRaiz(PtPalavra *a, char *s){
  if (a == NULL){
    a = (PtPalavra*) malloc(sizeof(PtPalavra));
    strcpy(a->palavra, s);
    a->esq = NULL;
    a->dir = NULL;
  }
    return(a);
}

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

PtPalavra *rotacao_direita(PtPalavra *p)
{
    PtPalavra *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

PtPalavra *rotacao_esquerda(PtPalavra *p)
{
    PtPalavra *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

PtPalavra *rotacao_dupla_direita(PtPalavra *p)
{
    PtPalavra *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if (v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;
    p = v;
    return p;
}

PtPalavra *rotacao_dupla_esquerda(PtPalavra *p)
{
    PtPalavra *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if (y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;
    p = y;
    return p;
}

// Insere nodo em uma arvore AVL
PtPalavra *InsereAVL(PtPalavra *a, char *s, int *ok)
{
    if (a == NULL) // se a arvore estiver vazia insere como raiz
    {
        a = (PtPalavra *)malloc(sizeof(PtPalavra));
        strcpy(a->palavra, s);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    } // senao, insere um nodo na avl conforme a ordem lexicografica da palavra s
    else if (strcmp(s, a->palavra) < 0) 
    {
        a->esq = InsereAVL(a->esq, s, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a = Caso1(a, ok);
                break;
            }
        }
    }
    else
    {
        a->dir = InsereAVL(a->dir, s, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a, ok);
                break;
            }
        }
    }
    return a;
}

PtPalavra *Caso1(PtPalavra *a, int *ok)
{
    PtPalavra *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

PtPalavra *Caso2(PtPalavra *a, int *ok)
{
    PtPalavra *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotacao_esquerda(a);
    else
        a = rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}
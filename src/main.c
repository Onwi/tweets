#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "lista.h"

int main(int argc, char *argv[]){ 
    FILE *entrada;
    FILE *consulta;
    FILE *saida;

    char separador[] = {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"};
    PtPalavra *arv = cria_arvore(); // cria arvore
    arv->ocorrencias = inicializa();
    char *palavra, linha[1000];

    if(argc != 4){ // testa numero de parametros, se for diferente de 4 encerra
        printf("Numero incorreto de parametros!\n");
        printf("Para chamar o programa digite: %s <entrada> <consulta> <saida>\n", argv[0]);
        return 1;
    }

    // abertura dos arquivos
    if((entrada = fopen(argv[1], "r")) == NULL){
        printf("erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    if((consulta = fopen(argv[2], "r")) == NULL){
        printf("erro ao abrir o arquivo %s\n", argv[2]);
        return 1;
    }
    
    if((saida = fopen(argv[3], "w")) == NULL){
        printf("erro ao abrir o arquivo %s\n", argv[3]);
        return 1;
    }

    int id_char, id_num, ok = 0;
    int compAVL = 0; // variavel para contar o número de comparações na avl
    int rotAVL = 0; // variavel para contar o número de rotações na avl
    int nodos = 0; // conta o número de nodos inseridos

    // le o arquivo de entrada e coloca as palavras na avl
    while(fgets(linha, 5000, entrada)){
        id_char = strtok(linha, ";"); // pega o id
        id_num = atoi(id_char);

        palavra = strtok(NULL, separador); // primeira palavra depois do ;

        /*
            a inserção dos ids está errada, no modo atual atualiza apenas a lista da
            raiz da árvore.
            a inserção dos ids precisa ocorrer dentro da funçao insereAVL, i guess
        */

        while(palavra != NULL){
            if(!consultaAVL(arv, palavra, &compAVL)){ // se a palavra não estiver na estrura
                arv = InsereAVL(arv, palavra, &ok, &rotAVL); // insere ela e o id na avl
                nodos++;
                arv->ocorrencias = insereInicio(arv->ocorrencias, id_num);
            }else{// senão, insere apenas o id, caso este não esteja na lista de ocorrencias
                if(!consultaLista(arv->ocorrencias, id_num)){
                    arv->ocorrencias = insereInicio(arv->ocorrencias, id_num);
                }
            }
            palavra = strtok(NULL, separador); // pega a proxima palavra do tweet
        }
    }

    // fecha os arquivos

    return 0;
}
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
    PtPalavra *aux_lista = cria_arvore(); // variavel auxilixar para inserção das ocorrencias na lista
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
    int compInd = 0; // variavel para contar o número de comparações na avl
    int rotAVL = 0; // variavel para contar o número de rotações na avl
    int nodos = 0; // conta o número de nodos inseridos

    // INDEXAÇÃO
    // le o arquivo de entrada e coloca as palavras na avl
    while(fgets(linha, 5000, entrada)){
        id_char = strtok(linha, ";"); // pega o id
        id_num = atoi(id_char);

        palavra = strtok(NULL, separador); // primeira palavra depois do ;

        while(palavra != NULL){
            if(!consultaAVL(arv, palavra,  compInd)){ // se a palavra não estiver na estrura
                arv = InsereAVL(arv, palavra, &ok, &rotAVL); // insere ela e o id na avl
                nodos++;
                aux_lista = consultaAVL(arv, palavra,  compInd);
                aux_lista->ocorrencias = insereInicio(aux_lista->ocorrencias, id_num);
            }else{// senão, insere apenas o id, caso este não esteja na lista de ocorrencias
                aux_lista = consultaAVL(arv, palavra,  compInd);
                aux_lista->ocorrencias = insereInicio(aux_lista->ocorrencias, id_num);
            }
            palavra = strtok(NULL, separador); // pega a proxima palavra do tweet
        }
    }

    int altArvore = Altura(arv);
    lista *ptAux;

    // CONSULTAS E SAIDAS
    int compCon = 0;
    // consulta e imprime cada palavra da avl no arquivo de saida
    while(fgets(linha, 100, consulta)){
        arv = consultaAVL(arv, linha,  compCon);
        if(arv){ // se a palavra for encontrada, imprime-a no arquivo juntamento com
                 // sua lista de occorencias
            fprintf(saida , "consulta: %s   Palavra encontrada nos tweets ", arv->palavra);
            for(ptAux = arv->ocorrencias; ptAux != NULL; ptAux = ptAux->prox){
                fprintf(saida,"%d", ptAux->linha);
                if(ptAux->prox){
                    fprintf(saida, ", ");
                }
            }
        }
    }
    
    // imprime as estatisticas da indexação
    fprintf(saida, "********** Estatisticas da Indexacao **************");
    fprintf(saida, "nodos = %d", nodos);
    fprintf(saida, "comparacoes = %d", compInd);
    fprintf(saida, "rotacoes = %d", rotAVL);
    fprintf(saida, "altura da arvore = %d", altArvore);
    // estatisticas das consultas
    fprintf(saida, "********** Estatisticas das Consultas **************");
    fprintf(saida, "comparacoes = %d", compCon);

    // fecha os arquivos
    fclose(entrada);
    fclose(consulta);
    fclose(saida);
    
    return 0;
}
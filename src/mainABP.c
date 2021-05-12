#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"


int main(int argc, char *argv[]){
    FILE *entrada;
    FILE *consulta;
    FILE *saida;

    char separador[] = {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"};
    PtPalavra *arv = cria_arvore(); // cria arvore
    PtPalavra *aux_lista = cria_arvore(); // variavel auxilixar para inserção das ocorrencias na lista
    char *palavra, palavraSaida[100], linha[1000];

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

    int id_num;
    char *id_char;
    int compABP = 0; // número de comparações realizadas
    
    // INDEXAÇÃO
    while(fgets(linha, 5000, entrada)){
        id_char = strtok(linha, ";");
        id_num = atoi(id_char);

        palavra = strtok(NULL, separador);

        while(palavra != NULL){
            // se a palavra não estiver na árvore, insere ela e o id na avl
            if(!consultaABP(arv, palavra, &compABP)){
                arv = InsereArvore(arv, palavra, &compABP);
                aux_lista = consultaABP(arv, palavra, &compABP);
                aux_lista->ocorrencias = insereFim(aux_lista->ocorrencias, id_num);
            }else{ // senão insere só o id, caso esse não esteja na lista de ocorrencias
                aux_lista = consultaABP(arv, palavra, &compABP);
                if(!consultaLista(aux_lista->ocorrencias, id_num)){
                    aux_lista->ocorrencias = insereFim(aux_lista->ocorrencias, id_num);
                }
            }
            palavra = strtok(NULL, separador);
        }

    }

    // CONSULTAS E SAIDAS
    int compSaida = 0;
    lista *ptAux;
    PtPalavra *arvCons = cria_arvore();

    while (fgets(linha, 100, consulta)){
        // remove \n da palavra
        linha[strcspn(linha, "\n")] = 0;
        //consulta se a palavra esta na ABP
        // se sim, imprime ela no arquivo de saida
        arvCons = consultaABP(arv, linha, &compSaida);
        if(arvCons){
            fprintf(saida , "consulta %s  -  Palavra encontrada nos tweets ", arvCons->palavra);
            for(ptAux = arvCons->ocorrencias; ptAux != NULL; ptAux = ptAux->prox){
                fprintf(saida, "%d", ptAux->linha);
                if(ptAux->prox){
                    fprintf(saida, ", ");
                }
            }
        }else{
            fprintf(saida, "%s - Palavra não encontrada", linha);
        }
        fprintf(saida, "\n");
    }

    // imprime as estatisticas da indexação
    fprintf(saida, "\n********** Estatisticas da Indexação **************");
    fprintf(saida, "\nnodos = %d", contaNodos(arv));
    fprintf(saida, "\ncomparações = %d", compABP);
    fprintf(saida, "\naltura da árvore = %d", Altura(arv));
    // estatisticas das consultas
    fprintf(saida, "\n\n********** Estatísticas das Consultas **************");
    fprintf(saida, "\ncomparações = %d", compSaida);

    // fecha os arquivos
    fclose(entrada);
    fclose(consulta);
    fclose(saida);
    

    return 0;
}
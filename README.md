# TWEETS

Análise de desempenho de um simulador de buscador de palavras-chave implementado em duas versões, utilizando dois tipos de estruturas de dados diferentes, uma árvore AVL e uma ABP (árvore binária de pesquisa).

A análise do desempenho é feita através do número de comparações realizadas durante as fases de indexação e consulta das palavras nas duas estruturas.

Durante a fase de indexação as palavras são lidas do arquivo de entrada (`<entrada>`) e colocadas na estrutura conforme sua ordem lexicográfica - ou seja, uma P palavra estará na subárvore esquerda de uma palavra Q se ela aparecer antes de P na ordem lexicográfica (função em C: strcmp()) - e as estatísticas das comparações são computadas. Também durante esta fase é armazenado uma lista de ocorrências de id’s em cada nodo da árvore, esses id’s representam o número dos tweets em que cada palavra ocorre ao menos uma vez.
  
Durante a fase de consultas, lê-se do arquivo de consulta (`<consulta>`) as palavras a serem buscadas na estrutura, e se forem encontradas, imprime-as juntamente com seus id’s de ocorrências no arquivo de saída (`<saida>`).

compilar o programa para ABP:
`gcc src/mainABP.c src/ABP.c src/lista.c -o 'tweetsABP'`

e para AVL:
`gcc src/mainAVL.c src/avl.c src/lista.c -o 'tweetsAVL'`

Para depois de compilado chamar o programa a partir da linha de comando usa-se:
`./tweetsAVL(ABP) <entrada> <consulta> <saida>`
  

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// converte uma palavra para minusculo
void converte_minuscula(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
        s[i] = tolower(s[i]);
}

//

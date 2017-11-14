#include <stdio.h>
#include <stdlib.h>
#include "lista_enc/lista_enc.h"
#include "lista_enc/no.h"
#include "archive_reader/leitura_arquivo.h"

int main()
{
    lista_enc_t* cep;
    cep = le_arquivo("/home/gpdse/Ana/ZIP_CODE_search/zipcodes\ archives/BR.txt");
    printf("Hello world!\n");
    return 0;
}

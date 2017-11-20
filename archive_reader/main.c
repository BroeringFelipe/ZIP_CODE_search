#include <stdio.h>
#include <stdlib.h>
#include "../lista_enc/lista_enc.h"
#include "../lista_enc/no.h"
#include "leitura_arquivo.h"

int main()
{
	int i =0;
	zip_code *paises[83];

    //lista_enc_t* cep;
    le_arquivo("../zipcodes_archives/BR.txt", paises, i);
    printf("Hello world!\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lista_enc/no.h"
#include "../lista_enc/lista_enc.h"

#ifndef LEITURA_ARQUIVO_H_INCLUDED
#define LEITURA_ARQUIVO_H_INCLUDED

typedef struct zip_codes zip_code;

void le_arquivo(char* caminho_do_arquivo, zip_code **paises, int i);

#endif // LEITURA_ARQUIVO_H_INCLUDED

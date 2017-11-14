#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lista_enc/no.h"
#include "../lista_enc/lista_enc.h"

#ifndef LEITURA_ARQUIVO_H_INCLUDED
#define LEITURA_ARQUIVO_H_INCLUDED

typedef struct zip_codes zip_code;

lista_enc_t* le_arquivo(char* caminho_do_arquivo);

#endif // LEITURA_ARQUIVO_H_INCLUDED

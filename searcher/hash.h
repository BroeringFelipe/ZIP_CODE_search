//
//  hash.h
//  tabela_hash
//

#ifndef hash_h
#define hash_h

#include <stdio.h>
#include <stdlib.h>
#include "lista_enc/lista_enc.h"
#include "lista_enc/no.h"

typedef struct zip_codes zip_code;

lista_enc_t ***create_hash_table(const char* file_path, int* n_characters, int* n_countries);

#endif /* hash_h */

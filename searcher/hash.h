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

lista_enc_t *create_hash_table(const char* file_path, no_t *hash_table[255][83], int n_characters, int n_countries);

void free_zipcode_list(lista_enc_t *zipcode_list);

char *no_get_country_code(no_t *no);
char *no_get_place_name(no_t *no);

#endif /* hash_h */

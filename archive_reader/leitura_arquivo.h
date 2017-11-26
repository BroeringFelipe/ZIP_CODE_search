/*
 ============================================================================
 Name        : leitura_arquivo.c
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../lista_enc/lista_enc.h"

#ifndef LEITURA_ARQUIVO_H_INCLUDED
#define LEITURA_ARQUIVO_H_INCLUDED

typedef struct zip_codes zip_code;
typedef struct countries_zip_codes country_zip_code;

country_zip_code* create_country_zip_code();
zip_code **create_data_vector(int array_len);

void read_archive(char* file_path, country_zip_code* country);
void imprime_zip_code(zip_code **dados, int tamanho);

zip_code **country_get_data(country_zip_code* country);
void country_set_data(country_zip_code* country, zip_code** data);

int  country_get_tamanho(country_zip_code* country);
void country_set_tamanho(country_zip_code* country, int array_len);

char* data_get_place_name(zip_code **dados, int i);
//void data_array_set_data(zip_code **data_array, zip_code *data, int i);
//zip_code* data_array_get_data(zip_code **data_array, int i);


#endif // LEITURA_ARQUIVO_H_INCLUDED

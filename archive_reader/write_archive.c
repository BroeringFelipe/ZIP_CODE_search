/*
 ============================================================================
 Name        : write_archive.h
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura_arquivo.h"


country_zip_code *organize_database(country_zip_code **countries, int countries_len){

	int i, j, n_addresses;
	int index_country[countries_len];
	unsigned char aux_letter;

	zip_code **data_one_archive;
	zip_code **data_countries;

	char *place_name;

	country_zip_code *one_archive;
	one_archive = create_country_zip_code();

	for(i=0, n_addresses=0 ; i<countries_len; i++){ //count number of addresses
		n_addresses+= country_get_tamanho(countries[i]);
	}


	data_one_archive = create_data_vector(n_addresses);
	country_set_data(one_archive, data_one_archive);
	country_set_tamanho(one_archive, n_addresses);

	for(i=0; i<countries_len; i++){	//Clear indexes
		index_country[i] = 0;
	}

	i=0;
	for(aux_letter = 0; aux_letter < 255; aux_letter++){

		for(j=0; j<countries_len; j++){ //
			data_countries = country_get_data(countries[j]);

			if(country_get_tamanho(countries[j]) > (index_country[j])){
				place_name = data_get_place_name(data_countries, index_country[j]);
				while((unsigned char)place_name[0] == aux_letter){
					data_one_archive[i] = data_countries[index_country[j]];
					index_country[j]++;
					i++;
					if(country_get_tamanho(countries[j]) > (index_country[j])){
						place_name = data_get_place_name(data_countries, index_country[j]);
					}else{
						break;
					}
				}
			}
		}
	}

#ifdef	DEBUG
    printf("\n\nnumero de endereços: %d\n\n", n_addresses);
    
	for(i=0; i<countries_len; i++){
		printf("%d\t%d\t%d\n", i, country_get_tamanho(countries[i]), index_country[i]);
	}
	place_name = data_get_place_name(country_get_data(countries[8]), index_country[5]);
	printf("\n\n%s\n\n",place_name);

	printf("\n\n%d\n\n",place_name[0]);
#endif

	return one_archive;
}

/* ------------------------------------- */
/* Funcao para escrever um unico arquivo */
/* ------------------------------------- */

void write_file(const char* file_path, country_zip_code* countries){

    if (file_path == NULL || countries == NULL){
        fprintf(stderr, "write_file: ponteiros invalidos\n");
        exit(EXIT_FAILURE);
    }
    
    FILE* file = fopen(file_path, "w");
    if (file == NULL){
        perror("write_file:");
        exit(EXIT_FAILURE);
    }
    
                    fprintf(file, "teste");
    
    zip_code **data_one_archive = country_get_data(countries);
    
    int n_addresses = country_get_tamanho(countries), i = 0;
    printf("\ttamanho: %d", n_addresses);
    
    for(i = 0; i < n_addresses; i++){
        fprintf(file, "%s\n", data_get_place_name(data_one_archive, i));
        printf("%s\n", data_get_place_name(data_one_archive, i)); //nao acabei!!!!!!!! :D
    }
    
    fclose(file);
    
}





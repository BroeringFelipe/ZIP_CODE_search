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

printf("\n\n%d\n\n", n_addresses);

	i=0;
	for(aux_letter = 0; aux_letter < 255; aux_letter++){

		for(j=0; j<countries_len; j++){ //
			data_countries = country_get_data(countries[j]);

			if(country_get_tamanho(countries[j]) > (index_country[j])){
				place_name = data_get_place_name(data_countries, index_country[j]);
				while(place_name[0] == aux_letter){
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

	return one_archive;
}


//
//  hash.c
//  tabela_hash
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "lista_enc/lista_enc.h"
#include "lista_enc/no.h"
#include "hash.h"


#define length_buffer 150

struct zip_codes {
    char country_code[3];
    char* postal_code;
    char* place_name;
    char* admin_name1;
    char* admin_code1;
    char* admin_name2;
    char* admin_name3;
    float latitude;
    float longitude;
    short int accuracy;
};

char country_codes[83][3] = {	"AD", "AR", "AS", "AT", "AU", "AX", "BD", "BE", "BG", "BM", "BR", "BY", "CA",
								"CH", "CO", "CR", "CZ", "DE", "DK", "DO", "DZ", "ES", "FI", "FO", "FR", "GB",
								"GF", "GG", "GL", "GP", "GT", "GU", "HR", "HU", "IE", "IM", "IN", "IS", "IT",
								"JE", "JP", "LI", "LK", "LT", "LU", "LV", "MC", "MD", "MH", "MK", "MP", "MQ",
								"MT", "MX", "MY", "NC", "NL", "NO", "NZ", "PH", "PK", "PL", "PM", "PR", "PT",
								"RE", "RO", "RU", "SE", "SI", "SJ", "SK", "SM", "TH", "TR", "UA", "US", "UY",
								"VA", "VI", "WF", "YT", "ZA"    };

lista_enc_t *create_hash_table(const char* file_path, no_t *hash_table[255][83], int n_characters, int n_countries){
    
#ifdef DEBUG
	uint64_t zip_code_count = 0;
#endif

    lista_enc_t *zipcode_list = cria_lista_enc();
    zip_code *data = NULL;
    no_t *no_data = NULL;

    int i = 0;


    char buffer[300];

    char    postal_code_temp[length_buffer],	place_name_temp[length_buffer],		admin_name1_temp[length_buffer],
			admin_code1_temp[length_buffer],	admin_name2_temp[length_buffer],
			admin_name3_temp[length_buffer],	count_char_incremento_buffer[length_buffer];

    char    country_code_comp[3];
    
    uint64_t incremento_buffer;
    int ret = 0;
    FILE * arquivo = fopen(file_path, "r");
    if (arquivo == NULL) {
        perror("Error at 'read_archive()' - fopen");
        exit(EXIT_FAILURE);
    }

    //i=0;

    //tamanho = i;
    //data_vector = create_data_vector(i);

    //rewind(arquivo);
    

    country_code_comp[0] = '\0';
    
    i=-1;
    while(fgets(buffer, 300, arquivo) != NULL)  {
        
    	data = malloc(sizeof(zip_code));
        data->country_code[0] = '\0';
        
        //data = calloc(1, sizeof(zip_code));
        
    	incremento_buffer = 0;


        ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",data->country_code);
        if(ret == 0){
        	data->country_code[0] = '\0';
        	incremento_buffer += 1;
        }else{
        	incremento_buffer += (strlen(data->country_code) + 1);
        }

        ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",postal_code_temp);
		if(ret == 0){
			postal_code_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(postal_code_temp) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",place_name_temp);
		if(ret == 0){
			place_name_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(place_name_temp) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",admin_name1_temp);
		if(ret == 0){
			admin_name1_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(admin_name1_temp) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",admin_code1_temp);
		if(ret == 0){
			admin_code1_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(admin_code1_temp) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",admin_name2_temp);
		if(ret == 0){
			admin_name2_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(admin_name2_temp) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",admin_name3_temp);
		if(ret == 0){
			admin_name3_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(admin_name3_temp) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%f;", &data->latitude);
		if(ret == 0){
			data->latitude = 0;
			incremento_buffer += 1;
		}else{
			sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",count_char_incremento_buffer);
			incremento_buffer += (strlen(count_char_incremento_buffer) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%f;", &data->longitude);
		if(ret == 0){
			data->latitude = 0;
			incremento_buffer += 1;
		}else{
			sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",count_char_incremento_buffer);
			incremento_buffer += (strlen(count_char_incremento_buffer) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%hd;", &data->accuracy);
		if(ret == 0){
			data->accuracy = 0;
			incremento_buffer += 1;
		}else{
			sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",count_char_incremento_buffer);
			incremento_buffer += (strlen(count_char_incremento_buffer) + 1);
		}


        data->postal_code = malloc(strlen(postal_code_temp) + 1);
        if (data->postal_code == NULL) exit (1);
        strncpy(data->postal_code, postal_code_temp, strlen(postal_code_temp) + 1);

        data->place_name = malloc(strlen(place_name_temp) + 1);
        if (data->place_name == NULL) exit (1);
        strncpy(data->place_name, place_name_temp, strlen(place_name_temp) + 1);

        data->admin_name1 = malloc(strlen(admin_name1_temp) + 1);
        if (data->admin_name1 == NULL) exit (1);
        strncpy(data->admin_name1, admin_name1_temp, strlen(admin_name1_temp) + 1);

        data->admin_code1 = (char*)malloc(strlen(admin_code1_temp) + 1);
        if (data->admin_code1 == NULL) exit (1);
        strncpy(data->admin_code1, admin_code1_temp, strlen(admin_code1_temp) + 1);

        data->admin_name2 = malloc(strlen(admin_name2_temp) + 1);
        if (data->admin_name2 == NULL) exit (1);
        strncpy(data->admin_name2, admin_name2_temp, strlen(admin_name2_temp) + 1);

        data->admin_name3 = malloc(strlen(admin_name3_temp) + 1);
        if (data->admin_name3 == NULL) exit (1);
        strncpy(data->admin_name3, admin_name3_temp, strlen(admin_name3_temp) + 1);
        
        no_data = cria_no(data);

		if(strcmp(country_code_comp, data->country_code) != 0){
			for(i = 0;strcmp(data->country_code, country_codes[i]) != 0; i++);
			hash_table[((unsigned char)data->place_name[0])][i] = no_data;
		}
        
		strncpy(country_code_comp, data->country_code, 3);
        
        add_cauda(zipcode_list, no_data);


#ifdef DEBUG

	zip_code_count++;

        printf("%llu\t%s %s %s %s %s %s %s %f %f %d\n\n",
			zip_code_count,		data->country_code, 	data->postal_code, data->place_name,
			data->admin_name1,	data->admin_code1, 	data->admin_name2,
			data->admin_name3, 	data->latitude, 	data->longitude,
			data->accuracy);

#endif

    }
    fclose(arquivo);

    //country->data = data_vector;
    
    return zipcode_list;
}

void free_zipcode_list(lista_enc_t *zipcode_list){
	no_t *no_lista;
	no_t *no_lista_anterior;
	zip_code *data;

	no_lista = obtem_cabeca(zipcode_list);

	while(no_lista != NULL){
		data = obtem_dado (no_lista);
		free(data->postal_code);
		free(data->place_name);
		free(data->admin_name1);
		free(data->admin_name2);
		free(data->admin_name3);
		free(data->admin_code1);
		free(data);
		no_lista_anterior = no_lista;
		no_lista = obtem_proximo (no_lista);
		free(no_lista_anterior);
	}

	free(zipcode_list);

}

void search_city(no_t *hash_table[255][83], char* place_name, int country){
	int place_name_lenght;
	unsigned char letter;

	no_t *no_list;
	zip_code *data;

	letter = (unsigned char)place_name[0];
	place_name_lenght = strlen(place_name);

	no_list = hash_table[letter][country-1];


	for(;no_list != NULL; no_list = obtem_proximo(no_list)){

		data = obtem_dado(no_list);

		if((letter == (unsigned char)(data->place_name[0])) && ((strcmp(country_codes[country-1], data->country_code) == 0))){

			if(strncmp(place_name, data->place_name,place_name_lenght) == 0){
				 printf("%s: %s %s %s %s %s %s %f %f %d\n\n",
							data->place_name, 	data->country_code, data->postal_code, data->admin_name1,
							data->admin_code1, 	data->admin_name2, 	data->admin_name3, data->latitude,
							data->longitude, 	data->accuracy);
			}
		}

	}
}


char *no_get_country_code(no_t *no){
	zip_code *data;
	data = obtem_dado(no);
	return data->country_code;
}

char *no_get_place_name(no_t *no){
	zip_code *data;
	data = obtem_dado(no);
	return data->place_name;
}

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

lista_enc_t ***create_hash_table(const char* file_path, int* n_characters, int* n_countries){

#ifdef DEBUG
	uint64_t zip_code_count = 0;
#endif

	//lista_enc_t *hash_table[][];
	lista_enc_t *zipcode_list;
    zip_code* data;
    //zip_code** data_vector;
    //country = (country_zip_code*)malloc(sizeof(country_zip_code));
    int i = 0;
    int tamanho;

    char buffer[300];

    char    postal_code_temp[length_buffer],	place_name_temp[length_buffer],		admin_name1_temp[length_buffer],
			admin_code1_temp[length_buffer],	admin_name2_temp[length_buffer],
			admin_name3_temp[length_buffer],	count_char_incremento_buffer[length_buffer];

    uint64_t incremento_buffer;
    int ret = 0;
    FILE * arquivo = fopen(file_path, "r");
    if (arquivo == NULL) {
        perror("Error at 'read_archive()' - fopen");
        exit(EXIT_FAILURE);
    }

    i=0;


    tamanho = i;
    //data_vector = create_data_vector(i);

    rewind(arquivo);

    i=0;
    while(fgets(buffer, 300, arquivo) != NULL)  {

    	data = malloc(sizeof(zip_code));

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

        add_cauda(zipcode_list, cria_no(data));
        i++;

#ifdef DEBUG

	zip_code_count++;

        printf("%llu\t%s %s %s %s %s %s %s %s %s %f %f %d\n\n",
			zip_code_count,		data->country_code, 	data->postal_code, data->place_name,
			data->admin_name1,	data->admin_code1, 	data->admin_name2,
			data->admin_name3, 	data->latitude, 	data->longitude,
			data->accuracy);

#endif

    }
    fclose(arquivo);

    //country->data = data_vector;

}

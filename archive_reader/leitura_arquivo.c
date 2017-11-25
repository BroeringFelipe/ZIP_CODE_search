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
#include <stdint.h>
#include "leitura_arquivo.h"
#include "../lista_enc/no.h"
#include "../lista_enc/lista_enc.h"

#define length_buffer 50
//#define DEBUG

/* PADRAO DA LEITURA DO ARQUIVO:
country code      : iso country code, 2 characters
postal code       : varchar(20)
place name        : varchar(180)
admin name1       : 1. order subdivision (state) varchar(100)
admin code1       : 1. order subdivision (state) varchar(20)
admin name2       : 2. order subdivision (county/province) varchar(100)
admin code2       : 2. order subdivision (county/province) varchar(20)
admin name3       : 3. order subdivision (community) varchar(100)
admin code3       : 3. order subdivision (community) varchar(20)
latitude          : estimated latitude (wgs84)
longitude         : estimated longitude (wgs84)
accuracy          : accuracy of lat/lng from 1=estimated to 6=centroid */

struct zip_codes {
    char country_code[3];
    char* postal_code;
    char* place_name;
    char* admin_name1;
    char* admin_code1;
    char* admin_name2;
    char* admin_code2;
    char* admin_name3;
    char* admin_code3;
    float latitude;
    float longitude;
    short int accuracy;
};

struct countries_zip_codes{
	zip_code** data;
	int tamanho;
};

country_zip_code* creat_country_zip_code(){
	return ((country_zip_code*)malloc(sizeof(country_zip_code)));
}

void read_archive(char* file_path, country_zip_code* country){

#ifdef DEBUG
	uint64_t zip_code_count = 0;
#endif

    zip_code* data;
    zip_code** data_vector;
    //country = (country_zip_code*)malloc(sizeof(country_zip_code));
    int i = 0;

    char buffer[300];

    char    postal_code_temp[length_buffer],	place_name_temp[length_buffer],		admin_name1_temp[length_buffer],
			admin_code1_temp[length_buffer],	admin_name2_temp[length_buffer],	admin_code2_temp[length_buffer],
			admin_name3_temp[length_buffer],	admin_code3_temp[length_buffer],	count_char_incremento_buffer[length_buffer];

    uint64_t incremento_buffer;
    int ret = 0;
    FILE * arquivo = fopen(file_path, "r");
    if (arquivo == NULL) {
        perror("Error at 'read_archive()' - fopen");
        exit(EXIT_FAILURE);
    }

    i=0;
    while(fgets(buffer, 300, arquivo) != NULL)
    	i++;	//Count number of lines

    country->tamanho = i;
    data_vector = (zip_code**)malloc(sizeof(zip_code)* i);

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

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",admin_code2_temp);
		if(ret == 0){
			admin_code2_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(admin_code2_temp) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",admin_name3_temp);
		if(ret == 0){
			admin_name3_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(admin_name3_temp) + 1);
		}

		ret = sscanf((char*)((uint64_t)buffer+(uint64_t)incremento_buffer),"%80[^\t]\t",admin_code3_temp);
		if(ret == 0){
			admin_code3_temp[0] = '\0';
			incremento_buffer += 1;
		}else{
			incremento_buffer += (strlen(admin_code3_temp) + 1);
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

        data->admin_code2 = malloc(strlen(admin_code2_temp) + 1);
        if (data->admin_code2 == NULL) exit (1);
        strncpy(data->admin_code2, admin_code2_temp, strlen(admin_code2_temp) + 1);

        data->admin_name3 = malloc(strlen(admin_name3_temp) + 1);
        if (data->admin_name3 == NULL) exit (1);
        strncpy(data->admin_name3, admin_name3_temp, strlen(admin_name3_temp) + 1);

        data->admin_code3 = malloc(strlen(admin_code3_temp) + 1);
        if (data->admin_code3 == NULL) exit (1);
        strncpy(data->admin_code3, admin_code3_temp, strlen(admin_code3_temp) + 1);

        data_vector[i]= data;
        i++;

#ifdef DEBUG

	zip_code_count++;

        printf("%llu\t%s %s %s %s %s %s %s %s %s %f %f %d\n\n",
			zip_code_count,		data->country_code, 	data->postal_code, data->place_name,
			data->admin_name1,	data->admin_code1, 	data->admin_name2, data->admin_code2,
			data->admin_name3, data->admin_code3, 	data->latitude, 	data->longitude,
			data->accuracy);

#endif

    }
    fclose(arquivo);

    country->data = data_vector;

}

void imprime_zip_code(zip_code **data, int tamanho){

	int i;

	for(i=0; i<tamanho; i++){

		printf("%d\t%s %s %s %s %s %s %s %s %s %f %f %d\n\n",
				i,						data[i]->country_code, 	data[i]->postal_code, 	data[i]->place_name,
				data[i]->admin_name1,	data[i]->admin_code1, 		data[i]->admin_name2, 	data[i]->admin_code2,
				data[i]->admin_name3, 	data[i]->admin_code3, 		data[i]->latitude, 	data[i]->longitude,
				data[i]->accuracy);

	}
}

zip_code **country_get_data(country_zip_code* country){

	if (country == NULL)	{
		fprintf(stderr,"country_get_data: invalid country pointer!");
		exit(EXIT_FAILURE);
	}

	return country->data;
}

void country_set_data(country_zip_code* country, zip_code** data){

	if (country == NULL)	{
		fprintf(stderr,"country_set_data: invalid country pointer!");
		exit(EXIT_FAILURE);
	}

	if (data == NULL)	{
		fprintf(stderr,"country_set_data: invalid data pointer!");
		exit(EXIT_FAILURE);
	}

	country->data = data;

}

int country_get_tamanho(country_zip_code* country){

	if (country == NULL)	{
		fprintf(stderr,"country_get_tamanho: invalid country pointer!");
		exit(EXIT_FAILURE);
	}

	return country->tamanho;

}

char* data_get_place_name(zip_code **data, int i){

	if (data == NULL)	{
		fprintf(stderr,"get_place_name: dado invalido!");
		exit(EXIT_FAILURE);
	}

	return data[i]->place_name;

}



/*
void libera_lista(lista_enc_t* lista){
    while (1){
        temporada* dados = obtem_dado(obtem_cabeca(lista));

        free(dados->contry);
        free(dados->name);
        free(dados->team);
        free(dados->engine);
        free(dados->clinched);
        free(dados->race);

        if(obtem_tamanho(lista) == 0)
            break;
    }

    free(lista);
}
*/

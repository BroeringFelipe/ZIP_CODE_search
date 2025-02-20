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

#define length_buffer 50
#undef DEBUG
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


country_zip_code* create_country_zip_code(){
	return ((country_zip_code*)malloc(sizeof(country_zip_code)));
}

zip_code **create_data_vector(int array_len){
	return (zip_code**)malloc(sizeof(zip_code)* array_len);
}

void country_set_tamanho(country_zip_code* country, int array_len){
	country->tamanho = array_len;
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
    data_vector = create_data_vector(i);

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

void free_zip_code(country_zip_code *country){

	int i;

	for(i=0; i < (country->tamanho); i++){
		free(country->data[i]->postal_code);
		free(country->data[i]->place_name);
		free(country->data[i]->admin_name1);
		free(country->data[i]->admin_name2);
		free(country->data[i]->admin_name3);
		free(country->data[i]->admin_code1);
		free(country->data[i]->admin_code2);
		free(country->data[i]->admin_code3);
		free(country->data[i]);
	}

	free(country->data);
	free(country);
}

/* ---------------------------------------------------- */


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
    
    for(i=0; i<countries_len; i++){    //Clear indexes
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
    
#ifdef    DEBUG
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
    
    zip_code **data = country_get_data(countries);
    
    int n_addresses = country_get_tamanho(countries), i = 0;
    printf("\ttamanho: %d", n_addresses);
    
    for(i = 0; i < n_addresses; i++){
        /*fprintf(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%f\t%f\t%d\n",*/
        fprintf(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%f\t%f\t%d\n",
                data[i]->country_code,     data[i]->postal_code,     data[i]->place_name,
                data[i]->admin_name1,    data[i]->admin_code1,         data[i]->admin_name2,     /*data[i]->admin_code2,*/
                data[i]->admin_name3,     /*data[i]->admin_code3,*/         data[i]->latitude,     data[i]->longitude,
                data[i]->accuracy);
#ifdef DEBUG
        printf("%s\n", data_get_place_name(data, i)); 
#endif
    }
    
    fclose(file);
    
}

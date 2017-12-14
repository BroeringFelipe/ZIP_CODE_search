/*
 ============================================================================
 Name        : main.c
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "leitura_arquivo.h"
#include "quicksort.h"

#undef DEBUG_LIST
#define n_countries	83
//#define DEBUG
#undef DEBUG
#define DEBUG_TIME

#ifdef DEBUG_TIME

	#ifdef __unix__                    			/* __unix__ is usually defined by compilers targeting Unix systems */
		#include <stdint.h>
		#include <unistd.h>

	#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
		#include <process.h>
		#include <math.h>
		#include <windows.h>

	#endif
#endif


int main(){

#ifdef DEBUG_TIME

	#ifdef __unix__                    			/* __unix__ is usually defined by compilers targeting Unix systems */
		struct timespec t_debug_1;
		struct timespec t_debug_2;
		srand(getpid() ^ clock());
		double sum_t_debug_1, sum_t_debug_2;

	#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
		clock_t t_debug_1, t_debug_2;
		srand(getpid()^time(NULL));

	#endif

    double media_tempo_f;

#endif

	int i;
	country_zip_code *countries[n_countries];
	country_zip_code *one_archive;
	char endereco[] = "../zipcodes_archives/";
    //char endereco[] = "/Users/aninhabanderchuk/Google Drive/Engenharia Eletrônica/* 5˚ Fase */5. Programação de Computadores II/PRG: Trabalho Final - CEP/ZIP_CODE_search/zipcodes_archives/";

    
	for(i=0; i<n_countries; i++){
		countries[i] = create_country_zip_code();
	}

	char endereco_temp[500];

	char nome_arquivos[83][3] = {	"AD", "AR", "AS", "AT", "AU", "AX", "BD", "BE", "BG", "BM", "BR", "BY", "CA",
									"CH", "CO", "CR", "CZ", "DE", "DK", "DO", "DZ", "ES", "FI", "FO", "FR", "GB",
									"GF", "GG", "GL", "GP", "GT", "GU", "HR", "HU", "IE", "IM", "IN", "IS", "IT",
									"JE", "JP", "LI", "LK", "LT", "LU", "LV", "MC", "MD", "MH", "MK", "MP", "MQ",
									"MT", "MX", "MY", "NC", "NL", "NO", "NZ", "PH", "PK", "PL", "PM", "PR", "PT",
									"RE", "RO", "RU", "SE", "SI", "SJ", "SK", "SM", "TH", "TR", "UA", "US", "UY",
									"VA", "VI", "WF", "YT", "ZA"    };

#ifdef DEBUG_TIME

    #ifdef __unix__
    	clock_gettime(CLOCK_MONOTONIC ,&t_debug_1);

	#elif defined(_WIN32) || defined(WIN32)
    	t_debug_1 = clock();

	#endif
#endif


	for(i = 0; i < 83; i++){
		strcpy(endereco_temp, endereco);
		strcat(endereco_temp, nome_arquivos[i]);
		strcat(endereco_temp, ".txt");

		read_archive(endereco_temp, countries[i]);
	}

#ifdef DEBUG_TIME

	#ifdef __unix__
    	clock_gettime(CLOCK_MONOTONIC ,&t_debug_2);

    	sum_t_debug_1 = (double)(unsigned)t_debug_1.tv_nsec / 1000000000.0;
    	sum_t_debug_1 += ((double)(unsigned)t_debug_1.tv_sec * 1.0);

    	sum_t_debug_2 = (double)(unsigned)t_debug_2.tv_nsec / 1000000000.0;
    	sum_t_debug_2 += ((double)(unsigned)t_debug_2.tv_sec * 1.0);

    	media_tempo_f = sum_t_debug_2 - sum_t_debug_1;
    	clock_gettime(CLOCK_MONOTONIC ,&t_debug_1);

	#elif defined(_WIN32) || defined(WIN32)
    	t_debug_2 = clock();
    	media_tempo_f = ((double)t_debug_2 - (double)t_debug_1) / CLOCKS_PER_SEC;
    	t_debug_1 = clock();

	#endif

    printf("Tempo leitura dos arquivos: %.3fs\n\n", media_tempo_f);

#endif

	for(i = 0; i < 83; i++){
		quicksort(country_get_data(countries[i]), 0, (country_get_tamanho(countries[i]) - 1));
	}


#ifdef DEBUG_TIME

	#ifdef __unix__
    	clock_gettime(CLOCK_MONOTONIC ,&t_debug_2);

    	sum_t_debug_1 = (double)(unsigned)t_debug_1.tv_nsec / 1000000000.0;
    	sum_t_debug_1 += ((double)(unsigned)t_debug_1.tv_sec * 1.0);

    	sum_t_debug_2 = (double)(unsigned)t_debug_2.tv_nsec / 1000000000.0;
    	sum_t_debug_2 += ((double)(unsigned)t_debug_2.tv_sec * 1.0);

    	media_tempo_f = sum_t_debug_2 - sum_t_debug_1;

	#elif defined(_WIN32) || defined(WIN32)
    	t_debug_2 = clock();
    	media_tempo_f = ((double)t_debug_2 - (double)t_debug_1) / CLOCKS_PER_SEC;

	#endif

    printf("Tempo de execucao quicksort: %.3fs\n\n", media_tempo_f);

#endif

	one_archive = organize_database(countries, n_countries);

#ifdef DEBUG_LIST
imprime_zip_code(country_get_data(one_archive), country_get_tamanho(one_archive));
#endif
    
    /* Escrever unico arquivo */
    
    
    char endereco_arquivo[] = "../zipcodes_archives/one_archive.txt"; //Felipe
    //char endereco_arquivo[] = "/Users/aninhabanderchuk/Google Drive/Engenharia Eletrônica/* 5˚ Fase */5. Programação de Computadores II/PRG: Trabalho Final - CEP/ZIP_CODE_search/zipcodes_archives/one_archive.txt"; //Ana
 
    write_file(endereco_arquivo, one_archive);
    
    
    /* Clear memory */
    for(i=0; i<n_countries; i++){
        free_zip_code(countries[i]);
    }
    
    free(country_get_data(one_archive));
    free(one_archive);
    
    return 0;
}

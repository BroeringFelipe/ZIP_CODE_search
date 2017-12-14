#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "lista_enc/lista_enc.h"
#include "lista_enc/no.h"
#include "hash.h"

#define N_CHARACTERS 255
#define N_COUNTRIES 83

#define n_countries	83

#undef DEBUG_HASHTABLE

#define DEBUG_TIME
//#undef DEBUG_TIME

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

    char place_name[100];
    int country;
    char keyboard;
    const char nome_arquivos[83][3] = {    "AD", "AR", "AS", "AT", "AU", "AX", "BD", "BE", "BG", "BM", "BR", "BY", "CA",
        "CH", "CO", "CR", "CZ", "DE", "DK", "DO", "DZ", "ES", "FI", "FO", "FR", "GB",
        "GF", "GG", "GL", "GP", "GT", "GU", "HR", "HU", "IE", "IM", "IN", "IS", "IT",
        "JE", "JP", "LI", "LK", "LT", "LU", "LV", "MC", "MD", "MH", "MK", "MP", "MQ",
        "MT", "MX", "MY", "NC", "NL", "NO", "NZ", "PH", "PK", "PL", "PM", "PR", "PT",
        "RE", "RO", "RU", "SE", "SI", "SJ", "SK", "SM", "TH", "TR", "UA", "US", "UY",
        "VA", "VI", "WF", "YT", "ZA"    };
    
    
    const char endereco_arquivo[] = "../zipcodes_archives/one_archive.txt"; //Felipe
    //char endereco_arquivo[] = "/Users/aninhabanderchuk/Google Drive/Engenharia Eletrônica/* 5˚ Fase */5. Programação de Computadores II/PRG: Trabalho Final - CEP/ZIP_CODE_search/zipcodes_archives/one_archive.txt"; //Ana
    
    no_t *hash_table[N_CHARACTERS][N_COUNTRIES];
    
    lista_enc_t *zipcode_list;
    
    int i, j;
    
    
    for(j = 0; j<255; j++){
        for(i = 0; i<83; i++){
            hash_table[j][i] = NULL;
        }
    }
    
#ifdef DEBUG_TIME

    #ifdef __unix__
    	clock_gettime(CLOCK_MONOTONIC ,&t_debug_1);

	#elif defined(_WIN32) || defined(WIN32)
    	t_debug_1 = clock();

	#endif
#endif

    zipcode_list = create_hash_table(endereco_arquivo, hash_table, N_CHARACTERS, N_COUNTRIES);
    
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

    printf("Tempo leitura do arquivo dos zipcode mais o tempo da criação da tabela hash: %.3fs\n\n", media_tempo_f);

#endif



#ifdef DEBUG_HASHTABLE
    for(j = 0; j<255; j++){
        for(i = 0; i<83; i++){
            if(hash_table[j][i] != NULL){
                printf("%d\t%d\t%p\t%s\t%s\n", j, i, hash_table[j][i], no_get_country_code(hash_table[j][i]), no_get_place_name(hash_table[j][i]));
            }
        }
        printf("\n\n");
    }
#endif

    
    puts("Programa para busca de CEP a partir do nome de uma cidade.\n");
    puts("Voce pode fazer a busca somente pelo nome da cidade ou a-\ndicionar tambem o pais para tornar a busca mais rapida.\n\n");

    do{
    puts("- - - Tabela de codigo referente a cada pais - - -");
    for(i = 0; i < 21; i++)
        printf("\n %02d:\t%s\t\t%d:\t%s\t\t%d:\t%s\t\t%d:\t%s\t",    i + 1, nome_arquivos[i], i + 22, nome_arquivos[i+21],
               i + 43, nome_arquivos[i+42], i + 64, nome_arquivos[i+63]);
    
    printf("\n\nDigite o nome da cidade da qual voce deseja realizar a busca: ");


    scanf("%99[^\n]", place_name);
    getchar();

    printf("\nCaso voce saiba, digite o nome do pais que ela pertence: ");

    scanf("%d", &country);
    getchar();

    printf("\n");


#ifdef DEBUG_TIME

    #ifdef __unix__
    	clock_gettime(CLOCK_MONOTONIC ,&t_debug_1);

	#elif defined(_WIN32) || defined(WIN32)
    	t_debug_1 = clock();

	#endif
#endif

    search_city(hash_table, place_name, country);

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

    printf("Tempo de execucao da busca COM tabela hash: %.3fs\n\n", media_tempo_f);

#endif
    



#ifdef DEBUG_TIME

    #ifdef __unix__
    	clock_gettime(CLOCK_MONOTONIC ,&t_debug_1);

	#elif defined(_WIN32) || defined(WIN32)
    	t_debug_1 = clock();

	#endif


    printf("\n\nBusca sem hashtable:\n");
    search_city_without_hashtable(zipcode_list, place_name, country);

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

    printf("Tempo de execucao da busca SEM tabela hash: %.3fs\n\n", media_tempo_f);

#endif




    printf("Se voce deseja fazer outra busca, digite 'y', caso queira encerrar o programa, digite qualquer tecla:\n");

    scanf("%c", &keyboard);
    getchar();

    }while(keyboard == 'y');



    free_zipcode_list(zipcode_list);
    
    return 0;
}

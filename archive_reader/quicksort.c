/*
 ============================================================================
 Name        : quicksort.c
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
#include <stdint.h>
#include "leitura_arquivo.h"
#include "quicksort.h"

void swap_dados(zip_code **dados, int i, int j);
int mediana(zip_code **dados, int esq, int dir);
int partition(zip_code **dados, int esq, int dir);

void quicksort(zip_code **dados, int esq, int dir){

	int p;

	if(esq<dir){
		p = partition(dados, esq, dir);
		quicksort(dados, esq, p);
		quicksort(dados, (p+1), dir);
	}
}

int partition(zip_code **dados, int esq, int dir){

	int med, i, j;
	char *pivot;

	med = mediana(dados, esq, dir);

	pivot = get_place_name(dados, med);
	i = esq - 1;
	j = dir + 1;

	while(1){

		do{
			i = i + 1;
		}while((strncmp(get_place_name(dados, i), pivot, 50)) < 0);

		do{
			j = j - 1;
		}while((strncmp(get_place_name(dados, j), pivot, 50)) > 0);

		if(i >= j){
			return j;
		}

		swap_dados(dados, i, j);

	}
}

int mediana(zip_code **dados, int esq, int dir){

	int med;

	med = (esq + dir)/2;


	if((strncmp(get_place_name(dados, esq),get_place_name(dados, dir), 50)) < 0){
		swap_dados(dados, esq, dir);
	}

	if((strncmp(get_place_name(dados, med),get_place_name(dados, esq), 50)) < 0){
		swap_dados(dados, med, esq);
	}

	if((strncmp(get_place_name(dados, dir),get_place_name(dados, med), 50)) < 0){
		swap_dados(dados, dir, med);
	}

	return med;
}


void swap_dados(zip_code **dados, int i, int j){
	dados[i] = (uint64_t)dados[i] ^ (uint64_t)dados[j];
	dados[j] = (uint64_t)dados[i] ^ (uint64_t)dados[j];
	dados[i] = (uint64_t)dados[i] ^ (uint64_t)dados[j];
}

/*
 ============================================================================
 Name        : quicksort.h
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

#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

void quicksort(zip_code **dados, int esq, int dir);
//void swap_dados(zip_code **dados, int i, int j);
int mediana(zip_code **dados, int esq, int dir);

#endif // QUICKSORT_H_INCLUDED

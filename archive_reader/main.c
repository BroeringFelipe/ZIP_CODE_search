#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lista_enc/lista_enc.h"
#include "../lista_enc/no.h"
#include "leitura_arquivo.h"

typedef struct paises_zip_codes{
	zip_code** dados;
	int tamanho;
} paises_zip_code;


int main()
{
	int i = 0;
	paises_zip_code paises[83];
	char endereco[] = "../zipcodes_archives/";
    
    //char endereco[] = "/Users/aninhabanderchuk/Google Drive/Engenharia Eletrônica/* 5˚ Fase */5. Programação de Computadores II/PRG: Trabalho Final - CEP/ZIP_CODE_search/zipcodes_archives/";
    
	char endereco_temp[500];

	char nome_arquivos[83][3] = {	"AD", "AR", "AS", "AT", "AU", "AX", "BD", "BE", "BG", "BM", "BR", "BY", "CA",
									"CH", "CO", "CR", "CZ", "DE", "DK", "DO", "DZ", "ES", "FI", "FO", "FR", "GB",
									"GF", "GG", "GL", "GP", "GT", "GU", "HR", "HU", "IE", "IM", "IN", "IS", "IT",
									"JE", "JP", "LI", "LK", "LT", "LU", "LV", "MC", "MD", "MH", "MK", "MP", "MQ",
									"MT", "MX", "MY", "NC", "NL", "NO", "NZ", "PH", "PK", "PL", "PM", "PR", "PT",
									"RE", "RO", "RU", "SE", "SI", "SJ", "SK", "SM", "TH", "TR", "UA", "US", "UY",
									"VA", "VI", "WF", "YT", "ZA"    };

	for(i = 0; i < 83; i++){
		strcpy(endereco_temp, endereco);
		strcat(endereco_temp, nome_arquivos[i]);
		strcat(endereco_temp, ".txt");

		paises[i].dados = le_arquivo(endereco_temp, &paises[i].tamanho);
	}


    return 0;
}

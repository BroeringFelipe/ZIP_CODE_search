#include <stdio.h>
#include <stdlib.h>
#include "lista_enc/lista_enc.h"
#include "lista_enc/no.h"
#include "hash.h"

int main()
{
	char nome_arquivos[83][3] = {	"AD", "AR", "AS", "AT", "AU", "AX", "BD", "BE", "BG", "BM", "BR", "BY", "CA",
									"CH", "CO", "CR", "CZ", "DE", "DK", "DO", "DZ", "ES", "FI", "FO", "FR", "GB",
									"GF", "GG", "GL", "GP", "GT", "GU", "HR", "HU", "IE", "IM", "IN", "IS", "IT",
									"JE", "JP", "LI", "LK", "LT", "LU", "LV", "MC", "MD", "MH", "MK", "MP", "MQ",
									"MT", "MX", "MY", "NC", "NL", "NO", "NZ", "PH", "PK", "PL", "PM", "PR", "PT",
									"RE", "RO", "RU", "SE", "SI", "SJ", "SK", "SM", "TH", "TR", "UA", "US", "UY",
									"VA", "VI", "WF", "YT", "ZA"    };

	//const char endereco_arquivo[] = "../zipcodes_archives/arquivo_final.txt"; //Felipe
	//char endereco_arquivo[] = "/Users/aninhabanderchuk/Google Drive/Engenharia Eletrônica/* 5˚ Fase */5. Programação de Computadores II/PRG: Trabalho Final - CEP/ZIP_CODE_search/zipcodes_archives/one_archive.txt"; //Ana

	//int n_characters, n_countries;

	//lista_enc_t ***hash_table;

	//hash_table = create_hash_table(endereco_arquivo, &n_characters, &n_countries);
    /*********/
    
    char cidade[100];
    char pais[3];
    int i = 0;
    puts("CODIGO\tPAIS\n");
    for(i = 0; i < 83; i++){
        printf("%d:\t%s", i + 1, nome_arquivos[i]);
    }
    puts("Digite o nome da cidade da qual voce deseja realizar a busca:\n");
    scanf("%s", cidade);
    puts("Caso voce saiba, digite o nome do pais que ela pertence:\n");
    scanf("%s", pais);
    
    
     
     
     /*********/
    return 0;

}



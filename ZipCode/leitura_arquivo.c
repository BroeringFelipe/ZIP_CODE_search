#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura_arquivo.h"
#include "no.h"
#include "lista_enc.h"

#define TAMANHO 50
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

/*------------------------*/
/*IMPLEMENTAÇÃO COM LISTAS*/
/*------------------------*/

lista_enc_t* le_arquivo(char* caminho_do_arquivo)
{
    lista_enc_t* lista_zip_code = cria_lista_enc();

    zip_code* dados;
    char buffer[300];

    char    postal_code_temp[TAMANHO], place_name_temp[TAMANHO], admin_name1_temp[TAMANHO], admin_code1_temp[TAMANHO],
            admin_name2_temp[TAMANHO], admin_code2_temp[TAMANHO], admin_name3_temp[TAMANHO], admin_code3_temp[TAMANHO];

    int ret = 0;
    int dados_por_linha = 12;

    FILE * arquivo = fopen(caminho_do_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro em 'le_arquivo()' - fopen");
        exit(EXIT_FAILURE);
    }

    //fgets(buffer, 300, arquivo);

    while(fgets(buffer, 300, arquivo) != NULL)  {

        dados = malloc(sizeof(zip_code));

        ret = sscanf(buffer, "%s\t%80[^\t]\t%80[^\t]\t%80[^\t]\t%80[^\t]\t%80[^\t]\t%80[^\t]\t%80[^\t]\t%80[^\t]\t%f\t%f\t%hd",
                    dados->country_code, postal_code_temp, place_name_temp, admin_name1_temp, admin_code1_temp, admin_name2_temp,
                    admin_code2_temp, admin_name3_temp, admin_code3_temp, &dados->latitude; &dados->longitude, &dados->accuracy);

        if (ret != dados_por_linha){

            fprintf(stderr, "erro no arquivo: %d\n", ret);
            exit(EXIT_FAILURE);

        }

        /*  Alocacao dinamica dos nomezinhos     */
        /*  strlen retorna o tamanho da string   */
        /*  "+1" para o /n e tal                 */

        dados->postal_code = malloc(strlen(postal_code_temp) + 1);
        if (dados->postal_code == NULL) exit (1);
        trncpy(dados->postal_code, postal_code_temp, strlen(postal_code_temp) + 1);

        dados->place_name = malloc(strlen(place_name_temp) + 1);
        if (dados->place_name == NULL) exit (1);
        trncpy(dados->place_name, place_name_temp, strlen(place_name_temp) + 1);

        dados->admin_name1 = malloc(strlen(admin_name1_temp) + 1);
        if (dados->admin_name1 == NULL) exit (1);
        trncpy(dados->admin_name1, admin_name1_temp, strlen(admin_name1_temp) + 1);

        dados->admin_code1 = malloc(strlen(admin_code1_temp) + 1);
        if (dados->admin_code1 == NULL) exit (1);
        trncpy(dados->admin_code1, admin_code1_temp, strlen(admin_code1_temp) + 1);

        dados->admin_name2 = malloc(strlen(admin_name2_temp) + 1);
        if (dados->admin_name2 == NULL) exit (1);
        trncpy(dados->admin_name2, admin_name2_temp, strlen(admin_name2_temp) + 1);

        dados->admin_code2 = malloc(strlen(admin_code2_temp) + 1);
        if (dados->admin_code2 == NULL) exit (1);
        trncpy(dados->admin_code2, admin_code2_temp, strlen(admin_code2_temp) + 1);

        dados->admin_name3 = malloc(strlen(admin_name3_temp) + 1);
        if (dados->admin_name3 == NULL) exit (1);
        trncpy(dados->admin_name3, admin_name3_temp, strlen(admin_name3_temp) + 1);

        dados->admin_code3 = malloc(strlen(admin_code3_temp) + 1);
        if (dados->admin_code3 == NULL) exit (1);
        trncpy(dados->admin_code3, admin_code3_temp, strlen(admin_code3_temp) + 1);

        add_cauda(lista_zip_code, cria_no(dados));

        printf("\t%s %s %s %s %s %s %s %s %s %f %f %hd", dados->country_code, dados->postal_code, dados->place_name, dados->admin_name1,
                dados->admin_code1, dados->admin_name2, dados->admin_code2,
                dados->admin_name3, dados->admin_code3, dados->latitude, dados->longitude);

    }
    fclose(arquivo);

    return lista_zip_code;

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
}*/

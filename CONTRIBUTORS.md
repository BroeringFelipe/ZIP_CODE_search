Contribuidores do Projeto:

Ana Claudia Banderchuk: Responsavel pelas implementações de: 





#ifndef LEITURA_ARQUIVO_H_INCLUDED
#define LEITURA_ARQUIVO_H_INCLUDED

typedef struct zip_codes zip_code;
typedef struct countries_zip_codes country_zip_code;

country_zip_code* create_country_zip_code(void);
zip_code **create_data_vector(int array_len);

void read_archive(char* file_path, country_zip_code* country);
void imprime_zip_code(zip_code **dados, int tamanho);

zip_code **country_get_data(country_zip_code* country);
void country_set_data(country_zip_code* country, zip_code** data);

int  country_get_tamanho(country_zip_code* country);
void country_set_tamanho(country_zip_code* country, int array_len);

char* data_get_place_name(zip_code **dados, int i);
//void data_array_set_data(zip_code **data_array, zip_code *data, int i);
//zip_code* data_array_get_data(zip_code **data_array, int i);

void free_zip_code(country_zip_code *country);

/* -------------- */
country_zip_code *organize_database(country_zip_code **countries, int countries_len);
void write_file(const char* file_path, country_zip_code* countries);





void quicksort(zip_code **dados, int esq, int dir);
//void swap_dados(zip_code **dados, int i, int j);
int mediana(zip_code **dados, int esq, int dir);




typedef struct zip_codes zip_code;

lista_enc_t *create_hash_table(const char* file_path, no_t *hash_table[255][83], int n_characters, int n_countries);

void free_zipcode_list(lista_enc_t *zipcode_list);

void search_city(no_t *hash_table[255][83], char* place_name, int country);

char *no_get_country_code(no_t *no);
char *no_get_place_name(no_t *no);

Diesson Stefano Allebrandt Responsavel por implementar as funcoes: - frequencia_caracter; - criar_byte;

Joao Vitor Bassani Responsavel por implementar as funcoes: - cria_arvore_huffman; - exporta_arvore;

As funcoes responsaveis por desenvolver o processo de compactacao e descompactacao, chamando as funcoes auxiliares e manipulacao dos arquivos de entrada e saida, foram desenvolvidas em conjunto.

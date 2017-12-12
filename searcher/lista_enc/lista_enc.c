#include <stdio.h>
#include <stdlib.h>

#include "lista_enc.h"
#include "no.h"

//#define DEBUG

struct listas_enc {
    no_t *cabeca;
    no_t *cauda;
    int tamanho;
};

//cria uma lista vazia
lista_enc_t *cria_lista_enc (void) {
    lista_enc_t *p = malloc(sizeof(lista_enc_t));

    if (p == NULL){
        perror("cria_lista_enc:");
        exit(EXIT_FAILURE);
    }

    p->cabeca = NULL;
    p->cauda = NULL;
    p->tamanho = 0;

    return p;
}

void add_cabeca(lista_enc_t *lista, no_t* elemento){
    
    no_t* cabeca_antiga;
    
    if (lista == NULL || elemento == NULL){
        fprintf(stderr,"add_cauda: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }
    
    //lista vazia
    if (lista->tamanho == 0)
    {
#ifdef DEBUG
        printf("add_cauda: add primeiro elemento: %p\n", elemento);
#endif // DEBUG
        
        lista->cauda = elemento;
        lista->cabeca = elemento;
        lista->tamanho++;
        
        desliga_no(elemento);
    }
    else {
        cabeca_antiga = lista->cabeca;
        lista->cabeca = elemento;
        liga_nos(elemento, cabeca_antiga);
        lista->tamanho++;
    }
    
}

void add_cauda(lista_enc_t *lista, no_t* elemento)
{
    if (lista == NULL || elemento == NULL){
        fprintf(stderr,"add_cauda: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

   //lista vazia
   if (lista->tamanho == 0)
   {
        #ifdef DEBUG
        printf("add_cauda: add primeiro elemento: %p\n", elemento);
        #endif // DEBUG

        lista->cauda = elemento;
        lista->cabeca = elemento;
        lista->tamanho++;

        desliga_no(elemento);
   }
   else {
        // Remove qualquer ligacao antiga
        desliga_no(elemento);
        // Liga cauda da lista com novo elemento
        liga_nos(lista->cauda, elemento);

        lista->cauda = elemento;
        lista->tamanho++;
   }
}

int obtem_tamanho(lista_enc_t *lista){
    return lista->tamanho;
}

no_t* obtem_cabeca(lista_enc_t *lista){
    return lista->cabeca;
}



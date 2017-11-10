#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

typedef struct nos no_t;

no_t *cria_no(void *dado);
void liga_nos (no_t *fonte, no_t *destino);
void desliga_no (no_t *no);
no_t *obtem_proximo (no_t *no);
void *obtem_dado (no_t *no);

#endif // NO_H_INCLUDED

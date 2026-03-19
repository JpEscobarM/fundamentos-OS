#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include <pthread.h> //THREAD.H  JA IMPORTA A LIB PTHREADS
#include "globals.h" //VARIAVEIS GLOBAIS
#include <time.h>


extern pthread_mutex_t mutex;

void *funcao_teste(void *thread_id);
void *gera_random_number(void *id);
void *consome_random_number(void *id);


#endif // THREAD_H_INCLUDED

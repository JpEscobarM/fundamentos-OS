#ifndef THREAD.H
#define THREAD.H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


extern double saldo;
extern pthread_t t1;
extern pthread_t t2;

/**
 *
 *Faz 100 retiradas de 10 reais
 *@return void*
 */
void* descontar();

/**
 *
 * @return void*
 */
void* depositar();

#endif

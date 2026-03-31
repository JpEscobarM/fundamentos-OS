//
// Created by jmartins on 30/03/2026.
//
#ifndef THREAD_H
#define THREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/**
 * quantidade de threads possiveis para o processamento do vetor de dados
 */
#define QTD_THREADS_PROCESSAMENTO 10

/**
 * quantidade de elementos no vetor de dados
 */
#define QTD_ELEMENTOS 900000
/**
 * vetor de dados
 */
double *vetorDados;

/**
 * threads de processamento do vetor de dados
 */
 pthread_t calculadoras_t[QTD_THREADS_PROCESSAMENTO];

/**
 * barreira para as threads
 */
 pthread_barrier_t barreira;


typedef struct
{
    int id;
    int inicio ; //onde inicia o processamento dos dados
    int fim; //onde terminao processamento dos dados

}Param_t;

/**
 * Inicializa os parâmetros das threads de processamento.
 *
 * Aloca memória para os parâmetros das threads e define
 * os intervalos de processamento do vetor de dados.
 *
 * @param param ponteiro para o vetor de parâmetros das threads
 */
void inicializa_parametros_threads(Param_t **param);

/**
 * exibe no terminal os parametros ja inicializados
 * @param param
 */
void exibe_parametros_threads(Param_t **param);

/**
 * inicializa barreira global
 */
void inicializa_barreira();

/**
 *
 * @param param vetor de parametro das threads para serem inicializados
 */
void inicializa_pthreads(Param_t **param);


void *calcula_vetor_dados(void *args);

void inicializa_vetor_dados();

#endif
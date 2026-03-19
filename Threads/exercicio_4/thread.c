#include <stdio.h>
#include <stdlib.h>
#include "thread.h"

pthread_mutex_t mutex;

void *funcao_teste(void *thread_id)
{

    long id = (long) thread_id;

    printf("\nCRIOU A THREAD TESTE %ld", id);

    pthread_exit(NULL);
}

void *gera_random_number(void *id)
{
    long thread_id = (long) id;
    long gerado;

    pthread_mutex_lock(&mutex);

    srand(time(NULL)^clock());
    random_number =  rand() % 100000;


    printf("\n[THREAD_ID] -> {%ld} [GERADOR] -> {%ld}", thread_id, random_number);

    pronto = 1;

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *consome_random_number(void *arg){

    long thread_id = (long) arg;

    while(1)
    {
        pthread_mutex_lock(&mutex);

        if(pronto)
        {
            printf("\n[THREAD_ID] -> {%ld} [CONSUMIDOR] -> {%ld}",thread_id,random_number);
            pthread_mutex_unlock(&mutex);
            pronto = 0;
            break;
        }

        pthread_mutex_unlock(&mutex);
    }

}

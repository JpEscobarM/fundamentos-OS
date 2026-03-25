/*
Crie um programa com 5 threads usando um laço
e passe para cada uma o nome da respectiva thread

Cada thread dorme por 10 segundos de 1 em 1 segundo.

Cada thread retorna ao término um código de ERRO caso o
seu nome não inicie com letra maiúscula e SUCESSO caso
inicie.


*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#define QTD_THREADS 5

int ERRO_T = 404;
int SUCESSO_T= 200;


typedef struct{

    char nome[20];

}Param_t;

void inicializa_threads(pthread_t **vetorThreads){

        *vetorThreads = malloc(sizeof(pthread_t)*QTD_THREADS);

}

int verificaNome(char *nome)
{
    char c = nome[0];



    if( (c > 64) && (c<91) ) //A = 65 Z = 90
    {

        return 1;
    }
    else{
        return 0;
    }

}

void* thread_sleep(void *args){


    Param_t *param = (Param_t*)args;

    for(int i = 0 ; i < 10 ; i ++)
    {
        //sleep(1);
    }

    if(verificaNome(param->nome)) pthread_exit((void *)&SUCESSO_T);

    else pthread_exit((void *)&ERRO_T);

}

int main(){


    pthread_t *vetorThreads = NULL;//THREADS

    inicializa_threads(&vetorThreads);

    int *threadReturns[QTD_THREADS];//VETOR DE RETORNOS

    Param_t params[QTD_THREADS];//PARAMETROS

    for(int i = 0 ; i <QTD_THREADS; i++)
    {

       strcpy(params[i].nome, "dfogkogf");

        params[i].nome[0] = 61+i ;

        printf("\n\t%s\n",params[i].nome);
    }


    for(int i = 0 ; i <QTD_THREADS; i++)
    {

       pthread_create(&vetorThreads[i],NULL,thread_sleep,(void*)&params[i]);
    }

    for(int i = 0 ; i <QTD_THREADS; i++)
    {

      pthread_join(vetorThreads[i],(void **) &threadReturns[i]);
    }

     for(int i = 0 ; i <QTD_THREADS; i++)
    {

     printf("\tTHREAD[%d] RETORNOU=%d\n",i,*threadReturns[i]);
    }


return 0;
}

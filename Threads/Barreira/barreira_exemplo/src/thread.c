#include "thread.h"

void inicializa_parametros_threads(Param_t **param)
{
    *param = malloc((sizeof(Param_t)*QTD_THREADS_PROCESSAMENTO));

    if (*param == NULL)
    {
        perror("Erro ao alocar memoria para parametros");
        exit(1);
    }

    for (int i = 0 ; i < QTD_THREADS_PROCESSAMENTO; i++ )
    {

        (*(param) + i)->id = i;//aritimetica de ponteiros
        (*(param) + i)->inicio = i * (QTD_ELEMENTOS / QTD_THREADS_PROCESSAMENTO);

        if (i == QTD_THREADS_PROCESSAMENTO - 1) //se i for igual a quantidade de (threads-1) entao pega o resto do vetor inteiro

        {
            (*(param) + i)->fim =QTD_ELEMENTOS;
        }
        else  //continua a divisao normal
        {
            (*param)[i].fim = (i + 1) * (QTD_ELEMENTOS / QTD_THREADS_PROCESSAMENTO);
        }
    }

}

void exibe_parametros_threads(Param_t **param)
{
    if (*param == NULL)
    {
        perror("Erro ao exibir memoria para parametros");
        exit(0);
    }

    for (int i = 0 ; i < QTD_THREADS_PROCESSAMENTO; i++ )
    {
        printf("\nID{%d} INICIO{%d} FIM{%d}",(*param+i)->id,(*param+i)->inicio,(*param+i)->fim);



    }
}

void inicializa_barreira()
{
    pthread_barrier_init(&barreira,NULL,QTD_THREADS_PROCESSAMENTO);
}

void* calcula_vetor_dados(void *args)
{
    Param_t **param = (Param_t **) args;

    exibe_parametros_threads(param);

    pthread_exit(NULL);
}


void inicializa_pthreads( Param_t **param)
{
    for (int i = 0 ; i < QTD_THREADS_PROCESSAMENTO; i++ )
    {
        pthread_create(&calculadoras_t[i],NULL,calcula_vetor_dados,(void *)param);
    }
}
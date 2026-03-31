#include "thread.h"


int main(void)
{

    printf("\tDivide um vetor de double em relacao a quantidade de threads e cada uma procura o maior numero do seu respectivo bloco\n\n");

    Param_t *param_t = NULL;

    inicializa_parametros_threads(&param_t);

    inicializa_barreira();

    inicializa_vetor_dados();



    inicializa_pthreads(&param_t);
    for (int i = 0; i < QTD_THREADS_PROCESSAMENTO; i++)
    {
        pthread_join(calculadoras_t[i], NULL);
    }


    pthread_barrier_destroy(&barreira);


    free(param_t);
    return 0;
}

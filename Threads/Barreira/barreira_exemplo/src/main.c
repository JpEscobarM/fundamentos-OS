#include "thread.h"
#include <time.h>

int main(void)
{

    printf("\tDivide um vetor de double em relacao a quantidade de threads e cada uma procura o maior numero do seu respectivo bloco\n\n");

    struct timespec inicio, fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);

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

    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo =
        (fim.tv_sec - inicio.tv_sec) +
        (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("Tempo: %.4f segundos\n", tempo);

    free(vetorDados);
    free(param_t);

    return 0;
}

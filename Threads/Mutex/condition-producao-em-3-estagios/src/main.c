#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define QTD_THREADS 5

int QTD_PECAS_FUNDIDAS = 0;
int QTD_PECAS_POLIDAS = 0;;
int QTD_PECAS_PINTADAS =0;

pthread_mutex_t lock_fundicao = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_polimento = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_pintura = PTHREAD_MUTEX_INITIALIZER; //termina após 50 peças pintadas

pthread_cond_t tem_fundida= PTHREAD_COND_INITIALIZER;
pthread_cond_t tem_polida = PTHREAD_COND_INITIALIZER;

void* fundicao(void *args) {
    while (1) {
        sleep(1);
        pthread_mutex_lock(&lock_fundicao);

        QTD_PECAS_FUNDIDAS++;
        printf("\nUma peça foi fundida.");
        pthread_cond_signal(&tem_fundida);

        pthread_mutex_unlock(&lock_fundicao);

    }
    pthread_exit(NULL);
}

void *polimento(void *args) {
    while (1) {

        pthread_mutex_lock(&lock_fundicao);

        while (QTD_PECAS_FUNDIDAS == 0) {
            pthread_cond_wait(&tem_fundida,&lock_fundicao);
        }
        QTD_PECAS_FUNDIDAS--;

        pthread_mutex_unlock(&lock_fundicao);

        sleep(1);
        pthread_mutex_lock(&lock_polimento);

        QTD_PECAS_POLIDAS++;
        printf("\nUma peca foi polida.");
        pthread_cond_signal(&tem_polida);

        pthread_mutex_unlock(&lock_polimento);
    }
    pthread_exit(NULL);
}

void *pintura(void *args) {

    while (1) {
        pthread_mutex_lock(&lock_polimento);

        while (QTD_PECAS_POLIDAS == 0 ) {
            pthread_cond_wait(&tem_polida,&lock_polimento);
        }
        QTD_PECAS_POLIDAS--;
        pthread_mutex_unlock(&lock_polimento);

        sleep(1);

        pthread_mutex_lock(&lock_pintura);
        QTD_PECAS_PINTADAS++;
        printf("\nUma peca foi pintada: %d",QTD_PECAS_PINTADAS);

        if (QTD_PECAS_PINTADAS == 50) {
            exit(1);
        }
        pthread_mutex_unlock(&lock_pintura);

    }
    pthread_exit(NULL);
}

int main(void) {


    pthread_t etapa_fundicao_th[QTD_THREADS];
    pthread_t etapa_polimento_th[QTD_THREADS];
    pthread_t etapa_pintura_th[QTD_THREADS];

    for (int i = 0 ; i < QTD_THREADS ; i++) {
        pthread_create(&etapa_fundicao_th[i], NULL, fundicao, NULL);
    }

    for (int i = 0 ; i < QTD_THREADS ; i++) {
     pthread_create(&etapa_polimento_th[i],NULL, polimento, NULL);
    }

    for (int i = 0 ; i < QTD_THREADS ; i++) {
        pthread_create(&etapa_pintura_th[i],NULL, pintura, NULL);
    }

    for (int i = 0 ; i < QTD_THREADS ; i++) {
        pthread_join(etapa_fundicao_th[i], NULL);
        pthread_join(etapa_polimento_th[i], NULL);
        pthread_join(etapa_pintura_th[i], NULL);
    }

    return 0;
}
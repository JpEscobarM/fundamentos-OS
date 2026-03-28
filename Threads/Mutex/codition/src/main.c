#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t depositThreads[4]; //THREADS QUE DEPOSITAM SALDO
pthread_t withdrawThreads[4]; //THREADS QUE RETIRAM SALDO

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t haveBalance = PTHREAD_COND_INITIALIZER; //CONDICIONAL NECESSARIO

double balance= 0.0;

/**
 * FAZ DEPOSITOS DE 20 REAIS A CADA 1 SEG
 * @return NULL
 */
void* deposit() {


    for (int i = 0 ; i < 10 ; i++) {
        sleep(1);
        printf("\nwill deposit $20.0");

        pthread_mutex_lock(&lock);
        balance += 20.0;

        pthread_cond_signal(&haveBalance); //SINALIZA QUE TEM SALDO

        pthread_mutex_unlock(&lock);
        printf("\ndeposit $20.0");
    }

    pthread_exit(NULL);
}

/**
 * REALIZA 10 RETIRADAS DE 20 REAIS A CADA 1 SEGUNDO
 * @return NULL
 */
void* withdraw() {


    for (int i = 0 ; i < 10 ; i++) {
        sleep(1);
        printf("\nwill try to withdraw balance");

        pthread_mutex_lock(&lock);

        while (balance < 20 ) {
            pthread_cond_wait(&haveBalance,&lock); //ESPERA O SALDO
        }

        balance-=20.0;
        pthread_mutex_unlock(&lock);
        printf("\nwithdrew $20.0");

    }

    pthread_exit(NULL);
}

int main() {

    printf("\tstarting deposits\n");
    printf("\nInitial balance %0.2lf\n",balance);

    //INICIALIZANDO THREDS DE RETIRADA
    for (int i = 0 ; i < 4 ; i++) {
        pthread_create(&withdrawThreads[i],NULL,withdraw,NULL);
    }

    //INICIALIZANDO THREDS DE DEPOSITO
    for (int i = 0 ; i < 4 ; i++) {
        pthread_create(&depositThreads[i],NULL,deposit,NULL);
    }

    for (int i = 0 ; i < 4 ; i++) pthread_join(withdrawThreads[i],NULL);

    for (int i = 0 ; i < 4 ; i++) pthread_join(depositThreads[i],NULL);

    printf("\nBalance is equal %0.2lf",balance);
    printf("\n\n\tend");
    return 0;
}
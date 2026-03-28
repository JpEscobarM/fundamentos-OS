#include "thread.h"
#include <stdio.h>


double saldo = 10000.0;
pthread_t t1;
pthread_t t2;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* descontar()
{
    sleep(1);

    for (int i =0; i < 100; i++)
    {
        while (pthread_mutex_trylock(&lock) != 0) {
            printf("<descontar> saldo está ocupado\n");
        }
        printf("Saldo passou de %0.2lf para ",saldo);
        saldo -= 10;
        printf("%0.2f\n",saldo);
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void* depositar()
{
    sleep(1);

    for (int i =0; i < 100; i++)
    {
        while (pthread_mutex_trylock(&lock) != 0) {
            printf("<descontar> saldo está ocupado\n");
        }
        printf("Saldo passou de %0.2lf para ",saldo);
        saldo += 10;
        printf("%0.2f\n",saldo);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

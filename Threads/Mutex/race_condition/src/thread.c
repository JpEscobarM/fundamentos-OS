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
        pthread_mutex_lock(&lock);
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
        /**pode ser substituido por pthread_mutex_lock(&lock)**/
        pthread_mutex_lock(&lock);
        printf("Saldo passou de %0.2lf para ",saldo);
        saldo += 10;
        printf("%0.2f\n",saldo);
        sleep(1);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

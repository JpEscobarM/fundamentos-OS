#include "thread.h"
#include <stdio.h>


double saldo = 10000.0;
pthread_t t1;
pthread_t t2;


void* descontar()
{
    sleep(1);

    for (int i =0; i < 100; i++)
    {
        printf("Saldo passou de %0.2lf para ",saldo);
        saldo -= 10;
        printf("%0.2f\n",saldo);
    }

}

void* depositar()
{
    sleep(1);

    for (int i =0; i < 100; i++)
    {
        printf("Saldo passou de %0.2lf para ",saldo);
        saldo += 10;
        printf("%0.2f\n",saldo);
    }
}

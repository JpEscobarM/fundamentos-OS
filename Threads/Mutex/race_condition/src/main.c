#include <stdio.h>
#include <stdlib.h>
#include "thread.h"

int main()
{
    printf("\tInicio");

    printf("\nSaldo Inicial %0.2lf\n",saldo);

    pthread_create(&t1,NULL,descontar,NULL);
    pthread_create(&t2,NULL,depositar,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
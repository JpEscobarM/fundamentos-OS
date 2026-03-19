#include <stdio.h>
#include <stdlib.h>
#include "thread.h"

#define num_threads 2



int main(int argc, char **argv)
{


    pthread_t t1,t2;

    long thread_id1 = 0;
     long thread_id2 = 1;
    pronto=0;

    pthread_mutex_init(&mutex,NULL);

    for(int i =0; i < 10; i++)
    {
    pthread_create(&t1, NULL, gera_random_number, (void *)thread_id1);
    pthread_create(&t2,NULL,consome_random_number,(void*)thread_id2);

    printf("\nRAND BRUTO = %d", rand());

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    }


    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    return 0;
}

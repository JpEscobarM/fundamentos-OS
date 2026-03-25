#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 20

int ERRO_TH = 0;
int SUCESSO_TH = 1;



typedef struct{

    int thread_id;
    int num;
    int sec;
    int *retorno;

}ThreadArgs;

void* generate_random(void *args)
{

    ThreadArgs *args_t = (ThreadArgs *) args;


    printf("\n\nTHREAD_ID{%2d}|NUMERO{%2d}", args_t->thread_id,args_t->num);

    if (args_t->num % 2 == 0)
    {
        printf("\nÉ par, vai dormir por %d",args_t->sec);
        sleep(args_t->sec);

        pthread_exit((void *) &SUCESSO_TH);
    }
    else
    {
        pthread_exit((void *) &ERRO_TH);
    }

}


int main()
{

    srand(time(NULL));

    pthread_t threads_v[NUM_THREADS];
    ThreadArgs tArgs[NUM_THREADS];


    for(int i =0 ; i< NUM_THREADS ; i ++){
        tArgs[i].thread_id =i;
        tArgs[i].sec=i;
        tArgs[i].num = rand();
    }

    for(int i =0 ; i< NUM_THREADS ; i ++){
        pthread_create(&threads_v[i],NULL,generate_random,(void*) &tArgs[i]);
    }

    for(int i =0 ; i< NUM_THREADS ; i ++)
    {
        pthread_join(threads_v[i],(void **) &tArgs[i].retorno);


        printf("\nTHREAD RETORNO %d",*tArgs[i].retorno);


    }




    return 0;
}

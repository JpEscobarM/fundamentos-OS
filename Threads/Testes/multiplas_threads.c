#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 10



typedef struct{

    int thread_id;
    int num;
    int sec;

}ThreadArgs;

void* generate_random(){

}


int main()
{

    srand(time(NULL));

    pthread_t threads_v[NUM_THREADS];
    ThreadArgs tArgs[NUM_THREADS];


    for(int i =0 ; i< NUM_THREADS ; i ++){
        tArgs[i].thread_id =i;
        tArgs[i].sec=i;
        tArgs[i].num = rand()%1000;
    }

    for(int i =0 ; i< NUM_THREADS ; i ++){

    }


    return 0;
}

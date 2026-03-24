#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


typedef struct{

   int thread_id;
   char *nome;

}Param_t;

void* funcao_tarefa1(void *args){

    Param_t *param= (Param_t*)args;

    for( int i = 0 ; i < 10 ; i ++){
    printf("\nThread ID = %d Texto = %s ",param->thread_id, param->nome);


    }

     pthread_exit(NULL);
}



int main()
{

    pthread_t thread;

    Param_t param;


    param.nome = "teste";
    param.thread_id = 1;

    pthread_create(&thread,NULL,funcao_tarefa1,(void *)&param);

    pthread_join(thread,NULL);

    return 0;
}



/*
 * DESCRIÇÂO DA TAREFA
3. Construa um programa em pthreads que faça o incremento de um contador global, com as seguintes características:

a) O incremento do contador deve ser realizado por uma função executada pelas threads, contendo um laço de repetição que realiza n incrementos no contador global.

b) Essa função deverá ser executada por duas ou mais threads concorrentes.

c) A quantidade de incrementos por thread e a quantidade de threads criadas devem ser parametrizáveis, podendo ser definidos na execução do programa.

d) Ao final da execução, o programa deve exibir:

I. O resultado esperado, calculado como número de incrementos por thread × número de threads;

II. valor final obtido no contador global.

Os seguintes cenários devem ser testados:

a) 2, 4 e 8 threads executando 1000 incrementos cada

b) 2, 4 e 8 threads executando 10000 incrementos cada

c) 2, 4 e 8 threads executando 100000 incrementos cada

d) 2, 4 e 8 threads executando 1000000 incrementos cada
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define num_threads 8
#define incremento 100000
#define resultado_esperado (incremento *num_threads)


int count;

sem_t semaphore;

// FunÃ§Ã£o de thread
void* funcao_da_thread(void* num)
{
    long numero = (long)num;
    printf("Thread nÂº %ld em execucao |Count = %ld \n", numero, count);

    sem_wait(&semaphore);
    for (int i = 0; i < incremento; i++)
    {

        count++;

    }
    sem_post(&semaphore);

    pthread_exit(NULL);
}


int main(int argc, char** argv)
{
    // Cria thread


    pthread_t threads[num_threads];
    sem_init(&semaphore,0,1);

    // identifica parametro
    long numero_da_thread = 1;
    count = 0;



    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, funcao_da_thread, (void*)numero_da_thread++);
    }


    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i],NULL);
    }

    sem_destroy(&semaphore);

    printf("\nresultado esperado %d", resultado_esperado);

    printf("\nsaida: %d",count);

    return 0;
}

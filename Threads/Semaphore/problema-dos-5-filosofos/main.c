/**
* 3. Resolva o problema do jantar dos filósofos com uso de semáforos. Andrew Tanembaum descreve o problema da seguinte maneira:

"Em 1965, Dijkstra formulou e então solucionou um problema de sincronização que ele chamou de problema do jantar dos filósofos. (...)
O problema pode ser colocado de maneira bastante simples, como a seguir: cinco filósofos estão sentados em torno de uma mesa circular.
Cada filósofo tem um prato de espaguete. O espaguete é tão
escorregadio que um filósofo precisa de dois garfos para comê-lo. Entre cada par de pratos há um garfo. A vida de um filósofo consiste
em alternar períodos de alimentação e pensamento. Quando um filósofo fica suficientemente faminto, ele tenta pegar seus garfos à esquerda e à direita
, um de cada vez, não importa a ordem. Se for bem-sucedido em pegar dois garfos, ele come por um tempo, então larga os garfos e continua a pensar.
A questão fundamental é: você consegue escrever um programa para cada filósofo que faça o que deve fazer e jamais fique travado? ".
A figura abaixo representa a mesa disposta para 5 filósofos.

O programa, então, deve evitar os impasses (deadlocks), onde todos pegam um garfo e ficam esperando o outro; e evitar inanição
(starvation), onde alguns filósofos nunca comem. Resolva isso utilizando semáforos, considerando que o tamanho do semáforo é equivalente
à quantidade de garfos que, por sua vez, é equivalente à quantidade de filósofos.

Dicas:

- O programa (e, consequentemente, cada thread) deverá permanecer em execução de maneira contínua.

- A sequência de execução deve ser pensar, pegar os garfos (ou aguardar), comer e soltar os garfos.

- Atribua um tempo para representar as ações de comer e pegar.

- Utilize sem_wait() para pegar os garfos e sem_post() para soltá-los

- Organize o código de forma a identificar os filósofos pares e ímpares

- Procure identificar, para cada filósofo, qual é o garfo que está à sua direita e à sua esquerda.

 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define FOME 5
#define QTD_THREADS 6

typedef struct
{
    char *nome;
    int garfoOcupado; //boolean, 0 - nao está sendo usado 1- esta sendo usado
    int comFome;

}Filosofo;


Filosofo filosofos[5] = {
    {"Socrates", 0, 0},
    {"Platao", 0, 0},
    {"Aristoteles", 0, 0},
    {"Diogenes", 0, 0},
    {"Kant", 0, 0}
};

/*
 * THREADS
 */
sem_t sem;
pthread_t listaThreads[QTD_THREADS];
int contadorDeComidas;

void* deixa_com_fome()
{



    while (contadorDeComidas<FOME)
    {

        sem_wait(&sem);

        int posicaoFilosofo = rand() % 5; //gera numero entre 0 e 4
        filosofos[posicaoFilosofo].comFome = 1;
        printf("\n\tO filosofo %s está com fome",filosofos[posicaoFilosofo].nome);

        sem_post(&sem);
    }

    pthread_exit(NULL);
}


void* comer(void* args)
{
    int posicaoFilosofo = (int)args;



    int garfoAEsquerda;


    while (contadorDeComidas < FOME)
    {
        sem_wait(&sem);
        printf("\n-----------------------------");
        if (filosofos[posicaoFilosofo].comFome == 1)
        {
            //se estiver no inicio do vetor, tem que pegar o garfo da outra ponta
            if (posicaoFilosofo - 1 == -1)
            {
                garfoAEsquerda = 4;


            }
            else
            {
                garfoAEsquerda = posicaoFilosofo - 1;
            }

            //se ninguem estiver usando seu garfo, e o garfo da esquerda estiver livre, pega os dois
            if ((filosofos[posicaoFilosofo].garfoOcupado == 0) && (filosofos[garfoAEsquerda].garfoOcupado == 0))
            {
                filosofos[posicaoFilosofo].garfoOcupado = 1;
                filosofos[garfoAEsquerda].garfoOcupado = 1;

                printf("\nO Filosofo %s pegou seu garfo e o garfo de %s e irá comer",
                       filosofos[posicaoFilosofo].nome, filosofos[garfoAEsquerda].nome);

                printf("\n\t%s comeu\n",filosofos[posicaoFilosofo].nome);

                filosofos[posicaoFilosofo].garfoOcupado = 0;
                filosofos[garfoAEsquerda].garfoOcupado = 0;
                filosofos[posicaoFilosofo].comFome = 0;
                printf("O filosofo %s está sem fome e liberou os garfos", filosofos[posicaoFilosofo].nome);
                contadorDeComidas++;
            }
        }
        else
        {
            printf("\nO Filosofo %s nao esta com fome no momento",filosofos[posicaoFilosofo]);
        }
        printf("\n-----------------------------\n");
        sem_post(&sem);
    }


    pthread_exit(NULL);
}



int main(void)
{
    contadorDeComidas = 0;
    sem_init(&sem,0,1);

    srand(time(NULL));

    pthread_create(&listaThreads[0],NULL,deixa_com_fome,NULL);//inicia thread que deixa com fome

    for (int i = 1; i < QTD_THREADS;i++)
    {
        int posicoesFilosofos = i-1;
        pthread_create(&listaThreads[i],NULL,comer,(void*) posicoesFilosofos);
    }

    for (int i = 1; i < QTD_THREADS;i++)
    {
        pthread_join(listaThreads[i],NULL);
    }



    sem_destroy(&sem);

    return 0;
}
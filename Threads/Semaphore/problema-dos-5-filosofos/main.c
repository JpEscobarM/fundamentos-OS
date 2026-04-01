#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_FILOSOFOS 5

typedef struct {
    char *nome;
    int id;
} Filosofo;

Filosofo filosofos[NUM_FILOSOFOS] = {
    {"Socrates", 0},
    {"Platao", 1},
    {"Aristoteles", 2},
    {"Diogenes", 3},
    {"Kant", 4}
};

sem_t garfos[NUM_FILOSOFOS];
pthread_t threads[NUM_FILOSOFOS];

void pensar(Filosofo f) {
    printf("%s esta pensando...\n", f.nome);
    sleep(rand() % 3 + 1);
}

void comer(Filosofo f) {
    printf("%s esta comendo...\n", f.nome);
    sleep(rand() % 3 + 1);
}

void pegar_garfos(Filosofo f) {
    int esquerdo = f.id;
    int direito = (f.id + 1) % NUM_FILOSOFOS; // o resto é sempre == id, a nao ser que o id == % {NUM} ai será 0 ou seja, volta pro inicio do vetor

    if (f.id % 2 == 0) {//quebra a espera circular
        sem_wait(&garfos[direito]);
        printf("%s pegou o garfo da direita (%d)\n", f.nome, direito);

        sem_wait(&garfos[esquerdo]);
        printf("%s pegou o garfo da esquerda (%d)\n", f.nome, esquerdo);
    } else {
        sem_wait(&garfos[esquerdo]);
        printf("%s pegou o garfo da esquerda (%d)\n", f.nome, esquerdo);

        sem_wait(&garfos[direito]);
        printf("%s pegou o garfo da direita (%d)\n", f.nome, direito);
    }
}

void soltar_garfos(Filosofo f) {
    int esquerdo = f.id;
    int direito = (f.id + 1) % NUM_FILOSOFOS;

    sem_post(&garfos[esquerdo]);
    sem_post(&garfos[direito]);

    printf("%s soltou os garfos (%d) e (%d)\n", f.nome, esquerdo, direito);
}

void* rotina_filosofo(void* arg) {
    Filosofo *f = (Filosofo*) arg;

    while (1) {
        pensar(*f);

        printf("%s esta com fome\n", f->nome);

        pegar_garfos(*f);
        comer(*f);
        soltar_garfos(*f);

        printf("----------------------------------\n");
    }

    return NULL;
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        sem_init(&garfos[i], 0, 1);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_create(&threads[i], NULL, rotina_filosofo, &filosofos[i]);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        sem_destroy(&garfos[i]);
    }

    return 0;
}
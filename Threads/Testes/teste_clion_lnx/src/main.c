#include <stdio.h>
#include "thread.h"

int main() {
    pthread_t t;
    pthread_create(&t, NULL, tarefa, NULL);
    pthread_join(t, NULL);
    return 0;
}
#include <stdio.h>
#include "thread.h"

void* tarefa(void* arg) {
    printf("Thread rodando\n");
    return NULL;
}
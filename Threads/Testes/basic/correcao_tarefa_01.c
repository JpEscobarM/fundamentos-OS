/**

		Programação Concorrente com Pthreads e Linguagem C

		s02-a10-tarefa.c

		Crie um programa com 5 threads usando laço e
		passe para cada uma o nome da respectiva thread.
		Cada thread dorme por 10 segundos de 1 em 1 segundo.
		Cada thread retorna ao termino um codigo de ERRO caso o
		seu nome nao inicie com letra maiuscula, e SUCESSO caso inicie.
*/


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define	N_THREADS	5

int ERRO_TH = 111;		// Codigo que indica erro na thread
int SUCESSO_TH = 222; 	// Codigo que indica sucesso na thread

pthread_t minhas_threads[N_THREADS];		// Identificadores para 10 threads


/** Espera passar 10 segundos, de segundo em segundo */
void codigo_tarefa(char *nome){
	for( int ns=0; ns < 10; ++ns) {
		sleep(1);
		printf("Tarefa %s: passaram %d segundos do total de 10.\n", nome, ns+1);
	}
	if( isupper(nome[0]) )
		pthread_exit(&SUCESSO_TH);
	pthread_exit(&ERRO_TH);
}


/** Função principal, cria as threads */
int main(void){
	char *param_threads[N_THREADS] = {
			"joao", "Pedro", "maria", "Ana", "jose" };

	int *retornos[N_THREADS];	// Codigo de termino das threads

	printf("Inicio\n");

	// Cria todas as threads
	for( int i=0; i<N_THREADS; ++i)
		pthread_create(&minhas_threads[i], NULL, (void *) codigo_tarefa, (void *)param_threads[i]);

	// Espera por todas as threads
	for( int i=0; i<N_THREADS; ++i) {
		pthread_join(minhas_threads[i], (void **) &retornos[i]);
		printf("Thread %s terminou com retorno %d\n", param_threads[i], *retornos[i]);
	}

	printf("Fim\n");
	return(0);
}




#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define	N_THREADS	4


pthread_t th_deposita;				// Identificador da UNICA thread que deposita
pthread_t th_retira[N_THREADS];		// Identificadores das threads que retiram

pthread_mutex_t mutex_saldo = PTHREAD_MUTEX_INITIALIZER;
double saldo = 0.0;					// Saldo inicial é zero


pthread_cond_t tem_saldo = PTHREAD_COND_INITIALIZER;	// Espera pelo saldo necessário



/** Faz 1 deposito de 10*20*4 = 800 reais */
void codigo_tarefa_deposita(void){
	sleep(1);
	printf("Vai depositar 800.00 reais\n");
	pthread_mutex_lock(&mutex_saldo);	
	saldo += 800;

	//pthread_cond_signal( &tem_saldo);		// Sinaliza que tem algum saldo
	pthread_cond_broadcast( &tem_saldo);	// Sinaliza que tem algum saldo

	pthread_mutex_unlock(&mutex_saldo);	
	printf("Depositou 800.00 reais\n");
}


/** Faz 10 retiradas de 20 reais a cada 1 segundo */
void codigo_tarefa_retira(void){
	for( int ns=0; ns < 10; ++ns) {
		sleep(1);
		printf("Vai tentar retirar 20.00 reais\n");
		pthread_mutex_lock(&mutex_saldo);

		// Testa se tem o saldo necessário		
		while( saldo < 20.0 )
			pthread_cond_wait( &tem_saldo, &mutex_saldo);	// Espera por saldo X1       X2!!!

		saldo -= 20.0;

		pthread_mutex_unlock(&mutex_saldo);	
		printf("Retirou 20.00 reais\n");
	}
}


/** Função principal, cria as threads */
int main(void){
	printf("Inicio\n");
	printf("Saldo inicial %0.2lf\n", saldo);

	// Cria todas as threads que retiram
	for( int i=0; i<N_THREADS; ++i)
		pthread_create(&th_retira[i], NULL, (void *) codigo_tarefa_retira, NULL);

	// Cria a UNICA thread que deposita
	pthread_create(&th_deposita, NULL, (void *) codigo_tarefa_deposita, NULL);

	// Espera por todas as threads que retiram
	for( int i=0; i<N_THREADS; ++i)
		pthread_join(th_retira[i], NULL);

	// Espera pela UNICA thread que deposita
	pthread_join(th_deposita, NULL);

	printf("Saldo final ficou %0.2lf\n", saldo);

	printf("Fim\n");
	return(0);
}



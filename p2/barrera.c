#include "barrera.h"

void crea (barrera_t *b, int N) 
{
	//Inicializar permitidos al valor de N
	b->permitidos = N;
	//Inicializar el mutex
	pthread_mutex_init(&(b->mutex),NULL);
	//Inicializar la variable de condición
	pthread_cond_init(&(b->condicion),NULL);
}

void destruye (barrera_t *b) 
{
	//Destruir el mutex
	pthread_mutex_destroy(&(b->mutex));
	//Destruir la variable de condición
	pthread_cond_destroy(&(b->condicion));
}

void sincronizar (barrera_t *b)
{
	//Entrar en el mutex
	pthread_mutex_lock(&(b->mutex));

	//Decrementar permitidos
	b->permitidos--;

	//Si permitidos es 0 liberar a todos los hilos de la variable de condición
	if (b->permitidos==0)
	{
		pthread_cond_broadcast(&(b->condicion));
	}
	else //Si no, bloquearse en la variable de condición
	{
		pthread_cond_wait(&(b->condicion), &(b->mutex)); //me bloqueo y libero el mutex
	}

	//Incrementar permitidos para que cuando salgan todos los hilos pueda volverse a usar la barrera
	b->permitidos++;

	//Liberar el mutex
	pthread_mutex_unlock(&(b->mutex));
}

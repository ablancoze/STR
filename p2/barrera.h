#include <stdio.h>
//Incluir la librería para la utilización de posix
#include <signal.h>
#include <pthread.h>


typedef struct 
{
	//Definir el mutex
	pthread_mutex_t mutex;
	//Definir la variable de condición
	pthread_cond_t condicion;
	int permitidos;
} barrera_t;

void crea (barrera_t *b, int N);
void destruye (barrera_t *b);
void sincronizar (barrera_t *b);

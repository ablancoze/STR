#include "buffer_acotado.h"
#include <stdio.h>
#include <stdlib.h>

#define REPETICIONES 5
#define NUM_HILOS 3

void hilo_productor(limited_buffer_t *b) 
{
	//Llamar REPETICIONES veces a limited_buffer_put mostrando un mensaje con el número que se introducirá
	for (int i; i <= REPETICIONES; i++)
	{
		limited_buffer_put(b,i);
	}
}

void hilo_consumidor(limited_buffer_t *b) 
{
	int *elem=(int*)malloc(sizeof(int));
	//Llamar REPETICIONES veces a limited_buffer_get mostrando un mensaje con el número leído
	for (int i; i <= REPETICIONES; i++)
	{
		limited_buffer_get(b,elem);
	}
}


int main (void) 
{
	//Definir una variable limited_buffer_t
	limited_buffer_t b;

	//Inicializar el buffer
	limited_buffer_create (&b,10);

	//Crear dos vectores idP e idC de tipo pthread_t y de tamaño NUM_HILOS para almacenar los identificadores de los productores y de los consumidores
	pthread_t idP[NUM_HILOS];
	pthread_t idC[NUM_HILOS];
	//Lanzar los NUM_HILOS productores y consumidores
	for (int i = 0; i<= NUM_HILOS; i++)
	{
		pthread_create(&idP[i], NULL, (void *)hilo_productor, &b);
		pthread_create(&idC[i], NULL, (void *)hilo_consumidor, &b);
	}
	//Esperar a que terminen todos los productores y los consumidores
	for (int i = 0; i<= NUM_HILOS; i++)
	{
		pthread_join(idP[i], NULL);
		pthread_join(idC[i], NULL);
	}
	//Destruir el buffer
	limited_buffer_destroy(&b);
	return 0;
}

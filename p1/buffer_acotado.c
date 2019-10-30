#include "buffer_acotado.h"
#include <stdio.h>   
#include <stdlib.h> 
# define VACIO 0

void limited_buffer_create  (limited_buffer_t *buffer, int buff_size) 
{
	//Reservar la memoria para el campo buf del parámetro buffer usando el parámetro buff_size
	buffer->buf = (int*)malloc(buff_size*sizeof(int));	
	//Inicializar los contadores y el tamaño del buffer
	buffer->cuenta = 0;
	buffer->primero = 0;
	buffer->ultimo = 0;
	buffer->tamano = buff_size;
	//Inicializar el mutex
	pthread_mutex_init(&(buffer->mutex),NULL);
	//Inicializar las variables de condición
	pthread_cond_init(&(buffer->buffer_lleno),NULL);
	pthread_cond_init(&(buffer->buffer_vacio),NULL);
}

void limited_buffer_destroy (limited_buffer_t  *buffer) 
{
	//Liberar el buffer
	free(buffer->buf);
	//Destruir el mutex
	pthread_mutex_destroy(&(buffer->mutex));
	//Destruir las variables de condición
	pthread_cond_destroy(&(buffer->buffer_lleno));
	pthread_cond_destroy(&(buffer->buffer_vacio));

}

void limited_buffer_put (limited_buffer_t  *buffer, int  elem) 
{
	//Acceder a la región crítica a través del mutex
	pthread_mutex_lock(&(buffer->mutex));
	//Mientras el buffer esté lleno, bloquearse en la variable de condición lleno
	if (buffer->cuenta == buffer->tamano)
	{
		pthread_cond_wait(&(buffer->buffer_lleno), &(buffer->mutex));
	}
	//Añadir elem en el buffer y actualizar cuenta y último
	buffer->buf[buffer->ultimo] = elem;
	if (controlOutArrayUltimo(buffer) == 1)
	{
		buffer->ultimo = 0;
	}
	else
	{
		buffer->ultimo ++;
	}
	buffer->cuenta ++;
	printf("insertando elemento %d en la posicion %d \n",elem,buffer->ultimo);
	//Liberar el mutex
	pthread_mutex_unlock(&(buffer->mutex));
	//Hacer un signal en la variable de condición vacio
	pthread_cond_signal(&(buffer->buffer_vacio));

}

void limited_buffer_get (limited_buffer_t  *buffer, int *elem) 
{
	//Acceder a la región crítica a través del mutex
	pthread_mutex_lock(&(buffer->mutex));
	//Mientras el buffer esté vacío, bloquearse en la variable de condición vacio
	if (buffer->cuenta == VACIO)
	{
		pthread_cond_wait(&(buffer->buffer_lleno), &(buffer->mutex));
	}
	//Guardar en *elem el primer elemento del buffer y actualizar cuenta y primero
	*elem = buffer->buf[buffer->primero];
	if (controlOutArrayPrimero(buffer) == 1)
	{
		buffer->primero = 0;
	}
	else
	{
		buffer->primero ++;
	}
	buffer->cuenta --;
	printf("sacando elemento %d de la posicion %d \n",*elem,buffer->primero);
	//Liberar el mutex
	pthread_mutex_unlock(&(buffer->mutex));
	//Hacer un signal en la variable de condición lleno
	pthread_cond_signal(&(buffer->buffer_lleno));
}

int controlOutArrayPrimero(limited_buffer_t *buffer)
{
	//Para incrementar primero
	if (buffer->primero >= buffer->tamano-1)
	{
		return 1;
	}
	return 0;
}

int controlOutArrayUltimo(limited_buffer_t *buffer)
{
	//Para incrementar primero
	if (buffer->ultimo >= buffer->tamano-1)
	{
		return 1;
	}
	return 0;
}

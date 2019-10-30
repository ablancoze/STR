//Compilación por consola: gcc p5.c funciones_time.c -o p5 -lpthread -lrt
//Configuración en eclipse: botón derecho sobre el proyecto -> Properties -> C/C++ Build -> Settins -> Cross GCC Linker -> Libraries -> Añadir pthread y rt

#include <stdlib.h>
#include <stdio.h>
//Añadir el include de las señales
#include <signal.h>
//Añadir el include de los hilos
#include <pthread.h>
//Añadir el include de los relojes
#include <time.h> 

#include "funciones_time.h"

//Crear una estructura denominada seniales_t con dos campos de tipo entero: recibidas y esperadas
typedef struct 
{
	int recibidas;
	int esperadas;
}signal_t;



void HiloSigInt(signal_t *seniales) 
{
	//Crear un conjunto de señales
	sigset_t señales;
	int signal;
	
	//Inicializar el conjunto de señales a vacío
	sigemptyset(&señales);
	
	//Añadir SIGINT al conjunto de señales
	sigaddset(&señales, SIGINT);
	
	//Añadir SIGRTMIN al conjunto de señales
	sigaddset(&señales, SIGRTMIN);
	
	//Añadir el conjunto de señales a la máscara de señales bloqueadas
	pthread_sigmask(SIG_BLOCK, &señales, NULL);
	
	//Quitar SIGRTMIN del conjunto de señales. Esto es necesario ya que, aunque bloqueamos las dos señales, solamente esperamos por SIGINT
	sigdelset(&señales, SIGRTMIN);
	
	//Mientras las señales recibidas sean menos que las esperadas
	while(seniales->recibidas < seniales->esperadas)
	{
		//Esperar por el conjunto de señales (solamente contiene SIGINT)
		if(sigwait(&señales, &signal)==0)
		{
			//Incrementar el contador de las capturas producidas
			seniales->recibidas++;
		}
	}//Fin mientras
}

void HiloPeriodicoConRetardos(signal_t *seniales) 
{
	//Crear un conjunto de señales
	sigset_t señales;
	
	//Inicializar el conjunto de señales a vacío
	sigemptyset(&señales);
	
	//Añadir SIGINT al conjunto de señales
	sigaddset(&señales, SIGINT);
	
	//Añadir SIGRTMIN al conjunto de señales
	sigaddset(&señales, SIGRTMIN);
	
	//Añadir el conjunto de señales a la máscara de señales bloqueadas
	pthread_sigmask(SIG_BLOCK, &señales, NULL);
	
	//Definir tres variables de tipo struct timespec para almacenar la lectura de la hora actual, el instante siguiente y el periodo de repetición
	struct timespec hora, siguiente, periodo;
	
	//Definir una variable de tipo puntero a struct tm para almacenar la transformación de la hora en formato calendario. Debe ser de tipo puntero porque la función localtime devuelve la dirección de memoria con la conversión.
	struct tm* time;
	
	//Leer la hora actual usando CLOCK_MONOTONIC
	clock_gettime(CLOCK_MONOTONIC, &hora);
	
	//Inicializar el periodo de repetición a 5 segundos (hay que inicializar también los nanosegundos)
	segundos2timespec(&periodo, 5.0);
	
	//Calcular el siguiente instante como la suma de la hora actual y el periodo de repetición (para hacer la suma, usar las funciones definidas en la librería funciones_time)
	SumaTimeSpec(&siguiente, hora, periodo);
	
	//Mientras las señales recibidas sean menos que las esperadas
	while(seniales->recibidas < seniales->esperadas)
	{
		//Leemos la hora actual de CLOCK_MONOTONIC
		clock_gettime(CLOCK_MONOTONIC, &hora);
		
		//Transformamos la hora actual a formato struct tm (usar la variable definida fuera del bucle) mediante la función localtime (usar los segundos de la hora actual)
		time = localtime(&hora.tv_sec);
		
		//Mostrar la hora en formato día/mes/año horas:minutos:segundos.milisegundos. Los milisegundos se obtienen de dividir los nanosegundos de la hora actual por 1000000
		printf("%d/%d/%d %d:%d:%d.%d \n", time->tm_mday, time->tm_mon, time->tm_year, time->tm_hour, time->tm_min, time->tm_sec, hora.tv_nsec/1000000);
		
		//Leemos la hora actual de CLOCK_REALTIME
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &hora);
		
		//Transformamos la hora actual a formato struct tm (usar la variable definida fuera del bucle) mediante la función localtime (usar los segundos de la hora actual)
		time = localtime(&hora.tv_sec);
		
		//Mostrar la hora en formato día/mes/año horas:minutos:segundos.milisegundos. Los milisegundos se obtienen de dividir los nanosegundos de la hora actual por 1000000
		printf("%d/%d/%d %d:%d:%d.%d \n", time->tm_mday, time->tm_mon, time->tm_year, time->tm_hour, time->tm_min, time->tm_sec, hora.tv_nsec/1000000);
		
		//Leemos la hora actual de CLOCK_THREAD_CPUTIME_ID
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &hora);
		
		//Transformamos la hora actual a formato struct tm (usar la variable definida fuera del bucle) mediante la función localtime (usar los segundos de la hora actual)
		time = localtime(&hora.tv_sec);
		
		//Mostrar la hora en formato día/mes/año horas:minutos:segundos.milisegundos. Los milisegundos se obtienen de dividir los nanosegundos de la hora actual por 1000000
		printf("%d/%d/%d %d:%d:%d.%d \n", time->tm_mday, time->tm_mon, time->tm_year, time->tm_hour, time->tm_min, time->tm_sec, hora.tv_nsec/1000000);
		
		//Crear un bucle for de 100000000 de vueltas que no haga nada (el cuerpo del bucle estará vacío). Esta acción incrementará el tiempo de procesador del hilo
		for (int i = 0;i<100000000;i++)
		{
			/*aaaaa*/
		}
		
		//Dormir el hilo hasta el instante calculado usando CLOCK_MONOTONIC y retardo absoluto
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME,&siguiente, NULL);
		
		//Calcular el siguiente instante añadiendo el periodo al valor calculado previamente (para hacer la suma, usar las funciones definidas en la librería funciones_time)
		AcumTimeSpec(&siguiente, periodo);
	}//Fin mientras

}

void HiloPeriodicoConTemporizador(signal_t *seniales){
	//Crear un conjunto de señales
	sigset_t señales;
	int signal;
	//Inicializar el conjunto de señales a vacío
	sigemptyset(&señales);
	
	//Añadir SIGINT al conjunto de señales
	sigaddset(&señales, SIGINT);
	
	//Añadir SIGRTMIN al conjunto de señales
	sigaddset(&señales, SIGRTMIN);
	
	//Añadir el conjunto de señales a la máscara de señales bloqueadas
	pthread_sigmask(SIG_BLOCK, &señales, NULL);
	
	//Quitar SIGINT del conjunto de señales. Esto es necesario ya que, aunque bloqueamos las dos señales, solamente esperamos por SIGRTMIN
	sigdelset(&señales, SIGINT);
	
	//Definir una variable id_timer de tipo timer_t que sirva de identificador del temporizador
	timer_t id_timer;
	
	//Definir una variable evento de tipo struct sigevent para indicar la acción del temporizador
	struct sigevent event;
	
	//Inicializar la señal evento indicando que el temporizador generará una señal y que la señal generada será SIGRTMIN
	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo = SIGRTMIN;
	//Definir una variable datos_temporizador de tipo struct itimerspec
	struct itimerspec datos_temporizador;
	//Leer la hora actual de CLOCK_MONOTONIC y almacenarla en el campo it_value de datos_temporizador
	clock_gettime(CLOCK_MONOTONIC, &datos_temporizador.it_value);
	//Añadir dos segundos al campo it_value de datos_temporizador
	datos_temporizador.it_value.tv_sec=2;
	datos_temporizador.it_value.tv_tv_nsec=0;
	//Establecer el campo it_interval de datos_temporizador a 2 segundos (hay que inicializar también los nanosegundos)
	datos_temporizador.it_interval.tv_sec=2;
	//Crear el temporizador usando CLOCK_MONOTONIC, evento e id_timer
	timer_create(CLOCK_MONOTONIC, &event, &id_timer);
	//Armar el temporizador usando id_timer, retardos absolutos y datos_temporizador (no es necesario guardar el tiempo restante en caso de salida prematura, por lo que se puede usar NULL)
	timer_settime(id_timer, TIMER_ABSTIME, &datos_temporizador, NULL);
	//Mientras las señales recibidas sean menos que las esperadas
	while(seniales->recibidas < seniales->esperadas)
	{
		//Imprimir el número de señales recibidas actualmente
		printf("Recibidas: %d \n", seniales->recibidas);
		//Esperar por la señal SIGRTMIN
		sigwait(&señales, &signal);
	}//Fin mientras

}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf(
				"Error en la ejecución. El formato correcto es p2_2 num_capturas\n");
		return 0;
	}
	signal_t seniales;
	seniales.esperadas= atoi(argv[1]);
	seniales.recibidas=0;

	//Crear un conjunto de señales
	sigset_t señales;
	//Inicializar el conjunto de señales a vacío
	sigemptyset(&señales);
	//Añadir SIGINT al conjunto de señales
	sigaddset(&señales, SIGINT);
	//Añadir SIGRTMIN al conjunto de señales
	sigaddset(&señales, SIGRTMIN);
	
	//Añadir el conjunto de señales a la máscara de señales bloqueadas
	pthread_sigmask(SIG_BLOCK, &señales, NULL);
	//Crear identificadores de hilo de tipo pthread_t para todos los hilos

	//Crear un hilo con la función HiloSigInt y el parámetro seniales

	//Crear un hilo con la función HiloPeriodicoConRetardos y el parámetro seniales

	//Crear un hilo con la función HiloPeriodicoConRetardos y el parámetro seniales

	//Esperar al hilo HiloSigInt

	//Esperar al hilo HiloPeriodicoConRetardos

	//Esperar al hilo HiloPeriodicoConTemporizador

}



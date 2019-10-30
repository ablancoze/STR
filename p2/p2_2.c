//Compilación por consola: gcc p2_2.c -o p2_2 -lpthread
//Configuración en eclipse: botón derecho sobre el proyecto -> Properties -> C/C++ Build -> Settins -> Cross GCC Linker -> Libraries -> Añadir pthread

//Añadir la librería de utilización de señales
#include <signal.h>
//Añadir la librería de utilización de pthreads
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void HiloSigInt (int *num_capturas) {
	//Crear un conjunto de señales
	sigset_t senal;
	int sig;

	//Inicializar el conjunto de señales a vacío
	sigemptyset(&senal);
	
	//Añadir SIGINT al conjunto de señales
	sigaddset(&senal, SIGINT);
	
	//Añadir el conjunto de señales a la máscara de señales bloqueadas
	pthread_sigmask(SIG_BLOCK, &senal, NULL);
	
	//Mientras no se capturen *num_capturas señales
	int capturas=0;
	for (int i=0;i<*num_capturas;i++)
	{
		//Esperar por el conjunto de señales (solamente contiene SIGINT)
		if(sigwait(&senal, &sig)==0)
		{
			//Incrementar las capturas
			capturas=i;
		}	
	}
}

int main (int argc, char *argv[]) {
	if (argc!=2) {
		printf("Error en la ejecución. El formato correcto es p2_2 num_capturas\n");
		return 0;
	}
	int num_capturas=atoi(argv[1]);
	//Crear un conjunto de señales
	sigset_t signal;
	//Inicializar el conjunto de señales a vacío
	sigemptyset(&signal);
	//Añadir SIGINT al conjunto de señales
	sigaddset(&signal, SIGINT);
	//Añadir el conjunto de señales a la máscara de señales bloqueadas
	pthread_sigmask(SIG_BLOCK, &signal, NULL);
	//Crear un identificador de hilo de tipo pthread_t
	pthread_t thread_local;
	//Crear un hilo con la función HiloSigInt y el número de capturas por las que se desea esperar
	pthread_create(&thread_local, NULL, (void *)HiloSigInt,(void *)&num_capturas);
	//Esperar por el hilo anterior
	pthread_join(thread_local, NULL);
}

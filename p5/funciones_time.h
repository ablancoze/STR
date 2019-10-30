#include <time.h>
#include <stdio.h>
void RestaTimeSpec(struct timespec *dst, struct timespec src1, struct timespec src2); // dst=src1-src2
void SumaTimeSpec(struct timespec *dst, struct timespec src1, struct timespec src2);  // dst=src1+src2
void AcumTimeSpec(struct timespec *dst, struct timespec src);						  // dst=dst+src
void ClearTimeSpec(struct timespec *dst);											  // dst=0
void CopiarTimeSpec(struct timespec *dst, struct timespec src);						  // dst=src
void ImprimirTimeSpec(struct timespec dst);
void segundos2timespec(struct timespec *dst, double src);							  // Transforma un valor real a un timespect de la siguiente forma
																					  // la parte entera representan segundos
																					  // la parte decimal representan nanosegundos
double timespec2segundos(struct timespec src);										  // Transforma un valor timespect a un valor en segundos de la siguiente forma
																					  // la parte entera representan segundos
																					  // la parte decimal representan nanosegundos
void ms2timespec(struct timespec *dst, int src);									  // Transforma un valor entero representado en forma de milisegundos a timespec
int timespec2ms(struct timespec src);												  // Transforma un valor timespec a un entero representado en forma de milisegundos

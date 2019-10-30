#include "funciones_time.h"

void RestaTimeSpec(struct timespec *dst, struct timespec src1, struct timespec src2) {
	if (src2.tv_nsec > src1.tv_nsec) {
		dst->tv_sec = src1.tv_sec - src2.tv_sec - 1;
		dst->tv_nsec = (src1.tv_nsec - src2.tv_nsec) + 1000000000;
	}
    else {
		dst->tv_sec = src1.tv_sec - src2.tv_sec;
		dst->tv_nsec = src1.tv_nsec - src2.tv_nsec;
    }
}

void SumaTimeSpec(struct timespec *dst, struct timespec src1, struct timespec src2) {
	if (src2.tv_nsec + src1.tv_nsec > 1000000000) {
		dst->tv_sec = src1.tv_sec + src2.tv_sec + 1;
		dst->tv_nsec =  src2.tv_nsec + src1.tv_nsec - 1000000000;
	}
	else {
		dst->tv_nsec =  src2.tv_nsec + src1.tv_nsec;
		dst->tv_sec  = src1.tv_sec + src2.tv_sec;
	}
}

void AcumTimeSpec(struct timespec *dst, struct timespec src)
{
	if (dst->tv_nsec + src.tv_nsec > 1000000000) {
		dst->tv_sec = dst->tv_sec + src.tv_sec + 1;
		dst->tv_nsec =  dst->tv_nsec + src.tv_nsec - 1000000000;
	}
	else {
		dst->tv_nsec = dst->tv_nsec + src.tv_nsec;
		dst->tv_sec  = dst->tv_sec  + src.tv_sec;
	}
}

void ClearTimeSpec(struct timespec *dst) {
	dst->tv_sec = dst->tv_nsec = 0;
}

void CopiarTimeSpec(struct timespec *dst, struct timespec src) {
	dst->tv_sec  = src.tv_sec ;
	dst->tv_nsec = src.tv_nsec ;
}

void ImprimirTimeSpec(struct timespec dst) {
	printf("Sec:  %ld\n", dst.tv_sec );
	printf("nSec: %09ld\n", dst.tv_nsec );
}

void segundos2timespec(struct timespec *dst, double src) {
	dst->tv_sec=(int)src;
	dst->tv_nsec=(src-dst->tv_sec)*1000000000;
	while (dst->tv_nsec>999999999) {
		dst->tv_nsec-=1000000000;
		dst->tv_sec++;
	}
}

double timespec2segundos(struct timespec src) {
	return src.tv_sec+src.tv_nsec/1000000000.0;
}

void ms2timespec(struct timespec *dst, int src) {
	dst->tv_sec=src/1000;
	dst->tv_nsec=(src%1000)*1000000;
}

int timespec2ms(struct timespec src) {
	return src.tv_sec*1000+src.tv_nsec/1000000;
}

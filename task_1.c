#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5

int main(void) {
    /* ПОСТРОЕНИЕ СЛАУ */
    long double x[N+1];
    long double f[N+1];
    long double F[N];
    // поиск значений в точках функции
    for (int i = 0; i <= N; i++) {
        x[i] = 2 * i / (long double)N;
        f[i] = x[i] * fabs(cosl(5*x[i]));
        //printf("%Lf %Lf\n", x[i], f[i]);
    }
    // значение правой части уравнения
    for (int i = 1; i < N; i++) {
        F[i-1] = 6 * (f[i-1] - 2*f[i] + f[i+1]) * ((N/(long double)2)*(N/(long double)2));
        printf("%Lf\n", F[i-1]);
    }

    /* РЕШЕНИЕ СЛАУ */
    // использован метод прогонки
    long double a[N];
    long double b[N];
    long double c[N];
    a[0] = 0;
    b[N-2] = 0;
    for (int i = 0; i < (N-2); i++) {
        a[i+1] = 1;
        c[i] = 4;
        b[i] = 1;
    }
    c[N-2] = 4;

	long double g[N];
    long double m;
	for (int i = 1; i < (N-1); i++) {
		m = a[i]/c[i-1];
        c[i] = c[i] - m*b[i-1];
		F[i] = F[i] - m*F[i-1];
	}
	g[N-2] = F[N-2]/c[N-2];
	for (int i = N-3; i >= 0; i--)
		g[i] = (F[i]-b[i]*g[i+1])/c[i];
    for (int i = 0; i < (N-1); i++)
        printf("c[%d] = %Lf\n", i+1, g[i]);

    /* ПОИСК ОСТАЛЬНЫХ КОЭФФИЦИЕНТОВ (это уже нетрудная задача и здесь не требовалась) */
    printf("---------\n");
    for (int i = 0; i < (N-1); i++) {
        printf("a[%d] = %Lf\n", i+1, f[i+1]);
    }
    printf("---------\n");
    long double buf;
    for (int i = 1; i < N; i++) {
        if (i > 1)
            buf = ((long double)1/2)*(2/((long double)N))*g[i-1] - 
            ((long double)1/6)*(2/((long double)N))*(g[i-1] - g[i-2]) + 
            (f[i]-f[i-1])*((long double)N/2);
        else
            buf = ((long double)1/2)*(2/((long double)N))*g[i-1] - 
            ((long double)1/6)*(2/((long double)N))*(g[i-1] - 0) + 
            (f[i]-f[i-1])*((long double)N/2);
        printf("b[%d] = %Lf\n", i, buf);
    }
    printf("---------\n");
    for (int i = 0; i < (N-1); i++) {
        if (i > 0)
            printf("d[%d] = %Lf\n", i+1, (g[i]-g[i-1]) * ((long double)N/2));
        else
            printf("d[%d] = %Lf\n", i+1, g[i]*((long double)N/2));
    }
    return 0;
}
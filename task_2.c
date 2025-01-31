#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _USE_MATH_DEFINES           // необходимо для получения значения числа Пи
#define N (100+1)

int main(void) {
    int K = N-4;
    /* ПОСТРОЕНИЕ ПРАВОЙ ЧАСТИ СЛАУ */
    long double F[N-3];
    F[0] = cos(2.0*M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N) + 3;
    F[1] = cos(3.0*M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N) - 1;
    F[N-6] = cos((N-3)*M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N) - 1;
    F[N-5] = cos((N-2)*M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N) + 3;
    for (int i = 2; i <= (N-7); i++) {
        F[i] = cosl(i*M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N)*(M_PI/N);
    }

    /* РЕШЕНИЕ ИЗМЕНЕННОЙ СЛАУ */
    // использован метод прогонки для пятидиагональной матрицы
    long double a, b, c, d, e;
    a = 1;
    b = -4;
    c = 6;
    d = -4;
    e = 1;
    // прямой ход
    long double A[N];
    long double B[N];
    long double C[N];
    A[1] = -d/c;
    B[1] = -e/c;
    C[1] = F[0]/c;
    A[2] = -(b*B[1] + d)/(c + b*A[1]);
    B[2] = -e/(c + b*A[1]);
    C[2] = (F[1] - b*C[1])/(c + b*A[1]);
    long double p[N];
    for (int i = 3; i <= (K-2); i++) {
        p[i] = c + a*(A[i-2]*A[i-1] + B[i-2]) + b*A[i-1];
        A[i] = (-a*A[i-2]*B[i-1] - b*B[i-1] - d)/p[i];
        B[i] = -e/p[i];
        C[i] = (-a*(A[i-2]*C[i-1] + C[i-2]) - b*C[i-1] + F[i-1])/p[i];
    }
    // обратный ход
    A[K-1] = a*A[K-2] + b;
    B[K-1] = a*B[K-2] + c;
    C[K-1] = F[K-1] - a*C[K-2];
    long double s;
    s = a*A[K-3] + b;
    A[K] = s*A[K-2] + a*B[K-3] + c;
    B[K] = s*B[K-2] + d;
    C[K] = F[K-2] - a*C[K-3] - s*C[K-2];
    long double x[K];
    x[K-1] = (C[K]*A[K-1] - A[K]*C[K-1])/(B[K]*A[K-1] - B[K-1]*A[K]);
    x[K-2] = (C[K-1] - B[K-1]*x[K-1])/A[K-1];
    for (int i = (K-3); i >= 0; i--) {                          // вычисление оставшихся переменных
        x[i] = A[i+1]*x[i+1] + B[i+1]*x[i+2] + C[i+1];
    }
    // вывод ответа на экран (заметим, что первые 2 и последние 2 элемента не зависят от числа переменных)
    printf("x[0] = 1.000000\nx[1] = 1.000000\n");
    for (int i = 0; i < K; i++) {
        printf("x[%d] = %Lf\n", i+2, x[i]);
    }
    printf("x[%d] = 1.000000\nx[%d] = 1.000000\n", N-2, N-1);
    return 0;
}
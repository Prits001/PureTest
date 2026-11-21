#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include <omp.h>
#include <math.h>

// Вычисление числа Пи с использованием алгоритмической оптимизации и OpenMP (O(N))
DOUBLE calc_pi(ULONGLONG n)
{
    DOUBLE s = 0.0;
    DOUBLE a = omp_get_wtime(); // время начала работы подпрограммы

    // Распараллеливаем цикл с редукцией суммы
#pragma omp parallel for reduction(+:s)
    for (LONGLONG i = 0; i < (LONGLONG)n; i++)
    {
        DOUBLE sign = (i % 2 == 0) ? 1.0 : -1.0; // Вычисляем знак
        DOUBLE denom = 2.0 * (DOUBLE)i + 1.0;     // Вычисляем знаменатель
        s += sign / denom; 
    }

    DOUBLE pi = 4.0 * s;        // вынос умножения на 4 за пределы цикла
    DOUBLE b = omp_get_wtime(); // время окончания работы подпрограммы
    DOUBLE t = b - a;           // время работы подпрограммы в секундах
    printf_s("Затраченное время: %lf сек.\n", t);
    return pi;
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

    ULONGLONG n = 0;
    int threads = 0;

    printf_s("Введите количество членов ряда: ");
    if (scanf_s("%llu", &n) != 1) return 1;

    // Опциональный ввод количества потоков (если запуск интерактивный)
    // При пакетном тестировании в PureTest (через inputs.txt) используются все доступные ядра
    printf_s("Введите количество потоков: ");
    if (scanf_s("%d", &threads) == 1 && threads > 0)
    {
        omp_set_num_threads(threads);
    }

    DOUBLE pi = calc_pi(n);
    printf_s("pi = %.20lf\n", pi); // вывод результата с 20 знаками после запятой
    return 0;
}

#include <stdio.h>
#include "prova1.h"

int hotpo(unsigned int n)
{
    if (n % 2 == 0) {
        return n / 2;
    }
    return (n * 3) + 1;
}

int collatz(unsigned int n)
{
    int i = 0;
    while (n != 1) {
        n = hotpo(n);
        i++;
    }
    return i;
}

void leIntervalo(int *endmin, int *endmax)
{
    int min = 0, max = 0, invalido = 1;
    while (invalido == 1) {
        scanf("%d", &min);
        scanf("%d", &max);
        if (min > 0 && max > 0 && min < max) {
            invalido = 0;
        }
    }
    *endmin = min;
    *endmax = max;
}

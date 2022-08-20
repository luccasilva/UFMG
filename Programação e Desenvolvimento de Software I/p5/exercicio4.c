#include <stdio.h>
#include "prova1.h"

void main()
{
    int a, b;
    leIntervalo(&a, &b);
    int c, max_n, max_c = 0;
    while (a <= b) {
        c = collatz(a);
        if (c > max_c) {
            max_n = a;
            max_c = c;
        }
        a++;
    }
    printf("\nnumero com a maior sequencia de Collatz: ");
    printf("%d (%d passos)", max_n, max_c);
}

#include <stdio.h>
#include "estatistica.h"

int main () {
float x, u, b;
printf("\nCauchy=%f",cauchy(-2));
printf("\nGumbel=%f",gumbel(0,0.5,2));
printf("\nLaplace=%f",laplace(-6,-5,4));
return 0;
}

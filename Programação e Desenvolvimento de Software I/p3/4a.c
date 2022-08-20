#include <stdio.h>

float x;
float y;

void troca(float *end_valor1,float *end_valor2){
  float troca = *end_valor1;
  *end_valor1 = *end_valor2;
  *end_valor2 = troca;
}

int main() {
  x=1;
  y=2;
  troca(&x, &y);
  printf("x = %f e y = %f\n", x,y);
  return 0;
}

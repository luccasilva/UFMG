#include <stdio.h>
float x;
int y;
float parteInteira (float x, int y);

float parteInteira (float x, int y){
  y=x;
  x=y;
  return x;
 }

 int main() {
   printf("digite um num float\n");
   scanf("%f", &x);
   x = parteInteira(x,y);
   printf("%f\n", x);
   return 0;
 }

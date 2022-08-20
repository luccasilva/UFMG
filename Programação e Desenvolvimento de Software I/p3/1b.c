#include <stdio.h>
float x;
int y;
float z;
float parteInteira (float x, int y);
float parteFracionaria (float x, int y, float z);

float parteInteira (float x, int y){
  y=x;
  x=y;
  return x;
 }

 float parteFracionaria (float x, int y, float z){
   x = parteInteira(x,y);
   z = z-x;
   return z;
 }

 int main() {
   printf("digite um num float\n");
   scanf("%f", &x);
   z=x;
   z = parteFracionaria(x,y,z);
   printf("%f\n", z);
   return 0;
 }

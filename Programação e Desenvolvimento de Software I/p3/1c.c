#include <stdio.h>
int x;
int y;
float z1;
float z2;
float divints (int x, int y, float z1);

float divints (int x, int y, float z1){
  z1=x;
  z2=y;
  z1=z1/z2;
  return z1;
 }

 int main() {
   printf("digite o primeiro inteiro da divisao\n");
   scanf("%d", &x);
   printf("digite o segundo inteiro da divisao\n");
   scanf("%d", &y);
   z1 = divints(x,y,z1);
   printf("\n %d / %d = %f", x,y,z1);
   return 0;
 }

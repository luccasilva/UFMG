#include <stdio.h>

int enesimoFibonacci(int n){
  int ene = 2;
  int aux = 0;
  int fb = 0;
  int fb1 = 0;
  int fb2 = 1;
  if (n==1) {
    return 0;
  }
  if (n==2) {
    return 1;
  }
  while (ene!=n) {
    aux = fb1 + fb2;
    fb = aux;
    fb1 = fb2;
    fb2 = fb;
    ene = ene + 1;
  }
  return aux;
}

void main () {
  int n;
 printf("digite um num maior que 0\n");
 scanf("%d", &n);
 printf("O enesimoFibonacci e %d\n", enesimoFibonacci(n));

}

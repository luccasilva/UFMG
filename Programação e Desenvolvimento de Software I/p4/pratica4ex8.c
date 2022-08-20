#include <stdio.h>

double fatorial (int n){
  double fatorial=n;
  int aux = n-1;
  while(aux!=1){
    fatorial=fatorial*aux;
    aux = aux-1;
  }
  return fatorial;
}
int main () {
  int n;
  printf("Digite um numero\n");
  scanf("%d", &n);
  printf("O fatorial de %d e igual a %lf\n", n, fatorial(n));
  return 0;
}

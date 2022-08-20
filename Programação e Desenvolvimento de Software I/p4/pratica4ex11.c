#include <stdio.h>

int numeroDivisores(int n){
  int aux = n;
  int div = 1;
  while(aux!=1){
    if (n%aux==0) {
      div = div+1;
    }
    aux = aux-1;
  }
  return div;
}

void main () {
  int n;
 printf("Digite um num\n");
 scanf("%d", &n);
 printf("O num de divisores de %d eh %d\n", n, numeroDivisores(n));
}

#include <stdio.h>

int somaImpares(int n){
  int aux = n;
  int soma = 0;
  do {
    if((aux%2)!=0){
    soma = soma + aux;
    }
    aux = aux-1;
  } while (aux!=0);
  return soma;
}

void main () {
  int n;
  printf("Digite um numero\n");
  scanf("%d", &n);
  printf("A soma de todos os Impares de 0 ate %d e %d\n", n,somaImpares(n));
}

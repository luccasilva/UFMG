#include <stdio.h>

int ehPar(int n){
  if (n%2==0) {
    return 1;
  }
return 0;
}

void main () {
  int n;
  printf("Digite um num inteiro\n");
  scanf("%d", &n);
  if (ehPar(n)==1){
    printf("O num e par\n");
  }
  else{
    printf("O num e impar\n");
  }
}

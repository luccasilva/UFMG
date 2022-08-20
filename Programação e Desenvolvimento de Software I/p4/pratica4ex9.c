#include <stdio.h>

int somaNumerosDiv3ou5(int n){
  int soma=0;
  int aux=n;
  int verif=0;
  do{
  if (aux%3==0){
    verif=verif+1;
  }
  if (aux%5==0) {
    verif=verif+1;
  }
  if(verif==1){
    soma = soma + aux;
  }
  aux = aux-1;
  verif=0;
}while (aux!=0);
return soma;
}

void main () {
  int n;
   printf("Digite um num\n");
   scanf("%d", &n);
   printf("somaNumerosDiv3ou5 = %d\n",somaNumerosDiv3ou5(n));
}

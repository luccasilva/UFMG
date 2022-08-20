#include <stdio.h>

int ehDivisivelPor3ou5(int n){
  int x=0;
  if (n%3==0) {
    x = x+1;
  }
  if (n%5==0) {
    x = x+1;
  }
  if (x==1){
    return 1;
  }
return 0;
}

void main () {
  int n;
 printf("Digite um num\n");
 scanf("%d", &n);
 if (ehDivisivelPor3ou5(n)==1) {
   printf("%d eh Divisivel Por 3 ou 5\n", n);
 }
 else{
   printf("%d nao eh Divisivel Por 3 ou 5\n", n);
 }
}

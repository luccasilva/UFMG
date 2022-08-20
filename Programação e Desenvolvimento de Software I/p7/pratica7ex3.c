#include <stdio.h>

int fibo(int fib[1000],int n){
   int res;
   fib[0]=1;
   fib[1]=1;
  for (int i = 2; i < n; i++) {
  fib[i]=fib[i-1]+fib[i-2];
  }
  res = fib[n-1];
  return res;
}


void main () {
  int n;
  int fib[1000];
  printf("Qual numero da sequencia de Fib?");
  scanf("%d", &n);
  printf("%d\n", fibo(fib,n));
}

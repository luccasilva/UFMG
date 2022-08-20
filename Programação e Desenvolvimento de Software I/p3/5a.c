#include <stdio.h>

int x=1;
int expoente;

unsigned long long fast_pow_2(int expoente){
x = x << expoente;
}

int main() {
  printf("digite seu expoente\n");
  scanf("%d", &expoente);
  fast_pow_2(expoente);
  printf("2 elevado a %d = %d\n",expoente, x);
  return 0;
}

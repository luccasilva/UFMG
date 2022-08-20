#include <stdio.h>
#include <math.h>

unsigned long long x=1;
unsigned long long expoente;

unsigned long long fast_pow_2(int expoente){
x = x << expoente;
}

int main() {
  printf("maior expoente e 2 elevado a 63\n");
  expoente = 63;
  fast_pow_2(expoente);
  printf("2 elevado a %llu = %llu\n",expoente, x);
  return 0;
}

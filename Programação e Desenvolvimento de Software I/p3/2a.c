#include <stdio.h>

int i;
float f;
char c;

int main() {
  printf("O endereco do inteiro e: %p\n", &i);
  printf("O endereco do float e: %p\n", &f);
  printf("O endereco do char e: %p\n", &c);
  return 0;
}

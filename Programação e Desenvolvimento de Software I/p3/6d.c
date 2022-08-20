#include <stdio.h>

unsigned int number;

int ddd(unsigned int number){
  return number/100000000;
}

int soma1SePar(unsigned int number){
  return number | 1;
}

int parOuImpar(unsigned int number) {
  return !(number & 1);
}

int main() {

  printf("Primeiro teste para funcao ddd: 3133479697\n");
  number = 3133479697;
  printf("DDD = %u\n", ddd(number));

  printf("\n");

  printf("Segundo teste para funcao ddd: 2133479690\n");
  number = 2133479690;
  printf("DDD = %u\n", ddd(number));

  printf("\n");

  printf("Terceiro teste para funcao ddd: 1533476690\n");
  number = 1533476690;
  printf("DDD = %u\n", ddd(number));

  printf("\n");

  printf("Primeiro teste para funcao soma1SePar: 3\n");
  number = 3;
  printf("soma1SePar = %u\n", soma1SePar(number));

  printf("\n");

  printf("Segundo teste para funcao soma1SePar: 4\n");
  number = 4;
  printf("soma1SePar = %u\n", soma1SePar(number));

  printf("\n");

  printf("Terceiro teste para funcao soma1SePar: 6\n");
  number = 6;
  printf("soma1SePar = %u\n", soma1SePar(number));

  printf("\n");

  printf("Primeiro teste para funcao parOuImpar: 2\n");
  number = 2;
  printf("Par ou impar = %u\n", parOuImpar(number));

  printf("\n");

  printf("Segundo teste para funcao parOuImpar: 3\n");
  number = 3;
  printf("Par ou impar = %u\n", parOuImpar(number));

  printf("\n");

  printf("Terceiro teste para funcao parOuImpar: 5\n");
  number = 5;
  printf("Par ou impar = %u\n", parOuImpar(number));

  return 0;
}

#include <stdio.h>
int x;
int *px;

void soma1(int *px) {
  *px = *px+1;
}

int main() {
  printf("Escolha um num para ser somado em uma unidade:\n");
  scanf("%d",&x);
  soma1(&x);
  printf("Resultado:\n");
  printf("%d\n", x);
  return 0;
}

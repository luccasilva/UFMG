#include <stdio.h>
int x=0;
int *px;

void soma1(int *px) {
  *px = *px+1;
}

void main() {
  soma1(&x);
  soma1(&x);
  soma1(&x);
  printf("%d", x);
}

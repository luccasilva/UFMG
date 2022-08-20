#include <stdio.h>

int mdc(unsigned int x, unsigned int y){
  int mdc = 0;
  int div = 1;
  int menor;
  if (x<y) {
    menor = x;
  }
  if (y<x) {
    menor = y;
  }
  if (y==x) {
    mdc = x;
    return mdc;
  }
  while (div<=menor) {
    if ((x%div==0) && (y%div==0)){
      mdc = div;
    }
    div = div + 1;
  }
  return mdc;
}

void main () {
  int x,y;
 printf("digite dois num x y\n");
 scanf("%d %d", &x,&y);
 printf("o mdc de %d e %d eh igual a %d\n", x,y,mdc(x,y));
}

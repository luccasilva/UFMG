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

int mmc(unsigned int x, unsigned int y){
  int maior;
  if (x>y){
    maior = x;
  }
  if (y>x){
    maior = y;
  }
  if (x==y){
    return x;
  }
  while (((maior%x)!=0) || ((maior%y)!=0)){
    maior = maior + 1;
  }
  return maior;
}

void main () {
  int x,y;
 printf("Digite dois num x y\n");
 scanf("%d %d", &x,&y);
 while (x<=0 || y<=0) {
   printf("Digite dois num x y MAIORES QUE ZERO!!!!!!!!\n");
   scanf("%d %d", &x,&y);
 }
 printf("O MMC entre %d e %d eh: %d e o MDC eh: %d\n", x,y,mmc(x,y),mdc(x,y));
}

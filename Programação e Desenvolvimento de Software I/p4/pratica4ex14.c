#include <stdio.h>

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
 printf("O MMC entre %d e %d eh: %d\n", x,y,mmc(x,y));
}

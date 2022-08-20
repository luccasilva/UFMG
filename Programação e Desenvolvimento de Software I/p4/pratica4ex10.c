#include <stdio.h>
#include <math.h>

float calculaMedia (int x, int y, int z, int operacao) {
  if(operacao==1){
    return pow(1/3,(x*y*z));
  }
  if(operacao==2){
    return (x+2*y+3*z)/6;
  }
  if(operacao==3){
    return 3/(1/x+1/y+1/z);
  }
  if(operacao==4){
    return (x+y+z)/3;
  }
return 0;
}

void main () {
  int x,y,z;
  int operacao;
 printf("digite os num X Y e Z\n");
 scanf("%d %d %d",&x ,&y ,&z);
 printf("Digite qual calculo vc deseja, 1 2 3 ou 4\n");
 scanf("%d", operacao);
 printf("O resultado eh %f\n", calculaMedia(x,y,z,operacao));
}

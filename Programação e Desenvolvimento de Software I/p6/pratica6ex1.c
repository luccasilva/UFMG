#include <stdio.h>
#include <math.h>
float fatorial(int i){
  int cont = i;
  while (cont!=1) {
    cont = cont-1;
    i = i*cont;
  }
  return i;
}

float euler(){
  float e = 1;
  int aux = 1;
  while (1/fatorial(aux)>pow(10,-6)){
    e = e+(1/fatorial(aux));
    aux = aux+1;
  }
  return e;
}

void main () {
  float e;
  printf("euler = %f\n", euler(e));
}

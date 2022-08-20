#include <stdio.h>

float paraMetrosPorSegundo(float v){
  return v/3.6;
}

void main () {
  float v;
  printf("Digite a velocidade em Km/Hr\n");
  scanf("%f", &v);
  printf("Sua velocidade em m/s %f\n", paraMetrosPorSegundo(v));
}

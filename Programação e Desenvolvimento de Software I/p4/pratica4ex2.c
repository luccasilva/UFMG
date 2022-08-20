#include <stdio.h>

float areaCirculo(float raio){
  return 3.14*raio*raio;
}

void main () {
  float raio;
  printf("Digite o raio do circulo\n");
  scanf("%f", &raio);
  printf("\n a area do circulo de raio %f e %f m*m",raio,areaCirculo(raio));

}

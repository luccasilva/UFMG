#include <stdio.h>

float pesoIdeal(float h, char sexo){
  if (sexo=='M') {
    return (72.7*h)-58;
  }
  else if (sexo=='F') {
    return (62.1*h)-44.7;
  }
  else {
    return 0;
  }
}
void main () {
  float h;
  char sexo;
  printf("Digite sua altura em m e seu sexo (M/F)\n");
  scanf("%f %c", &h, &sexo);
  printf("%f Kg e seu peso ideal\n", pesoIdeal(h,sexo));
}

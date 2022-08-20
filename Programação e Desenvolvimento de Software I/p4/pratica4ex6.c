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
  float h,kg;
  char sexo;
  printf("Digite sua altura em m, seu peso atual e seu sexo (M/F)\n");
  scanf("%f %f %c", &h, &kg, &sexo);
  if (kg>pesoIdeal(h,sexo)) {
    printf("Voce deve perder %f Kg\n", kg-pesoIdeal(h,sexo));
  }
  else if (kg<pesoIdeal(h,sexo)){
    printf("Voce deve ganhar %f Kg\n", pesoIdeal(h,sexo)-kg);
  }
  else  {
      printf("Voce esta no peso ideal");
  }
}

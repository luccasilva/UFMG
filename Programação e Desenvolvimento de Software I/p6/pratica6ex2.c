#include <stdio.h>

void conceito(int nota){
  switch (nota) {
case 0:
printf("Conceito = F");
break;
case 1:
printf("Conceito = F");
break;
case 2:
printf("Conceito = F");
break;
case 3:
printf("Conceito = F");
break;
case 4:
printf("Conceito = F");
break;
case 5:
printf("Conceito = E");
break;
case 6:
printf("Conceito = D");
break;
case 7:
printf("Conceito = C");
break;
case 8:
printf("Conceito = B");
break;
case 9:
printf("Conceito = A");
break;
case 10:
printf("Conceito = A");
break;
  }
  return;
}

void main () {
  int nota;
  printf("Digite a nota do aluno \n");
  scanf("%d", &nota);
  conceito(nota);
}

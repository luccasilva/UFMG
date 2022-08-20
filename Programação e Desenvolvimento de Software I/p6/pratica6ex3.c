#include <stdio.h>
#include <string.h>

int tamstring(char string[128]){
  int tamanho = 0;
  for (int i = 0; i < 128; i++) {
    if (string[i]=='\0') {
      return tamanho;
    }
    tamanho=tamanho+1;
  }
}

void main () {
  char linha[128];
  printf("digite uma linha:\n");
  //strcpy(linha,"lucca"); conta o /n no fgets
  fgets(linha, 128, stdin);
  printf("Tamanho eh - %d\n", tamstring(linha));
}

#include <stdio.h>
#include <string.h>

void lowstring(char string[128]){
  for (int i = 0; i < 129; i++) {
    if (string[i]>=97&&string[i]<=122) {
      string[i]=string[i]-32;
    }
  }
  printf("string high eh - %s\n", string);
  return;
}

void main () {
  char linha[128];
  printf("digite uma linha:\n");
  fgets(linha, 128, stdin);
  lowstring(linha);
}

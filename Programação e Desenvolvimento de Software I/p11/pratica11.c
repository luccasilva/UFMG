#include <stdio.h>
#include <stdlib.h>

void main () {
FILE *arq;
arq = fopen("cartelas.txt", "r");
int vencedores = 0;
int losters = 0;

int v[6];
int vencedor[6];
int lost[6];

int n;

while(feof(arq) == 0) {
  for (int i=0; i<6; i++) {
    fscanf(arq, "%d", &n);
    v[i] = n;
  }

  int aux;
    for( int k=0; k<6; k++ ){
      for( int j=k+1; j<6; j++ ){
        if( v[k] > v[j] ){
            aux = v[k];
            v[k] = v[j];
            v[j] = aux;
        }
      }
    }

  if (v[0]==6&v[1]==9&v[2]==22&v[3]==23&v[4]==48&v[5]==52){
    vencedores ++;
  }
  if (v[0]==4&v[1]==8&v[2]==15&v[3]==16&v[4]==23&v[5]==42){
    losters ++;
  }
}
fclose(arq);
printf("Vencedores = %d\n", vencedores);
printf("Lost = %d\n", losters);
}

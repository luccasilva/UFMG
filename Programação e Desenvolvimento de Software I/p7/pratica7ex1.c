#include <stdio.h>

int prodesc(float u[100],float v[100],int n){
  int pe = 0;
  for (int i = 0; i < n; i++) {
  pe = pe+(u[i]*v[i]);
  }
  return pe;
}



void main () {
  int n = 3;
  float u[100];
  u[0]=1;
  u[1]=2;
  u[2]=3;
  float v[100];
  v[0]=1;
  v[1]=2;
  v[2]=3;
  printf("PE eh = %d\n", prodesc(u,v,n));
}

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void main () {
  int k,m,n;
  int mat[100][100];
  scanf("%d %d %d", &k,&m,&n);
  for (int ii = 0; ii < n; ii++) {
  for (int i = 0; i < m; i++) {
    mat[i][ii]=rand()%k+1;
    printf("%d\n", mat[i][ii]);
  }
}
}

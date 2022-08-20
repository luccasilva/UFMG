#include <stdio.h>
void main() {
	int x = 0;
	//coloque seu código aqui:
  int *y;
  y = &x;
  *y = 3;

	printf("%d", x);
}

#include <stdio.h>
#include <stdlib.h>

int main () {

float poupanca;

poupanca = 789.54;
poupanca = poupanca+(poupanca*0.0056);
poupanca = poupanca+303.20;
poupanca = poupanca+(poupanca*0.0056);
poupanca = poupanca-58.25;
poupanca = poupanca+(poupanca*0.0056);

printf("A conta tera: %.2f",poupanca);

return 0;
}

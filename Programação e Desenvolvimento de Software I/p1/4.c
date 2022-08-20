#include <stdio.h>
#include <stdlib.h>

int main () {

float hb=1.84, pb=122, ho=1.76, po=45;
float imcb,imco;
float ib, io;

imcb = pb/(hb*hb);
imco = po/(ho*ho);

printf("IMC de Brutos: %.1f", imcb);
printf("\n");
printf("IMC de Olivia: %.1f", imco);

ib = 25*(hb*hb);
ib = pb - ib;

io = 18.5*(ho*ho);
io = io - po;

printf("\n");
printf("\n");

printf("Brutos precisa perder: %.1f kg", ib);
printf("\n");
printf("Olivia precisa ganhar: %.1f kg", io);

return 0;
}

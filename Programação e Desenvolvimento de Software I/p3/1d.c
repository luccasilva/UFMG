 #include <stdio.h>
 float x;
 int y;
 int y1;
 int y2;
 float z;
 float z1;
 float z2;

 //float parteInteira (float x, int y);
 //float parteFracionaria (float x, int y, float z);
 //float divints (int y1, int y2, float z1);

 float parteInteira (float x, int y){
   y=x;
   x=y;
   return x;
  }

  float parteFracionaria (float x, int y, float z){
    x = parteInteira(x,y);
    z = z-x;
    return z;
  }

  float divints (int y1, int y2, float z1){
    z1=y1;
    z2=y2;
    z1=z1/z2;
    return z1;
   }


  int main() {
    printf("Primeiro teste para funcao parte inteira: 2.32\n");
    x = 2.32;
    x = parteInteira(x,y);
    printf("%f\n", x);

    printf("Segundo teste para funcao parte inteira: 223.42\n");
    x = 223.42;
    x = parteInteira(x,y);
    printf("%f\n", x);

    printf("Terceiro teste para funcao parte inteira: 10.2\n");
    x = 10.2;
    x = parteInteira(x,y);
    printf("%f\n", x);

    printf("\n");

    printf("Primeiro teste para funcao parte fracionaria: 2.32\n");
    x = 2.32;
    z=x;
    z = parteFracionaria(x,y,z);
    printf("%f\n", z);

    printf("Segundo teste para funcao parte fracionaria: 223.64\n");
    x = 223.64;
    z=x;
    z = parteFracionaria(x,y,z);
    printf("%f\n", z);

    printf("Terceiro teste para funcao parte fracionaria: 10.2\n");
    x = 10.2;
    z=x;
    z = parteFracionaria(x,y,z);
    printf("%f\n", z);

    printf("\n");

    printf("Primeiro teste para funcao divints: 1/2\n");
    y1=1;
    y2=2;
    z1 = divints(y1,y2,z1);
    printf("\n %d / %d = %f\n", y1,y2,z1);

    printf("Segundo teste para funcao divints: 12/8\n");
    y1=12;
    y2=8;
    z1 = divints(y1,y2,z1);
    printf("\n %d / %d = %f\n", y1,y2,z1);

    printf("Terceiro teste para funcao divints: 92/5\n");
    y1=92;
    y2=5;
    z1 = divints(y1,y2,z1);
    printf("\n %d / %d = %f\n", y1,y2,z1);
    return 0;
  }

#include <stdio.h>
#include <stdlib.h>

int main(){
  int cpf, backup, cpf1, cpf2, cpf3, cpf4, cpf5, cpf6, cpf7, cpf8, cpf9;
  int dv, uv;
  int dig = 1, nmr1=0;
  float nmr2;
  printf("Digite seu CPF sem o digito verificador \n");
  scanf("%d", &cpf);

backup = cpf;

if (cpf==0)
 {
 	dig=1;
 }

//Verifica quantos digitos tem o cpf
else 
while (backup!=0){		
dig = dig+1;
backup=backup/10;
}

//nao pode ser diferente de 9
 if (dig!=10)
 {
 	printf("CPF invalido \n");  
 	return 0;
 }		

//Armazena cada digito em uma variavel diferente
cpf1=cpf/100000000;                
cpf2=(cpf/10000000)-(cpf1*10);
cpf3=(cpf/1000000)-(cpf1*100)-(cpf2*10);
cpf4=(cpf/100000)-(cpf1*1000)-(cpf2*100)-(cpf3*10);
cpf5=(cpf/10000)-(cpf1*10000)-(cpf2*1000)-(cpf3*100)-(cpf4*10);
cpf6=(cpf/1000)-(cpf1*100000)-(cpf2*10000)-(cpf3*1000)-(cpf4*100)-(cpf5*10);
cpf7=(cpf/100)-(cpf1*1000000)-(cpf2*100000)-(cpf3*10000)-(cpf4*1000)-(cpf5*100)-(cpf6*10);
cpf8=(cpf/10)-(cpf1*10000000)-(cpf2*1000000)-(cpf3*100000)-(cpf4*10000)-(cpf5*1000)-(cpf6*100)-(cpf7*10);
cpf9=(cpf/1)-(cpf1*100000000)-(cpf2*10000000)-(cpf3*1000000)-(cpf4*100000)-(cpf5*10000)-(cpf6*1000)-(cpf7*100)-(cpf8*10);

//Calcula a soma dos produtos dos nove dígitos utilizando peso
nmr1=cpf9*2+cpf8*3+cpf7*4+cpf6*5+cpf5*6+cpf4*7+cpf3*8+cpf2*9+cpf1*10;

//nmr2 recebe o resto da divisao do produto por 11
nmr2=nmr1%11;

//Verificar se a dezena do nmr verificdor e 0
if (nmr2==0)
{
	dv=0;
}
else
if (nmr2==1)
{
	dv=0;
}
else

//caso contrário a dezena corresponde  a subtrair de 11 o resto da divisão por 11 da soma dos produtos. 	
dv=11-(nmr2=nmr1%11);

//Calcula a soma dos produtos dos dez dígitos, onde o dígito menos significativo passa a ser a dezena dos dígitos verificadores
nmr1=dv*2+cpf9*3+cpf8*4+cpf7*5+cpf6*6+cpf5*7+cpf4*8+cpf3*9+cpf2*10+cpf1*11;

//nmr2 recebe o resto da divisao do produto por 11
nmr2=nmr1%11;

//Verificar se a unidade do nmr verificdor e 0
if (nmr2==0)
{
	uv=0;
}
else
if (nmr2==1)
{
	uv=0;
}
else

//caso contrário a unidade corresponde  a subtrair de 11 o resto da divisão por 11 da soma dos produtos. 	
uv=11-(nmr2=nmr1%11);

printf("Seu Digito Verificador e %d%d\n", dv, uv);
printf("Seu CPF completo e %d - %d%d\n", cpf, dv, uv);

  system("PAUSE");
  return 0;
}

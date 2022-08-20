float paraMetrosPorSegundo(float v){
  return v/3.6;
}

float areaCirculo(float raio){
  return 3.14*raio*raio;
}

int ehPar(int n){
  if (n%2==0) {
    return 1;
  }
return 0;
}

int ehDivisivelPor3ou5(int n){
  int x=0;
  if (n%3==0) {
    x = x+1;
  }
  if (n%5==0) {
    x = x+1;
  }
  if (x==1){
    return 1;
  }
return 0;
}

float pesoIdeal(float h, char sexo){
  if (sexo=='M') {
    return (72.7*h)-58;
  }
  else if (sexo=='F') {
    return (62.1*h)-44.7;
  }
  else {
    return 0;
  }
}

int somaImpares(int n){
  int aux = n;
  int soma = 0;
  do {
    if((aux%2)!=0){
    soma = soma + aux;
    }
    aux = aux-1;
  } while (aux!=0);
  return soma;
}

double fatorial (int n){
  double fatorial=n;
  int aux = n-1;
  while(aux!=1){
    fatorial=fatorial*aux;
    aux = aux-1;
  }
  return fatorial;
}

int somaNumerosDiv3ou5(int n){
  int soma=0;
  int aux=n;
  int verif=0;
  do{
  if (aux%3==0){
    verif=verif+1;
  }
  if (aux%5==0) {
    verif=verif+1;
  }
  if(verif==1){
    soma = soma + aux;
  }
  aux = aux-1;
  verif=0;
}while (aux!=0);
return soma;
}

float calculaMedia (int x, int y, int z, int operacao) {
  if(operacao==1){
    return pow(1/3,(x*y*z));
  }
  if(operacao==2){
    return (x+2*y+3*z)/6;
  }
  if(operacao==3){
    return 3/(1/x+1/y+1/z);
  }
  if(operacao==4){
    return (x+y+z)/3;
  }
return 0;
}

int numeroDivisores(int n){
  int aux = n;
  int div = 1;
  while(aux!=1){
    if (n%aux==0) {
      div = div+1;
    }
    aux = aux-1;
  }
  return div;
}

int enesimoFibonacci(int n){
  int ene = 2;
  int aux = 0;
  int fb = 0;
  int fb1 = 0;
  int fb2 = 1;
  if (n==1) {
    return 0;
  }
  if (n==2) {
    return 1;
  }
  while (ene!=n) {
    aux = fb1 + fb2;
    fb = aux;
    fb1 = fb2;
    fb2 = fb;
    ene = ene + 1;
  }
  return aux;
}

int mdc(unsigned int x, unsigned int y){
  int mdc = 0;
  int div = 1;
  int menor;
  if (x<y) {
    menor = x;
  }
  if (y<x) {
    menor = y;
  }
  if (y==x) {
    mdc = x;
    return mdc;
  }
  while (div<=menor) {
    if ((x%div==0) && (y%div==0)){
      mdc = div;
    }
    div = div + 1;
  }
  return mdc;
}

int mmc(unsigned int x, unsigned int y){
  int maior;
  if (x>y){
    maior = x;
  }
  if (y>x){
    maior = y;
  }
  if (x==y){
    return x;
  }
  while (((maior%x)!=0) || ((maior%y)!=0)){
    maior = maior + 1;
  }
  return maior;
}

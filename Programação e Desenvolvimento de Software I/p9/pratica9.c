#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct guerreiro{
  int atq,def,carisma,life,id;
}guerreiro;

int roladado(){
  int r1,r2,r3;
  r1 = 1+rand()%6;
  r2 = 1+rand()%6;
  r3 = 1+rand()%6;
  return r1+r2+r3;
}

void criaGuerreiro(guerreiro *a){
  a->atq = roladado();
  a->carisma = roladado();
  a->def = roladado();
  a->life = roladado()+roladado()+roladado();
  return;
}

void bonus(guerreiro *a){
  switch (a->carisma) {
    case 18:
    a->carisma=a->carisma+3;
    break;
    case 17:
    a->carisma=a->carisma+2;
    break;
    case 16:
    a->carisma=a->carisma+2;
    break;
    case 15:
    a->carisma=a->carisma+1;
    break;
    case 14:
    a->carisma=a->carisma+1;
    break;
    case 6:
    a->carisma=a->carisma-1;
    break;
    case 7:
    a->carisma=a->carisma-1;
    break;
    case 4:
    a->carisma=a->carisma-2;
    break;
    case 5:
    a->carisma=a->carisma-2;
    break;
    case 3:
    a->carisma=a->carisma-3;
    break;
    return;
  }
}

void ataca(guerreiro *a,guerreiro *b) {
  int golpe = roladado()+a->atq+a->carisma;
  int escudo = roladado()+b->def+b->carisma;
  int dano = golpe-escudo;
  if (dano>0){
    b->life = b->life-dano;
  }
  return;
}

void main () {
  guerreiro lucca,emily;
  criaGuerreiro(&lucca);
  lucca.id = 1;
  criaGuerreiro(&emily);
  emily.id = 2;
  bonus(&lucca);
  bonus(&emily);

  while (emily.life>0||lucca.life>0) {
    if (lucca.life > 0) {
      ataca(&lucca,&emily);
    }
    if (emily.life > 0) {
      ataca(&emily,&lucca);
    }
  }
  if (emily.life<=0) {
    printf("Lucca ganhou com %d de vida", lucca.life);
  }
  if (lucca.life<=0) {
    printf("Emily ganhou com %d de vida", emily.life);
  }
  }

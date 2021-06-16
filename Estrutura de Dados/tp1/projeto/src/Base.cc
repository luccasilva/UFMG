#include "Base.h"

Base::Base() {
  this->Resources=0;
  this->Kill=0;
}

Base::~Base(){
    this->Resources=0;
    this->Kill=0;
}

void Base::setKillResources(int kill, int resources){
    this->Resources = this->Resources + resources;
    this->Kill = this->Kill + kill;
}

int Base::getBaseKill(){
    return this->Kill;
}

int Base::getBaseResources(){
    return this->Resources;
}

void Base::endExploration(){
    std::cout << "BASE: TOTAL DE ALIENS "<< this->getBaseKill() <<" RECURSOS "<< this->getBaseResources() << std::endl;
}
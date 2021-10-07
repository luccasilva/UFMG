#include "Person.h"

person::person(){
    this->number = 0;
    this->age = 0;
    this->xCord = 0;
    this->yCord = 0;
    this->HC = -1;
}

void person::setNumber(int number){
    this->number = number;
}

void person::setAge(int number){
    this->age = number;
}

void person::setXcord(int number){
    this->xCord = number;
}

void person::setYcord(int number){
    this->yCord = number;
}

void person::setHC(int number){
    this->HC = number;
}

int person::getHC(){
    return this->HC;
}

int person::getNumber(){
    return this->number;
}

int person::getAge(){
    return this->age;
}

int person::getXcord(){
    return this->xCord;
}

int person::getYcord(){
    return this->yCord;
}
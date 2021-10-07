#include "HealthCenter.h"

healthCenter::healthCenter(){
    this->number = 0;
    this->totalCapacity = 0;
    this->capacity = 0;
    this->xCord = 0;
    this->yCord = 0;
    this->priority = nullptr;
}

void healthCenter::setNumber(int number){
    this->number = number;
}

void healthCenter::setCapacity(int number){
    this->priority = new int[number];
    this->capacity = number;
}

void healthCenter::setTotalCapacity(int number){
    this->totalCapacity = number;
}

void healthCenter::setXcord(int number){
    this->xCord = number;
}

void healthCenter::setYcord(int number){
    this->yCord = number;
}

int healthCenter::getNumber(){
    return this->number;
}

int healthCenter::getCapacity(){
    return this->capacity;
}

int healthCenter::getTotalCapacity(){
    return this->totalCapacity;
}

int healthCenter::getXcord(){
    return this->xCord;
}

int healthCenter::getYcord(){
    return this->yCord;
}

void healthCenter::setAlocation(int number, int pos){
    this->priority[pos]=number;
    this->capacity--;  
}

int healthCenter::deQueuePriority(int number){
    return this->priority[number];
}

double healthCenter::getDistance(person P){
    return sqrt ( (pow((P.getXcord() - this->xCord),2) + pow((P.getYcord() - this->yCord),2)) );
}
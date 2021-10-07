#ifndef HEALTHCENTER_H
#define HEALTHCENTER_H

#include <string>
#include <iostream>
#include "Person.h"
#include <math.h> 

class healthCenter {
  
  public:
    healthCenter();
    void setNumber(int number);
    void setCapacity(int number);
    void setTotalCapacity(int number);
    void setXcord(int number);
    void setYcord(int number);
    int getNumber();
    int getCapacity();
    int getTotalCapacity();
    int getXcord();
    int getYcord();
    void setAlocation(int number, int pos);
    int deQueuePriority(int number);
    double getDistance(person P);

  private:
    int number;
    int totalCapacity;
    int capacity;
    int xCord;
    int yCord;
    int *priority;
};

#endif
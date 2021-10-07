#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class person {
  
  public:
    person();
    void setNumber(int number);
    void setAge(int number);
    void setXcord(int number);
    void setYcord(int number);
    void setHC(int number);
    int getNumber();
    int getAge();
    int getXcord();
    int getYcord();
    int getHC();
    
  private:
    int number;
    int age;
    int xCord;
    int yCord;
    int HC;
};

#endif
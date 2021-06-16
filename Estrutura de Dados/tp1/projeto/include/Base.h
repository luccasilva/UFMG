#ifndef BASE_H
#define BASE_H

#include <string>
#include <string>
#include <iostream>

class Base {
  
  public:
    Base();
    virtual ~Base();
    void setKillResources(int kill, int resources);
    int getBaseKill();
    int getBaseResources();
    void endExploration();

  private:
    int Resources;
    int Kill;
};

#endif
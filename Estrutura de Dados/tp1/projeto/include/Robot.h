#ifndef ROBOT_H
#define ROBOT_H

#include "Stack.h"
#include "Queue.h"
#include "Map.h"

#include <sstream>

class Robot {

  public:
    Robot();
    virtual ~Robot();
    void Activate(int robotNumber);
    void Execute(int robotNumber,Map map);
    void Report();
    void Return(int robotNumber);
    void moveNow(int robotNumber,Map map,int moveX,int moveY);
    void killNow(int robotNumber,Map map);
    void collectNow(int robotNumber,Map map);
    void setKill();
    int getKill();
    void setResources();
    int getResources();
    void setPriorityCommand(std::string command);
    void setCommonCommand(std::string command);
    void setHistory(std::string command);
    std::string deQueueCommand();
    std::string popPriorityCommand();
    bool isActive();

  private:
    Stack PriorityList;
    Queue CommandList;
    Queue History;
    bool Active;
    int Resources;
    int Kill;
    int pos_x;
    int pos_y;
};

#endif
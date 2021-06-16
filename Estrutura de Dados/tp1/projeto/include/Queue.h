#ifndef QUEUE_H
#define QUEUE_H

#include <string>

class Place {

    public:
      Place();

    private:
      std::string item;
      Place *next;

      friend class Queue;
};

class Queue {

  public:
    Queue();
    virtual ~Queue();
    int getSize();
    bool queueIsEmpty();
    void toQueue(std::string command);
    std::string deQueue();
    void cleanQueue();

  protected:
    int _size;

  private:
    Place* _front;
    Place* _back;
};

#endif
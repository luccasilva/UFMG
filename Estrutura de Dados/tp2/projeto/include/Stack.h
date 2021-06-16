#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>

struct Item {
    int esq;
    int dir;
};

class Node {

  public:
    Node();

  private:
    Item item;
    Node *next;

    friend class Stack;
};

class Stack {

  public:
    Stack();
    virtual ~Stack();
    int getSize();
    bool stackIsEmpty();
    void pushStack(Item item);
    Item popStack();
    void cleanStack();

  protected:
    int _size;

  private:
    Node* _top;
};

#endif
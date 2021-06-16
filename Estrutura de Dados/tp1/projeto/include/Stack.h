#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>

class Node {

  public:
    Node();

  private:
    std::string item;
    Node *next;

    friend class Stack;
};

class Stack {

  public:
    Stack();
    virtual ~Stack();
    int getSize();
    bool stackIsEmpty();
    void pushStack(std::string command);
    std::string popStack();
    void cleanStack();

  protected:
    int _size;

  private:
    Node* _top;
};

#endif
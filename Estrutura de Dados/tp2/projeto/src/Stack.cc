#include "Stack.h"

Node::Node() {
  this->next = nullptr;
}

Stack::Stack() {
  this->_top = nullptr;
  this->_size = 0;
}

Stack::~Stack() {
  cleanStack();
  delete this->_top;
}

void Stack::pushStack(Item item) {
  Node* newNode = new Node();
  newNode->item = item;
  newNode->next = _top;
  this->_top = newNode;
  this->_size++;
}

Item Stack::popStack() {
  Item aux;
  Node *p;
  aux = _top->item;
  p = _top;
  this->_top = _top->next;
  delete p;
  this->_size--;
  return aux;
}

void Stack::cleanStack(){
  while (!stackIsEmpty()){
    Stack::popStack();
  }
}

bool Stack::stackIsEmpty(){
  if(_size==0){
    return true;
  }
  return false;  
}

int Stack::getSize(){
  return this->_size;
}
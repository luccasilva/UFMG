#include "Queue.h"

Place::Place() {
  this->item = 'X';
  this->next = nullptr;
}

Queue::Queue() {
  this->_front = new Place();
  this->_back = this->_front;
  this->_size = 0;
}

Queue::~Queue() {
  cleanQueue();
  delete this->_front;
}

void Queue::toQueue(std::string command) {
  Place* newPlace = new Place();
  newPlace->item = command;
  _back->next = newPlace;
  _back = newPlace;
  this->_size++;
}

std::string Queue::deQueue() {
  if(_size == 0){
    return "EMPTY";
  }

  std::string aux;
  Place *p;
  aux = _front->next->item;
  p = _front;
  _front = _front->next;
  delete p;
  this->_size--;
  return aux;
}

void Queue::cleanQueue(){
  Place *p;
  p = _front->next;
  while (p!=nullptr){
    _front->next = p->next;
    delete p;
    p = _front->next;
  }
}

bool Queue::queueIsEmpty(){
  if(_size==0){
    return true;
  }
  return false;  
}

int Queue::getSize(){
  return this->_size;
}
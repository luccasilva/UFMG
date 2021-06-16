#include "Node.hpp"

Node::Node(int data, Node* next){
    this->_data = data;
    this->_next = next;
}

void Node::setData(int data){
    this->_data = data;
}

void Node::setNext(Node *next){
    this->_next = next;
}

    /** Retorna o dado armazenado no nó. 
       @retorna um inteiro.
     */
int Node::getData() const{
    return this->_data;
}
    /** Retorna o próximo nó.
     */
Node* Node::getNext() const{
    return this->_next;
}

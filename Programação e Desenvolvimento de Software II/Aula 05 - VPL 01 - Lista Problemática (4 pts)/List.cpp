#include "List.hpp"
#include <iostream>

using namespace std;

List::List()
{
	_size = 0;
	_head = nullptr;
}

void List::insert(int value)
{
    Node* node = new Node();
	node->_value = value;
	node->_next = _head;
	_head = node;
	_size = _size+1;
}

void List::clearList()
{
    Node *ant, *atual;
    atual = _head;
    while (atual != nullptr) {
        ant = atual;
        atual = atual->_next;
        delete ant;
    }
}

void List::print()
{
	Node* head = _head;
	if (_size > 0) {
		while (head->_next) {
			cout << head->_value << " ";
			head = head->_next;
		}
		cout << head->_value << endl;
	} else {
	    cout << "-" << endl;
	}
}

int List::removeFirst()
{
  if (_size == 0) {
        return -1;
    }
  	_size--;
    int primeiro;
	Node* atual = _head;
	_head = _head->_next;
    primeiro = atual->_value;
	delete atual;
	return primeiro;
}

int List::indexOf(int value)
{
	if (_size > 0) {
		Node* head = _head;
		int index = 0;
		while (head && head->_value != value) {
			index++;
			head = head->_next;
		}
		if (head->_value == value)
			return index; 
		return -1;
	} else {
		return -1;
	}
}

void List::remove(int value)
{
	if (_size == 0) {
		return;
	} else if (_head->_value == value) {
		_size--;
		Node* current = _head;
		_head = _head->_next;
		delete current;
        return;
	} else {
		Node* previous = _head;
		Node* current = _head->_next;
		while (current != nullptr) {
			if (current->_value == value) {
				break;
			} else {
				previous = current;
				current = current->_next;
			}
		}
		if (current == nullptr) {
			return;
		} else {
			_size--;
			previous->_next = current->_next;
			delete current;
		}
	}
}

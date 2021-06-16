#include <iostream>
#include "List.hpp"

using namespace std;

int main()
{
    int N, K;
    List* L = new List();
    cin >> N;
    cin >> K;
    for (int indice = 0; indice <= N; indice++) {
        L->insert(indice);
    }

    L->print();
    cout << L->_size;
    cout << endl;
    
    for (int indice = 0; indice < K; indice++) {
        L->removeFirst();
    }

    L->print();
    cout << L->_size;
    cout << endl;
    
    Node* node;
    node = L->_head;
    while (node != nullptr) {
        if (node->_value % 2 == 0) {
            L->remove(node->_value);
        }
        node = node->_next;
    }
    L->print();
    cout << L->_size;
    cout << endl;

    L->clearList();

    delete L;
	return 0;
}


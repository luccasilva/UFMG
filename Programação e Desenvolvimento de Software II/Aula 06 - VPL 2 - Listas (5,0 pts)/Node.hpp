#ifndef NODE
#define NODE

using namespace std;

class Node {

  private:

    int _data;
    Node * _next;

  public:

    Node(int data, Node* next);
    void setData(int data);
    void setNext(Node *next);
    /** Retorna o dado armazenado no nó. 
       @retorna um inteiro.
     */
    int getData() const;
    /** Retorna o próximo nó.
     */
    Node* getNext() const;
	
};

#endif
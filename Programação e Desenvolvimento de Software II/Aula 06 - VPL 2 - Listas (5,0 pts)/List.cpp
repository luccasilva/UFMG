#include "List.hpp"

  List::List(){
    this->head = nullptr;
    this->tamanho = 0;
  }

  List::~List(){
    Node* Last = head;
    Node* aux = head;
    for (int i = 0; i < tamanho-1; i++){
      aux = Last;
      delete Last;
      Last = aux->getNext();
    }
  }

  /** Essa função insere um elemento no começo da lista.
   */
  void List::insert(int value){
    Node* NovoNode = new Node(value, this->head);
    head = NovoNode;
    tamanho = tamanho + 1;      
  }

  /** Essa função remove o primeiro nó da lista, e retorna o dado armazenado nele.
     @retorna um inteiro armazenado no primeiro nó da lista.
    */
  int List::remove(){
    Node* FirstNode = head;
    Node* ProxNode = head->getNext();
    int headdata = head->getData();
    delete head;
    head = ProxNode;
    tamanho = tamanho - 1;
    return headdata;
  }

  /** Esse método indica se a lista está vazia.
     @retorna verdadeiro se a lista está vazia, e falso caso contrário.
    */
  int List::isEmpty(){
    if (this->tamanho==0){
      return true;
    }
    return false;
  }

  /** Informa o número de elementos da lista.
     @retorna um inteiro n, onde n é o número de nó da lista.
    */
  unsigned List::size() const{
    return this->tamanho;
  }

  /** Retorna o elemento do meio da lista.
     Se a lista possui 2*n ou 2*n + 1 elementos, então o elemento do meio é
      o que está no índice n, assumindo que o primeiro índice é 0.
      @retorna o elemento do meio da lista.
    */
  int List::middle() const{
    int meio = tamanho/2;
    Node* Node1 = head;
    for (int i = 0; i < meio; i++){
      Node1 = Node1->getNext();
    }
    return Node1->getData();
  }

  /** Retorna o último elemento da lista.
     @retorna o inteiro armazenado no último nó da lista.
    */
  int List::last() const{
    Node* Node1 = head;
    for (int i = 0; i < tamanho-1; i++){
      Node1 = Node1->getNext();
    }
    return Node1->getData();
  }
  
  /** Esse método move o primeiro nó da lista para última posição.
     Em outras palavras, rotate() + last() == head.
    */
  void List::rotate(){
    Node* Last = head;
    for (int i = 0; i < tamanho-1; i++){
      Last = Last->getNext();
    }
    Last->setNext(head);
    Last = Last->getNext();
    head = head->getNext();
    Last->setNext(nullptr);
  }
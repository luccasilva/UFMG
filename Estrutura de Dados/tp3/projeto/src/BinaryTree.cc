#include "BinaryTree.h"

Node::Node() {
  this->item.letter = '$';
  this->left = nullptr;
  this->right = nullptr;
}

binaryTree::binaryTree() {
  this->root = nullptr;
}

binaryTree::~binaryTree() {
}

void binaryTree::Insert(Item item){
  recursiveInsertion(root,item);
}

void binaryTree::recursiveInsertion(Node* &p, Item item){
  if(p==nullptr){
    p = new Node();
    p->item = item;
  }
  else{
    if(item.letter < p->item.letter)
      recursiveInsertion(p->left, item);
    else
      recursiveInsertion(p->right, item);
  }
}

void binaryTree::Remove(Item item) {
  return recursiveRemotion(root, item);
}

void binaryTree::recursiveRemotion(Node* &no, Item item) {
  Node *aux;
  if (no == nullptr) {
    throw("ERROR");
  }
  if (item.letter < no->item.letter)
    return recursiveRemotion(no->left, item);
  else if (item.letter > no->item.letter)
    return recursiveRemotion(no->right, item);
  else {
    if (no->right == nullptr) {
      aux = no;
      no = no->left;
      free(aux);
    }
    else if(no->left == nullptr) {
      aux = no;
      no = no->right;
      free(aux);
    }
    else
      Previous(no, no->left);
  }
}

void binaryTree::Previous(Node *q, Node* &r){
  if(r->right != nullptr) {
    Previous(q, r->right);
    return;
  }
  q->item = r->item;
  q = r;
  r = r->left;
  free(q);
}

bool isEven(char c){
    if (c=='0'||c=='2'||c=='4'||c=='6'||c=='8'){
      return true;
    }
    else{
      return false;
    }
}

void binaryTree::dCommand(std::string str){
    Node *aux = root;
    Item item;
    for(unsigned int i = 0; i < str.length(); i++) {

        if(str.at(i)=='x' && str.at(i+1)=='x') {
            aux = root;
            item = aux->item;
            std::cout << item.letter;
        }

        else if(str.at(i)=='x') {
            aux = root;
        }

        else {
            while(i!=str.length() && str.at(i)!='x') {

              if (isEven(str.at(i))){
                  aux = aux->right;
              }

              else{
                  aux = aux->left;
              }

              i++;
            }

            i--;
            item = aux->item;
            std::cout << item.letter;
        }
    }
    std::cout << std::endl;
}

int randEvenNumber(){
      int r;
      r = rand()%(9);
      while (r%2!=0){
          r = rand()%(9);
      }
      return r;  
}

int randOddNumber(){
      int r;
      r = rand()%(9);
      while (r%2==0){
          r = rand()%(10);
      }
      return r;  
}

void binaryTree::Search(Item item) {
    std::cout << "x";
    return recursiveSearch(root, item);
}

void binaryTree::recursiveSearch(Node *no, Item item) {
    if (no == nullptr) {
        return;
    }
    if (item.letter < no->item.letter){
        std::cout << randOddNumber();
        return recursiveSearch(no->left, item);
    }
    else if (item.letter > no->item.letter){
        std::cout << randEvenNumber();
        return recursiveSearch(no->right, item);
    }
    else{
        return;
    }
}

void binaryTree::cCommand(std::string str){
    Item item;
    for(unsigned int i = 0; i < str.length(); i++) {
        item.letter = str.at(i);
        Search(item);
    }
    std::cout << std::endl;
}
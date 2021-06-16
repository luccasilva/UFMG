#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
#include <iostream>

struct Item {
    char letter;
};

class Node {

  public:
    Node();

  private:
    Item item;
    Node *left;
    Node *right;

    friend class binaryTree;
};

class binaryTree {

  public:
    binaryTree();
    ~binaryTree();

    void Insert(Item item);
    void Remove(Item item);
    void dCommand(std::string str);
    void cCommand(std::string str);
    Node *root;

  private:
    void recursiveInsertion(Node* &p, Item item);
    void recursiveRemotion(Node* &p, Item item);
    void Previous(Node *q, Node* &r);
    void Search(Item item);
    void recursiveSearch(Node *no, Item item);
    
};

#endif
#ifndef FHEAP_H
#define FHEAP_H

#include <iostream>

#include "Vertex.cpp"

class Node;
//class Tree;

class FHeap{

 private:
  int size;
  //Tree *rootList;
  Node *rootList;
  Node *min;

  fibUnion();
  consolidate();
  cut();
  cascadingCut();
  delete();
  void link(Node *child, Node *parent);

 public:
  FHeap();
  FHeap(Vertex v);

  void insertVertex(Vertex v);
  void insertNode(Node *n);
  minimum();
  Vertex extractMin(void);
  decreaseKey();

  ~FHeap();

}; // end of class FHeap

#endif

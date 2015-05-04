#ifndef FHEAP_H
#define FHEAP_H

#include <iostream>

class Node;
class Tree;

class FHeap{

 private:
  int size;
  Tree *rootList;
  Node *min;

  fibUnion();
  consolidate();
  cut();
  cascadingCut();
  delete();
  
 public:
  FHeap();
  
  void insertVertex(Vertex v);
  void insertNode(Node n);
  minimum();
  Vertex extractMin();
  decreaseKey();

  ~FHeap();

}; // end of class FHeap

#endif

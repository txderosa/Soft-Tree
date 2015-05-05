#ifndef FHEAP_H
#define FHEAP_H

#include <iostream>
#include "Vertex.cpp"

class Node;

class FHeap{

 private:
  int size;
  Node *rootList;
  Node *min;
  
  void fibUnion(FHeap h2);//Tom
  //  consolidate();//Toren
  void cut(Node *x);//Tom
  void cascadingCut(Node *n);//Tom
  // delete();//Toren
  void link(Node *child, Node *parent);

 public:
  FHeap();
  FHeap(Vertex v);

  void insertVertex(Vertex v);//toren
  void insertNode(Node *n);//toren
  Node* minimum();//tom
  Vertex extractMin(void);
  decreaseKey();
 
}; // end of class FHeap

#endif

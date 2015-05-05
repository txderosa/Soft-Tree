#ifndef FHEAP_H
#define FHEAP_H

#include <iostream>
#include <cmath> // floor and log10
#include "Vertex.cpp"

class Node;

class FHeap{

 private:
  int size;
  Node *rootList;
  Node *min;
  
  void fibUnion(FHeap h2);//Tom
  void consolidate(void);//Toren
  void cut(Node *x);//Tom
  void cascadingCut(Node *n);//Tom
  // delete();//Toren
  void link(Node *child, Node *parent);

 public:
  FHeap();
  FHeap(Vertex v);
  ~FHeap();  

  void insertVertex(Vertex v);//toren
  void insertNode(Node *n);//toren
  Node* minimum(void);//tom
  Vertex extractMin(void);
  void decreaseKey(Vertex v, int k);
 
}; // end of class FHeap

#endif

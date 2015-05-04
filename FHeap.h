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

  void fibUnion(FHeap h2);//Tom
//  consolidate();//Toren
  void cut(Node *x);//Tom
  void cascadingCut(Node *n);//Tom
 // delete();//Toren
  
 public:
  FHeap();
  
  void insertVertex(Vertex v);//toren
  void insertNode(Node *n);//toren
  Node* minimum();//tom
 // extractMin();//torn
 // decreaseKey();//toren

  ~FHeap();

}; // end of class FHeap

#endif

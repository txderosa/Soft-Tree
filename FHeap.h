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

  void fibUnion(FHeap h2);//Tom
  consolidate();//Toren
  void cut(Node &x, Node &y);//Tom
  cascadingCut();//Tom
  delete();//Toren
  
 public:
  FHeap();
  
  void insertVertex(Vertex v);//toren
  void insertNode(Node n);//toren
  minimum();//tom
  extractMin();//torn
  decreaseKey();//toren

  ~FHeap();

}; // end of class FHeap

#endif

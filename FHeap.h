#ifndef FHEAP_H
#define FHEAP_H

#include <iostream>
#include <vector>
#include <cmath> // floor and log10 for consolidate
#include <limits> // "negative infinity" for delete
#include "Vertex.cpp"

class Node;

class FHeap{

 private:
  int size;
  Node *rootList;
  Node *min;
  int capacity;
  std::vector<Node *>handles;
  
  void fibUnion(FHeap h2);//Tom
  void consolidate(void);//Toren
  void cut(Node *x);//Tom
  void cascadingCut(Node *n);//Tom
  void deleteNode(Node *x);//Toren
  void link(Node *child, Node *parent);

 public:
  FHeap();
  FHeap(int numVertices);
  FHeap(Vertex v);
  ~FHeap();

  void insertVertex(Vertex v);//toren
  void insertNode(Node *n);//toren
  Node* minimum(void);//tom
  Vertex extractMin(void);
  void decreaseKey(int vertexID, int k);
 
  /*** for Fib in MST ***/
  bool empty(void);
  bool contains(int vertexID);
  int getKey(int vertexID);

  void showHandles(void);

}; // end of class FHeap

#endif

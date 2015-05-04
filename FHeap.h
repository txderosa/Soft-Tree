#ifndef FHEAP_H
#define FHEAP_H

#include <iostream>

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
  
 public:
  FHeap();
  
  insert();
  minimum();
  extractMin();
  decreaseKey();

  ~FHeap();

}; // end of class FHeap

#endif

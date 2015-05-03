#ifndef _SOFTHEAP_H_
#define _SOFTHEAP_H_

#include <limits>

#include "SoftHeapUtil.cpp"

class Sheap{
 private:
  static const int INFINITY;

  //Data members of Sheap
  Tree *first; // points to the tree with smallest rank
  int rank; // = the largest rank of a tree in the list

  //Tree makeTree(Vertex v);  Tree(v)
  //Node makeNode(Vertex v);  Node(v)
  //ilcell makeILCell(Vertex v);  ilcell(v)
  void sift(Node &x);
  Node combine(Node &x, Node &y);
  void meld(Sheap &q);
  void mergeInto(Sheap &q);
  void repeatedCombine(int k);
  void updateSuffixMin(Tree &t);
  void insertTree(Tree &t1, Tree &t2);
  void removeTree(Tree &t);
  bool leaf(Node &x);
  
 public:
  Sheap();
  Sheap(Vertex v);
  ~Sheap();
  
  void insert(Vertex &v);
  Vertex extractMin(void);

  /*
  // needed for MST
  empty();
  contains();
  decreaseKey();
  */
  
};

#endif

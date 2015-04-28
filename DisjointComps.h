#ifndef DISJOINTCOMPS_H
#define DISJOINTCOMPS_H

#include <iostream>

#include "Graph.h"

typedef struct comp_struct{
  int head_id;
  int tail_id;
  int size;
  std::vector<int> vertices;
} Component;

class DisjointComps{
  
 private:
  std::vector<Component> components;

 public:
  DisjointComps();
  DisjointComps(int size);
  
  void makeComp(Vertex &v);
  int findComp(Vertex v) const;
  void unionComps(Vertex u, Vertex v, Graph &g);

  ~DisjointComps();

}; // end of class DisjointComp

#endif 

#include "MST.h"

Graph Prim(Graph g){
  std::cerr << "Called Prim(Graph)" << std::endl;
  vector<int> Q;
  for(int i = 0; i < g.numVertices(); i++)
  {
    //Do stuff
    g.setParent(NULL);
    g.setKey(INFINITY);
    
  
  }
    


  return Graph();
}

Graph Kruskal(Graph g){
  std::cerr << "Called Kruskal(Graph)" << std::endl;
  return Graph();

}

Graph Soft(Graph g){
  std::cerr << "Called Soft(Graph)" << std::endl;
  return Graph();
}


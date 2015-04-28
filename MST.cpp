#include "MST.h"

bool keyComp(Vertex v1, Vertex v2)
{
  if(v1.key() > v2.key)
  {
    return true;
  }
  return false;
}

Graph Prim(Graph g){
  std::cerr << "Called Prim(Graph)" << std::endl;
  vector<Vertex> Q;
  Vertex r = g.vertex(0);
  for(int i = 1; i < g.numVertices(); i++)
  {
    //Do stuff
    g.vertex(i).setKey(INFINITY);
    Q.push_back(g.vertex(i));
  }
  r.setKey(0);
  Q.push_back(r);
  std::make_heap(Q.begin(), Q.end(), keyCompare);
  //while(Q.size() > 0)
  {
    
  
  }
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


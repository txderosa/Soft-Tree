#include <algorithm> // for Kruskal: sort()

#include "MST.h"
#include "DisjointComps.h" // for Kruskal

#define DEBUG 1 // 1 to turn debug on

Graph Prim(Graph g, Graph &mst){
  if(DEBUG) std::cerr << "Called Prim(Graph)" << std::endl;
  return Graph();
}

// comp func to sort edges by weight
bool sortEdgesByWeight(Edge a, Edge b){
  return (a.weight() < b.weight());
}

Graph Kruskal(Graph g, Graph &mst){
  if(DEBUG) std::cerr << "Called Kruskal(Graph)" << std::endl;
  
  int nVertices = g.numVertices();
  //Graph mst(nVertices);
  DisjointComps dc(nVertices);
  
  // make each vertex into a single vertex component
  for(int i = 0; i < nVertices; i++){
    dc.makeComp(g.vertex(i));
  }
  
  // sort the edes into nondecreasing order by weight
  std::vector<Edge> edges = g.edges();
  std::sort(edges.begin(), edges.end(), sortEdgesByWeight);

  // go through each edge in the sorted list
  for(std::vector<Edge>::iterator it = edges.begin(); it != edges.end(); it++){
    int u_id = it->u();
    int v_id = it->v();

    if(dc.findComp(g.vertex(u_id)) != dc.findComp(g.vertex(v_id))){
      // the two endpoints of the edge are in disjoint components
      // so add the edge to the MST and merge the two compenents
      mst.insertEdge(*it);
      dc.unionComps(g.vertex(u_id), g.vertex(v_id), g);
    }
  }

  return mst;
}

Graph Soft(Graph g, Graph &mst){
  if(DEBUG) std::cerr << "Called Soft(Graph)" << std::endl;
  return Graph();
}


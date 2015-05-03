#include <algorithm> // for Kruskal: sort()
#include <limits> //For infinity in Prim

#include "MST.h"
#include "DisjointComps.h" // for Kruskal
#include "SoftHeap.h" // for Soft

#define DEBUG 0 // 1 to turn debug on

bool keyComp(Vertex v1, Vertex v2)
{
  if(v1.key() > v2.key())
  {
    return true;
  }
  return false;
}

Graph Prim(Graph g, Graph &mst){
  if(DEBUG) std::cerr << "Called Prim(Graph, Graph&)" << std::endl;
  std::vector<Vertex> Q;
  //Vertex r = g.vertex(0);
  for(int i = 0; i < g.numVertices(); i++)
  {
    //Do stuff
    g.vertex(i).setKey(std::numeric_limits<int>::max());
    Q.push_back(g.vertex(i));
  }
  //r.setKey(0);
  //Q.push_back(r);
  //std::make_heap(Q.begin(), Q.end(), keyComp); //not needed?
  Q[0].setKey(0);
  while(Q.size() > 0)
  {
    std::make_heap(Q.begin(), Q.end(), keyComp);
    Vertex u = Q[0];
    if(DEBUG) std::cout << "Vertext u = " << Q[0].id() << std::endl;
    Q[0].setKey(-1);
    Q.erase(Q.begin());
    //std::swap_ranges(Q.begin(), Q.begin()+1, Q.end()-1);
    //Q.pop_back();
    std::vector<Neighbor> adj_u = g.adj(u.id());
    for(unsigned int i = 0; i < adj_u.size(); i ++)
    {
      if(g.vertex(std::get<0>(adj_u[i])).key() >= 0 && std::get<1>(adj_u[i]) < g.vertex(std::get<0>(adj_u[i])).key())
      {
	if(DEBUG) std::cout << " Adjacent vertex = " << std::get<0>(adj_u[i]) << std::endl;
        g.vertex(std::get<0>(adj_u[i])).setParent(u.id());
	g.vertex(std::get<0>(adj_u[i])).setKey(std::get<1>(adj_u[i]));
      }
    }
    
  }
  
  for(int i = 0; i < g.numVertices(); i++)
  {
    if(g.vertex(i).key() != -1)
    {
      mst.insertEdge(g.vertex(i).id(), g.vertex(i).parent(), g.vertex(i).key());
      //g.vertex(g.vertex(i).parent()).setKey(-1);
      g.vertex(g.vertex(i).parent()).setKey(-1);
      //g.vertex(i).setParent(-1);
    }
  }
  
  return mst;
}

// comp func to sort edges by weight
bool sortEdgesByWeight(Edge a, Edge b){
  return (a.weight() < b.weight());
}

Graph Kruskal(Graph g, Graph &mst){
  if(DEBUG) std::cerr << "Called Kruskal(Graph, Graph&)" << std::endl;
  
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

int Soft(Graph g, Graph &mst){
  if(DEBUG) std::cerr << "Called Soft(Graph, Graph&)" << std::endl;
  // copy g into mst, and work build the MST inside of mst
  mst = g;

  Sheap Q; // Q = emptyset

  // fixed initial starting vertex: first vertex in G.V
  Vertex r = mst.vertex(0);
  r.setKey(0);
  Q.insert(r);

  // insert vertices into Q
  for(int i = 1; i < mst.numVertices(); i++){
    mst.vertex(i).setKey(std::numeric_limits<int>::max());
    Q.insert(mst.vertex(i));
  }
  
  Vertex u;
  int u_id;
  while(!Q.empty()){ // !!! Q.empty() needs to be implemented
    u = Q.extractMin();
    u_id = u.id();
    if(DEBUG) std::cout << "Vertex u = " << u.id() << std::endl;
    //Q[0].setKey(-1); !!! what is this for???
    //Q.erase(Q.begin()); !!! this should be done in extractMin

    std::vector<Neighbor> adj_u = mst.adj(u_id);
    for(std::vector<Neighbor>::iterator it = adj_u.begin(); it != adj_u.end(); it++){
      int neighborID = it->first;
      int neighborKey = mst.vertex(neighborID).key();
      int weight = it->second;
      if(DEBUG) std::cout << " Adjacent vertex = " << neighborID << std::endl;      
      if( Q.contains(neighborID) && (weight < neighborKey) ){ //!!! Q.contains() needs to be implemented; could use g to track inside by using g.vertex().setKey(-1) trick?
	mst.vertex(neighborID).setParent(u_id);
	Q.decreaseKey(neighborID, weight); //!!! Q.decreaseKey needs to be implemented
      }
    }
    
  } // end of algorithm

  // return id of last vertex for tracing out the MST in mst
  return u_id;
}

void extractMST(Graph &mst, int lastID){
  if(DEBUG) std::cerr << "Called extractMST(Graph, int)" << std::endl;
  int nVertices = mst.numVertices();
  Graph tmp(nVertices);
  int v_id = lastID;
  int u_id, weight;
  // build MST from parent info in mst
  for(int i = 0; i < nVertices-1; i++){
    u_id = mst.vertex(v_id).parent();
    weight = mst.vertex(v_id).key();
    Edge e(u_id, v_id, weight);
    tmp.insertEdge(e);
    v_id = u_id;
  }
  // replace the graph with the MST
  mst = tmp;
  
}

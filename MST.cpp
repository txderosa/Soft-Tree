#include "MST.h"

#define DEBUG 0 // 1 to turn debug on

bool keyComp(Vertex v1, Vertex v2)
{
  if(v1.key() > v2.key())
  {
    return true;
  }
  return false;
}

void Prim(Graph g, Graph &mst){
  if(DEBUG) std::cerr << "Called Prim(Graph, Graph&)" << std::endl;
  // copy g into mst, and build the MST inside of mst
  mst = g;

  std::vector<Vertex> Q; // Q = emptyset
  /*
  std::vector<bool> containsVertex;
  for(int i = 0; i < mst.numVertices(); i++){
    containsVertex.push_back(true);
  }
  */

  // fixed initial starting vertex: first vertex in G.V
  mst.vertex(0).setKey(0);
  Vertex r = mst.vertex(0);
  Q.push_back(r);

  // insert vertices into Q
  for(int i = 1; i < mst.numVertices(); i++){
    mst.vertex(i).setKey(std::numeric_limits<int>::max());
    Q.push_back(mst.vertex(i));
  }

  Vertex u;
  int u_id;
  while(!Q.empty()){ 
    // make Q into a min-heap
    std::make_heap(Q.begin(), Q.end(), keyComp);
    
    // Q.extractMin();
    u = Q.front(); std::pop_heap(Q.begin(), Q.end(), keyComp); Q.pop_back(); 
    u_id = u.id();
    //containsVertex[u_id] = false;
    if(DEBUG){
      std::cout << "Vertex u = " << u.id() << std::endl;
      //if(containsVertex[u_id]) std::cerr << "is in Q" << std::endl;
    } 

    std::vector<Neighbor> adj_u = mst.adj(u_id);
    for(std::vector<Neighbor>::iterator it = adj_u.begin(); it != adj_u.end(); it++){
      int neighborID = it->first;
      //int neighborKey = mst.vertex(neighborID).key();
      //bool containsNeighbor = containsVertex[neighborID];
      int neighborKey;
      std::vector<Vertex>::iterator neighborIt = std::find(Q.begin(), Q.end(), g.vertex(neighborID));
      bool containsNeighbor = neighborIt != Q.end();
      if(containsNeighbor)
	neighborKey = neighborIt->key();
      else
	continue;
      int weight = it->second;
      if(DEBUG){
	std::cout << " Adjacent vertex = " << neighborID;
	//if(containsNeighbor) std::cerr << " is in Q" << std::endl;
	//else std::cerr << " NOT in Q";
	std::cerr << std::endl;
      }
      
      if( containsNeighbor && (weight < neighborKey) ){
	mst.vertex(neighborID).setParent(u_id);
	neighborIt->setKey(weight);
	mst.vertex(neighborID).setKey(weight);
      }
    }
    
  } // end of algorithm

  /*
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
      //if(g.vertex(std::get<0>(adj_u[i])).key() >= 0 && std::get<1>(adj_u[i]) < g.vertex(std::get<0>(adj_u[i])).key())
      bool containsNeighbor = false;
      if(std::find(Q.begin(), Q.end(), g.vertex(adj_u[i].first)) != Q.end()) containsNeighbor = true;
      if(containsNeighbor && std::get<1>(adj_u[i]) < g.vertex(std::get<0>(adj_u[i])).key())
      {
	if(DEBUG) std::cout << " Adjacent vertex = " << std::get<0>(adj_u[i]) << std::endl;
        g.vertex(std::get<0>(adj_u[i])).setParent(u.id());
	g.vertex(std::get<0>(adj_u[i])).setKey(std::get<1>(adj_u[i]));
      }
    }
  }
  
  for(int i = 0; i < g.numVertices(); i++)
  {
    if(g.vertex(i).key() != -1 && g.vertex(i).parent() != -1)
    {
      mst.insertEdge(g.vertex(i).id(), g.vertex(i).parent(), g.vertex(i).key());
      //g.vertex(g.vertex(i).parent()).setKey(-1);
      g.vertex(g.vertex(i).parent()).setKey(-1);
      //g.vertex(i).setParent(-1);
    }
  }

  mst = g;
  */
  
}

void extractPrimMST(Graph &mst){
  Graph tmp(mst.numVertices());
  for(int i = 0; i < mst.numVertices(); i++)
    {
      if(mst.vertex(i).key() != -1 && mst.vertex(i).parent() != -1)
	{
	  tmp.insertEdge(mst.vertex(i).id(), mst.vertex(i).parent(), mst.vertex(i).key());
	  mst.vertex(mst.vertex(i).parent()).setKey(-1);
	}
    }
  mst = tmp;
}

// comp func to sort edges by weight
bool sortEdgesByWeight(Edge a, Edge b){
  return (a.weight() < b.weight());
}

void Kruskal(Graph g, Graph &mst){
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

}

void Fib(Graph g, Graph &mst){
  if(DEBUG) std::cerr << "Called Fib(Graph, Graph&)" << std::endl;
  // copy g into mst, and build the MST inside of mst
  mst = g;

  FHeap Q(g.numVertices()); // Q = emptyset

  // fixed initial starting vertex: first vertex in G.V
  mst.vertex(0).setKey(0);
  Vertex r = mst.vertex(0);
  Q.insertVertex(r);

  // insert vertices into Q
  for(int i = 1; i < mst.numVertices(); i++){
    mst.vertex(i).setKey(std::numeric_limits<int>::max());
    Q.insertVertex(mst.vertex(i));
  }

  if(DEBUG) Q.showHandles();
  
  Vertex u;
  int u_id;
  while(!Q.empty()){
    u = Q.extractMin();
    u_id = u.id();
    if(DEBUG) std::cout << "Vertex u = " << u.id() << std::endl;

    std::vector<Neighbor> adj_u = mst.adj(u_id);
    for(std::vector<Neighbor>::iterator it = adj_u.begin(); it != adj_u.end(); it++){
      int neighborID = it->first;
      //int neighborKey = mst.vertex(neighborID).key();
      int neighborKey;
      if(Q.contains(neighborID))
	neighborKey = Q.getKey(neighborID);
      else
	continue;
      int weight = it->second;
      if(DEBUG) std::cout << " Adjacent vertex = " << neighborID << std::endl;      
      if( Q.contains(neighborID) && (weight < neighborKey) ){
	mst.vertex(neighborID).setParent(u_id);
	Q.decreaseKey(neighborID, weight);
	mst.vertex(neighborID).setKey(weight);
      }
    }
    
  } // end of algorithm

}

void extractMST(Graph &mst){
  if(DEBUG) std::cerr << "Called extractMST(Graph, int)" << std::endl;
  int nVertices = mst.numVertices();
  Graph tmp(nVertices);
  int u_id, weight;
  // build MST from parent info in mst
  for(int i = 0; i < nVertices; i++){
    u_id = mst.vertex(i).parent();
    if(u_id > -1){
      if(DEBUG){
	std::cerr << "v_id: " << i << std::endl;
	std::cerr << "u_id: " << u_id << std::endl;
      }
      weight = mst.vertex(i).key();
      Edge e(u_id, i, weight);
      tmp.insertEdge(e);
    }
  }
  // replace the graph with the MST
  mst = tmp;
  
}

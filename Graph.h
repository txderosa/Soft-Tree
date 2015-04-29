#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <utility>

#include "Edge.cpp"
#include "Vertex.cpp"
/*
typedef struct vertice_struct{
  string name;
  std::vector<Edge> edgeList;
  std::vector<Node> adjList;
  int key;
  Node parent;
} Node;
*/
typedef std::pair<int,int> Neighbor;

class Graph{

 private:
  int nVertices;
  int nEdges;
  std::vector< std::vector<Neighbor> > adjList;
  std::vector<Vertex> vertexList;
  std::vector<Edge> edgeList;

 public:
  Graph();
  Graph(int v);
  
  Graph& operator=(const Graph &g);

  int insertEdge(Edge e);
  int insertEdge(const int v1, const int v2, const int w);
  
  int numVertices(void) const;
  int numEdges(void) const;

  // access the vertices in the graph
  Vertex& vertex(int vertexID);

  // get a copy of the adjacency list of the vertex with id=v
  // the adjacency list stores information about the neighbor'ID 
  // and weight of the edge from v to that neighbor
  std::vector<Neighbor> adj(const int v); 

  std::vector<Edge> edges(void);

  void printEdges(std::ostream &out);

  ~Graph();

  /*** for debugging ***/
  void showAdj(bool verbose) const;
  void showEdges(void) const;

}; // end of class Graph

#endif

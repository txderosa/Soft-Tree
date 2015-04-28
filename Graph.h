#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <utility>

typedef struct edge_struct{
  int u;
  int v;
  int weight;
} Edge;

typedef struct vertice_struct{
  string name;
  std::vector<Edge> edgeList;
  std::vector<Node> adjList;
  int key;
  Node parent;
} Node;

typedef std::pair<int,int> Neighbor;

class Graph{

 private:
  int nVertices;
  int nEdges;
  std::vector< std::vector<Neighbor> > adjList;
  std::vector<Edge> edgeList;

 public:
  Graph();
  Graph(int v);

  int addEdge(const Edge e);
  
  int numVertices(void) const;
  int numEdges(void) const;
  std::vector<Neighbor> adj(const int v);

  void showAdj(bool verbose) const;
  void showEdges(void) const;

}; // end of class Graph

#endif

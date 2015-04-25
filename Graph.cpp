#include "Graph.h"

#define DEBUG 1 // 1 to turn debug on

Graph::Graph(){
  if(DEBUG) std::cerr << "Called Graph::Graph() [default constructor]"<< std::endl;
  nVertices = 1;
  nEdges = 0;
  std::vector< std::vector<Neighbor> > list (nVertices, std::vector<Neighbor>());
  adjList = list;
}

Graph::Graph(int v){
  if(DEBUG) std::cerr << "Called Graph::Graph(int) [value constructor]"<< std::endl;
  nVertices = v;
  nEdges = 0;
  std::vector< std::vector<Neighbor> > list (nVertices, std::vector<Neighbor>());
  adjList = list;
}

int Graph::addEdge(const Edge e){
  if(DEBUG) std::cerr << "Called Graph::addEdge(Edge)" << std::endl;
  int v1 = e.u;
  int v2 = e.v;
  int w = e.weight;

  // check for valid vertices
  if(v1 >= nVertices){
    std::cerr << "Graph: vertex not in graph: " << v1 << std::endl;
    exit(EXIT_FAILURE);
  }
  if(v2 >= nVertices){
    std::cerr << "Graph: vertex not in graph: " << v2 << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // add v2 into adjacency list of v1
  adjList[v1].push_back(std::make_pair(v2, w));
  // add v1 into adjacency list of v2
  adjList[v2].push_back(std::make_pair(v1, w));
  // add Edge to edgeList
  edgeList.push_back(e);
  nEdges++;

  /*
  for(std::vector< std::pair<int,int> >::iterator it = adjList[v1].begin(); it != adjList[v1].end(); it++){
    if(it->second == v2){

    }
  }
  */

  return w;
}

int Graph::numVertices(void) const{
  return nVertices;
}

int Graph::numEdges(void) const{
  return nEdges;
}

std::vector<Neighbor> Graph::adj(int v){
  if(DEBUG) std::cerr << "Called Graph::adj(int)" << std::endl;
  if(v >= nVertices){
    std::cerr << "Graph: vertex not in graph: " << v << std::endl;
    exit(EXIT_FAILURE);
  }
  return adjList[v];
}

void Graph::showAdj(bool verbose) const{
  if(DEBUG){
    std::cerr << "Called Graph::showAdj(bool)" << std::endl;
    std::cerr << "Adjacency List:" << std::endl;
    for(int i = 0; (unsigned)i < adjList.size(); i++){
      std::cerr << i << ": ";
      for(std::vector<Neighbor>::const_iterator it = adjList[i].begin(); it != adjList[i].end(); it++){
	//std::cerr << i << " " << it->first << " " << it->second << std::endl;
	//std::cerr << it->first << "(" << it->second << ") ";
	if(verbose) std::cerr << it->first << "_" << it->second << " ";
	else std::cerr << it->first << " ";
      }
      std::cerr << std::endl;
    }  
  }
  
}

void Graph::showEdges(void) const{
  if(DEBUG){
    std::cerr << "Called Graph::showEdges(void)" << std::endl;
    std::cerr << "Edge List:" << std::endl;
    for(std::vector<Edge>::const_iterator it = edgeList.begin(); it != edgeList.end(); it++){
      std::cerr << it->u << " " << it->v << " " << it->weight << std::endl;
    }
  }
  
}

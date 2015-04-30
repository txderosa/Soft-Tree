#include "Graph.h"

#define DEBUG 0 // 1 to turn debug on

Graph::Graph(){
  if(DEBUG) std::cerr << "Called Graph::Graph() [default constructor]"<< std::endl;
  nVertices = 1;
  nEdges = 0;
  std::vector< std::vector<Neighbor> > list (nVertices, std::vector<Neighbor>());
  adjList = list;
  for(int i = 0; i < nVertices; i++)
    vertexList.push_back(Vertex(i));
}

Graph::Graph(int v){
  if(DEBUG) std::cerr << "Called Graph::Graph(int) [value constructor]"<< std::endl;
  nVertices = v;
  nEdges = 0;
  std::vector< std::vector<Neighbor> > list (nVertices, std::vector<Neighbor>());
  adjList = list;
  for(int i = 0; i < nVertices; i++)
    vertexList.push_back(Vertex(i));  
}

Graph& Graph::operator=(const Graph &g){
  if(DEBUG) std::cerr << "Called Graph::operator=(const Graph&) [assignment operator]" << std::endl;
  // check for self-assignment, only copy if different objects
  if(this != &g){
    nVertices = g.nVertices;
    nEdges = g.nEdges;
    adjList = g.adjList;
    vertexList = g.vertexList;
    edgeList = g.edgeList;
  }

  return (*this);
}

int Graph::insertEdge(Edge e){
  if(DEBUG) std::cerr << "Called Graph::insertEdge(Edge)" << std::endl;
  int v1 = e.u();
  int v2 = e.v();
  int w = e.weight();
  
  // check for valid vertices
  if( (v1 >= nVertices) || (v1 < 0) ){
    std::cerr << "Graph: vertex not in graph: " << v1 << std::endl;
    exit(EXIT_FAILURE);
  }
  if( (v2 >= nVertices) | (v2 < 0) ){
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

  return w;
}

int Graph::insertEdge(const int v1, const int v2, const int w){
  if(DEBUG) std::cerr << "Called Graph::insertEdge(const int, const int, const int)" << std::endl;
  // check for valid vertices
  if( (v1 >= nVertices) || (v1 < 0) ){
    std::cerr << "Graph: vertex not in graph: " << v1 << std::endl;
    exit(EXIT_FAILURE);
  }
  if( (v2 >= nVertices) || (v2 < 0) ){
    std::cerr << "Graph: vertex not in graph: " << v2 << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // add v2 into adjacency list of v1
  adjList[v1].push_back(std::make_pair(v2, w));
  // add v1 into adjacency list of v2
  adjList[v2].push_back(std::make_pair(v1, w));
  // add Edge to edgeList
  edgeList.push_back(Edge(v1,v2,w));
  nEdges++;

  return w;
}

int Graph::numVertices(void) const{
  return nVertices;
}

int Graph::numEdges(void) const{
  return nEdges;
}

Vertex& Graph::vertex(int vertexID){
  return vertexList[vertexID];
}

std::vector<Neighbor> Graph::adj(int v){
  if(DEBUG) std::cerr << "Called Graph::adj(int)" << std::endl;
  if(v >= nVertices){
    std::cerr << "Graph: vertex not in graph: " << v << std::endl;
    exit(EXIT_FAILURE);
  }
  return adjList[v];
}

std::vector<Edge> Graph::edges(void){
  if(DEBUG) std::cerr << "Called Graph::edges()" << std::endl;
  return edgeList;
}

void Graph::printEdges(std::ostream &out){
  out << "Called Graph::showEdges(void)" << std::endl;
  out << "Edge List:" << std::endl;
  for(std::vector<Edge>::const_iterator it = edgeList.begin(); it != edgeList.end(); it++){
    out << it->u() << " " << it->v() << " " << it->weight() << std::endl;
  }
  
}

Graph::~Graph(){
  if(DEBUG) std::cerr << "Called Graph::~Graph() [destructor]" << std::endl;
  
}

/*** for debugging ***/
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
      std::cerr << it->u() << " " << it->v() << " " << it->weight() << std::endl;
    }
  }
  
}

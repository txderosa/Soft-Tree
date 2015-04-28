#include <iostream>
#include <fstream>

#include "Graph.h"
#include "MST.h"
//#include "Timer.h"

#define DEBUG 1 // 1 to turn debug on

void usage(char *progName){
  std::cerr << "usage: " << progName << " <input-file> <output-file>" << std::endl;
}

int main(int argc, char **argv){
  if(argc != 3){
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  
  std::ifstream fin;
  fin.open(argv[1]);
  if(!fin.good()){
    std::cerr << argv[0] << ": ";
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }
  
  std::ofstream fout;
  fout.open(argv[2]);
  if(!fout.good()){
    std::cerr << argv[0] << ": ";
    perror(argv[2]);
    exit(EXIT_FAILURE);
  }
 
  /*** parse file and create graph ***/
  int nGraphs, nVertices, nEdges;//, v1, v2 , weight;
  fin >> nGraphs;
  fout << "There are " << nGraphs << " graphs in " << argv[1] << std::endl;
  for(int i = 0; i < nGraphs; i++){
    // build graph
    fin >> nVertices;
    fin >> nEdges;
    Graph graph(nVertices);
    for(int e = 0; e < nEdges; e++){
      Edge edge;
      fin >> edge;
      if(DEBUG) std::cerr << "received edge: " << edge << std::endl;
      graph.insertEdge(edge);  
    }
    
    if(DEBUG){
      std::cerr << graph.numVertices() << " vertices, " << graph.numEdges() << " edges" << std::endl;
      graph.showEdges();
      graph.showAdj(false);
    }

    /*
    // run algorithms and time
    Timer kruskal_timer();
    kruskal_timer.start();
    Kruskal(graph);
    kruskal_timer.end();

    Timer prim_timer();
    prim_timer.start();
    Prim(graph);
    prim_timer.end();

    Timer soft_timer();
    soft_timer.start();
    Soft(graph);
    soft_timer.end();
    */

    // report timings
    fout << "Graph " << i+1 << ": " << nVertices << " vertices, " << nEdges << " edges" << std::endl;
    fout << "Kruskal: " << 0.0 << std::endl;
    // print out MST for debugging
    fout << "Prim: " << 0.0 << std::endl;
    // print out MST for debugging
    fout << "Soft Heap: " << 0.0 << std::endl;
    // print out MST for debugging
    
  }
  
  return 0;
}

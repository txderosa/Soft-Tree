#include <iostream>
#include <fstream>
#include <sstream>

#include <utility>
#include <map>

#include <random>
#include <chrono>

#define MAX_WEIGHT 100
#define NUM_GRAPHS 10

#define DEBUG 1 // 1 to turn debug on

void usage(char *progName){
  std::cerr << "Usage: " << progName << " <num-vertices> <output-file>" << std::endl;
}

bool cmpEdge(std::pair<int,int> left ,std::pair<int,int> right){
  if(left.first == right.first){
    return left.second < right.second;
  }
  return left.first < right.first;
}

int main(int argc, char **argv){
  if(argc != 3){
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  
  /*** parse command line ***/
  int nVertices;
  std::stringstream buf;
  buf << argv[1];
  buf >> nVertices;

  std::ofstream fout;
  fout.open(argv[2]);
  if(!fout.good()){
    std::cerr << argv[0] << ": ";
    perror(argv[2]);
    exit(EXIT_FAILURE);
  }

  if(DEBUG){
    std::cerr << "nVertices: " << nVertices << " output-file: " << argv[2] << std::endl;
  }

  /*** seed RNG ***/
  std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
  std::minstd_rand rng(time.time_since_epoch().count());

  /*** generate graphs ***/
  long long max_nEdges = (nVertices*(nVertices-1))/2;
  int min_nEdges = nVertices-1;
  //int nReserved = nVertices-1;
  long long trgt_nEdges;
  
  fout << NUM_GRAPHS << std::endl;
  // generate NUM_GRAPHS with density 10% to 100%
  for(int g = 1; g < NUM_GRAPHS+1; g++){
    if(DEBUG) std::cerr << "Generating Graph " << g << std::endl;
    long long nEdges = 0;
    trgt_nEdges = (g*max_nEdges)/10;
    if(trgt_nEdges < min_nEdges) trgt_nEdges = min_nEdges;
    fout << nVertices << " " << trgt_nEdges << std::endl;
    std::map<std::pair<int,int>,int,bool(*)(std::pair<int,int>,std::pair<int,int>)> unique_edges(cmpEdge);

    // if complete graph, just add all edges
    if(trgt_nEdges == max_nEdges){
      if(DEBUG) std::cerr << "Generating complete graph" << std::endl;
      for(int i = 0; i < nVertices-1; i++){
	for(int j = i+1; j < nVertices; j++){
	  int weight = (1 + (rng() % MAX_WEIGHT));
	  fout << i << " " << j << " " << weight << std::endl;
	}
      }
      continue;
    }

    // generate min_nEdges to make a connected graph
    for(int x = 0; x < min_nEdges; x++){
      int randNeighbor = (x+1) + (rng()%(nVertices-x-1));
      std::pair<int,int> edge (x,randNeighbor);
      unique_edges.insert(std::pair<std::pair<int,int>,int>(edge, nEdges));
      nEdges++;
    }

    // fill graph with edges until we reach trgt_nEdges
    while(nEdges < trgt_nEdges){
      int u = rng() % (nVertices-1);
      int v = (u+1) + (rng()%(nVertices-u-1));
      std::pair<int,int> edge (u,v);
      std::pair<std::map<std::pair<int,int>,int>::iterator,bool> rv;
      rv = unique_edges.insert(std::pair<std::pair<int,int>,int>(edge, nEdges));
      if(rv.second == true) nEdges++;
    }

    // print out edges
    for(std::map<std::pair<int,int>,int>::iterator it = unique_edges.begin(); it != unique_edges.end(); it++){
      int weight = (1 + (rng() % MAX_WEIGHT));
      fout << (it->first).first << " " << (it->first).second << " " << weight << std::endl;
    }
    
  } // end of generating NUM_GRAPHS with density 10% to 100%

  return 0;
}

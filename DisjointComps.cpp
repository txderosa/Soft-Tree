#include <iostream>

#include "DisjointComps.h"
#include "Graph.h"

#define DEBUG 0 // 1 to turn debug on

DisjointComps::DisjointComps(){
  if(DEBUG) std::cerr << "Called DisjointComps::DisjointComps() [default constructor]" << std::endl;
}

DisjointComps::DisjointComps(int size){
  if(DEBUG) std::cerr << "Called DisjointComps::DisjointComps(int) [value constructor]" << std::endl;
  Component init;
  init.head_id = -1;
  init.tail_id = -1;
  init.size = 0;

  std::vector<Component> c (size, init);
  components = c;
}

void DisjointComps::makeComp(Vertex &v){
  if(DEBUG) std::cerr << "Called DisjointComps::makeComp(Vertex)" << std::endl;
  int vid = v.id();
  // create component
  components[vid].head_id = vid;
  components[vid].tail_id = vid;
  components[vid].size = 1;
  components[vid].vertices.push_back(vid);
  
  /*
  Component c;
  c.head_id = vid;
  c.tail_id = vid;
  c.size = 1;
  c.vertices.push_back(vid);
  
  // add component to collection
  components[vid] = c;
  */

  // update v
  v.setCompID(vid);
}

int DisjointComps::findComp(Vertex v) const{
  if(DEBUG) std::cerr << "Called DisjointComps::findComp(Vertex) const" << std::endl;
  return components[v.compID()].head_id;
}

void DisjointComps::unionComps(Vertex u, Vertex v, Graph &g){
  if(DEBUG) std::cerr << "Called DisjointComps::unionComp(Vertex, Vertex, Graph)" << std::endl;
  int u_comp_size = components[u.compID()].size;
  int v_comp_size = components[v.compID()].size;
  int u_cID = u.compID();
  int v_cID = v.compID();

  // merge the smaller component into the bigger component
  if(u_comp_size <= v_comp_size){
    // component with u is smaller, merge u's comp into v's comp
    components[v_cID].tail_id = components[u_cID].tail_id;
    components[v_cID].size += u_comp_size;
    // update the component IDs of vertices in u's component
    // and add the vertices in u's comp into v's comp
    for(std::vector<int>::iterator it = components[u_cID].vertices.begin(); it != components[u_cID].vertices.end(); it++){
      g.vertex(*it).setCompID(v_cID);
      components[v_cID].vertices.push_back(*it);
    }
  }
  else{
    // component with v is smaller, merge v's comp into u's comp
    components[u_cID].tail_id = components[v_cID].tail_id;
    components[u_cID].size += v_comp_size;
    // update the component IDs of vertices in v's component
    // and add the vertices in v's comp into u's comp
    for(std::vector<int>::iterator it = components[v_cID].vertices.begin(); it != components[v_cID].vertices.end(); it++){
      g.vertex(*it).setCompID(u_cID);
      components[u_cID].vertices.push_back(*it);
    }
  }
  
}

DisjointComps::~DisjointComps(){
  if(DEBUG) std::cerr << "Called DisjointComps::~DisjointComps() [destructor]" << std::endl;
  
}

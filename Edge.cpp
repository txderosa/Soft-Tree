#ifndef EDGE_CPP
#define EDGE_CPP

#include <iostream>

class Edge{

private:
 
  int e_u;
  int e_v;
  int e_weight;
  
public:

  Edge(){
    e_u = 0;
    e_v = 0;
    e_weight = 0;
  }

  Edge(int v1, int v2, int w){
    e_u = v1;
    e_v = v2;
    e_weight = w;
  }

  int u(void) const{
    return e_u;
  }

  int v(void) const{
    return e_v;
  }

  int weight(void) const{
    return e_weight;
  }

  friend std::istream& operator>>(std::istream& in, Edge &e){
    in >> e.e_u >> e.e_v >> e.e_weight;
    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const Edge &e){
    out << e.u() << " " << e.v() << " " << e.weight();
    return out;
  }

}; // end of class Edge 

#endif

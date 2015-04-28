#ifndef VERTEX_CPP
#define VERTEX_CPP

#include <iostream>

class Vertex{

private:

  int v_id;
  int v_parent;
  int v_key;
  int v_comp_id;

public:

  Vertex(){
    v_id = 0;
    v_parent = -1;
    v_key = -1;
    v_comp_id = -1;
  }

  Vertex(int id){
    v_id = id;
    v_parent = -1;
    v_key = -1;
    v_comp_id = -1;
  }


  int id(void) const{ return v_id; }

  int parent(void) const{ return v_parent; }
  void setParent(int parentID){ v_parent = parentID; }

  int key(void) const{ return v_key; }
  void setKey(int newKey){ v_key = newKey; }

  int compID(void) const{ return v_comp_id; }
  void setCompID(int newCompID){ v_comp_id = newCompID; }

}; // end of class Vertex

#endif

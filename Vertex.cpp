#ifndef VERTEX_CPP
#define VERTEX_CPP

#define V_DEBUG 0 // 1 to turn debug on

#include <iostream>

class Vertex{

private:

  int v_id;
  int v_parent;
  int v_key;
  //int v_ckey; !!! wrong scope! belongs to Node
  int v_comp_id;

public:

  Vertex(){
    v_id = 0;
    v_parent = -1;
    v_key = -1;
    //v_ckey = -1; !!! wrong scope! belongs in Node
    v_comp_id = -1;
  }

  Vertex(int id){
    v_id = id;
    v_parent = -1;
    v_key = -1;
    //v_ckey = -1; !!! wrong scope! belongs to Node
    v_comp_id = -1;
  }


  Vertex& operator=(const Vertex &v){
    if(V_DEBUG) std::cerr << "Called Vertex:operator=(const Vertex&) [assignment operator]" << std::endl;
    // check for self-assignment, only copy if different objects
    if(this != &v){
      v_id = v.id();
      v_parent = v.parent();
      v_key = v.key();
      v_comp_id = v.compID();
    }
    return *this;
  }

  int id(void) const{ return v_id; }

  int parent(void) const{ return v_parent; }
  void setParent(int parentID){ v_parent = parentID; }

  int key(void) const{ return v_key; }
  void setKey(int newKey){ v_key = newKey; }

  /* !!! wrong scope! belongs in Node
  int ckey(void) const{ return v_ckey; }
  void setCKey(int newCKey){ v_ckey = newCKey; }
  */

  int compID(void) const{ return v_comp_id; }
  void setCompID(int newCompID){ v_comp_id = newCompID; }

}; // end of class Vertex

#endif

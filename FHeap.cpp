#include "FHeap.h"
#include "Vertex.cpp"

#define DEBUG 1 // 1 to turn debug on for FHeap
#define N_DEBUG 1 // 1 to turn debug on for Node
#define T_DEBUG 1 // 1 to turn debug on for Tree

class Node {
  // each node contains a pointer to its parent and to any one of its children
  // children are linked together in a circular, doubly linked list
private:
  
  Node *n_parent;
  Node *n_childList; // points to any one child in the child list
  Node *n_left;
  Node *n_right;
  Vertex n_data, n_vertex;
  int n_key;
  int n_degree, n_numChildren; // number of children in child list
  bool n_marked; // indicates whether node has lost a child since the last time node was made the child of another node (nodes start as unmarked, and are unmarked when it is made the child of another node)

public:
  Node(){ 
    if(N_DEBUG) std::cerr << "Called Node::Node() [default constructor]" << std::endl;
    n_parent = NULL;
    n_childList = NULL;
    n_left = this;
    n_right = this;
    n_key = n_vertex.key();
    n_degree = n_numChildren = 0;
    n_marked = false;
  }
  
  Node(Vertex v){
    if(N_DEBUG) std::cerr << "Called Node::Node(Vertex) [value constructor]" << std::endl;
    n_parent = NULL;
    n_childList = NULL;
    n_left = this;
    n_right = this;
    n_degree = n_numChildren = 0;
    n_marked = false;
    n_data = n_vertex = v;
    n_key = n_vertex.key();
  }

  Node& operator=(const Node &n){
    if(N_DEBUG) std::cerr << "Called Node::operator=(const Node&) [assignment operator]" << std::endl;
    // check for self-assignment, only copy if different objects
    if(this != &n){
      n_parent = n.n_parent;
      n_left = n.n_left;
      n_right = n.n_right;
      setChildList(n.n_childList);
            
      n_degree = n_numChildren = n.n_degree;
      n_marked = n.n_marked;
      n_data = n_vertex = n.n_vertex;      
      n_key = n.n_key;
    }
    
    return *this;
  }

  int degree(void) const{ return n_degree; }
  int numChildren(void) const{ return n_numChildren; }
  int key(void) const{ return n_key; }
  
  bool marked(void) const{ return n_marked; }
  void setMarked(bool m) { n_marked = m; }

  Vertex& data(void){ return n_data; }
  Vertex& vertex(void){ return n_vertex; }
  void setData(Vertex v){ 
    n_data = n_vertex = v; 
    n_key = v.key();
  }
  void setVertex(Vertex v){ 
    n_vertex = n_data = v; 
    n_key = v.key();
  }

  Node *left(void){ return n_left; }
  Node *setLeft(Node *l){ 
    Node *tmp = n_left;
    n_left = l; 
    return tmp;
  }

  Node *right(void){ return n_right; }
  Node *setRight(Node *r){ 
    Node *tmp = n_right;
    n_right = r; 
    return tmp;
  }
  
  Node *parent(void){ return n_parent; }
  Node *setParent(Node *p){ 
    Node *tmp = n_parent;
    n_parent = p;
    return tmp;
  }
  
  Node *childList(void){ return n_childList; }
  void setChildList(Node *cl){ 
    // release current children
    Node *cur = n_childList;
    while(cur->n_right != cur){
      Node *tmp = cur->n_right;
      delete cur;
      cur = tmp;
    }
    delete cur;
    // acquire new children
    n_childList = cl;
  }
  
  ~Node(){
    if(N_DEBUG) std::cerr << "Called Node::~Node() [destructor]" << std::endl;
    // clean up resources
    if(n_parent != NULL) n_parent = NULL;
    if(n_childList != NULL) delete n_childList; // !!!

    if( (n_left == this) && (n_right == this) ){
      // only child
      n_left = NULL;
      n_right = NULL;
    }
    else{
      // has siblings, adjust their pointers
      if(n_left == n_right){
	// has 1 sibling, set sibling to point to itself
	Node *sibling = n_left;
	sibling->n_right = sibling;
	sibling->n_left = sibling;
      }
      else{
	// has more than 1 sibling, set left to point to right
	n_left->n_right = n_right;
	n_right->n_left = n_left;
      }
      n_left = NULL;
      n_right = NULL;
    }
    
  }
  
}; // end of class Node

/*
class Tree {
  // a tree in a soft heap has min-heap property with respect to a node's ckey value (ie, if x is a node and x.left exists, then x.ckey <= x.left.ckey; if x.right exists, then x.ckey <= x.right.ckey)
private:
  int t_rank;
  Node *t_root;
  Tree *t_next;
  Tree *t_prev;
  Tree *t_sufmin;
  
public:
  Tree(){
    if(T_DEBUG) std::cerr << "Called Tree::Tree() [default constructor]" << std::endl;
    t_rank = 0;
    t_root = NULL;
    t_next = NULL;
    t_prev = NULL;
    t_sufmin = NULL;
  }

  Tree(Vertex v){
    if(T_DEBUG) std::cerr << "Called Tree::Tree(Vertex) [value constructor]" << std::endl;
    t_rank = 0;
    t_root = new Node(v);
    t_next = NULL;
    t_prev = NULL;
    t_sufmin = this;
  }

  Tree& operator=(const Tree &t){
    if(T_DEBUG) std::cerr << "Called Tree::operator=(const Tree&) [assignment operator]" << std::endl;
    // check for self-assignment, only copy if different objects
    if(this != &t){
      t_rank = t.t_rank;
      setNext(t.t_next);
      setPrev(t.t_prev);
      setSufmin(t.t_sufmin);
    }
    return *this;
  }

  int rank(void) const{ return t_rank; }

  Node *root(void){ return t_root; }
  void setRoot(Node *r){
    // release our resources
    if(t_root != NULL) delete t_root;
    // acquire new resources
    t_root = r;
  }
  
  Tree *next(void){ return t_next; }
  void setNext(Tree *n){
    // release our resources
    if(t_next != NULL) delete t_next;
    // acquire new resources
    t_next = n;    
  }

  Tree *prev(void){ return t_prev; }
  void setPrev(Tree *p){
    // release our resources
    if(t_prev != NULL) delete t_prev;
    // acquire new resources
    t_prev = p;
  }

  Tree *sufmin(void){ return t_sufmin; }
  void setSufmin(Tree *s){
    // release our resources
    if(t_sufmin != NULL) delete t_sufmin;
    // acquire new resources
    t_sufmin = s;
  }

  ~Tree(){
    if(T_DEBUG) std::cerr << "Called Tree::~Tree() [destructor]" << std::endl;
    // clean up resources
    if(t_root != NULL) delete t_root; // delete all nodes in tree
    if(t_next != NULL) t_next = NULL;
    if(t_prev != NULL) t_prev = NULL;
    if(t_sufmin != NULL) t_sufmin = NULL;
  }
}; // end of class Tree
*/

/***** START OF FHEAP *****/
  void insertVertex(Vertex v)
  { 
    Node n(v);
    n.degree = 0;
    n.parent = NULL; 
    n.child = NULL;
    n.mark = false;
    if(getMin() == NULL)
    {
	    rootList = new Tree(n);
	    setMin(n);
     }
    else
    {
      rootList->insert(n);
      if(n.key < getMin())
      {
	setMin(n);
      }
    }
    size = size + 1;
  }

  void insertNode(Node n)
  { 
    n.degree = 0;
    n.parent = NULL; 
    n.child = NULL;
    n.mark = false;
    if(getMin() == NULL)
    {
	    rootList = new Tree(n);
	    setMin(n);
     }
    else
    {
      rootList->insert(n);
      if(n.key < getMin())
      {
	setMin(n);
      }
    }
    size = size + 1;
  }

  Node extractMin()
  {
    Node z = getMin();
    if(z != NULL)
    {
      for(int i = 0; i < z.getChildren(); i ++)
      {
        rootList->insert(z.getChild(i));
	x.p = NULL;
      }
      rootList.remove(z);
      if(z.right == z)
      {
	setMin(NULL);
      }
      else
      {
	setMin(z.right);
	consolidate();
      }
      size = size - 1;
      return z;
    }
  }
	

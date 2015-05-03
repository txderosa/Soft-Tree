#ifndef _SOFTHEAPUTIL_CPP_
#define _SOFTHEAPUTIL_CPP_

#include <cmath> // for ceil()

#define ILC_DEBUG 1 // 1 to turn debug on for ilcell
#define N_DEBUG 1 // 1 to turn debug on for Node
#define T_DEBUG 1 // 1 to turn debug on for Tree

class ilcell {
private:
  Vertex ic_vertex;
  ilcell *ic_next;
  
public:		
  ilcell(){
    if(ILC_DEBUG) std::cerr << "Called ilcell::ilcell() [default constructor]" << std::endl;
    ic_next = NULL;
  }

  ilcell(Vertex v){
    if(ILC_DEBUG) std::cerr << "Called ilcell::ilcell(Vertex) [value constructor]" << std::endl;
    ic_vertex = v;
    ic_next = NULL;
  }

  ilcell& operator=(const ilcell &ic){
    if(ILC_DEBUG) std::cerr << "Called ilcell::operator=(const ilcell&) [assignment operator]" << std::endl;
    // check for self-assignment, only copy if different objects
    if(this != &ic){
      ic_vertex = ic.ic_vertex;
      setNext(ic.ic_next);
    }
    return *this;
  }

  Vertex& data(void){ return ic_vertex; }
  void setData(Vertex v){ ic_vertex = v; }
  
  ilcell *next(void){ return ic_next; }
  void setNext(ilcell *n){ 
    // release our resources
    if(ic_next != NULL) delete ic_next;  
    // acquire new resources
    ic_next = n; 
  }

  ~ilcell(){ 
    if(ILC_DEBUG) std::cerr << "Called ilcell::~ilcell() [destructor]" << std::endl;
    // clean up resources
    if(ic_next != NULL){
      delete ic_next;
    }
  }
  
}; // end of class ilcell

class Node {
private:
  static const int r = 7; //=ceiling[log2(1/epsilon)] + 5, for epsilon = .25
  int n_rank; // rank of a node never changes; rank of children = n_rank-1 if they exist
  int n_targetSize; // target size of a node, given by calcTargetSize(n_rank)
  int n_ckey; // upper bound on keys of elements in n_list
  int n_listSize;
  
  Node *n_left;
  Node *n_right;
  ilcell *n_list;
  ilcell *n_list_tail;
  
  int calcTargetSize(int rank){
    if(rank <= r)
      return 1;
    else
      return std::ceil( (3*calcTargetSize(rank-1))/2 ); // choice of 3/2 is arbitrary; any constant between 1 and 2 would do
  }

public:
  Node(){ 
    if(N_DEBUG) std::cerr << "Called Node::Node() [default constructor]" << std::endl;
    n_rank = 0;
    n_targetSize = calcTargetSize(n_rank);
    n_ckey = -1;
    n_listSize = 0;
    n_left = NULL;
    n_right = NULL;
    n_list = NULL;
    n_list_tail = NULL;
  }
  
  Node(Vertex v){
    if(N_DEBUG) std::cerr << "Called Node::Node(Vertex) [value constructor]" << std::endl;
    n_rank = 0;
    n_targetSize = 1;
    n_ckey = v.key();
    n_listSize = 1;
    n_left = NULL;
    n_right = NULL;
    n_list = new ilcell(v);
    n_list_tail = n_list;
  }

  Node& operator=(const Node &n){
    if(N_DEBUG) std::cerr << "Called Node::operator=(const Node&) [assignment operator]" << std::endl;
    // check for self-assignment, only copy if different objects
    if(this != &n){
      n_rank = n.n_rank;
      n_targetSize = n.n_targetSize;
      n_ckey = n.n_ckey;
      n_listSize = n.n_listSize;
      setLeft(n.n_left);
      setRight(n.n_right);
      setHead(n.n_list);
      setTail(n.n_list_tail);
    }
    return *this;
  }

  int rank(void) const{ return n_rank; }
  void setRank(int r){ n_rank = r; }

  int targetSize(void) const{ return n_targetSize; }
  void setTargetSize(int ts){ n_targetSize = ts; }

  int ckey(void) const{ return n_ckey; }
  void setCkey(int c){ n_ckey = c; }

  int size(void) const{ return n_listSize; }

  Node *left(void){ return n_left; }
  void setLeft(Node *l){ 
    // release our resources
    if(n_left != NULL) delete n_left;  
    // acquire new resources
    n_left = l; 
  }

  Node *right(void){ return n_right; }
  void setRight(Node *r){ 
    // release our resources
    if(n_right != NULL) delete n_right;  
    // acquire new resources
    n_right = r; 
  }
  
  ilcell *head(void){ return n_list; }
  void setHead(ilcell *h){ 
    // release our resources
    if(n_list != NULL) delete n_list;  
    // acquire new resources
    n_list = h; 
  }
  
  ilcell *tail(void){ return n_list_tail; }
  void setTail(ilcell *t){ 
    // release our resources
    if(n_list_tail != NULL) delete n_list_tail;  
    // acquire new resources
    n_list_tail = t; 
  }
  
  ~Node(){
    if(N_DEBUG) std::cerr << "Called Node::~Node() [destructor]" << std::endl;
    // clean up resources
    if(n_left != NULL) delete n_left;
    if(n_right != NULL) delete n_right;
    if(n_list != NULL) delete n_list; // this should take care of n_list_tail as well
  }
}; // end of class Node

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

#endif

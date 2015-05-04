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
  int n_degree, n_numChildren; // number of children in child list
  bool n_marked; // indicates whether node has lost a child since the last time node was made the child of another node (nodes start as unmarked, and are unmarked when it is made the child of another node)

public:
  Node(){ 
    if(N_DEBUG) std::cerr << "Called Node::Node() [default constructor]" << std::endl;
    n_parent = NULL;
    n_childList = NULL;
    n_left = this;
    n_right = this;
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
  }

  Node& operator=(const Node &n){
    if(N_DEBUG) std::cerr << "Called Node::operator=(const Node&) [assignment operator]" << std::endl;
    // check for self-assignment, only copy if different objects
    if(this != &n){
      
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

/***** START OF FHEAP *****/
  void FHeap::consolidate()
  {
    double phi = 1.61803;
    int magicNum = (int)std::floor(std::log10(size)/ std::log10(phi));
    vector<Node*> array(magicNum, NULL);
    for(int i = 0; i < rootList->size(); i++)
    {
	Node *x = rootList;
        d = x.degree;
	while(array[d] != NULL)
	{
          Node y = array[d]; 
          if(x.key > y.key)
	  {
            SWAP(x,y);
          }
          heapLink(x,y);
          array[d] = NULL;
          d = d + 1;
        }
        array[d] = x;
    }
    min = NULL;
    for(int i = 0; i < magicNum; i++)
    {
      if(array[i] != NULL)
      {
	if(min == NULL)
        {
	  rootList = new Tree(array[i]);
	  min = array[i];
	}
	else
	{
	  rootList->insert(array[i]);
	  if(array[i].key < min->key)
	  {
	    min = array[i];
	  }
	}
      }
    }
  }
  void FHeap::decreaseKey(Vertex v, int k)
  {
   Node *x = handles[v.id];
   if(k > x->key())
   {
     std::cerr << "New key is greater than current key" << std::endl;
   }
   x->setKey(k);
   Node *y = x->parent();
   if(y != NULL && x->key() < y->key())
   {
     x->cut(y);
     x->cascadingCut(y);
   }
   if(x->key() < min->key())
   {
     min = x;  
   }
  }
              

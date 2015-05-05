#include "FHeap.h"

#define DEBUG 1 // 1 to turn debug on for FHeap
#define N_DEBUG 1 // 1 to turn debug on for Node

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
  void setDegree(int d){ n_degree = n_numChildren = d; }
  int numChildren(void) const{ return n_numChildren; }
  void setNumChildren(int n){ n_numChildren = n_degree = n; }
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
    if(n_childList != NULL){
      Node *cur = n_childList;
      while(cur->n_right != cur){
	Node *tmp = cur->n_right;
	delete cur;
	cur = tmp;
      }
      delete cur;
    }
    // acquire new children
    n_childList = cl;
  }
  void setCLNULL(void){ n_childList = NULL; }
  void insertChild(Node *child){
    Node *clLeft = n_childList->left();
    child->setLeft(clLeft);
    child->setRight(n_childList);
    clLeft->setRight(child);
    n_childList->setLeft(child);
    n_degree++;
    n_numChildren++;
  }

  ~Node(){
    if(N_DEBUG) std::cerr << "Called Node::~Node() [destructor]" << std::endl;
    // clean up resources
    if(n_parent != NULL) n_parent = NULL;
    if(n_childList != NULL) setChildList(NULL);

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

/***** START OF FHEAP *****/
FHeap::FHeap(){
  if(DEBUG) std::cerr << "Called FHeap::FHeap() [default constructor]" << std::endl;
  size = 0;
  rootList = NULL;
  min = NULL;
}

FHeap::FHeap(Vertex v){
  if(DEBUG) std::cerr << "Called FHeap::FHeap() [value constructor]" << std::endl;
  size = 1;
  Node *n = new Node(v);
  rootList = n;
  min = n;
}

FHeap::~FHeap(){
  if(DEBUG) std::cerr << "Called FHeap::FHeap() [destructor]" << std::endl;
  // clean up resources
  if(min != NULL) min = NULL;
  if(rootList != NULL){ // this will take care of deleting min
    Node n;
    n.setChildList(rootList);
    n.setChildList(NULL);
    // above code is same as below:
    /*
    Node *cur = rootList;
    while(cur->n_right != cur){
      Node *tmp = cur->n_right;
      delete cur;
      cur = tmp;
    }
    delete cur;
    */
  }
  
}

void FHeap::insertVertex(Vertex v)
{ 
  Node *n = new Node(v);
  if(min == NULL)
    {
      rootList = n;
      min = n;
      size = 1;
    }
  else
    {
      insertNode(n);
    }
  
}


void FHeap::insertNode(Node *n)
{ 
  if(min == NULL){
    // create root list for H containing just n
    n->setDegree(0);
    n->setParent(NULL);
    n->setChildList(NULL);
    n->setMarked(false);
    rootList = n;
    min = n;
  }
  else {
    // heap is not empty
    // insert n into rootList, new node is added to left of root
    Node *rootLeft = rootList->left();
    n->setLeft(rootLeft);
    n->setRight(rootList);
    rootLeft->setRight(n);
    rootList->setLeft(n);
    if(n->key() < min->key())
      {
	min = n;
      }
    size = size + 1;
  }

}


Vertex FHeap::extractMin(void)
{
  Node *z = min;
  if(z != NULL)
    {
      Node *cur = z.childList();
      for(int i = 0; i < z->degree(); i++)
	{ 
	  Node *tmp = cur->right();
	  cur->setParent(NULL);
	  insertNode(cur);
	  cur = tmp;
	}
      z->setCLNULL();
      if(z->right() == z)
      {
	min = NULL;
      }
      else
      {
	min = z->right();
	consolidate();
      }
      size = size - 1;
      Vertex v = z->data();
      delete z;	    
      return v;
    }
  else{
    std::cerr << "FHeap: heap is empty, cannot extractMin" << std::endl;
    exit(EXIT_FAILURE);
  }
  return Vertex();
}
	
void FHeap::link(Node *child, Node *parent){
  // remove child from the rootList
  if(child->left() == child->right()){
    // has 1 sibling, set sibling to point to itself
    Node *sibling = child->left();n_left;
    sibling->setRight(sibling);
    sibling->setLeft(sibling);
  }
  else{
    // has more than 1 sibling, set left to point to right
    child->left()->setRight(child->right());
    child->right()->setLeft(child->left());
  }
  child->setLeft(NULL);
  child->setRight(NULL);
  
  // make child a child of parent, increment parent's degree
  parent->insertChild(child);

  // child.mark = false
  child->setMarked(false);
  
}

void FHeap::fibUnion(FHeap h2){
  //concatenate h2.rootList to this.rootList
  //if this.rootList is empty
  if(this->rootList->right() != NULL && this->rootList->left() != NULL){
    this->rootList->setRight(h2.rootList->right());
    this->rootList->setLeft(h2.rootList->left());
  //if h2.rootList is empty
  } else if(h2.rootList->right() != NULL && h2.rootList->left() != NULL){
    //do nothing
  //if this and h2 are both non-empty, concatenate 
  } else {
    h2.rootList->left()->setRight(this->rootList->right());
    this->rootList->right()->setLeft(h2.rootList->left());
    h2.rootList->setLeft(this->rootList);
    this->rootList->setRight(h2.rootList); 
  }
  if(this->min == NULL || (h2.min != NULL && h2.min->key() < this->min->key() )){
    this->min = h2.min;
  }
  this->size += h2.size;
}

void FHeap::cut(Node *x){
  //remove x from childList of y
/*
  if(y.childList() != &x){
    y.setChildList(y.childList()->right());
  }
  y.childList()->setLeft(y.childList()->right());
  y.childList()->setRight(y.childList()->left());
*/
  x->setLeft(x->right());
  x->setRight(x->left());
  x->parent()->setDegree(x->parent()->degree() - 1);
  x->parent()->setNumChildren(x->parent()->numChildren() - 1);
  x->setParent(NULL);
  //y->setDegree(y->degree() - 1);
  //y->setNumChildren(y->numChildren() -  1);
  //add x to rootList of H(this) 
  this->insertNode(x);
  x->setParent(NULL);
  x->setMarked(false);
}

void FHeap::cascadingCut(Node *y){
 // Node n = y.parent();
  if(y->parent() != NULL){
    if(y->marked() == false){ 
      y->setMarked(true); 
    } else {
      this->cut(y);
      this->cascadingCut(y->parent());
    } 
  }
}

Node* FHeap::minimum(){
  return min;
}

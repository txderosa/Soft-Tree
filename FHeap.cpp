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
    n_key = v.key();
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
  void setKey(int k){
    n_vertex.setKey(k);
    n_key = k;
  }

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
  void insertChild(Node *child){
    child->setParent(this);
    if(n_childList != NULL){
      Node *clLeft = n_childList->left();
      child->setLeft(clLeft);
      child->setRight(n_childList);
      clLeft->setRight(child);
      n_childList->setLeft(child);
      n_degree++;
      n_numChildren++;
    }
    else{
      n_childList = child;
      n_degree = 1;
      n_numChildren = 1;
    }
      
  }

  void removeFromSiblings(void){
    if(DEBUG) std::cerr << "Called removeFromSiblings(void)" << std::endl;
    // has siblings, adjust their pointers
    if( (n_left == this) && (n_right == this) ){
      // only child
      //n_left = NULL;
      //n_right = NULL;
    }
    else{
      if(n_left == n_right){
	// has 1 sibling, set sibling to point to itself
	Node *sibling = n_left;
	if(DEBUG){
	  std::cerr << "remove: me=" << this << " " << n_vertex.id() << std::endl;
	  std::cerr << "remove: sibling=" << sibling << std::endl;
     	  std::cerr << "remove: sibling_right=" << sibling->n_right << std::endl;
	 
	}
	sibling->n_right = sibling;
	sibling->n_left = sibling;
      }
      else{
	// has more than 1 sibling, set left to point to right
	if(DEBUG){
	  std::cerr << "remove: me=" << this << " " << n_vertex.id() << std::endl;
	  std::cerr << "remove: sibling_onleft=" << n_left << std::endl;
	  std::cerr << "remove: sibling_onright=" << n_right << std::endl;
	}
	n_left->n_right = n_right;
	n_right->n_left = n_left;
      }
    }
  }

  
  void setPCLNULL(void){
    n_parent = NULL;
    n_childList = NULL;
  }

  void setSiblingsNULL(void){
    n_left = NULL;
    n_right = NULL;
  }

  ~Node(){
    if(N_DEBUG) std::cerr << "Called Node::~Node() [destructor]" << std::endl;
    // clean up resources
    if(n_parent != NULL) n_parent = NULL;
    if(DEBUG) std::cerr << "~Node: childList: " << n_childList << std::endl;
    if(n_childList != NULL){ setChildList(NULL); }
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
  capacity = 1;
  std::vector<Node*> tmp (capacity, NULL);
  handles = tmp;
}

FHeap::FHeap(int numVertices){
  if(DEBUG) std::cerr << "Called FHeap::FHeap(int) [value constructor]" << std::endl;
  size = 0;
  rootList = NULL;
  min = NULL;
  capacity = numVertices;
  std::vector<Node*> tmp (capacity, NULL);
  handles = tmp;
}

FHeap::FHeap(Vertex v){
  if(DEBUG) std::cerr << "Called FHeap::FHeap(Vertex) [value constructor]" << std::endl;
  size = 1;
  Node *n = new Node(v);
  rootList = n;
  min = n;
  capacity = 2;
  std::vector<Node*> tmp (capacity, NULL);
  handles = tmp;
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

/***** private *****/
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

void FHeap::consolidate(void){
  if(DEBUG) std::cerr << "Called FHeap::consolidate(void)" << std::endl;
  double phi = 1.61803;
  int magicNum = (int)std::floor(std::log10(size)/std::log10(phi));
  if(DEBUG) std::cerr << "consolidate: magicNum: " << magicNum << std::endl;
  if(magicNum < 0) magicNum = 0;
  std::vector<Node*> array(magicNum+1, NULL);
  /*
  for(int i = 0; i < magicNum; i++){
    array[i] = NULL;
  }
  */
  // for each node w in the root list of H
  std::cerr << "consolidate: rootList=" << rootList << std::endl;
  std::cerr << "consolidate: size=" << size << std::endl;
  Node *w = rootList;
  for(int i = 0; i < size; i++){
    Node *x = w;
    std::cerr << "consolidate: x=" << x << std::endl;
    w = w->right();
    int d = x->degree();
    if(DEBUG) {
      std::cerr << "consolidate: d=" << d << std::endl;
      if(d >= magicNum) std::cerr << "d >= magicNum" << std::endl;
    } 
    while(d <= magicNum && array[d] != NULL){
      Node *y = array[d]; // another node with the same degree as x
      if(x->key() > y->key()){
	// we want to make y the child of x
	// but x has larger key, exchange x with y
	Node *swap = x;
	x = y;
	y = swap;
      }
      link(y,x);
      array[d] = NULL;
      d = d + 1;
    }
    if(d <= magicNum){
      std::cerr << "set array["<<d<<"]=" <<x->data().id()<< std::endl;
      array[d] = x;    
    }
  }
  // clear out H
  /*
  Node cleaner;
  cleaner.setChildList(min);
  cleaner.setChildList(NULL);
  */
  rootList = NULL;
  // build new FHeap
  min = NULL;
  for(int i = 0; i <= magicNum; i++){
    std::cerr << "consolidate: array["<<i<<"]=" << array[i] << std::endl;
    if(array[i] != NULL){
      std::cerr << "inserting " << array[i] << std::endl;
      // severe ties to siblings before inserting
      array[i]->removeFromSiblings(); // siblings no longer point to us
      array[i]->setLeft(array[i]);
      array[i]->setRight(array[i]);
      insertNode(array[i]);
      /*
      if(min == NULL){
	insertNode(array[i]);
	min = array[i];
      }
      else{
	insertNode(array[i]);
	if(array[i]->key() < min->key()){
	  min = array[i];
	}
      }
      */
    }
  }
  
  
  if(DEBUG){
    std::cerr << "End of consolidate: min="<<min;
    if(min != NULL) std::cerr <<" min.right="<<min->right();
    std::cerr<<std::endl;
  }

}

void FHeap::cut(Node *x){
  if(DEBUG) std::cerr << "Called FHeap::cut(Node*)" << std::endl;
  if(x->parent() != NULL){
    //remove x from childList of y
    if(x->left() == x->right()){
      // has 1 sibling, set sibling to point to itself
      Node *sibling = x->left();
      sibling->setRight(sibling);
      sibling->setLeft(sibling);
    }
    else{
      // has more than 1 sibling, set left to point to right
      x->left()->setRight(x->right());
      x->right()->setLeft(x->left());
    }
    x->setLeft(x);
    x->setRight(x);
    
    // decrement y.degree
    int parentD = x->parent()->degree();
    x->parent()->setDegree(parentD-1);

    // add x to root list of H
    insertNode(x);
    x->setParent(NULL);
    x->setMarked(false);
  }
  else{
    std::cerr << "FHeap: cut: x does not have a parent" << std::endl;
  }
}

void FHeap::cascadingCut(Node *y){
 // Node n = y.parent();
  if(y->parent() != NULL){
    if(y->marked() == false){ 
      y->setMarked(true); 
    } else {
      Node *z = y->parent();
      this->cut(y);
      this->cascadingCut(z);
    } 
  }
}

void FHeap::deleteNode(Node *x){
  decreaseKey(x->data().id(), std::numeric_limits<int>::min());
  extractMin();
}

void FHeap::link(Node *child, Node *parent){
  // remove child from rootList
  if( (child->left() == child) && (child->right() == child) ){
      // only child
      //n_left = NULL;
      //n_right = NULL;
    }
  else{
    if(child->left() == child->right()){
      // has 1 sibling, set sibling to point to itself
      Node *sibling = child->left();
      sibling->setRight(sibling);
      sibling->setLeft(sibling);
    }
    else{
      // has more than 1 sibling, set left to point to right
      child->left()->setRight(child->right());
      child->right()->setLeft(child->left());
    }
    child->setLeft(child);
    child->setRight(child);
  }

  // make child a child of parent, increment parent's degree
  parent->insertChild(child);

  // child.mark = false
  child->setMarked(false);
  
}

/***** public *****/
void FHeap::insertVertex(Vertex v)
{ 
  if(v.id() < 0){
    std::cerr << "FHeap: insertVertex: Vertex with id " << v.id() << " cannot be inserted into FHeap" << std::endl;
  }
  if(v.id() >= capacity){
    std::cerr << "FHeap: insertVertex: Vertex with id " << v.id() << " is larger than FHeap's capacity " << capacity << std::endl;
    exit(EXIT_FAILURE);
  }
  Node *n = new Node(v);
  // update handles
  handles[v.id()] = n;
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
  if(n->data().id() >= capacity){
    exit(EXIT_FAILURE);
  }
  if(min == NULL || rootList == NULL){
    // create root list for H containing just n
    rootList = n;
    min = n;
    std::cerr << "insertNode: update min=" << n << std::endl;
    size = 1;
  }
  else {
    // heap is not empty
    // insert n into rootList, new node is added to left of root
    if(DEBUG) {
      std::cerr << "insertNode: rootList=" << rootList;
      if(rootList != NULL) std::cerr<< " rootLeft=" << rootList->left();
      std::cerr <<  std::endl;
    }
    if(rootList != NULL){
      Node *rootLeft = rootList->left();
      n->setLeft(rootLeft);
      n->setRight(rootList);
      rootLeft->setRight(n);
      rootList->setLeft(n);
      size = size + 1;   
    }
    /*
    else{
      // root list is empty!
      rootList = n;
    }
    */
  }
  
  if(DEBUG) std::cerr << "insertNode: rootList=" << rootList << " rootLeft=" << rootList->left() <<  std::endl;
  
  if(n->key() < min->key())
    {
      min = n;
      std::cerr << "insertNode: update min" << std::endl;
    }
  
  // update handles
  handles[n->data().id()] = n;

}

Node* FHeap::minimum(void){
  return min;
}

Vertex FHeap::extractMin(void)
{
  if(DEBUG) std::cerr << "Called FHeap::extractMin(void)" << std::endl;
  Node *z = min;
  std::cerr << "min=" << min << std::endl;
  if(z != NULL)
    {
      if(z->right() == z){
	// z is only node in rootList
	std::cerr << "z.right=" << z->right() << " z=" << z << std::endl;
	rootList = NULL;
	std::cerr << "extractMin: rootList=" << rootList << std::endl;
	size = 0;
      }
      else{
	if(z == rootList){
	  std::cerr << "extractMin assgin rootList = rootList.right" << std::endl;
	  std::cerr << "\tbefore: " << rootList << " " << rootList->right() << std::endl;
	  rootList = rootList->right();
	  std::cerr << "\tafter: " << rootList << " " << rootList->right() << std::endl;
	}
	std::cerr << "extractMin: rootList=" << rootList << std::endl;
	z->removeFromSiblings();
	size--;
	std::cerr << "extractMin: size after extract=" << size << std::endl;
      }
      // add children to rootList
      Node *cur = z->childList();
      if(DEBUG) std::cerr << "z.degree=" << z->degree() << std::endl;
      for(int i = 0; i < z->degree(); i++)
	{ 
	  if(DEBUG) std::cerr << "z.degree="<<z->degree()<<" "<<cur << std::endl;
	  if(cur == NULL) break;
	  Node *tmp = cur->right();
	  cur->setParent(NULL);
	  insertNode(cur);
	  cur = tmp;
	  if(tmp == NULL) break;
	}
      z->setPCLNULL();
      /*
      if(z->right() == z)
	{
	  if(DEBUG) std::cerr << "extractMin: min is only node in FHeap" << std::endl; 
	  min = NULL;
	}
      else
	{
	  min = z->right();
	  consolidate();
	  }
      */
      consolidate();
      Vertex v = z->data();
      if(DEBUG) std::cerr << "extractMin: z.childList " << z->childList() << std::endl;
      // update handles
      z->setSiblingsNULL();
      //delete z;
      handles[v.id()] = NULL;
      if(DEBUG) std::cerr << "extractMin: vertex " << v.id() << std::endl;
      return v;
    }
  else{
    std::cerr << "FHeap: heap is empty, cannot extractMin" << std::endl;
    exit(EXIT_FAILURE);
  }
  return Vertex();
}

void FHeap::decreaseKey(int vertexID, int k)
{
  if(DEBUG) std::cerr << "Called FHeap::decreaseKey(int,int)" << std::endl;
  if(DEBUG) std::cerr << "decKey of vertex " << vertexID << std::endl; 
  if(vertexID >= capacity){
    std::cerr << "FHeap: decreaseKey: Vertex with id " << vertexID << " not in FHeap!" << std::endl;
    exit(EXIT_FAILURE);
  }
  Node *x = handles[vertexID];
  if(x == NULL){
    std::cerr << "FHeap: decreaseKey: Vertex with id " << vertexID << " not in FHeap!" << std::endl;
    exit(EXIT_FAILURE);
  }
  if(k > x->key())
    {
      std::cerr << "New key is greater than current key" << std::endl;
      exit(EXIT_FAILURE);
    }
  x->setKey(k);
  Node *y = x->parent();
  if(y != NULL && x->key() < y->key())
    {
      cut(x);
      cascadingCut(y);
    }
  /*
  if(min == NULL){
    std::cerr << "decreaseKey: min is NULL" << std::endl;
    return;
  } 
  */ 
  if(x->key() < min->key())
    {
      min = x;  
      if(DEBUG) std::cerr << "decKey: set min="<<min<<std::endl;
    }
  showHandles();
}
	
/*** for Fib in MST ***/
bool FHeap::empty(void){
  return min == NULL;
}

bool FHeap::contains(int vertexID){
  if(vertexID < capacity)
    return handles[vertexID] != NULL;
  else
    return false;
}

int FHeap::getKey(int vertexID){
  if(DEBUG) std::cerr << "getKey: vertex " << vertexID << std::endl;
  if(contains(vertexID)){
    if(DEBUG) {
      showHandles();
      if(handles[vertexID] == NULL)
	std::cerr << "getKey: handles[" << vertexID << "] == NULL" << std::endl;
    }
    return handles[vertexID]->key();
  }
  else{
    std::cerr << "FHeap: getKey: Vertex " << vertexID << " does not exist in FHeap" << std::endl;
    exit(EXIT_FAILURE);
    return -1;
  }
}

void FHeap::showHandles(void){
  if(DEBUG){
    for(int i = 0; i < capacity; i++){
      std::cerr << i << ": " << handles[i];
      if(handles[i] != NULL)
	std::cerr << " " << handles[i]->key();
      std::cerr << std::endl;
    }
  }
}

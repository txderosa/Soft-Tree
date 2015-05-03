#ifndef _SOFTHEAPUTIL_CPP_
	
class ilcell { 
	Vertex vertex;
	ilcell *next;
		
	ilcell();
	~ilcell();
};

class Node; {
	int ckey, rank, listSize, targetSize;
	Node *left, *right;
	ilcell *list, *list_tail;
		
	Node();
	~Node();
};

class Tree {
	Node *root;
	Tree *next, *prev, *sufmin;
	int rank;
		
	Tree();
	~Tree();
};

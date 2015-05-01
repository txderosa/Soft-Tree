#ifndef _SOFTHEAP_H_
#define _SOFTHEAP_H_

#include "Vertex.cpp"
#include <limits>

class Queue{
	public:
	typedef struct ILCELL { 
		int key; // Vertex v? 
		struct ILCELL *next;
	} ilcell;

	typedef struct NODE {
		int ckey, rank, listSize, size;
		struct NODE *left, *right;
		struct ILCELL *il, il_tail; //il = list?
	} Node;

	typedef struct TREE {
		struct NODE *heap;
		struct HEAD *next, *prev, *sufmin;
		int rank;
	} Tree;

	//int r;
	//void setR(int value);
	static int INFINITY = std::numeric_limits<int>::max();

	//Data members of Queue
	Tree first;
	int rank;

	Queue makeQueue(Vertex &v);
	Tree makeTree(Vertex &v);
	Node makeNode(Vertex &);
	Queue insert(Queue &p, Vertex &v);
	Node combine(Node &x, Node &y);
	Queue meld(Queue &p, Queue &q);
	Vertex extractMin(Tree &p);
	void mergeInto(Queue &p, Queue &q);
	void repeatedCombine(Queue &q, int k);
	void updateSuffixMin(head &t);
	void insertTree(Queue &p, Tree &t1, Tree &t2);
	void removeTree(Queue &p, Tree &t);
	bool leaf(node &x);
};

#endif

#ifndef _SOFTHEAP_H_
#define _SOFTHEAP_H_

#include <limits>

class Queue{
	public:

	const static int INFINITY = std::numeric_limits<int>::max();

	//Data members of Queue
	int r = 7; //=ceiling[log2(1/epsilon)] + 5, for epsilon = .25
	Tree *first;
	int rank;

	Queue();
	Queue(Vertex v);
	~Queue();
	
	Tree makeTree(Vertex v);
	Node makeNode(Vertex v);
	ilcell makeILCell(Vertex v);
	Queue insert(Queue &p, Vertex &v);
	void sift(Node &x);
	Node combine(Node &x, Node &y);
	Queue meld(Queue &p, Queue &q);
	Vertex extractMin(Queue &p);
	void mergeInto(Queue &p, Queue &q);
	void repeatedCombine(Queue &q, int k);
	void updateSuffixMin(Tree &t);
	void insertTree(Queue &p, Tree &t1, Tree &t2);
	void removeTree(Queue &p, Tree &t);
	bool leaf(Node &x);
};

#endif

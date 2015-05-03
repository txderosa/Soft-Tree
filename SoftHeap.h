#ifndef _SOFTHEAP_H_
#define _SOFTHEAP_H_

#include <limits>
#include "SoftHeapUtil.cpp"

class Queue{
    private:
	const static int INFINITY = std::numeric_limits<int>::max();
	int r = 7; //=ceiling[log2(1/epsilon)] + 5, for epsilon = .25
	int rank;
	Tree *first;

	Tree makeTree(Vertex v);
	Node makeNode(Vertex v);
	ilcell makeILCell(Vertex v);
	void sift(Node x);
	Node combine(Node x, Node y);
	Queue meld(Queue p, Queue q); //first Queue p change into this, changing to OO
	void mergeInto(Queue p, Queue q);
	void repeatedCombine(Queue q, int k);
	void updateSuffixMin(Tree t);
	void insertTree(Queue p, Tree t1, Tree t2);
	void removeTree(Queue p, Tree t);
	bool leaf(Node x);

    public:
	Queue(void);
	Queue(Vertex v);
	~Queue(void);
	
	Queue insert(Queue p, Vertex v);
	Vertex extractMin(Queue p);
};

#endif

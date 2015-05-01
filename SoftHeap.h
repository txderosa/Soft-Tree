#ifndef _SOFTHEAP_H_
#define _SOFTHEAP_H_

#include "Vertex.cpp"
#include <limits>

typedef struct ILCELL {
	int key; 
	struct ILCELL *next;
} ilcell;

typedef struct NODE {
	int ckey, rank, listSize, size;
	struct NODE *left, *right;
	struct ILCELL *il, il_tail;
} node;

typedef struct HEAD {
	struct NODE *heap;
	struct HEAD *next, *prev, *suffixMin;
	int rank;
} head;

int r;
static int INFINITY = std::numeric_limits<int>::max();
void setR(int value);

void insert(int newKey);
void meld(node &q);
void fixMinList(head &h); //upate-suffix-min
node* sift(node &v);
node combine(node &x, node &y);
//make-heap();
void extractMin(void);
bool leaf(node &x);
//concatenate(list, list)

#endif

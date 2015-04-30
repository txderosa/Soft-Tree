#ifndef _SOFTHEAP_H_
#define _SOFTHEAP_H_

#include "Vertex.cpp"

typedef struct ILCELL {
	int key; 
	struct ILCELL *next;
} ilcell;

typedef struct NODE {
	int ckey, rank;
	struct NODE *next, *child;
	struct ILCELL *il, il_tail;
} node;

typedef struct HEAD {
	struct NODE *heap;
	struct HEAD *next, *prev, *suffixMin;
	int rank;
} head;

int r;
void setR(int value);

void insert(int newKey);
void meld(node &q);
void fixMinList(head &h);
node* sift(node &v);
void extractMin(void);

#endif

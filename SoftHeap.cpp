#include "SoftHeap.h"



void insert(int newKey){
	node *q;
	ilcell *l;
	l = (ilcell *)malloc(sizeof(ilcell));
	l->key = newKey;
	l->next = NULL;
	q = newNode();	
	q->rank = 0;	
	q->ckey = newKey;
	q->il = l;
	q->il_tail = l;
	meld(q);
}

void meld(node &q){
	head *h, *prevHead, *toHead = header->next;
	node *top, *bottom;	
	while(q->rank > toHead->rank){
		toHead = toHead->next;
	}
	prevHead = toHead->prev;
	while(q->rank == toHead->rank){
		if(toHead->heap->ckey > q->key){
			top = q;
			bottom = toHead->heap;
		} else {
			top = toHead->heap;
			bottom = q;
		}
		q = newNode();
		q->ckey = top->ckey;
		q->rank = top->rank + 1;
		q->child = bottom;
		q->next = top;
		q->il = top->il;
		q->il_tail = top->il_tail;
		toHead = toHead->next;
	}
	if(prevHead == toHead->prev){
		h = newHead();
	} else {
		h = prevHead->next;
	}
	h->heap = q;
	h->rank = q->rank;
	h->prev = prevHead;
	h->next = toHead;
	prevHead->next = h;
	toHead->prev = h;
	fixMinList(h);
}

void fixMinList(head &h){
	head *temp;
	if(h->next == tail){
		temp = h;
	} else {
		temp = h->next->suffixMin;
	}
	while(h != header){
		if(h->heap->ckey < temp->heap->ckey){
			temp = h;
		}
		h->suffixMin = temp;
		h = h->prev;
	}
}

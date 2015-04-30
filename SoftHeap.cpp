#include "SoftHeap.h"
#include <limits> 

#define INFINITY std::numeric_limits<int>::max()

void setR(int value){ r = value; }

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

node* sift(node &v){
	node *temp;
	v->il = NULL;
	v->il_tail = NULL;
	if(v->next == NULL && v->child == NULL){
		v->ckey = INFINITY
		return v;
	}
	v->next = sift(v->next);
	if(v->next->ckey > v->child->ckey){
		temp = v->child;
		v->child = v->next;
		v->next = temp;
	}
	v->il = v->next->il;
	v->il_tail = v->next->il_tail;
	v->ckey = v->next->ckey;
	if(v->rank > r && (v->rank % 2 == 1 || v->child->rank < v->rank - 1)){
		v->next = sift(v->next);
		if(v->next->ckey> v->child->ckey){
			temp = v->child;
			v->child = v->next;
			v->next = v->child;
		}
		if(v->next->ckey != INFINITY && v->next->il != NULL){
			v->next->il_tail->next = v->il;
			v->il = v->next->il;
			if(v->il_tail == NULL){
				v->il_tail = v->next->il_tail;
			}
			v->ckey = v->next->ckey;
		}
	}
	if(v->child->ckey == INFINITY){
		if(v->next->ckey == INFINITY){
			v->child = NULL;
			v->next = NULL;
		} else {
			v->child = v->next->child;
			v->next = v->next->next;
		}
	}
	return v;
}

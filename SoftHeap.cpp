#include "SoftHeap.h"

void setR(int value){ r = value; }

head makeHeap(Vertex &v){ 
	Queue p = newHeap();
	p.first = makeTree(v);
	p.rank = 0;
	return p;	
}

head makeTree(Vertex &v){
	head t = newTree();
	t.root = makeNode(v);
	t.next = NULL;
	t.prev = NULL;
	t.rank = 0;
	t.sufmin = t;
	return t;
}

node makeNode(Vertex &v){
	node x = newNode();
	x.list = v; //list[x] = {e}
	x.ckey = v.key;
	x.rank = 0;
	x.size = 1;
	x.left = NULL;
	x.right = NULL;
	return x;
}

Queue insert(Queue &p, Vertex &v){
	return meld(p,makeHeap(v));
}

void sift(node &x){
	while(x.listSize < x.size && !leaf(x)){
		if(x.left == NULL || (x.right == NULL && x.left.ckey > c.right.ckey)){
			node temp = x.left;
			x.left = x.right;
			x.right = temp;
		}
		concatenate(x.list, x.left.list);
		x.ckey = x.left.ckey;
		x.left.list = NULL;
		if(leaf(x.left)) x.left == NULL;
		else sift(x.left);
	}
}

node combine(node &x, node &y){
	z = newNode();
	z.left = x;
	z.right = y;
	z.rank = x.rank + 1;
	if(z.rank <= r) z.size = 1;
	else z.size = (3 * x.size + 1)/2;
	sift(z);
	return z;

}

Queue meld(Queue &p, Queue &q){
	if(p.rank > q.rank){
		int temp = p.rank;
		p.rank = q.rank;
		q.rank = temp;
	}
	mergeInto(p,q)
	repeatedCombine(q, p.rank)
	return q;
}

Vertex extractMin(head &p){
	if(p.heap == NULL) return NULL;
	head T = p.first.sufmin; // sufmin[first[P]]
	node x = T.root
	//Vertex e = pickElement(list[x]) = ??

	if(x.listSize <= x.size/2){
		if(!leaf(x)){
			sift(x);
			updateSuffixMin(T);
		} else if(x.listSize != 0){
			removeTree(p,T);
		}
	}
	return e;
}

void mergeInto(Queue &p, Queue &q){
	if(p.rank > q.rank){
		//abort
	}
	head T1 = p.first;
	head T2 = q.first;
	while(T1 != NULL){
		while(T1.rank > T2.rank){
			T2 = T2.next;
		}
		head temp = T1;
		insertTree(q, T1, T2);
		T1 = temp;
	}
}

void repeatedCombine(Queue &q, int k){
	head t = q.first;
	while(t.next != NULL){
		if(t.rank = t.next.rank){
			if(t.next.next == NULL || t.rank != t.next.next.rank){
				t.root = combine(t.root, t.next.root);
				t.rank = t.root.rank;
				removeTree(q, t.next);
			}

		} else if(t.rank > k){
			break;
		}
		t = t.next;
	}
	if(t.rank > q.rank){
		q.rank = t.rank;
	}
	updateSuffixMin(t); //pass in q?
}

void updateSuffixMin(head t){
	while(t != NULL){
		if(t.root.ckey <= t.next.sufmin.root.ckey){
			t.sufmin = t; 
		} else {
			t.sufmin = t.next.sufmin;
		}
		t = t.prev;
	}
}

void insertTree(Queue p, head t1, head t2){
	t1.next = t2;
	if(t2.prev = NULL){
		p.first = t1;
	} else {
		t2.prev.next = t1;
	}
}

void removeTree(Queue p, head t){
	if(t.prev == NULL){
		p.first = t.next;
	} else {
		t.prev.next = t.next;
	}
	if(t.next != NULL){
		t.next.prev = t.prev; 
	}
}

bool leaf(node &x){
	if(x.left == NULL && x.right == NULL) return true;
	else return false;
}

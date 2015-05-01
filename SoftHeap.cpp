#include "SoftHeap.h"

void setR(int value){ r = value; }

head makeHeap(Vertex &v){ 
//very rough draft of this function
	head p = newHead();
	p.heap = makeTree(v);
	p.rank = 0;
	return p;	
}

head insert(head &p, Vertex &v){
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

head meld(head &p, head &q){
	if(p.rank > q.rank){
		int temp = p.rank;
		p.rank = q.rank;
		q.rank = temp;
	}
	//merge-into(p,q)
	//repeated-combine(q, p.rank)
	return q;
}

Vertex extractMin(head &p){
	if(p.heap == NULL) return NULL;
	//T = sufmin[first[P]] = p.heap.sufmin?
	//x = root[T] = T.root?
	//e = pickElement(list[x]) = ??

	if(x.listSize <= x.size/2){
		if(!leaf(x)){
			sift(x);
			updateSuffixMin(T);
		} else if(x.listSize != 0){

		}
	}
}

bool leaf(node &x){
	if(x.left == NULL && x.right == NULL) return true;
	else return false;
}

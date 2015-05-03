#include "SoftHeap.h"

Sheap::INFINITY = std::numeric_limits<int>::max();

/* TODO
  * make sure node.listSize incremements correctly and node.size is set correctly
  * check that concatenate in sift() works correctly
  * implement pickElement() in extractMin()
  * = operator for Tree
*/


Sheap::Sheap(){

}

Sheap::Sheap(v){ 
	first = makeTree(v);
	rank = 0;	
}

Sheap::~Sheap(){

}

Tree Sheap::makeTree(Vertex v){
	Tree t;// = newTree();
	t.root = makeNode(v);
	t.next = NULL;
	t.prev = NULL;
	t.rank = 0;
	t.sufmin = &t;
	return t;
}

Node Sheap::makeNode(Vertex v){
	Node x;// = newNode();
	x.list = makeILCell(v); //list[x] = {e}
	x.list_tail = x.list;
	x.ckey = v.key;
	x.rank = 0;
	x.listSize = 1;
	x.left = NULL;
	x.right = NULL;
	return x;
}

ilcell Sheap::makeILCell(Vertex v){
	ilcell c;
	c.vertex = v;
	c.next = NULL;
	return c;
}

Sheap Sheap::insert(Sheap &p, Vertex &v){
	return meld(p,makeSheap(v));
}

void Sheap::sift(Node &x){
	while(x.listSize < x.targetSize && !leaf(x)){
		if(x.left == NULL || (x.right == NULL && x.left.ckey > x.right.ckey)){
			Node temp = x.left;
			x.left = x.right;
			x.right = temp;
		}
		//concatenate(x.list, x.left.list);
		x.list_tail.next = x.left.list;
		x.ckey = x.left.ckey;
		x.listSize += x.left.listSize;
		x.left.list = NULL;
		x.left.list_tail = NULL;
		if(leaf(x.left)) x.left = NULL;
		else sift(x.left);
	}
}

Node Sheap::combine(Node &x, Node &y){
	Node z;// = newNode();
	z.left = x;
	z.right = y;
	z.rank = x.rank + 1;
	if(z.rank <= r) z.targetSize = 1;
	else z.targetSize = (3 * x.targetSize + 1)/2;
	sift(z);
	return z;

}

Sheap Sheap::meld(Sheap &p, Sheap &q){
	if(p.rank > q.rank){
		int temp = p.rank;
		p.rank = q.rank;
		q.rank = temp;
	}
	mergeInto(p,q);
	repeatedCombine(q, p.rank);
	return q;
}

Vertex Sheap::extractMin(Sheap &p){
	if(p.first == NULL) return NULL;
	Tree t = p.first.sufmin; // sufmin[first[P]]
	Node x = t.root;
	Vertex e;//= pickElement(list[x]) = ??

	if(x.listSize <= x.targetSize/2){
		if(!leaf(x)){
			sift(x);
			updateSuffixMin(t);
		} else if(x.listSize != 0){
			removeTree(p,t);
		}
	}
	return e;
}

void Sheap::mergeInto(Sheap &p, Sheap &q){
	if(p.rank > q.rank){
		std::cerr << "mergeInto abort: p.rank > q.rank" << std::endl;
		exit(EXIT_FAILURE);
	}
	Tree t1 = p.first;
	Tree t2 = q.first;
	while(t1 != NULL){
		while(t1.rank > t2.rank){
			t2 = t2.next;
		}
		Tree temp = t1;
		insertTree(q, t1, t2);
		t1 = temp;
	}
}

void Sheap::repeatedCombine(Sheap &q, int k){
	Tree t = q.first;
	while(t.next != NULL){
		if(t.rank == t.next.rank){
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

void Sheap::updateSuffixMin(Tree &t){
	while(t != NULL){
		if(t.root.ckey <= t.next.sufmin.root.ckey){
			t.sufmin = t; 
		} else {
			t.sufmin = t.next.sufmin;
		}
		t = t.prev;
	}
}

void Sheap::insertTree(Sheap &p, Tree &t1, Tree &t2){
	t1.next = t2;
	if(t2.prev == NULL){
		p.first = t1;
	} else {
		t2.prev.next = t1;
	}
}

void Sheap::removeTree(Sheap &p, Tree &t){
	if(t.prev == NULL){
		p.first = t.next;
	} else {
		t.prev.next = t.next;
	}
	if(t.next != NULL){
		t.next.prev = t.prev; 
	}
}

bool Sheap::leaf(Node &x){
	if(x.left == NULL && x.right == NULL) return true;
	else return false;
}

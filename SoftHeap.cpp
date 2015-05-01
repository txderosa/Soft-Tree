#include "SoftHeap.h"

/* TODO
  * make sure node.listSize incremements correctly and node.size is set correctly
  * check that concatenate in sift() works correctly
  * implement pickElement() in extractMin()
*/

//void setR(int value){ r = value; }

Queue makeQueue(Vertex &v){ 
	Queue p;// = newQueue();
	p.first = makeTree(v);
	p.rank = 0;
	return p;	
}

Tree makeTree(Vertex &v){
	Tree t;// = newTree();
	t.root = makeNode(v);
	t.next = NULL;
	t.prev = NULL;
	t.rank = 0;
	t.sufmin = t;
	return t;
}

Node makeNode(Vertex &v){
	Node x;// = newNode();
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

void sift(Node &x){
	while(x.listSize < x.size && !leaf(x)){
		if(x.left == NULL || (x.right == NULL && x.left.ckey > c.right.ckey)){
			Node temp = x.left;
			x.left = x.right;
			x.right = temp;
		}
		//concatenate(x.list, x.left.list);
		x.list.next = x.left.list;
		x.left.list = NULL;
		x.ckey = x.left.ckey;
		x.left.list = NULL;
		if(leaf(x.left)) x.left == NULL;
		else sift(x.left);
	}
}

Node combine(Node &x, Node &y){
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
	mergeInto(p,q);
	repeatedCombine(q, p.rank);
	return q;
}

Vertex extractMin(Tree &p){
	if(p.heap == NULL) return NULL;
	Tree t = p.first.sufmin; // sufmin[first[P]]
	Node x = T.root;
	//Vertex e = pickElement(list[x]) = ??

	if(x.listSize <= x.size/2){
		if(!leaf(x)){
			sift(x);
			updateSuffixMin(t);
		} else if(x.listSize != 0){
			removeTree(p,t);
		}
	}
	return e;
}

void mergeInto(Queue &p, Queue &q){
	if(p.rank > q.rank){
		std::cerr << "mergeInto abort: p.rank > q.rank" << std::endl;
		exit(EXIT_FAILURE);
	}
	Tree t1 = p.first;
	Tree t2 = q.first;
	while(T1 != NULL){
		while(t1.rank > t2.rank){
			t2 = t2.next;
		}
		Tree temp = t1;
		insertTree(q, t1, t2);
		t1 = temp;
	}
}

void repeatedCombine(Queue &q, int k){
	Tree t = q.first;
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

void updateSuffixMin(Tree &t){
	while(t != NULL){
		if(t.root.ckey <= t.next.sufmin.root.ckey){
			t.sufmin = t; 
		} else {
			t.sufmin = t.next.sufmin;
		}
		t = t.prev;
	}
}

void insertTree(Queue &p, Tree &t1, Tree &t2){
	t1.next = t2;
	if(t2.prev = NULL){
		p.first = t1;
	} else {
		t2.prev.next = t1;
	}
}

void removeTree(Queue &p, Tree &t){
	if(t.prev == NULL){
		p.first = t.next;
	} else {
		t.prev.next = t.next;
	}
	if(t.next != NULL){
		t.next.prev = t.prev; 
	}
}

bool leaf(Node &x){
	if(x.left == NULL && x.right == NULL) return true;
	else return false;
}

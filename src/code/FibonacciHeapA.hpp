
template <class V> class FibonacciHeap;

template <class V> struct Node {
	Node<V>* prev;
	Node<V>* next;
	Node<V>* child;
	Node<V>* parent;
	V value;
	int degree;
	bool marked;
public:
	friend class FibonacciHeap<V>;
    Node() = default;
	Node<V>* getPrev() {return prev;}
	Node<V>* getNext() {return next;}
	Node<V>* getChild() {return child;}
	Node<V>* getParent() {return parent;}
	V getValue() {return value;}
	bool isMarked() {return marked;}

	bool hasChildren() {return child;}
	bool hasParent() {return parent;}
};

template <class V> class FibonacciHeap {
	Node<V>* heap;
public:

	FibonacciHeap() {
		heap=_empty();
	}
	virtual ~FibonacciHeap() {
		if(heap) {
			_deleteAll(heap);
		}
	}
	Node<V>* insert(V value) {
		Node<V>* ret=_singleton(value);
		heap=_merge(heap,ret);
		return ret;
	}
	void merge(FibonacciHeap& other) {
		heap=_merge(heap,other.heap);
		other.heap=_empty();
	}

	bool isEmpty() {
		return heap==NULL;
	}

	V getMinimum() {
		return heap->value;
	}

	V removeMinimum() {
		Node<V>* old=heap;
		heap=_removeMinimum(heap);
		V ret=old->value;
		delete old;
		return ret;
	}

	void decreaseKey(Node<V>* n,V value) {
		heap=_decreaseKey(heap,n,value);
	}

	Node<V>* find(V value) {
		return _find(heap,value);
	}
private:
	Node<V>* _empty() {
		return NULL;
	}

	Node<V>* _singleton(V value) {
		Node<V>* n=new Node<V>;
		n->value=value;
		n->prev=n->next=n;
		n->degree=0;
		n->marked=false;
		n->child=NULL;
		n->parent=NULL;
		return n;
	}

	Node<V>* _merge(Node<V>* a,Node<V>* b) {
		if(a==NULL)return b;
		if(b==NULL)return a;
		if(a->value>b->value) {
			Node<V>* temp=a;
			a=b;
			b=temp;
		}
		Node<V>* an=a->next;
		Node<V>* bp=b->prev;
		a->next=b;
		b->prev=a;
		an->prev=bp;
		bp->next=an;
		return a;
	}

	void _deleteAll(Node<V>* n) {
		if(n!=NULL) {
			Node<V>* c=n;
			do {
				Node<V>* d=c;
				c=c->next;
				_deleteAll(d->child);
				delete d;
			} while(c!=n);
		}
	}
	
	void _addChild(Node<V>* parent,Node<V>* child) {
		child->prev=child->next=child;
		child->parent=parent;
		parent->degree++;
		parent->child=_merge(parent->child,child);
	}

	void _unMarkAndUnParentAll(Node<V>* n) {
		if(n==NULL)return;
		Node<V>* c=n;
		do {
			c->marked=false;
			c->parent=NULL;
			c=c->next;
		}while(c!=n);
	}

	Node<V>* _removeMinimum(Node<V>* n) {
		_unMarkAndUnParentAll(n->child);
		if(n->next==n) {
			n=n->child;
		} else {
			n->next->prev=n->prev;
			n->prev->next=n->next;
			n=_merge(n->next,n->child);
		}
		if(n==NULL)return n;
		Node<V>* trees[64]={NULL};
		
		while(true) {
			if(trees[n->degree]!=NULL) {
				Node<V>* t=trees[n->degree];
				if(t==n)break;
				trees[n->degree]=NULL;
				if(n->value<t->value) {
					t->prev->next=t->next;
					t->next->prev=t->prev;
					_addChild(n,t);
				} else {
					t->prev->next=t->next;
					t->next->prev=t->prev;
					if(n->next==n) {
						t->next=t->prev=t;
						_addChild(t,n);
						n=t;
					} else {
						n->prev->next=t;
						n->next->prev=t;
						t->next=n->next;
						t->prev=n->prev;
						_addChild(t,n);
						n=t;
					}
				}
				continue;
			} else {
				trees[n->degree]=n;
			}
			n=n->next;
		}
		Node<V>* min=n;
		Node<V>* start=n;
		do {
			if(n->value<min->value)min=n;
			n=n->next;
		} while(n!=start);
		return min;
	}

	Node<V>* _cut(Node<V>* heap,Node<V>* n) {
		if(n->next==n) {
			n->parent->child=NULL;
		} else {
			n->next->prev=n->prev;
			n->prev->next=n->next;
			n->parent->child=n->next;
		}
		n->next=n->prev=n;
		n->marked=false;
		return _merge(heap,n);
	}

	Node<V>* _decreaseKey(Node<V>* heap,Node<V>* n,V value) {
		if(n->value<value)return heap;
		n->value=value;
		if(n->parent) {
			if(n->value<n->parent->value) {
				heap=_cut(heap,n);
				Node<V>* parent=n->parent;
				n->parent=NULL;
				while(parent!=NULL && parent->marked) {
					heap=_cut(heap,parent);
					n=parent;
					parent=n->parent;
					n->parent=NULL;
				}
				if(parent!=NULL && parent->parent!=NULL)parent->marked=true;
			}
		} else {
			if(n->value < heap->value) {
				heap = n;
			}
		}
		return heap;
	}

	Node<V>* _find(Node<V>* heap,V value) {
		Node<V>* n=heap;
		if(n==NULL)return NULL;
		do {
			if(n->value==value)return n;
			Node<V>* ret=_find(n->child,value);
			if(ret)return ret;
			n=n->next;
		}while(n!=heap);
		return NULL;
	}
};
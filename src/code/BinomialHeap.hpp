template <class T>
struct BinomialNode;

template <class T>
struct BinomialHeap;

template <class T>
struct BinomialNode{
    T key;
    long int degree;
    BinomialNode<T>* child;
    BinomialNode<T>* parent;
    BinomialNode<T>* next;

    BinomialNode(T key):key(key), degree(0), child(nullptr), parent(nullptr), next(nullptr){};
};

template <class T>
struct BinomialHeap{
    BinomialNode<T>* root_node;

    void insert(T key);
    T find_min();
    void delete_min();
    void merge(BinomialHeap* other);
    bool is_exist(T key);

    BinomialNode<T>* merge_root(BinomialNode<T>* p, BinomialNode<T>* q);
    void link(BinomialNode<T>* root, BinomialNode<T>* child);
    BinomialNode<T>* merge(BinomialNode<T>* p, BinomialNode<T>* q);
    void find_min_key(BinomialNode<T>* &min_key, BinomialNode<T>* &pre_min_key);
    BinomialNode<T>* reverse(BinomialNode<T>* root);
    BinomialNode<T>* is_exist(BinomialNode<T>* root, T key);
};

// merge root list of two heaps by degree-increasing, return new root node
template <class T>
BinomialNode<T>* BinomialHeap<T>::merge_root(BinomialNode<T>* p, BinomialNode<T>* q){
    BinomialNode<T>* ret = nullptr;
    BinomialNode<T>** pos = &ret;

    while(p && q){
        if(p->degree < q->degree){
            *pos = p;
            p = p->next;
        }
        else{
            *pos = q;
            q = q->next;
        }

        pos = &((*pos)->next);
    }

    if(p){
        *pos = p;
    }

    if(q){
        *pos = q;
    }

    return ret;
}

// link child node to root node as child
template <class T>
void BinomialHeap<T>::link(BinomialNode<T>* root, BinomialNode<T>* child){
    child->parent = root;
    child->next = root->child;
    root->child = child;
    root->degree += 1;
}

// merge two heap, return merged heap
template <class T>
BinomialNode<T>* BinomialHeap<T>::merge(BinomialNode<T>* p, BinomialNode<T>* q){
    auto root = merge_root(p, q);
    if(root == nullptr){
        return root;
    }

    BinomialNode<T>* pre = nullptr;
    BinomialNode<T>* cur = root;
    BinomialNode<T>* nxt = cur->next;
    
    while(nxt != nullptr){
        if((cur->degree != nxt->degree) || ((nxt->next != nullptr) && (nxt->next->degree == nxt->degree))){
            pre = cur;
            cur = nxt;
        }
        else if(cur->key <= nxt->key){
            cur->next = nxt->next;
            link(cur, nxt);
        }
        else{
            if(pre == nullptr){
                root = nxt;
            }
            else{
                pre->next = nxt;
            }

            link(nxt, cur);
            cur = nxt;
        }

        nxt = cur->next;
    }

    return root;
}

// merge other heap to this heap
template <class T>
void BinomialHeap<T>::merge(BinomialHeap<T>* other){
    if(other != nullptr && other->root_node != nullptr){
        this->root_node = merge(this->root_node, other->root_node);
    }
}

// insert a node with key into this heap
template <class T>
void BinomialHeap<T>::insert(T key){
    auto new_node = new BinomialNode<T>(key);
    if(new_node != nullptr){
        this->root_node = merge(this->root_node, new_node);
    }
    return;
}

// store the pointers to minimum key and its pre to given pointers
template <class T>
void BinomialHeap<T>::find_min_key(BinomialNode<T>* &min_key, BinomialNode<T>* &pre_min_key){
    BinomialNode<T>* cur;
    BinomialNode<T>* pre;

    min_key = pre_min_key = nullptr;

    if(this->root_node == nullptr){
        return;
    }

    cur = this->root_node->next;
    pre = this->root_node;

    min_key = root_node;
    pre_min_key = nullptr;

    while(cur != nullptr){
        if(cur->key <= min_key->key){
            min_key = cur;
            pre_min_key = pre;
        }
        pre = cur;
        cur = cur->next;
    }
    return;
}

// return the minimum key value of this heap
template <class T>
T BinomialHeap<T>::find_min(){
    BinomialNode<T>* min_key;
    BinomialNode<T>* pre_min_key;
    find_min_key(min_key, pre_min_key);

    return min_key->key;
}

// reserve the heap
template <class T>
BinomialNode<T>* BinomialHeap<T>::reverse(BinomialNode<T>* root){
    BinomialNode<T>* next;
    BinomialNode<T>* tail = NULL;

    if(!root){
        return root;
    }

    root->parent = nullptr;
    while(root->next){
        next = root->next;
        root->next = tail;
        tail = root;
        root = next;
        root->parent = nullptr;
    }

    root->next = tail;
    return root;
}

// delete the min key node
template <class T>
void BinomialHeap<T>::delete_min(){
    auto root = this->root_node;
    BinomialNode<T>* min_key;
    BinomialNode<T>* pre_min_key;
    find_min_key(min_key, pre_min_key);

    if(pre_min_key == nullptr){
        root = root->next;
    }
    else{
        pre_min_key->next = min_key->next;
    }
    
    auto child = reverse(min_key->child);
    root = merge(child, root);
    delete min_key;

    this->root_node = root;

}

// check if key is existing in the heap
template <class T>
BinomialNode<T>* BinomialHeap<T>::is_exist(BinomialNode<T>* root, T key){
    BinomialNode<T>* child;
    BinomialNode<T>* parent;

    parent = root;
    while (parent != nullptr){
        if(parent->key == key){
            return parent;
        }
        else{
            child = is_exist(parent->child, key);
            if(child != nullptr){
                return child;
            }
            parent = parent->next;
        }
    }

    return nullptr;
    
}

template <class T>
bool BinomialHeap<T>::is_exist(T key){
    auto t = is_exist(this->root_node, key);
    if(t != nullptr){
        return true;
    }
    else{
        return false;
    }
}

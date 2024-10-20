template <class T>
struct SkewNode;

template <class T>
struct SkewHeap{
    SkewNode<T>* root;

    T find_min(){
        return this->root->key;
    }

    void delete_min(){
        this->root = _delete_min(this->root);
    }

    void merge(SkewNode<T>* other){
        this->root = _merge(this->root, other);
    }

    void insert(T key){
        this->root = _insert(this->root, key);
    }

    SkewNode<T>* _merge(SkewNode<T>* x, SkewNode<T>* y){
        if(!x)  return y;
        if(!y)  return x;

        if(x->key > y->key){
            auto t = x; x = y;  y = t;
        }

        x->right_child = _merge(x->right_child, y);
        return x;
    }

    SkewNode<T>* _insert(SkewNode<T>* n, T key){
        SkewNode<T>* t = new SkewNode<T>(key);
        return _merge(n, t);
    }

    SkewNode<T>* _delete_min(SkewNode<T>* n){
        SkewNode<T>* ret = _merge(n->left_child, n->right_child);
        delete n;
        return ret;
    }
};

template <class T>
struct SkewNode{
    T key;
    SkewNode<T>* left_child;
    SkewNode<T>* right_child;

    SkewNode<T>(T key): key(key), left_child(nullptr), right_child(nullptr){};
};

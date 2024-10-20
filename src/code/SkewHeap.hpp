template <class T>
struct SkewNode;

template <class T>
struct SkewHeap {
    SkewNode<T>* root;

    SkewHeap(): root(nullptr) {}

    T find_min() {
        if (this->root == nullptr) {
            throw std::runtime_error("Heap is empty");
        }
        return this->root->key;
    }

    void delete_min() {
        if (this->root == nullptr) return;
        this->root = _delete_min(this->root);
    }

    void merge(SkewHeap<T>* other) {
        if (other == nullptr) return;
        this->root = _merge(this->root, other->root);
        other->root = nullptr;
    }

    void insert(T key) {
        this->root = _insert(this->root, key);
    }

private:
    SkewNode<T>* _merge(SkewNode<T>* x, SkewNode<T>* y) {
        if (!x) return y;
        if (!y) return x;

        if (x->key > y->key) {
            std::swap(x, y);
        }

        x->right_child = _merge(x->right_child, y);
        std::swap(x->left_child, x->right_child);

        return x;
    }

    SkewNode<T>* _insert(SkewNode<T>* n, T key) {
        SkewNode<T>* t = new SkewNode<T>(key);
        return _merge(n, t);
    }

    SkewNode<T>* _delete_min(SkewNode<T>* n) {
        SkewNode<T>* ret = _merge(n->left_child, n->right_child);
        delete n;
        return ret;
    }
};

template <class T>
struct SkewNode {
    T key;
    SkewNode<T>* left_child;
    SkewNode<T>* right_child;

    SkewNode(T key): key(key), left_child(nullptr), right_child(nullptr) {}
};

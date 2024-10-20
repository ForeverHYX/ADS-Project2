template <class T>
struct FibonacciHeap;

template <class T>
struct FibonacciNode;

template <class T>
struct FibonacciHeap{
    FibonacciNode<T>* heap;

    FibonacciHeap(): heap(nullptr) {}

    ~FibonacciHeap(){
        while(this->heap != nullptr){
            this->delete_min();
        }
    }

    void insert(T key){
        auto n = new FibonacciNode<T>(key);
        this->heap = _merge(this->heap, n);
    }

    T find_min(){
        if(this->heap == nullptr) 
            throw std::runtime_error("Heap is empty");
        return this->heap->key;
    }

    void delete_min(){
        FibonacciNode<T>* minNode = this->heap;
        if(minNode == nullptr) return;

        // 合并子节点到根列表
        this->heap = _delete_min(this->heap);
        delete minNode;  // 删除原来的最小节点
    }

    void decrease_key(FibonacciNode<T>* node, T value){
        this->heap = _decrease_key(this->heap, node, value);
    }

    void merge(FibonacciHeap<T>* other){
        this->heap = _merge(this->heap, other->heap);
        other->heap = nullptr;  // other 置空以避免重复使用
    }

    bool is_exist(T key){
        if(_is_exist(this->heap, key) == nullptr){
            return false;
        } else {
            return true;
        }
    }

    // private:
    FibonacciNode<T>* _merge(FibonacciNode<T>* p, FibonacciNode<T>* q){
        if(p == nullptr) return q;
        if(q == nullptr) return p;

        // 保证 p 是较小的根节点
        if(p->key > q->key){
            auto t = p; p = q; q = t;
        }

        // 连接 p 和 q 的根节点
        FibonacciNode<T>* nxt_p = p->next;
        FibonacciNode<T>* pre_q = q->prev;

        p->next = q;
        q->prev = p;
        nxt_p->prev = pre_q;
        pre_q->next = nxt_p;

        return p;
    }

    void _unmark_and_unparent_all(FibonacciNode<T>* node){
        if(node == nullptr) return;
        FibonacciNode<T>* c = node;
        do {
            c->marked = false;
            c->parent = nullptr;
            c = c->next;
        } while(c != node);
    }

    void _add_child(FibonacciNode<T>* parent, FibonacciNode<T>* child){
        child->prev = child->next = child;
        child->parent = parent;
        parent->degree++;

        if(parent->child == nullptr){
            parent->child = child;
        } else {
            parent->child = _merge(child, parent->child);
        }
    }

    FibonacciNode<T>* _delete_min(FibonacciNode<T>* node){
        _unmark_and_unparent_all(node->child);  // 将最小节点的孩子合并到根列表

        if(node->next == node){
            node = node->child;  // 如果只有一个根节点，直接返回孩子
        } else {
            // 从根链表中删除最小节点
            node->next->prev = node->prev;
            node->prev->next = node->next;

            // 合并子节点和根节点
            node = _merge(node->next, node->child);
        }

        if(node == nullptr) return node;  // 如果没有节点返回空

        // 准备合并同度数的树
        FibonacciNode<T>* trees[64] = {nullptr};
        while(true){
            if(trees[node->degree] != nullptr){
                FibonacciNode<T>* tree = trees[node->degree];

                if(tree == node){
                    break;
                }

                trees[node->degree] = nullptr;

                // 比较两个根节点的键值
                if(node->key < tree->key){
                    tree->prev->next = tree->next;
                    tree->next->prev = tree->prev;

                    _add_child(node, tree);
                } else {
                    tree->prev->next = tree->next;
                    tree->next->prev = tree->prev;

                    if(node->next == node){
                        tree->next = tree->prev = tree;
                        _add_child(tree, node);
                        node = tree;
                    } else {
                        node->next->prev = tree;
                        node->prev->next = tree;
                        tree->next = node->next;
                        tree->prev = node->prev;
                        _add_child(tree, node);
                        node = tree;
                    }
                }
                continue;
            } else {
                trees[node->degree] = node;
            }

            node = node->next;
        }

        // 找出新的最小根节点
        FibonacciNode<T>* min = node;
        FibonacciNode<T>* start = node;

        do {
            if(node->key < min->key){
                min = node;
            }
            node = node->next;
        } while(node != start);

        return min;
    }

    FibonacciNode<T>* _is_exist(FibonacciNode<T>* node, T key){
        FibonacciNode<T>* t = node;
        if(t == nullptr) return nullptr;
        do {
            if(t->key == key) return t;
            FibonacciNode<T>* ret = _is_exist(t->child, key);
            if(ret) return ret;
            t = t->next;
        } while(t != node);
        return nullptr;
    }

    FibonacciNode<T>* _cut(FibonacciNode<T>* heap, FibonacciNode<T>* node){
        if(node->next == node){
            node->parent->child = nullptr;
        }
        else{
            node->next->prev = node->prev;
            node->prev->next = node->next;

            node->parent->child = node->next;
        }

        node->next = node->prev = node;
        node->marked = false;

        return _merge(heap, node);
    }

    FibonacciNode<T>* _decrease_key(FibonacciNode<T>* heap, FibonacciNode<T>* node,T value){
        if(node->key < value){
            return heap;
        }

        node->key = value;
        if(node->parent != nullptr){
            if(node->key < node->parent->key){
                heap = _cut(heap, node);

                FibonacciNode<T>* parent = node->parent;
                node->parent = nullptr;

                while(parent != nullptr && parent->marked == true){
                    heap = _cut(heap, parent);

                    node = parent;
                    parent = node->parent;
                    node->parent = nullptr;
                }

                if(parent != nullptr && parent->parent != nullptr){
                    parent->marked = true;
                }
            }
        }
        else{
            if(node->key < heap->key){
                heap = node;
            }
        }

        return heap;
    }

};

template <class T>
struct FibonacciNode{
    T key;
    bool marked;
    int degree;
    FibonacciNode<T>* prev;
    FibonacciNode<T>* next;
    FibonacciNode<T>* child;
    FibonacciNode<T>* parent;

    FibonacciNode(T key): key(key), marked(false), degree(0), prev(this), next(this), child(nullptr), parent(nullptr) {}
};

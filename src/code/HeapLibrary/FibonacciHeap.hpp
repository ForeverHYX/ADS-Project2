#include <iostream>
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

    bool is_empty(){
        return heap == nullptr;
    }

    void insert(T key){
        auto n = new FibonacciNode<T>(key);
        this->heap = _merge(this->heap, n);
    }

    T find_min(){
        if(this->heap != nullptr)
            return this->heap->key;
    }

    FibonacciNode<T>* find_node(T key){
        return _find_node(heap, key);
    }

    void delete_min(){
        FibonacciNode<T>* minNode = this->heap;
        if(minNode == nullptr) return;

        this->heap = _delete_min(this->heap);
        delete minNode;
    }

    void decrease_key(FibonacciNode<T>* node, T value){
        this->heap = _decrease_key(this->heap, node, value);
    }

    void merge(FibonacciHeap<T>* other){
        this->heap = _merge(this->heap, other->heap);
        other->heap = nullptr;
    }

    bool is_exist(T key){
        if(_is_exist(this->heap, key) == nullptr){
            return false;
        } else {
            return true;
        }
    }

    // private:

    // Due to the disorder of the root linked list of the Fibonacci heap, the merge operation is relatively simple, which is to merge two circular linked lists. It is worth noting that the node pointer returned by the merge operation should be smaller.
    FibonacciNode<T>* _merge(FibonacciNode<T>* p, FibonacciNode<T>* q){
        if(p == nullptr) return q;
        if(q == nullptr) return p;

        if(p->key > q->key){
            auto t = p; p = q; q = t;
        }

        FibonacciNode<T>* nxt_p = p->next;
        FibonacciNode<T>* pre_q = q->prev;

        p->next = q;
        q->prev = p;
        nxt_p->prev = pre_q;
        pre_q->next = nxt_p;

        return p;
    }

    FibonacciNode<T>* _find_node(FibonacciNode<T>* node, T key){
        if(node == nullptr){
            return nullptr;
        }
        FibonacciNode<T>* c = node;
        do{
            if(c->key == key){
                return c;
            }
            FibonacciNode<T>* t = _find_node(c->child, key);
            if(t != nullptr){
                return t;
            }
            c = c->next;
        }while(c != node);
        return nullptr;
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

    // First, unmark and unparent all child nodes of the node to be deleted to cut off the connection with the node to be deleted;

    // Then, delete the node to be deleted and connect the child node list of the node to be deleted

    // Then merge all trees with the same degree. The idea of ​​bucket row is used in the implementation, and the maximum degree is preset to 64. Traverse the linked list after connecting the child node linked list. If the degree corresponding to the linked list does not exist in the bucket, insert it; otherwise, merge (exit when merging to the same node, indicating that there is no tree with the same degree)

    // Give details for the merge operation: if the node to be merged is smaller, the node to be merged is regarded as the child of the node to be merged; otherwise, the node to be merged is regarded as the child of the node to be merged, and then the synthesized node is placed

    FibonacciNode<T>* _delete_min(FibonacciNode<T>* node){
        _unmark_and_unparent_all(node->child);

        if(node->next == node){
            node = node->child;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;

            node = _merge(node->next, node->child);
        }

        if(node == nullptr) return node; 

        FibonacciNode<T>* trees[64] = {nullptr};
        while(true){
            if(trees[node->degree] != nullptr){
                FibonacciNode<T>* tree = trees[node->degree];

                if(tree == node){
                    break;
                }

                trees[node->degree] = nullptr;

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

    // simple DFS
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

    // Cut off the node and all its child nodes and merge them into the root of the original heap
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

    // Mainly explain the situation of reducing non-root nodes:

    // If the modification destroys the properties of the heap, that is, `node->key < node->parent->key`, cut off the node and its child nodes and merge them into the root heap; then recursively repeat the operation upward until the root node or the node whose first child has been deleted is encountered

    // After the recursive operation is completed, if it stays below the root node, mark the first child of this root node as deleted
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
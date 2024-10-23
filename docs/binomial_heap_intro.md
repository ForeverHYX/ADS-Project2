### 二项堆

二项堆是**二项树**的集合，和堆类似，支持对最小元素进行查询，删除和更改的操作

#### 二项树的定义

二项树是递归定义的有序树，度为 k 的二项树 B~k~ 的定义如下

1. B~0~ 为仅有一个根结点的树
2. B~k~ 由两个 B~k-1~ 组成，其中一棵树是另一棵树的子树

#### 二项堆的定义

二项堆为满足以下条件的二项树的集合

1. 每棵树的均满足堆的性质，即父节点**不大于**子节点
2. **不**存在两棵二项树拥有相同的度，即度为 k 的二项树只有 0 或 1 个
3. 在实现时，二项树按照度数递增的顺序排列

下面是接口定义

```c++
template <class T>
struct BinomialNode{
    T key;
    int degree;
    BinomialNode<T>* child;
    BinomialNode<T>* parent;
    BinomialNode<T>* next;

    BinomialNode(T key):key(key), degree(0), child(nullptr), parent(nullptr), next(nullptr){};
};

template <class T>
struct BinomialHeap{
    BinomialNode<T>* root_node;

    void insert(T key);
    int find_min();
    void delete_min();
    void merge(BinomialHeap* other);

    BinomialNode<T>* merge_root(BinomialNode<T>* p, BinomialNode<T>* q);
    void link(BinomialNode<T>* root, BinomialNode<T>* child);
    BinomialNode<T>* merge(BinomialNode<T>* p, BinomialNode<T>* q);
    void find_min_key(BinomialNode<T>* &min_key, BinomialNode<T>* &pre_min_key);
    BinomialNode<T>* reverse(BinomialNode<T>* root);
    BinomialNode<T>* is_exist(BinomialNode<T>* root, T key);
    bool is_exist(T key);
};
```

BinomialNode 类包括了关键字 key，度 degree，孩子节点 child，父节点 parent 和兄弟节点 next 5 个成员变量

BinomialHeap 类是对 BinomialNode 类的封装，同时也包括了 project 中需要的一些操作

#### 合并

二项堆堆合并可以分为以下两步

1. 合并 p，q 的 root_node
2. 对 root_node 中重复度数的二项树进行连接，注意度数为 j 的二项树合并后度数为 j + 1，可能会和已经出现过的二项树度数重复，需要多次连接

在我们的二项堆中，我们要维护 root_node 的有序性（按照 degree 的值递增），merge_root 函数实现对两个堆对 root_node 进行合并，并保持其有序性

```c++
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
```

link 函数实现将 child 连接至 root

```c++
// link child node to root node as child
template <class T>
void BinomialHeap<T>::link(BinomialNode<T>* root, BinomialNode<T>* child){
    child->parent = root;
    child->next = root->child;
    root->child = child;
    root->degree += 1;
}
```

merge 函数可以实现两个堆的合并，也可以实现一个堆向另一个的合并

merge 函数主要处理合并过程的步骤 2，也就是对度数相同的二项树的合并过程

由于我们维护了 root_node 的有序性，因此其度数排列只可能是以下情况：{0, 0, 2, 3, 3, 4, 4, 5...}

通过 cur，pre 和 nxt 指针分情况进行处理

1. cur->degree != nxt->degree

    即当前度数和下一个度数不相同，无需操作

2. cur->degree == nxt->degree && nxt->next->degree == nxt->degree

    即当前，下一个，下下一个度数均相同，这种情况是可能出现的，以上面的排列为例，合并 (3, 3) 后，排列会变为 {1, 2, 4, 4, 4, 5...}，此时如果贸然操作前面的 (4, 4)，会导致局部出现 {5, 4, 5} 的排列，不利于处理

    因此跳过这次处理，改为处理后面的 (4, 4)，使得局部变为 {4, 5, 5}

3. cur->degree == nxt->degree && nxt->next->degree != nxt->degree

    即仅有当前和下一个节点的度数相同，此时根据两个节点的根关键字大小进行连接即可

```c++
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
```

#### 插入

插入操作可以看作是合并上一个只有一个节点的二项堆

```c++
// insert a node with key into this heap
template <class T>
void BinomialHeap<T>::insert(T key){
    auto new_node = new BinomialNode<T>(key);
    if(new_node != nullptr){
        this->root_node = merge(this->root_node, new_node);
    }
    return;
}
```

#### 查找

为了方便之后的删除操作，先实现一个 find_min_key 的函数，支持查询最小节点和其先导节点，也没有什么复杂的，遍历即可

```c++
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
```

find_min 函数

```c++
// return the minimum key value of this heap
template <class T>
int BinomialHeap<T>::find_min(){
    BinomialNode<T>* min_key;
    BinomialNode<T>* pre_min_key;
    find_min_key(this->root_node, min_key, pre_min_key);

    if(min_key == nullptr){
        return -1;
    }
    else{
        return min_key->key;
    }
}
```

#### 删除

删除操作可以理解为先找到被删除节点，然后将被删除节点的子树集合与去除掉被删除节点的原二项堆进行合并

为了方便删除函数的实现，先定义 reverse 函数，支持对二项堆的子树进行翻转

> 之所以需要这个 reverse 函数，原因是在二项堆里面，是按照度数递增储存的，但是在二项树里面，靠左子树的度数反而大于靠右子树，所以需要对其进行翻转，以得到两个都是递增排列的二项堆

翻转就是链表翻转，那个查重率 100% 的题目哦

```c++
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
```

删除函数

```c++
// delete the min key node
template <class T>
void BinomialHeap<T>::delete_min(){
    auto root = this->root_node;
    BinomialNode<T>* min_key;
    BinomialNode<T>* pre_min_key;
    find_min_key(this->root_node, min_key, pre_min_key);

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
```

#### 查询

查询节点是否存在

```c++
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
```

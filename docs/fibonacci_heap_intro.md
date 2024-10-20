### Fibonacci 堆

> 建议先通读 binomial_heap_intro.md

Fibonacci 堆是树的集合，和堆类似，支持对最小元素进行查询，删除和更改的操作

#### Fibonacci 堆的定义

Fibonacci 堆由一组最小堆组成，与二项堆不同，组成 Fibonacci 堆的树不一定是二项树，也不一定按照度数有序排列

接口定义与二项堆类似，不再赘述，主要解释增删操作的原理

下面是 Fibonacci 堆节点的定义

```c++
template <class T>
struct FibonacciHeap{
    FibonacciNode<T>* heap;
}

template <class T>
struct FibonacciNode{
    T key;
    bool marked;
    int degree;
    FibonacciNode<T>* prev;
    FibonacciNode<T>* next;
    FibonacciNode<T>* child;
    FibonacciNode<T>* parent;
};
```

由此可见，Fibonacci 堆的每棵树的每一层都是一个双向循环链表，Fibonacci 堆实际上就是指向所有树的根组成的双向循环链表的指针

其中 marked 是一个特殊的布尔值，标志第一个孩子是否被删除

> 和一些算法书上的实现不一样，本实现没有额外储存一个 min 指针，以维护其指向最小值，而是在进行合并操作的时候通过~特殊魔法~操作，使得头指针指向的就是最小值

#### 合并

由于 Fibonacci 堆根链表的无序性，合并操作相对简单，就是对两个循环链表进行合并，值得注意的是，合并操作返回的节点指针应当是较小的

#### 插入

插入操作和二项堆类似，相当于合并上一个仅有一个节点的 Fibonacci 堆

#### 查找

查找最小值，即遍历根链表，很简单

#### 删除

> 大的要来了

按照定义，删除操作涉及两步

1. 将待删除节点的子树连接到根链表
2. 合并所有度数相同的树

根据代码实现，解释一下实现到底干了什么

首先，对待删除节点的所有子节点进行 unmark 和 unparent 操作，断绝和待删除节点的联系；

然后，删除待删除节点，同时将待删除节点的子节点链表接入

接着是合并所有度数相同的树，在实现中利用了桶排的思想，预设度数最大为 64。遍历接入子节点链表后的链表，如果链表对应的度数不存在于桶中，则置入；否则进行合并（合并到相同节点时退出，说明已经没有度数相同的树了）

对于合并操作给出细节：假如待合入节点更小，则将被合入节点作为待合入节点的孩子；否则，先将被合入节点作为待合入节点的孩子，再将合成的节点置入

#### 查询

深搜

#### 减少

为了实现减少某个节点的值的操作，需要先定义一个剪切操作，即将该节点及其子节点全部剪下来，并入到原堆的根里面，在代码中实现如下

```c++
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
```

当某个节点的值减少后，从这个节点开始向上，可能就不符合堆的性质了，需要对其进行维护，具体维护方式的代码实现如下

```c++
FibonacciNode<T>* _decrease_key(FibonacciNode<T>* nodeheap, FibonacciNode<T>* node,T value){
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
```

主要解释减少非根节点的情况：

假如修改后破坏了堆的性质，即 `node->key < node->parent->key`，则剪下该节点及其子节点，并入根堆；然后向上递归地重复操作，直到遇到根节点或第一个孩子已经被删除的节点

递归操作完毕后，假如停留在了根节点以下，标记这个根节点的第一个孩子被删除
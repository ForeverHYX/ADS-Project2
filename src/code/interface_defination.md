To any heap class there, using the interface defination

take binomial heap class for example, all heap class support following interface

1. biuld an empty heap

```C++
auto binomial_heap = new BinomialHeap;
```

2. insert an elememt

```C++
int key;
binomial_heap.insert(key);
```

3. find the pointer to the node storing the min elememt

```C++
auto t =  binomial_heap.find_min();
```

4. delete the node storing the min elememt

```C++
binomial_heap.delete_min();
```

<<<<<<< HEAD
5. merge two heap, h2 will be merged to h1

```C++
merge(h1, h2)
```
=======
5. merge two heap

```C++
auto new_binomial_heap = merge_binomial_heap(binomial_heap_1, binomial_heap_2);
```
>>>>>>> 39056e3fc99c26c5c68323c62f8917a4216cf109

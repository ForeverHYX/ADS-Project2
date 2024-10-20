To any heap class there, using the interface defination

take binomial heap class for example, all heap class support following interface

1. biuld an empty heap

```C++
auto binomial_heap = new BinomialHeap<T>;
```

2. insert an elememt

```C++
T key;
binomial_heap<T>.insert(key);
```

3. find the pointer to the node storing the min elememt

```C++
auto t =  binomial_heap<T>.find_min();
```

4. delete the node storing the min elememt

```C++
binomial_heap<T>.delete_min();
```

5. check out if a key is existing

```C++
bool is_exist = binomial_heap<T>.is_exist(key);
```

6. decrease key

```C++
auto t =  binomial_heap<T>.find_min();
T* new_node = new T();
binomial_heap<T>.decrease_key(t, new_node);
```
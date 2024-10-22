#include <queue>
#include <vector>

<<<<<<< HEAD
=======
struct node { // 确保比较器可以使用 node 结构体
    long int dis;
    long int pos;

    // 比较运算符，确保可以与 node 比较
    bool operator >(const node &other) const {
        return dis > other.dis; // 对于最小堆，使用 dis > other.dis
    }
};

>>>>>>> 460a2c1f3ac1e2c03ec0d780eb3197dd5e69ccf5
template <class T>
struct cmp {
    bool operator()(const T& x, const T& y) const {
        return x > y; // 使用重载的 > 运算符进行比较
    }
    bool operator()( T& x,  T& y) const {
        return x > y; // 使用重载的 > 运算符进行比较
    }
};

template <class T>
struct Heap {
    std::priority_queue<T, std::vector<T>, cmp<T> > heap; // 注意这里的空格

    void insert(T key) {
        heap.push(key);
    }

    bool is_empty(){
        return heap.empty();
    }

    T find_min() {
        return heap.top();
    }

    void delete_min() {
        heap.pop();
    }

    bool is_exist(T key) {
        std::vector<T> t = heap.__get_container();
        for (typename std::vector<T>::iterator i = t.begin(); i != t.end(); ++i) {
            if (*i == key) {
                return true;
            }
        }
        return false;
    }
};

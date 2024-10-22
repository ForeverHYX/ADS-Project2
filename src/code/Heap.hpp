#include <queue>
#include <vector>

struct node {
    int dis;
    int pos;

    bool operator >(const node &other) const {
        return dis > other.dis;
    }
};

template <class T>
struct cmp {
    bool operator()(const T& x, const T& y) const {
        return x > y;
    }
};

template <class T>
struct Heap {
    std::priority_queue<T, std::vector<T>, cmp<T> > heap;

    void insert(T key) {
        heap.push(key);
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

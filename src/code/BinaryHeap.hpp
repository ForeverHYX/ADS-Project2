#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include <vector>

template <class T>
struct BinaryHeap {
    std::vector<T> heap;

    BinaryHeap() {
        heap.clear();
    }

    void insert(T key) {
        heap.push_back(key);
        _up_shift();
    }

    T find_min() {
        if (heap.empty()) {
            return T(); // 返回默认值
        }
        return heap[0];
    }

    void delete_min() {
        if (heap.empty()) {
            return; // 堆为空直接返回
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            _down_shift();
        }
    }

    void decreaseKey(size_t index, T new_val) {
        if (index >= heap.size() || new_val > heap[index]) {
            return;
        }
        heap[index] = new_val;
        _up_shift_from_index(index);
    }

private:
    void _up_shift() {
        size_t child = heap.size() - 1;
        size_t parent = (child - 1) / 2;

        T tmp = heap[child];

        while (child > 0) {
            if (heap[parent] <= tmp) {
                break;
            }
            heap[child] = heap[parent];
            child = parent;
            parent = (child - 1) / 2;
        }

        heap[child] = tmp;
    }

    void _down_shift() {
        size_t parent = 0;
        size_t left = 2 * parent + 1;
        size_t end = heap.size() - 1;

        T tmp = heap[parent];

        while (left <= end) {
            size_t right = left + 1;
            if (right <= end && heap[left] > heap[right]) {
                left = right;
            }

            if (tmp <= heap[left]) {
                break;
            }

            heap[parent] = heap[left];
            parent = left;
            left = 2 * parent + 1;
        }

        heap[parent] = tmp;
    }

    void _up_shift_from_index(size_t index) {
        size_t child = index;
        size_t parent = (child - 1) / 2;

        T tmp = heap[child];

        while (child > 0) {
            if (heap[parent] <= tmp) {
                break;
            }
            heap[child] = heap[parent];
            child = parent;
            parent = (child - 1) / 2;
        }

        heap[child] = tmp;
    }
};

#endif
